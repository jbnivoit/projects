/* -*- C -*- */
/*
 * C implementation of http://favcol.com
 *
 */
#include "FlickrClient.h"
#include "test.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void printFlickrPhoto(const FlickrPhoto *p) {
  printf("<photo id=\"%d\" owner=\"%s\" secret=\"%s\" server=\"%s\" title=\"%s\" ispublic=\"%d\" isfriend=\"%d\" isfamily=\"%d\" />\n",
	 p->m_id,
	 p->m_owner.m_start,
	 p->m_secret.m_start,
	 p->m_server.m_start,
	 p->m_title.m_start,
	 p->m_ispublic,
	 p->m_isfriend,
	 p->m_isfamily);
}

static void printResultPage(void *userData, 
			    const FlickrResultPage *page,
			    unsigned int offset, 
			    const FlickrPhoto *photo)
{
 printFlickrPhoto(photo);  
#warning "download image and then average it".
#warning "added CreativeCommons license filter".
}

int main(int argc, char **argv)
{
  curl_global_init( CURL_GLOBAL_ALL ) ;
  FlickrClient *c = newFlickrClient(flickr_API_key, flickr_API_secret);

  {
    FlickrSearchCriteria criteria;
    String tag;
    const char *favcol="favcol";

    FlickrSearchCriteria_Init(&criteria);
    String_InitWithString(&tag,favcol,strlen(favcol));
    
    flickr_photos_search(c,
			 &criteria,
			 SORT_INTERESTINGNESS_DESC, 
			 0,
			 20,
			 0,
			 NULL,
			 &printResultPage);
    
    FlickrSearchCriteria_Destroy(&criteria);
  }
  deleteFlickrClient(c);
  curl_global_cleanup() ;
  return EXIT_SUCCESS;
}
