/* -*- C -*- */
#include "FlickrClient.h"
#include "test.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct getTokenArg getTokenArg;
struct getTokenArg {
  String token;
  FlickrPerm perm;
  FlickrUser user;
};

static void getTokenArg_Init(getTokenArg *p)
{
  memset(p,0,sizeof(p));
  String_Init(&p->token);
  FlickrUser_Init(&p->user);
}

static void getTokenArg_Destroy(getTokenArg *p)
{
  String_Destroy(&p->token);
  FlickrUser_Destroy(&p->user);
}

static void copyGetTokenResult(void *userData, const String *token, 
			       FlickrPerm perm, const FlickrUser *user)
{
  getTokenArg *p = (getTokenArg*)userData;

  String_Copy(&p->token, token);
  FlickrUser_Copy(&p->user,user);
  p->perm=perm;
}

int main(int argc, char **argv)
{
  int rv = EXIT_SUCCESS;
  curl_global_init( CURL_GLOBAL_ALL ) ;
  FlickrClient *c = newFlickrClient(flickr_API_key, flickr_API_secret);
  {
    String url;

    String_Init(&url);
    
    if(argc==1) {
      String frob;
      
      String_Init(&frob);
      flickr_auth_getFrob(c, &frob);
      printf("frob=%s\n",String_GetString(&frob));
      
      flickr_auth_url(c,&frob, PERM_READ, &url);
      printf("url=%s\n",String_GetString(&url));
      String_Destroy(&frob);
    } else {
      String frob;
      String_InitWithString(&frob,argv[1],strlen(argv[1]));

      getTokenArg p;

      getTokenArg_Init(&p);
      flickr_auth_getToken(c,
			   &frob,
			   (void*)&p,
			   &copyGetTokenResult);
      printf("token=%s\n",String_GetString(&p.token));

      getTokenArg_Destroy(&p);
      String_Destroy(&frob);
    }
    String_Destroy(&url);
  }
  deleteFlickrClient(c);
  curl_global_cleanup() ;
  return rv;
}
