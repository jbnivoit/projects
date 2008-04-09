/* -*- C -*- */
#include "FlickrClient.h"
#include "test.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  int rv = EXIT_SUCCESS;
  curl_global_init( CURL_GLOBAL_ALL ) ;
  FlickrClient *c = newFlickrClient(flickr_API_key, flickr_API_secret);
  {
    String frob;
    String_Init(&frob);
    flickr_auth_getFrob(c, &frob);
    printf("%s\n",String_GetString(&frob));
    String_Destroy(&frob);
  }
  deleteFlickrClient(c);
  curl_global_cleanup() ;
  return rv;
}
