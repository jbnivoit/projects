#include "FlickrClientImpl.h"

#include <string.h>

typedef struct getListPhotoArg getListPhotoArg;
struct getListPhotoArg {
  XML_Parser m_parser;
  void *m_userData;
  void (*m_cb)(void *userData, FlickrTag *tag);
  FlickrTag m_tag;
  unsigned char m_parsing_tag;
};

static void getListPhoto_StartElementHandler(void *userData,
					   const XML_Char *name,
					   const XML_Char **atts)
{
  getListPhotoArg *rp = (getListPhotoArg*)userData;

  if(strcmp(name,"tag")!=0) {
    return;
  }
  rp->m_parsing_tag=1;
  
  FlickrTag_Init(&rp->m_tag);

  while(*atts!=NULL) {
    if( strcmp(*atts,"id")==0 ) {
      atts++;
      rp->m_tag.m_id = atoi(*atts);
    } else if( strcmp(*atts,"author")==0 ) {
      atts++;
      String_InitWithString(&rp->m_tag.m_author,*atts,strlen(*atts));
    } else if( strcmp(*atts,"authorname")==0 ) {
      atts++;
      String_InitWithString(&rp->m_tag.m_authorname,*atts,strlen(*atts));
    } else if( strcmp(*atts,"raw")==0 ) {
      atts++;
      String_InitWithString(&rp->m_tag.m_raw,*atts,strlen(*atts));
    }
    atts++;
  }
}

static void getListPhoto_EndElementHandler(void *userData, const XML_Char *name)
{
  if(strcmp(name,"tag")==0) {
    getListPhotoArg *args = (getListPhotoArg*)userData;
    args->m_parsing_tag=0;

    (args->m_cb)(args->m_userData,&args->m_tag);
    FlickrTag_Destroy(&args->m_tag);
  }
}

static void getListPhoto_CharacterDataHandler (void *userData,
				      const XML_Char *s,
				      int len)
{
  getListPhotoArg *args = (getListPhotoArg*)userData;
  if(args->m_parsing_tag==0) return;

  String_Append(&args->m_tag.m_tagbody,s,len);
}

static size_t writeToGetListPhotoParser(void *source, size_t sz, size_t nmemb, void *userData)
{
  getListPhotoArg *args = (getListPhotoArg*)userData;
  XML_Parse(args->m_parser,source,sz*nmemb,0);
  return sz*nmemb;
}

FlickrResult flickr_tags_getListPhoto(FlickrClient *client, 
				      FlickrPhotoId *photo_id,
				      void *userData, 
				      void (*cb)(void *userData, FlickrTag *tag))
{
    const FlickrRequestArg reqarg[] = {
      { "photo_id", photo_id->m_start },
    };
    unsigned char dummy=0;
    getListPhotoArg arg;

    memset(&arg,0,sizeof(getListPhotoArg));
    arg.m_userData = userData;
    arg.m_cb = cb;

    arg.m_parser = XML_ParserCreate(NULL);
    XML_SetUserData(arg.m_parser, &arg);

    XML_SetElementHandler(arg.m_parser,getListPhoto_StartElementHandler,getListPhoto_EndElementHandler);
    XML_SetCharacterDataHandler(arg.m_parser,getListPhoto_CharacterDataHandler);
    
    flickr_request(client, "flickr.tags.getListPhoto",
		   &arg, &writeToGetListPhotoParser,
		   reqarg, sizeof(reqarg)/sizeof(reqarg[0]));
  
    XML_Parse(arg.m_parser,&dummy,0,1);
    XML_ParserFree(arg.m_parser);
    return 0;
}

typedef struct getListUserArg getListUserArg;
struct getListUserArg {
  XML_Parser m_parser;
  void *m_userData;
  void (*m_cb)(void *userData, String *tag);
  String m_tag;
  unsigned int m_count;
  unsigned char m_parsing_tag;
};

static void getListUser_StartElementHandler(void *userData,
					   const XML_Char *name,
					   const XML_Char **atts)
{
  getListUserArg *rp = (getListUserArg*)userData;
  if(strcmp(name,"tag")==0) {
    rp->m_parsing_tag=1;
    String_Init(&rp->m_tag);
  }

  while(*atts!=NULL) {
    if( strcmp(*atts,"count")==0 ) {
      atts++;
      rp->m_count = atoi(*atts);
      break;
    }
    atts++;
  }
}

static void getListUser_EndElementHandler(void *userData, const XML_Char *name)
{
  if(strcmp(name,"tag")==0) {
    getListUserArg *args = (getListUserArg*)userData;
    args->m_parsing_tag=0;
    
    (args->m_cb)(args->m_userData,&args->m_tag);
    String_Destroy(&args->m_tag);
  }
}

