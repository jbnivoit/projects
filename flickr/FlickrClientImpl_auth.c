#include "FlickrClientImpl.h"
#include "FlickrXmlHandler.h"

#include <string.h>

typedef struct getFrobArg getFrobArg;
struct getFrobArg {
  XML_Parser m_parser;
  String *m_frob;
};

static void getFrob_CharacterDataHandler (void *userData,
				      const XML_Char *s,
				      int len)
{
  getFrobArg *args = (getFrobArg*)userData;
  String_Append(args->m_frob,s,len);
}

static size_t writeToGetFrobParser(void *source, size_t sz, size_t nmemb, void *userData)
{
  getFrobArg *args = (getFrobArg*)userData;
/*    printf("%s",(char*)source);  */
  XML_Parse(args->m_parser,source,sz*nmemb,0);
  return sz*nmemb;
}

FlickrResult flickr_auth_getFrob(FlickrClient *client, String *oFrob)
{
  getFrobArg arg;
  unsigned char dummy=0;

  arg.m_parser = XML_ParserCreate(NULL);
  arg.m_frob = oFrob;
  XML_SetUserData(arg.m_parser, &arg);

  XML_SetCharacterDataHandler(arg.m_parser,getFrob_CharacterDataHandler);
  
  flickr_request(client, "flickr.auth.getFrob",
		 &arg, &writeToGetFrobParser,
		 NULL,0);
  
  XML_Parse(arg.m_parser,&dummy,0,1);
  XML_ParserFree(arg.m_parser);
  String_TrimWhitespace(oFrob);
  return 0;
}

typedef enum {
  PARSING_UNKNOWN=0,
  PARSING_TOKEN,
  PARSING_PERMS,
  PARSING_USER
} checkTokenParsing;

typedef struct checkTokenArg checkTokenArg;
struct checkTokenArg {
  rspParser m_super;
  checkTokenParsing m_parsing_state;

  String m_token;
  String m_perms;
  FlickrUser m_user;
};

static void checkToken_EndElementHandler(void *userData,
					 const XML_Char *name)
{
  checkTokenArg *rp = (checkTokenArg*)userData;
  rp->m_parsing_state=PARSING_UNKNOWN;
}

static void checkToken_StartElementHandler(void *userData,
					 const XML_Char *name,
					 const XML_Char **atts)
{
  checkTokenArg *rp = (checkTokenArg*)userData;

  if(strcmp(name,"token")==0) {
    rp->m_parsing_state=PARSING_TOKEN;
  } else if(strcmp(name,"perms")==0) {
    rp->m_parsing_state=PARSING_PERMS;
  } else if(strcmp(name,"user")==0) {
    rp->m_parsing_state=PARSING_USER;

      matchXmlAttr matches[] = {
	{ "nsid",     XML_STRING, { &rp->m_user.m_nsid } },
	{ "username", XML_STRING, { &rp->m_user.m_username } }, 
	{ "fullname", XML_STRING, { &rp->m_user.m_fullname } }, 
      };
      extractAttrValues(matches,atts);
  }
}

static void checkToken_CharacterDataHandler (void *userData,
				      const XML_Char *s,
				      int len)
{
  checkTokenArg *rp = (checkTokenArg*)userData;
  switch(rp->m_parsing_state) {
  case PARSING_TOKEN:
    String_Append(&rp->m_token,s,len);
    break;
  case PARSING_PERMS:
    String_Append(&rp->m_perms,s,len);
    break;
  default:;
  }
}

