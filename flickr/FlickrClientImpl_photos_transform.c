#include "FlickrClientImpl.h"

static const char *deg(unsigned int d) {
  switch(d) {
  case  90: return "90";
  case 180: return "180";
  case 270: return "270";
  default:;
  }
  return "90";
}

FlickrResult flickr_photos_transform_rotate(FlickrClient *client, 
					    const FlickrPhotoId *photo_id,
					    unsigned int degrees)
{
  const FlickrRequestArg reqarg[] = {
    { "photo_id",  photo_id->m_start },
    { "degrees",   deg(degrees) }
  };
  unsigned char dummy=0;
  rspParser p = { NULL, 0 };

  p.m_parser = XML_ParserCreate(NULL);
  XML_SetUserData(p.m_parser, &p);
  XML_SetElementHandler(p.m_parser,rsp_StartElementHandler,noop_EndElementHandler);
  
  flickr_request_rsp(client, "flickr.photos.transform.rotate",
		     p,
		 reqarg);
  
  XML_Parse(p.m_parser,&dummy,0,1);
  XML_ParserFree(p.m_parser);
  return p.m_code;
  /* FIXME requires authentication with write permission */
}
