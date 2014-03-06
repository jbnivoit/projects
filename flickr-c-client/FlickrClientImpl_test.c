/* -*- C -*- */
#include "FlickrClientImpl.h"

#include <string.h>
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

FlickrResult flickr_test_echo(FlickrClient *client, const FlickrRequestArg args[], const unsigned int argsz)
{
  const char *method = "flickr.test.echo";
  void *userData=NULL;
  flickr_request(client,method,userData,printReplyCb,args,argsz);
  return 0;
}

typedef struct loginArg loginArg;
struct loginArg {
  rspParser m_super;
  String *m_id;
  String *m_username;
  unsigned char m_parsing_username;
};

static void loginArg_Init(loginArg *p,
			  String *id,
			  String *username)
{
  memset(p,0,sizeof(loginArg));
  p->m_id=id;
  p->m_username=username;
}

static void login_CharacterDataHandler (void *userData,
						  const XML_Char *s,
						  int len)
{
  loginArg *rp = (loginArg*)userData;
  if(rp->m_parsing_username==0) return;

  String_Append(rp->m_username,s,len);
}

static void login_StartElementHandler(void *userData,
						const XML_Char *name,
						const XML_Char **atts)
{
  loginArg *rp = (loginArg*)userData;

  if(strcmp(name,"user")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"id")==0 ) {
	atts++;
	String_InitWithString(rp->m_id,*atts,strlen(*atts));
	break;
      }
      atts++;
    }
  }

  else if(strcmp(name,"username")==0) {
    rp->m_parsing_username=1;
  }
}

FlickrResult flickr_test_login(FlickrClient *client, String *id, String *username)
{
  loginArg p;
  loginArg_Init(&p,id,username);

  rsp_ParserCreate(&p.m_super);
  rsp_SetElementHandler(&p.m_super,login_StartElementHandler,noop_EndElementHandler);
  rsp_SetCharacterDataHandler(&p.m_super,
			      &login_CharacterDataHandler);

  flickr_request(client, "flickr.test.login",
		 p.m_super.m_parser, &writeToParser,
		 NULL,0);
  
  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
  /* FIXME requires authentication with read permission */
}
