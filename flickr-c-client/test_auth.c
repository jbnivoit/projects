/* -*- C -*- */
#include "FlickrClient.h"
#include "test.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct getTokenArg getTokenArg;
struct getTokenArg {
  String *token;
};

static void getTokenArg_Init(getTokenArg *p, String *token)
{
  memset(p,0,sizeof(p));
  p->token=token;
}

static void copyGetTokenResult(void *userData, const String *token, 
			       FlickrPerm perm, const FlickrUser *user)
{
  getTokenArg *p = (getTokenArg*)userData;
  String_Copy(p->token, token);
}

void test_auth_getToken(FlickrClient *c,
			const String *frob,
			String *token) {
      getTokenArg p;
      getTokenArg_Init(&p,token);
      flickr_auth_getToken(c,
			   frob,
			   (void*)&p,
			   &copyGetTokenResult);
}