static FlickrResult flickr_auth_request(FlickrClient *client,
					const char *method,
					const FlickrRequestArg reqarg[],
					unsigned int reqsz,
					void *userData,
					void (*cb)(void *userData, const String *token, 
						   FlickrPerm perm, const FlickrUser *user)) {
  checkTokenArg p;

  String_Init(&p.m_token);
  FlickrUser_Init(&p.m_user);
  memset(&p,0,sizeof(checkTokenArg));

  rsp_ParserCreate(&p.m_super);
  rsp_SetElementHandler(&p.m_super,checkToken_StartElementHandler,checkToken_EndElementHandler);
  rsp_SetCharacterDataHandler(&p.m_super, &checkToken_CharacterDataHandler);
  
  flickr_request(client, method,
		 p.m_super.m_parser, &writeToParser,
		 reqarg, reqsz);
  
  rsp_ParserFree(&p.m_super);

  {
    FlickrPerm perm=permFromString(&p.m_perms);
    String_TrimWhitespace(&p.m_token);
    (*cb)(userData, &p.m_token, perm, &p.m_user);
  }

  String_Destroy(&p.m_token);
  FlickrUser_Destroy(&p.m_user);
  return p.m_super.m_code;
}

FlickrResult flickr_auth_checkToken(FlickrClient *client,
				    const FlickrAuthToken *auth_token,
				    void *userData,
				    void (*cb)(void *userData, const String *token, 
					       FlickrPerm perm, const FlickrUser *user)) {
  const FlickrRequestArg reqarg[] = {
    { "auth_token", auth_token->m_start },
  };
  return flickr_auth_request(client,"flickr.auth.checkToken",
			     reqarg, sizeof(reqarg)/sizeof(reqarg[0]),
			     userData,cb);
}

FlickrResult flickr_auth_getFullToken(FlickrClient *client,
				      const FlickrMiniToken mini_token,
				      void *userData,
				      void (*cb)(void *userData, const String *token, 
						 FlickrPerm perm, const FlickrUser *user))
{
  const FlickrRequestArg reqarg[] = {
    { "mini_token", mini_token },
  };
  return flickr_auth_request(client,"flickr.auth.getFullToken",
			     reqarg, sizeof(reqarg)/sizeof(reqarg[0]),
			     userData,cb);
}

FlickrResult flickr_auth_getToken(FlickrClient *client,
				  const String *frob,
				  void *userData,
				  void (*cb)(void *userData, const String *token, 
					     FlickrPerm perm, const FlickrUser *user))
{
  const FlickrRequestArg reqarg[] = {
    { "frob", frob->m_start },
  };
  return flickr_auth_request(client,"flickr.auth.getToken",
			     reqarg, sizeof(reqarg)/sizeof(reqarg[0]),
			     userData,cb);
}

static void sign_auth_args(FlickrClient *client, 
			   const String *frob,
			   const char *perms,
			   char sig[32])
{
  String sb;
  const FlickrRequestArg args[] = {
    { "api_key", client->m_apiKey },
    { "frob",    frob->m_start },
    { "perms",   perms }
  };
  
  String_InitWithString(&sb,client->m_secret,FLICKR_SECRET_LEN);

  {
    unsigned int i=0;
    const unsigned int argsz = sizeof(args)/sizeof(args[0]);

    for(;i<argsz;i++) {
      String_Append(&sb, args[i].m_arg, strlen(args[i].m_arg));
      String_Append(&sb, args[i].m_value, strlen(args[i].m_value));
    }
    
    extern void sign(String *sb, char sig[32]);
    sign(&sb,sig);
  }
}

#define APPEND(x,y) String_Append(x,y,strlen(y))
void flickr_auth_url(FlickrClient *client, String *iFrob, FlickrPerm iPerm, String *oUrl) {
  char sig[33];
  const char *p = perm(iPerm);

  memset(sig,0,sizeof(sig));
  String_Reinit(oUrl);
  String_Append(oUrl,flickr_AUTH_URI,strlen(flickr_AUTH_URI));
  String_Append(oUrl,"?",1);
  APPEND(oUrl,"api_key=");
  APPEND(oUrl,client->m_apiKey);
  APPEND(oUrl,"&perms=");
  APPEND(oUrl,p);
  APPEND(oUrl,"&frob=");
  String_AppendOther(oUrl,iFrob);
  APPEND(oUrl,"&api_sig=");

  sign_auth_args(client, 
		 iFrob,p,sig);
  APPEND(oUrl,sig);
}

void flickr_set_authentication_token(FlickrClient *client, const String *token)
{
  client->m_auth_token_set=1;
  String_InitWithOther(&client->m_auth_token,token);
}
