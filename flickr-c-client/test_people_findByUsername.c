/* -*- C -*- */
#include "FlickrClient.h"
#include "test.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  int rv = EXIT_SUCCESS;
  curl_global_init( CURL_GLOBAL_ALL ) ;
  FlickrClient *c = newFlickrClient(flickr_API_key, flickr_API_secret);
  {
    String find_email;
    String nsid, username;

    String_InitWithString(&find_email, findByEmail_input, strlen(findByEmail_input));
    String_Init(&nsid);
    String_Init(&username);

    flickr_people_findByUsername(c,&find_email,
				 &nsid,&username);
    
    if(0==String_CompareCString(&nsid,findByEmail_output_nsid))
      rv = EXIT_FAILURE;
    if(0==String_CompareCString(&username,findByEmail_output_username))
      rv = EXIT_FAILURE;
    
    String_Destroy(&find_email);
    String_Destroy(&nsid);
    String_Destroy(&username);
  }
  deleteFlickrClient(c);
  curl_global_cleanup() ;
  return rv;
}
