/* -*- C -*- */
#include "FlickrClient.h"
#include "test.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  curl_global_init( CURL_GLOBAL_ALL ) ;
  FlickrClient *c = newFlickrClient(flickr_API_key, flickr_API_secret);
  FlickrRequestArg arg[2] = {
    {"foo", "bar" },
    {"baz", "quux" }
  };
  flickr_test_echo(c,arg,sizeof(arg)/sizeof(arg[0]));
  deleteFlickrClient(c);
  curl_global_cleanup() ;
  return EXIT_SUCCESS;
}
