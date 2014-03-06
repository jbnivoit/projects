#include "FlickrClientImpl.h"

#include <string.h>

typedef struct uploadArg uploadArg;
struct uploadArg {
  rspParser m_super;
  String *m_photo_id;
  unsigned char m_parsing_photoid;
};

static void upload_StartElementHandler(void *userData,
				       const XML_Char *name,
				       const XML_Char **atts)
{
  uploadArg *rp = (uploadArg*)userData;
  if(strcmp(name,"photoid")==0 || strcmp(name,"ticketid")==0) {
    rp->m_parsing_photoid=1;
  }
}

static void upload_CharacterDataHandler (void *userData,
					 const XML_Char *s,
					 int len)
{
  uploadArg *rp = (uploadArg*)userData;
  if(rp->m_parsing_photoid==1)
    String_Append(rp->m_photo_id,s,len);
}

FlickrResult flickr_upload(FlickrClient *client,
			   const String *photo_file,
			   const FlickrPhoto *photo_args,
			   const String *tags,
			   unsigned int tagssz,
			   unsigned char async,
			   void *pUserData,
			   void (*progress_cb)(void *pUserData, size_t sz),
			   String *photo_id)
{
  resetCursor(client);
  {
    const FlickrRequestArg reqarg[] = {
      { "title",       photo_args->m_title.m_start         },
      { "description", photo_args->m_description.m_start   },
      { "tags",        tagssz==0?"":commaSeparatedList(client,tags,tagssz) },
      { "ispublic",    makeIntString(client,photo_args->m_ispublic) },
      { "isfriend",    makeIntString(client,photo_args->m_isfriend) },
      { "isfamily",    makeIntString(client,photo_args->m_isfamily) },
      { "async",       async?"1":"0" }
    };
    uploadArg p;
    p.m_photo_id = photo_id;
    p.m_parsing_photoid=0;
    
    rsp_ParserCreate(&p.m_super);
    rsp_SetElementHandler(&p.m_super,upload_StartElementHandler,noop_EndElementHandler);
    rsp_SetCharacterDataHandler(&p.m_super,
				&upload_CharacterDataHandler);

    flickr_request_upload(client,
			  flickr_UPLOAD_URI,
			  photo_file,
			  p.m_super.m_parser, &writeToParser,
			  pUserData,progress_cb,
			  reqarg, sizeof(reqarg)/sizeof(reqarg[0]));
    
    rsp_ParserFree(&p.m_super);
    return p.m_super.m_code;
    /* FIXME requires authentication with write permission */
  }
}
