/* -*- C -*- */
#include "FlickrClientImpl.h"
#include "FlickrXmlHandler.h"

#include <string.h>

static FlickrResult flickr_photosets_request(FlickrClient *client,
					     const char *method,
					     const FlickrPhotosetId *photoset_id,
					     const FlickrPhotoId *photo_id)
{
  rspParser p;
  const FlickrRequestArg reqarg[] = {
    { "photoset_id", photoset_id->m_start },
    { "photo_id",    photo_id->m_start },
  };
  rsp_ParserCreate(&p);
  
  flickr_request_rsp(client,method,p,reqarg);

  rsp_ParserFree(&p);
  return p.m_code;
  /* FIXME requires authentication with write permission */
}


FlickrResult flickr_photosets_addPhoto(FlickrClient *client,
				       const FlickrPhotosetId *photoset_id,
				       const FlickrPhotoId *photo_id) {
  return flickr_photosets_request(client,
				  "flickr.photosets.addPhoto",
				  photoset_id,
				  photo_id);
}

typedef struct photosetCreateArg photosetCreateArg;
struct photosetCreateArg {
  rspParser m_super;
  FlickrPhotosetId *m_id;
  String *m_url;
};

static void photosetCreate_StartElementHandler(void *userData,
					   const XML_Char *name,
					   const XML_Char **atts)
{
  photosetCreateArg *p = (photosetCreateArg*)userData;
  
  if(strcmp(name,"photoset")==0) {
    matchXmlAttr matches[] = {
      { "id",  XML_STRING, { p->m_id  } },
      { "url", XML_STRING, { p->m_url } }
    };
    extractAttrValues(matches,atts);
  }
}

FlickrResult flickr_photosets_create(FlickrClient *client,
				     const String *title,
				     const String *description,
				     const FlickrPhotoId *primary_photo_id,
				     FlickrPhotosetId *id,
				     String *url)
/* FIXME requires authentication with write permission */
{
  const FlickrRequestArg reqarg[] = {
    { "title",       title->m_start       },
    { "description", description->m_start },
    { "primary_photo_id",    primary_photo_id->m_start    },
  };
  photosetCreateArg p;
  rsp_ParserCreate(&p.m_super);
  p.m_id=id;
  p.m_url=url;

  rsp_SetElementHandler(&p.m_super,
			photosetCreate_StartElementHandler,
			noop_EndElementHandler);
    
  flickr_request_rsp(client, "flickr.photosets.create", p.m_super, reqarg);
    
  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}
typedef struct getContextArg getContextArg;
struct getContextArg {
  XML_Parser m_parser;
  FlickrPhotoContextResponse m_response;
};

static void getContext_StartElementHandler(void *userData,
					   const XML_Char *name,
					   const XML_Char **atts)
{
  FlickrPhotoContextResponse *rp = &((getContextArg*)userData)->m_response;
  FlickrPhotoContext *ctx = NULL;

  if(strcmp(name,"prevphoto")==0) {
    ctx = &rp->m_prev;
  }
  if(strcmp(name,"nextphoto")==0) {
    ctx = &rp->m_next;
  }
  if(ctx!=NULL) {
    matchXmlAttr matches[] = {
      { "id",     XML_UI,     { ui: &ctx->m_id  } },
      { "url",    XML_STRING, { &ctx->m_url } },
      { "secret", XML_STRING, { &ctx->m_secret } },
      { "title",  XML_STRING, { &ctx->m_title } }
    };
    extractAttrValues(matches,atts);
  }
}

static size_t writeToGetContextParser(void *source, size_t sz, size_t nmemb, void *userData)
{
  getContextArg *args = (getContextArg*)userData;
  XML_Parse(args->m_parser,source,sz*nmemb,0);
  return sz*nmemb;
}

FlickrResult flickr_photosets_getContext(FlickrClient *client,
					 const FlickrPhotoId *photo_id,
					 const FlickrPhotosetId *photoset_id,
					 void *userData,
					 void (*cb)(void *userData,
						    FlickrPhotoContext *prev,
						    FlickrPhotoContext *next))
{
    const FlickrRequestArg reqarg[] = {
      { "photo_id", photo_id->m_start },
      { "photoset_id", photoset_id->m_start },
    };
    unsigned char dummy=0;
    getContextArg arg;

    arg.m_parser = XML_ParserCreate(NULL);
    XML_SetUserData(arg.m_parser, &arg);

    XML_SetElementHandler(arg.m_parser,getContext_StartElementHandler,noop_EndElementHandler);

    memset(&arg.m_response,0,sizeof(FlickrPhotoContextResponse));
    
    flickr_request(client, "flickr.photosets.getContext",
		   &arg, &writeToGetContextParser,
		    reqarg, sizeof(reqarg)/sizeof(reqarg[0]));

     XML_Parse(arg.m_parser,&dummy,0,1);
     XML_ParserFree(arg.m_parser);

     (*cb)(userData,
	   &arg.m_response.m_prev,
	   &arg.m_response.m_next);

     return 0;
 }

