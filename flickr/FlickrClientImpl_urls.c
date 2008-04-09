#include "FlickrClientImpl.h"

#include <string.h>

typedef struct getGroupArg getGroupArg;
struct getGroupArg {
  rspParser m_super;
  String *m_url;
};

static void getGroup_StartElementHandler(void *userData,
					 const XML_Char *name,
					 const XML_Char **atts)
{
  getGroupArg *rp = (getGroupArg*)userData;

  if(strcmp(name,"group")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"url")==0 ) {
	atts++;
	String_InitWithString(rp->m_url,*atts,strlen(*atts));
	break;
      } 
      atts++;
    }
  }
}

FlickrResult flickr_urls_getGroup(FlickrClient *client,
				  const FlickrGroupId *group_id,
				  String *url)
{
  getGroupArg p;
  const FlickrRequestArg reqarg[] = {
    { "group_id",       group_id->m_start       },
  };
  p.m_url = url;

  rsp_ParserCreate(&p.m_super);
  rsp_SetElementHandler(&p.m_super,getGroup_StartElementHandler,noop_EndElementHandler);
  
  flickr_request_rsp(client, "flickr.urls.getGroup",
		     p.m_super,
		     reqarg);

  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}

static FlickrResult flickr_urls_getUrl(FlickrClient *client,
				       const char *method,
				       const String *user_id,
				       String *url)
{
  getGroupArg p;
  const FlickrRequestArg reqarg[] = {
    { "user_id", user_id->m_start },
  };
  p.m_url = url;

  rsp_ParserCreate(&p.m_super);
  rsp_SetElementHandler(&p.m_super,getGroup_StartElementHandler,noop_EndElementHandler);
  
  flickr_request_rsp(client, method,
		     p.m_super,
		     reqarg);

  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}

FlickrResult flickr_urls_getUserPhotos(FlickrClient *client,
				       const String *user_id,
				       String *url)
{
  return flickr_urls_getUrl(client,"flickr.urls.getUserPhotos",user_id,url);
}

FlickrResult flickr_urls_getUserProfile(FlickrClient *client,
					const String *user_id,
					String *url)
{
  return flickr_urls_getUrl(client,"flickr.urls.getUserProfile",user_id,url);
}

typedef struct lookupGroupArg lookupGroupArg;
struct lookupGroupArg {
  rspParser m_super;
  unsigned char m_parsing_groupname;
  String *m_id, *m_name;
};


static void lookupGroup_StartElementHandler(void *userData,
					 const XML_Char *name,
					 const XML_Char **atts)
{
  lookupGroupArg *rp = (lookupGroupArg*)userData;

  if(strcmp(name,"groupname")==0) {
    rp->m_parsing_groupname=1;
  }

  if(strcmp(name,"group")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"id")==0 ) {
	atts++;
	String_InitWithString(rp->m_id,*atts,strlen(*atts));
	break;
      } 
      atts++;
    }
  }
}

static void lookupGroup_CharacterDataHandler (void *userData,
				      const XML_Char *s,
				      int len)
{
  lookupGroupArg *rp = (lookupGroupArg*)userData;
  if(rp->m_parsing_groupname==0) return;

  String_Append(rp->m_name,s,len);
}

static FlickrResult flickr_urls_lookup(FlickrClient *client, const char *method,
				     const String *url,
				     String *id, String *name)
{
  lookupGroupArg p;
  const FlickrRequestArg reqarg[] = {
    { "url", url->m_start },
  };
  memset(&p,0,sizeof(lookupGroupArg));
  p.m_id = id;
  p.m_name = name;

  rsp_ParserCreate(&p.m_super);
  rsp_SetElementHandler(&p.m_super,lookupGroup_StartElementHandler,noop_EndElementHandler);
  rsp_SetCharacterDataHandler(&p.m_super, &lookupGroup_CharacterDataHandler);
  
  flickr_request_rsp(client, method,
		     p.m_super,
		     reqarg);
  
  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}

FlickrResult flickr_urls_lookupGroup(FlickrClient *client,
				     const String *url,
				     String *id, String *name) {
  return flickr_urls_lookup(client,"flickr.urls.lookupGroup",
			    url,id, name);
}

FlickrResult flickr_urls_lookupUser(FlickrClient *client,
				    const String *url,
				    String *id, String *name) {
  return flickr_urls_lookup(client,"flickr.urls.lookupUser",
			    url,id, name);
}
