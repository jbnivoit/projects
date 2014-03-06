/* -*- C -*- */
#include "FlickrClientImpl.h"

#include <string.h>

typedef struct blogsGetListArg blogsGetListArg;
struct blogsGetListArg {
  rspParser m_super;
  FlickrBlog m_blog;  
  void *m_userData;
  void (*m_cb)(void *userData, const FlickrBlog *blog);
};

static void getList_StartElementHandler(void *userData,
					   const XML_Char *name,
					   const XML_Char **atts)
{
  blogsGetListArg *rp = (blogsGetListArg*)userData;

  if(strcmp(name,"blog")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"id")==0 ) {
	atts++;
	String_InitWithString(&rp->m_blog.m_id,*atts,strlen(*atts));
	break;
      } else if( strcmp(*atts,"name")==0 ) {
	atts++;
	String_InitWithString(&rp->m_blog.m_name,*atts,strlen(*atts));
	break;
      } else if( strcmp(*atts,"needspassword")==0 ) {
	atts++;
	rp->m_blog.m_needspassword = atoi(*atts);
	break;
      } else if( strcmp(*atts,"url")==0 ) {
	atts++;
	String_InitWithString(&rp->m_blog.m_url,*atts,strlen(*atts));
	break;
      }
      atts++;
    }
    
    (*rp->m_cb)(rp->m_userData,&rp->m_blog);
  }
}

FlickrResult flickr_blogs_getList(FlickrClient *client, 
				  void *userData, void (*cb)(void *userData, const FlickrBlog *blog))
{
  blogsGetListArg p;

  FlickrBlog_Init(&p.m_blog);
  memset(&p,0,sizeof(blogsGetListArg));

  p.m_userData=userData;
  p.m_cb=cb;
  rsp_ParserCreate(&p.m_super);
  rsp_SetElementHandler(&p.m_super,getList_StartElementHandler,noop_EndElementHandler);
  
  flickr_request_rsp0(client, "flickr.blogs.getList",p.m_super);
  
  rsp_ParserFree(&p.m_super);
  FlickrBlog_Destroy(&p.m_blog);
  return p.m_super.m_code;
  /* FIXME requires authentication with read permission */
}

FlickrResult flickr_blogs_postPhoto(FlickrClient *client,
				    const FlickrBlogId  *blog_id,
				    const FlickrPhotoId *photo_id,
				    const String *title,
				    const String *description,
				    const String *blog_password)
{
  const FlickrRequestArg reqarg[] = {
    { "blog_id",       blog_id->m_start       },
    { "photo_id",      photo_id->m_start      },
    { "title",         title->m_start         },
    { "description",   description->m_start   },
    { "blog_password", blog_password->m_start }
  };
  rspParser p = { NULL, 0 };
  
  p.m_parser = XML_ParserCreate(NULL);
  XML_SetUserData(p.m_parser, &p);
  XML_SetElementHandler(p.m_parser,rsp_StartElementHandler,noop_EndElementHandler);
  
  flickr_request_rsp(client, "flickr.blogs.postPhoto", p, reqarg);
  
  rsp_ParserFree(&p);
  return p.m_code;
  /* FIXME requires authentication with write permission */
}
