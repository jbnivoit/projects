/* -*- C -*- */
#include "FlickrClient.h"
#include "test.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  curl_global_init( CURL_GLOBAL_ALL ) ;
  FlickrClient *c = newFlickrClient(flickr_API_key, flickr_API_secret);
  {
    String token;

    if(argc==2) {
      String_InitWithString(&token,argv[1],strlen(argv[1]));
    } else {
      /*
      String_Init(&token);
      {
	String frob;
	String_InitWithString(&frob,argv[1],strlen(argv[1]));
	
	test_auth_getToken(c,&frob,&token);
      }
      */
      printf("missing cmd line args\n");
      return EXIT_FAILURE;
    }
    
    flickr_set_authentication_token(c,&token);
    {
      String id, username;
      
      String_Init(&id);
      String_Init(&username);
      
      {
	FlickrResult rv = flickr_test_login(c, &id, &username);
	
	printf("%d|%s|%s\n", rv, String_GetString(&id), String_GetString(&username));
      }
      
      String_Destroy(&id);
      String_Destroy(&username);
      
    }
  }
  deleteFlickrClient(c);
  curl_global_cleanup() ;
  return EXIT_SUCCESS;
}
