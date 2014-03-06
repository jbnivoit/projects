/* -*- C -*- */
/*
 * C implementation of http://www.quasimondo.com/clockr.php
 * search on flickr using tags "digit" & "0"..."9".
 *
 */
#include "FlickrClient.h"
#include "test.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void printFlickrPhoto(const FlickrPhoto *p) {
  String url;
  
  String_Init(&url);
  
  flickr_build_photo_url(p->m_id,
			 atoi(p->m_server.m_start),
			 &p->m_secret,
			 PHOTO_SZ_THUMBNAIL,
			 &url);
  
  printf("%s\n",String_GetString(&url));
  String_Destroy(&url);
}

static void printResultPage(void *userData, 
			    const FlickrResultPage *page,
			    unsigned int offset, 
			    const FlickrPhoto *photo)
{
  printFlickrPhoto(photo);  
}

int main(int argc, char **argv)
{
  curl_global_init( CURL_GLOBAL_ALL ) ;
  FlickrClient *c = newFlickrClient(flickr_API_key, flickr_API_secret);

  {
    FlickrSearchCriteria criteria;
    String tag;

    FlickrSearchCriteria_Init(&criteria);
    String_InitWithString(&tag,"digit",5);
    criteria.m_tags=&tag;
    criteria.m_tagsz=1;
    criteria.m_sort=SORT_INTERESTINGNESS_DESC;
    criteria.m_per_page=20;
    
    flickr_photos_search(c,
			 &criteria,
			 NULL,
			 &printResultPage);
    
    FlickrSearchCriteria_Destroy(&criteria);
  }
  deleteFlickrClient(c);
  curl_global_cleanup() ;
  return EXIT_SUCCESS;
}
