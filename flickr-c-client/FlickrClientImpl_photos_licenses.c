#include "FlickrClientImpl.h"
#include "FlickrXmlHandler.h"

#include <string.h>

typedef struct licenseArg licenseArg;
struct licenseArg {
  rspParser m_super;
  FlickrLicense m_license;
  void *m_userData;
  void (*m_cb)(void *userData, const FlickrLicense *lic);
};

static void FlickrLicense_Init(FlickrLicense *p) {
  p->m_id=0;
  String_Init(&p->m_name);
  String_Init(&p->m_url);
}

static void FlickrLicense_Destroy(FlickrLicense *p) {
  String_Destroy(&p->m_name);
  String_Destroy(&p->m_url);
}

static void license_StartElementHandler(void *userData,
					 const XML_Char *name,
					 const XML_Char **atts)
{
  licenseArg *rp = (licenseArg*)userData;

  if(strcmp(name,"license")==0) {
    matchXmlAttr matches[] = {
      { "id",   XML_UI,     { ui: &rp->m_license.m_id } },
      { "name", XML_STRING, { &rp->m_license.m_name } },
      { "url",  XML_STRING, { &rp->m_license.m_url } },
    };
    
    FlickrLicense_Init(&rp->m_license);
    extractAttrValues(matches,atts);
    (*rp->m_cb)(rp->m_userData, &rp->m_license);
    FlickrLicense_Destroy(&rp->m_license);
  }
}

FlickrResult flickr_photos_licenses_getInfo(FlickrClient *client,
					    void *userData,
					    void (*cb)(void *userData, const FlickrLicense *lic))
{
  licenseArg p;
  memset(&p,0,sizeof(licenseArg));

  p.m_userData=userData;
  p.m_cb=cb;

  rsp_ParserCreate(&p.m_super);
  rsp_SetElementHandler(&p.m_super,license_StartElementHandler,noop_EndElementHandler);
  
  flickr_request_rsp0(client, "flickr.photos.licenses.getInfo",p.m_super);

  rsp_ParserFree(&p.m_super);

  return p.m_super.m_code;
}

FlickrResult flickr_photos_licenses_setLicense(FlickrClient *client,
					       const FlickrPhotoId *photo_id,
					       const unsigned int license_id)
{
  resetCursor(client);
  {
    rspParser p;
    const FlickrRequestArg reqarg[] = {
      { "photo_id",   photo_id->m_start   },
      { "license_id", makeIntString(client,license_id) },
    };
    
    rsp_ParserCreate(&p);
    
    flickr_request_rsp(client, "flickr.photos.licenses.setLicense",
		       p, reqarg);
    
    rsp_ParserFree(&p);
    return p.m_code;
  }
}