static void getListUser_CharacterDataHandler (void *userData,
				      const XML_Char *s,
				      int len)
{
  getListUserArg *args = (getListUserArg*)userData;
  if(args->m_parsing_tag==0) return;

  String_Append(&args->m_tag,s,len);
}

static size_t writeToGetListUserParser(void *source, size_t sz, size_t nmemb, void *userData)
{
  getListUserArg *args = (getListUserArg*)userData;
  XML_Parse(args->m_parser,source,sz*nmemb,0);
  return sz*nmemb;
}

FlickrResult flickr_tags_getListUser(FlickrClient *client,
				     String *user_id,
				     void *userData,
				     void (*cb)(void *userData, String *tag))
{
    const FlickrRequestArg reqarg[] = {
      { "user_id", user_id->m_start },
    };
    unsigned char dummy=0;
    getListUserArg arg = { NULL, userData, cb };

    arg.m_parser = XML_ParserCreate(NULL);
    XML_SetUserData(arg.m_parser, &arg);

    XML_SetElementHandler(arg.m_parser,getListUser_StartElementHandler,getListUser_EndElementHandler);
    XML_SetCharacterDataHandler(arg.m_parser,getListUser_CharacterDataHandler);
    
    flickr_request(client, "flickr.tags.getListUser",
		   &arg, &writeToGetListUserParser,
		   reqarg, sizeof(reqarg)/sizeof(reqarg[0]));
  
    XML_Parse(arg.m_parser,&dummy,0,1);
    XML_ParserFree(arg.m_parser);
    return 0;
}

static void getListUserPopular_EndElementHandler(void *userData, const XML_Char *name)
{
  if(strcmp(name,"tag")==0) {
    getListUserArg *args = (getListUserArg*)userData;
    args->m_parsing_tag=0;
    
    ((void (*)(void *, String *, unsigned int))args->m_cb)(args->m_userData,&args->m_tag,args->m_count);
    String_Destroy(&args->m_tag);
  }
}

FlickrResult flickr_tags_getListUserPopular(FlickrClient *client,
					    String *user_id,
					    unsigned int count,
					    void *userData,
					    void (*cb)(void *userData, String *tag, unsigned int count))
/* this function uses almost the same parser as flickr_tags_getListUser, only with a more
   sophisticated end element handler that passes the count as an additionnal parameter
   to the callback function */
{
  char buf[20];
    const FlickrRequestArg reqarg[] = {
      { "user_id", user_id->m_start },
      { "count", &buf[0] }
    };
    unsigned char dummy=0;
    getListUserArg arg = { NULL, userData, (void (*)(void *, String *))cb };

    if(count==0) count=10;
    sprintf(&buf[0],"%d",count);
    arg.m_parser = XML_ParserCreate(NULL);
    XML_SetUserData(arg.m_parser, &arg);

    XML_SetElementHandler(arg.m_parser,getListUser_StartElementHandler,getListUserPopular_EndElementHandler);
    XML_SetCharacterDataHandler(arg.m_parser,getListUser_CharacterDataHandler);
    
    flickr_request(client, "flickr.tags.getListUserPopular",
		   &arg, &writeToGetListUserParser,
		   reqarg, sizeof(reqarg)/sizeof(reqarg[0]));
  
    XML_Parse(arg.m_parser,&dummy,0,1);
    XML_ParserFree(arg.m_parser);
    return 0;
}

static void getRelated_EndElementHandler(void *userData, const XML_Char *name)
{
  if(strcmp(name,"tag")==0) {
    getListUserArg *args = (getListUserArg*)userData;
    args->m_parsing_tag=0;
    
    ((void (*)(void *, String *))args->m_cb)(args->m_userData,&args->m_tag);
    String_Destroy(&args->m_tag);
  }
}

FlickrResult flickr_tags_getRelated(FlickrClient *client, String *tag,
				    void *userData,
				    void (*cb)(void *userData, const String *tag))
{
    const FlickrRequestArg reqarg[] = {
      { "tag", tag->m_start }
    };
    unsigned char dummy=0;
    getListUserArg arg = { NULL, userData, (void (*)(void *, String *))cb };

    arg.m_parser = XML_ParserCreate(NULL);
    XML_SetUserData(arg.m_parser, &arg);

    XML_SetElementHandler(arg.m_parser,getListUser_StartElementHandler,getRelated_EndElementHandler);
    XML_SetCharacterDataHandler(arg.m_parser,getListUser_CharacterDataHandler);
    
    flickr_request(client, "flickr.tags.getRelated",
		   &arg, &writeToGetListUserParser,
		   reqarg, sizeof(reqarg)/sizeof(reqarg[0]));
  
    XML_Parse(arg.m_parser,&dummy,0,1);
    XML_ParserFree(arg.m_parser);
    return 0;
}
