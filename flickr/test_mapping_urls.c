/* -*- C -*- */
#include "FlickrClient.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
  String sb,sb2,secret;
  const char *URL = "http://static.flickr.com/2/1418878_1e92283336_m.jpg";
  const char *SECRET = "1e92283336";
  String where;
  FlickrPhotoSpec spec;

  spec.m_secret = &where;
  
  String_InitWithString(&sb, URL, strlen(URL));
  String_InitWithString(&sb2, SECRET, strlen(SECRET));
  flickr_split_photo_url(&sb, &spec);

  String_InitWithOther(&secret, spec.m_secret);

  if(spec.m_server_id==2 &&
     spec.m_id == 1418878 &&
     String_Compare(&secret,&sb2) &&
     spec.m_sz==PHOTO_SZ_SMALL)
    return EXIT_SUCCESS;

  printf("failure\n");
  return EXIT_FAILURE;
}