FlickrResult flickr_photosets_getPhotos(FlickrClient *client, 
					FlickrPhotosetId photoset_id,
					int extras,
					void *userData,
					void (*cb)(void *userData, 
						   String *id, String *primary, 
						   FlickrPhoto *photo))
{
#if 1
  return 0;
#else
  buildExtrasParam(client, extras);
  {
    const FlickrRequestArg reqarg[] = {
      { "photoset_id", photoset_id.m_start },
      { "extras", client->m_extras_scratchpad }
    };
    unsigned char dummy=0;
    FlickrPhoto photo;

    XML_Parser p = XML_ParserCreate(NULL);
    XML_SetUserData(p, &photo);

    XML_SetElementHandler(p,getInfo_StartElementHandler,noop_EndElementHandler);
    XML_SetCharacterDataHandler(p,getInfo_CharacterDataHandler);
    
    flickr_request(client, "flickr.photosets.getPhotos",
		   &args, &writeToGetInfoParser,
		   reqarg, sizeof(reqarg)/sizeof(reqarg[0]));
  
    XML_Parse(p,&dummy,0,1);
    XML_ParserFree(p);

    (*cb)(userData, &photo);
    
    return 0;
  }
#endif
}

FlickrResult flickr_photosets_delete(FlickrClient *client,
				     const FlickrPhotosetId *photoset_id)
{
  rspParser p;
  const FlickrRequestArg reqarg[] = {
    { "photoset_id", photoset_id->m_start },
  };
  rsp_ParserCreate(&p);
  
  flickr_request_rsp(client,"flickr.photosets.removeaddPhoto",p,reqarg);

  rsp_ParserFree(&p);
  return p.m_code;
  /* FIXME requires authentication with write permission */
}

FlickrResult flickr_photosets_removePhoto(FlickrClient *client,
					  const FlickrPhotosetId *photoset_id,
					  const FlickrPhotoId *photo_id)
{
  return flickr_photosets_request(client,
				  "flickr.photosets.removePhoto",
				  photoset_id,
				  photo_id);
}


FlickrResult FLICKR_API flickr_photosets_editMeta(FlickrClient *client,
						  const FlickrPhotosetId *photoset_id,
						  const String *title,
						  const String *description)
{
  rspParser p;
  const FlickrRequestArg reqarg[] = {
    { "photoset_id", photoset_id->m_start },
    { "title",       title->m_start       },
    { "description", description->m_start },
  };
  rsp_ParserCreate(&p);
  
  flickr_request_rsp(client,"flickr.photosets.editMeta",p,reqarg);

  rsp_ParserFree(&p);
  return p.m_code;
  /* FIXME requires authentication with write permission */
}

FlickrResult flickr_photosets_editPhotos(FlickrClient *client,
					 const FlickrPhotosetId *photoset_id,
					 const FlickrPhotoId *primary_photo_id,
					 const unsigned int photo_ids_sz,
					 const FlickrPhotoId *photo_ids)
{
  String scratch;
  String_Init(&scratch);
  {
    rspParser p;
    const FlickrRequestArg reqarg[] = {
      { "photoset_id",       photoset_id->m_start },
      { "primary_photo_id",  primary_photo_id->m_start    },
      { "photo_ids",         concatenateStrings(photo_ids_sz,photo_ids,&scratch) },  
    };
    rsp_ParserCreate(&p);
    
    flickr_request_rsp(client,"flickr.photosets.editPhotos",p,reqarg);
    
    rsp_ParserFree(&p);
    return p.m_code;
    /* FIXME requires authentication with write permission */
  }
}

typedef enum {
  PARSING_UNKNOWN,
  PARSING_TITLE,
  PARSING_DESC
} getInfoParsingState;

typedef struct photosetsGetInfoArg photosetsGetInfoArg;
struct photosetsGetInfoArg {
  rspParser m_super;
  FlickrPhotoset *m_photoset;
  getInfoParsingState m_parsing_state;
};

