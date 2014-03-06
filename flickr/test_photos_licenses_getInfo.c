/* -*- C -*- */
#include "FlickrClient.h"
#include "test.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void printLicense(void *userData, const FlickrLicense *lic) {
  printf("<license id=\"%d\" name=\"%s\" url=\"%s\" />\n",
	 lic->m_id,
	 lic->m_name.m_start,
	 lic->m_url.m_start);
}

int main(int argc, char **argv)
{
  curl_global_init( CURL_GLOBAL_ALL ) ;
  FlickrClient *c = newFlickrClient(flickr_API_key, flickr_API_secret);
  
  flickr_photos_licenses_getInfo(c,NULL,&printLicense);

  deleteFlickrClient(c);
  curl_global_cleanup() ;
  return EXIT_SUCCESS;
}
