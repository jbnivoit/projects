#ifndef _test_H
#define _test_H

extern const char flickr_API_key[32];
extern const char flickr_API_secret[16];

extern const char *findByEmail_input;
extern const char *findByEmail_output_nsid;
extern const char *findByEmail_output_username;

#include "FlickrClient.h"
#include "String.h"

extern void test_auth_getToken(FlickrClient *c,
			       const String *frob,
			       String *token);

#endif