static void photosetsGetInfo_StartElementHandler(void *userData,
					   const XML_Char *name,
					   const XML_Char **atts)
{
  photosetsGetInfoArg *p = (photosetsGetInfoArg*)userData;
  
  if(strcmp(name,"title")==0) {
    p->m_parsing_state = PARSING_TITLE;
  } else if(strcmp(name,"description")==0) {
    p->m_parsing_state = PARSING_DESC;
  } else {

    if(strcmp(name,"photoset")==0) {
      matchXmlAttr matches[] = {
	{ "id",      XML_STRING, { &p->m_photoset->m_id  } },
	{ "owner",   XML_STRING, { &p->m_photoset->m_owner } },
  	{ "primary", XML_STRING, { &p->m_photoset->m_primary } },
	{ "photos",  XML_UI,     { ui: &p->m_photoset->m_photos } }
      };
      extractAttrValues(matches,atts);
    } 
    p->m_parsing_state = PARSING_UNKNOWN;
  }
  
}

static void photosetsGetInfo_CharacterDataHandler (void *userData,
				      const XML_Char *s,
				      int len)
{
  photosetsGetInfoArg *p = (photosetsGetInfoArg*)userData;
  String *str=NULL;

  switch(p->m_parsing_state) {
  case PARSING_TITLE: str = &p->m_photoset->m_title; break;
  case PARSING_DESC:  str = &p->m_photoset->m_description; break;
  default:;
  }
  if(str!=NULL)  
    String_Append(str,s,len);
}

FlickrResult flickr_photosets_getInfo(FlickrClient *client,
				      const FlickrPhotosetId *photoset_id,
				      FlickrPhotoset *photoset)
{
  photosetsGetInfoArg p;
  const FlickrRequestArg reqarg[] = {
    { "photoset_id", photoset_id->m_start },
  };
  rsp_ParserCreate(&p.m_super);

  memset(photoset,0,sizeof(FlickrPhotoset));
  rsp_SetElementHandler(&p.m_super,
			photosetsGetInfo_StartElementHandler,
			noop_EndElementHandler);
  rsp_SetCharacterDataHandler(&p.m_super,
			      photosetsGetInfo_CharacterDataHandler);
  
  flickr_request_rsp(client,"flickr.photosets.getInfo",p.m_super,reqarg);

  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}

typedef struct photosetsGetListArg photosetsGetListArg;
struct photosetsGetListArg {
  photosetsGetInfoArg m_super;
  FlickrPhotoset m_photoset;
  void *m_userData;
  void (*m_cb)(void *userData, const FlickrPhotoset *set);
  unsigned char m_cancreate;
};

static void photosetsGetList_EndElementHandler(void *userData, const XML_Char *name)
{
  if(strcmp(name,"photoset")==0) {
    photosetsGetListArg *p  = (photosetsGetListArg *)userData;
    (*p->m_cb)(p->m_userData,&p->m_photoset);
  }
}

static void photosetsGetList_StartElementHandler(void *userData,
					   const XML_Char *name,
					   const XML_Char **atts)
{
  photosetsGetListArg *p = (photosetsGetListArg*)userData;
  
  if(strcmp(name,"photosets")==0) {
    matchXmlAttr matches[] = {
      { "cancreate",  XML_UC, { uc: &p->m_cancreate  } }
    };
    extractAttrValues(matches,atts);
  } else
    photosetsGetInfo_StartElementHandler(userData,
					 name,
					 atts);
}

unsigned char flickr_photosets_getList(FlickrClient *client, 
				       const String *user_id, 
				       void *userData, 
				       void (*cb)(void *userData, const FlickrPhotoset *set))
{
  photosetsGetListArg p;
  const FlickrRequestArg reqarg[] = {
    { "user_id",     user_id==NULL?NULL:user_id->m_start }
  };
  
  rsp_ParserCreate(&p.m_super.m_super);

  p.m_super.m_photoset=&p.m_photoset;
  p.m_userData=userData;
  p.m_cb=cb;

  rsp_SetElementHandler(&p.m_super.m_super,
			photosetsGetList_StartElementHandler,
			photosetsGetList_EndElementHandler);
  rsp_SetCharacterDataHandler(&p.m_super.m_super,
			      photosetsGetInfo_CharacterDataHandler);
  
  flickr_request_rsp(client,"flickr.photosets.getList",p.m_super.m_super,reqarg);

  rsp_ParserFree(&p.m_super.m_super);
  return p.m_cancreate;
}
  
FlickrResult flickr_photosets_orderSets(FlickrClient *client,
					const unsigned int photoset_ids_sz,
					const FlickrPhotosetId *photoset_ids)
{
  String scratch;
  String_Init(&scratch);
  {
    rspParser p;
    const FlickrRequestArg reqarg[] = {
      { "photoset_ids",         concatenateStrings(photoset_ids_sz,photoset_ids,&scratch) },  
    };
    rsp_ParserCreate(&p);
    
    flickr_request_rsp(client,"flickr.photosets.orderSets",p,reqarg);
    
    rsp_ParserFree(&p);
    return p.m_code;
    /* FIXME requires authentication with write permission */
  }
}
