#include "FlickrClientImpl.h"

FlickrResult flickr_groups_pools_add(FlickrClient *client,
				     const FlickrPhotoId *photo_id, 
				     const FlickrGroupId *group_id)
{
  rspParser p;
  const FlickrRequestArg reqarg[] = {
    { "photo_id", photo_id->m_start },
    { "group_id", group_id->m_start },
  };
  rsp_ParserCreate(&p);

  rsp_SetDefaultElementHandler(&p);
  
  flickr_request_rsp(client,"flickr.groups.pools.add",p,reqarg);

  rsp_ParserFree(&p);
  return p.m_code;
  /* FIXME requires authentication with write permission */
}

typedef struct getContextArg getContextArg;
struct getContextArg {
  rspParser m_super;
  FlickrPhotoContext m_prev;
  FlickrPhotoContext m_next;
  void *m_userData;
  void (*m_cb)(void *userData,
	       const FlickrPhotoContext *prev,
	       const FlickrPhotoContext *next);
};

FlickrResult flickr_groups_pools_getContext(FlickrClient *client,
							      const FlickrPhotoId *photo_id, 
							      const FlickrGroupId *group_id,
							      void *userData,
							      void (*cb)(void *userData,
									 const FlickrPhotoContext *prev,
									 const FlickrPhotoContext *next))
{

  return 0;
}

FlickrResult flickr_groups_pools_getGroups(FlickrClient *client,
					   void *userData,
					   void (*cb)(void *userData, const FlickrPoolGroup *group));

FlickrResult flickr_groups_pools_getPhotos(FlickrClient *client,
					   const FlickrGroupId *group_id,
					   const String *tag,
					   const String *user_id,
					   int extras,
					   unsigned int per_page,
					   unsigned int page,
					   void *userData,
					   void (*cb)(void *userData, const FlickrPoolPhoto *photo));

FlickrResult flickr_groups_pools_remove(FlickrClient *client,
					const FlickrPhotoId *photo_id, const FlickrGroupId *group_id);
