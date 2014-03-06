#include "FlickrClientImpl.h"
#include "FlickrXmlHandler.h"

#include <string.h>

FlickrResult flickr_favorites_add(FlickrClient *client, const FlickrPhotoId *photo_id)
{
  const FlickrRequestArg reqarg[] = {
    { "photo_id",  photo_id->m_start }
  };
  unsigned char dummy=0;
  rspParser p = { NULL, 0 };

  p.m_parser = XML_ParserCreate(NULL);
  XML_SetUserData(p.m_parser, &p);
  rsp_SetElementHandler(&p,rsp_StartElementHandler,noop_EndElementHandler);
  
  flickr_request_rsp(client, "flickr.favorites.add",p,reqarg);
  
  XML_Parse(p.m_parser,&dummy,0,1);
  XML_ParserFree(p.m_parser);
  return p.m_code;
}

void favorites_getPublicList_StartElementHandler(void *userData,
					   const XML_Char *name,
					   const XML_Char **atts)
{
  getListArg *rp = (getListArg*)userData;

  if(strcmp(name,"photos")==0) {

      matchXmlAttr matches[] = {
	{ "page",    XML_UI, { ui: &rp->m_page.m_page } },
	{ "pages",   XML_UI, { ui: &rp->m_page.m_pages } },
	{ "perpage", XML_UI, { ui: &rp->m_page.m_perpage } },
	{ "total",   XML_UI, { ui: &rp->m_page.m_total } },
      };
      extractAttrValues(matches,atts);

  } else if(strcmp(name,"photo")==0) {
    memset(&rp->m_photo,0,sizeof(FlickrPhoto));

      matchXmlAttr matches[] = {
	{ "id",      XML_UI,     { ui: &rp->m_photo.m_id } },
	{ "owner",   XML_STRING, { &rp->m_photo.m_owner } },
	{ "secret",  XML_STRING, { &rp->m_photo.m_secret } },
	{ "server",  XML_STRING, { &rp->m_photo.m_server } },
	{ "title",   XML_STRING, { &rp->m_photo.m_title } },
	{ "ispublic", XML_UC,    { uc: &rp->m_photo.m_ispublic } },
	{ "isfriend", XML_UC,    { uc: &rp->m_photo.m_isfriend } },
	{ "isfamily", XML_UC,    { uc: &rp->m_photo.m_isfamily } },
      };
      extractAttrValues(matches,atts);
        
    (*rp->m_cb)(rp->m_userData, &rp->m_page, rp->m_offset, &rp->m_photo);
    rp->m_offset++;
  }
}

/*
static size_t writeToFavoritesParser(void *source, size_t sz, size_t nmemb, void *userData)
{
  getListArg *args = (getListArg*)userData;
  XML_Parse(args->m_parser,source,sz*nmemb,0);
  return sz*nmemb;
}
*/

static FlickrResult flickr_favorites_get(const char *method, FlickrClient *client,
					    const String *user_id, 
					    FlickrPhotoExtras extras,
					    unsigned int per_page,
					    unsigned int page,
					    void *userData,
					    void (*cb)(void *userData, const FlickrResultPage *page,
						       unsigned int offset, const FlickrPhoto *photo))
{
  getListArg fav;
  char buf_per_page[20], buf_page[20];

  if(per_page==0) per_page=500;
  if(page==0) page=1;
  memset(&fav,0,sizeof(getListArg));
  fav.m_userData=userData;
  fav.m_cb=cb;

  sprintf(&buf_per_page[0],"%d",per_page);
  sprintf(&buf_page[0],"%d",page);
  buildExtrasParam(client, extras);
  {
    const FlickrRequestArg reqarg[] = {
      { "user_id",  user_id->m_start },
      { "extras",   client->m_extras_scratchpad },
      { "per_page", &buf_per_page[0] },
      { "page",     &buf_page[0] }
    };
    unsigned char dummy=0;

    fav.m_super.m_parser = XML_ParserCreate(NULL);
    rsp_SetUserData(&fav.m_super, &fav);

    rsp_SetElementHandler(&fav.m_super,favorites_getPublicList_StartElementHandler,noop_EndElementHandler);
    
    flickr_request_rsp(client, method,
		       &fav.m_super, reqarg);
  
    XML_Parse(fav.m_super.m_parser,&dummy,0,1);
    XML_ParserFree(fav.m_super.m_parser);
    return 0;
  }
}

FlickrResult flickr_favorites_getPublicList(FlickrClient *client,
					    const String *user_id, 
					    FlickrPhotoExtras extras,
					    unsigned int per_page,
					    unsigned int page,
					    void *userData,
					    void (*cb)(void *userData, const FlickrResultPage *page,
						       unsigned int offset, const FlickrPhoto *photo))
{
  return flickr_favorites_get("flickr.favorites.getPublicList",client,
			      user_id, 
			      extras,
			      per_page,
			      page,
			      userData,
			      cb);
}

FlickrResult flickr_favorites_getList(FlickrClient *client,
					    const String *user_id, 
					    FlickrPhotoExtras extras,
					    unsigned int per_page,
					    unsigned int page,
					    void *userData,
					    void (*cb)(void *userData, const FlickrResultPage *page,
						       unsigned int offset, const FlickrPhoto *photo))
{
  return flickr_favorites_get("flickr.favorites.getList",client,
			      user_id, 
			      extras,
			      per_page,
			      page,
			      userData,
			      cb);
}

FlickrResult flickr_favorites_remove(FlickrClient *client, const FlickrPhotoId *photo_id)
{
  rspParser p;
  const FlickrRequestArg reqarg[] = {
    { "photo_id", photo_id->m_start },
  };
  rsp_ParserCreate(&p);

  rsp_SetElementHandler(&p,NULL,noop_EndElementHandler);
  
  flickr_request_rsp(client, "flickr.favorites.remove",p,reqarg);

  rsp_ParserFree(&p);
  return p.m_code;
  /* FIXME requires authentication with write permission */
}
