/* -*- C -*- */
#include "FlickrClientImpl.h"

#include <string.h>

/* Photo URLs mapping methods */
/*
You can construct the url of a photo once you know it's id, server id and secret, as returned by many api methods.

The url takes the following format:

http://static.flickr.com/{server-id}/{id}_{secret}.jpg
	or
http://static.flickr.com/{server-id}/{id}_{secret}_[mstb].jpg
	or
http://static.flickr.com/{server-id}/{id}_{secret}_o.(jpg|gif|png)

Size Suffixes

The letter suffixes are as follows:
s	small square 75x75
t	thumbnail, 100 on longest side
m	small, 240 on longest side
-	medium, 500 on longest side
b	large, 1024 on longest side (only exists for very large original images)
o	original image, either a jpg, gif or png, depending on source format
Example


http://static.flickr.com/2/1418878_1e92283336_m.jpg

server-id: 2
photo-id: 1418878
secret: 1e92283336
size: m
*/

static FlickrPhotoFormat fmtFromString(const char *f) {
  switch(f[0]) {
  case 'g': return FORMAT_GIF;
  case 'p': return FORMAT_PNG;
  case 'j': return FORMAT_JPG;
  }
  return FORMAT_JPG;
}

  static const char *fmt(FlickrPhotoFormat f) {
    switch(f) {
    case FORMAT_GIF:
      return "gif";
    case FORMAT_PNG:
      return "png";
    case FORMAT_JPG:
    default:
      return "jpg";
    }
  }

void flickr_build_photo_url(unsigned int id, unsigned int server_id, const String *secret, FlickrPhotoSize sz, String *url)
{
  FlickrPhotoSpec spec = { id, server_id, (String*)secret, sz, FORMAT_JPG };
  flickr_build_photo_url_from_spec(&spec,url);
}

void flickr_build_photo_url_from_spec(FlickrPhotoSpec *spec, String *url) {
  const char *base_url = "http://static.flickr.com/";
  String_InitWithString(url, base_url, strlen(base_url));
  char c='m';
  
  switch(spec->m_sz) {
  case PHOTO_SZ_SMALLEST:
    break;
  case PHOTO_SZ_SMALL:
    c='s';
    break;
  case PHOTO_SZ_THUMBNAIL:
    c='t';
    break;
  case PHOTO_SZ_LARGE:
    c='b';
    break;

  case PHOTO_SZ_MEDIUM:
    String_Format(url,"http://static.flickr.com/%d/%d_%s.jpg",
		  spec->m_server_id,
		  spec->m_id,
		  spec->m_secret->m_start);
    return;
    
  case PHOTO_SZ_ORIGINAL:
  default:
    String_Format(url,"http://static.flickr.com/%d/%d_%s_o.%s",
		  spec->m_server_id,
		  spec->m_id,
		  spec->m_secret->m_start,
		  fmt(spec->m_fmt));
    return;
  }
  String_Format(url,"http://static.flickr.com/%d/%d_%s_%c.jpg",
		spec->m_server_id,
		spec->m_id,
		spec->m_secret->m_start,
		c);
}

void flickr_split_photo_url(const String *url, FlickrPhotoSpec *spec) {
  char s[50];
  char c='\0';
  char fmt[] = { '\0', '\0', '\0', '\0' };
  String *sb = spec->m_secret;

  memset(spec,0,sizeof(FlickrPhotoSpec));
  spec->m_fmt=FORMAT_JPG;
  spec->m_sz=PHOTO_SZ_MEDIUM;
  spec->m_secret = sb;

  if(4==sscanf(url->m_start,"http://static.flickr.com/%d/%d_%s_%c.jpg",
	       &spec->m_server_id,
	       &spec->m_id,
	       s,&c)) {
  CASE4:
    String_InitWithString(spec->m_secret,s,strlen(s));
    switch(c) {
    case 'm':
      spec->m_sz=PHOTO_SZ_SMALL;
      break;
    case 's':
      spec->m_sz=PHOTO_SZ_SMALLEST;
      break;
    case 't':
      spec->m_sz=PHOTO_SZ_THUMBNAIL;
      break;
    case 'b':
      spec->m_sz=PHOTO_SZ_LARGE;
      break;
    default:;
    }
    return;
  }

  if(4==sscanf(url->m_start,"http://static.flickr.com/%d/%d_%s_o.%s",
	       &spec->m_server_id,
	       &spec->m_id,
	       s,fmt)) {
    String_InitWithString(spec->m_secret,s,strlen(s));
    spec->m_fmt = fmtFromString(fmt);
    spec->m_sz = PHOTO_SZ_ORIGINAL;
    return;
  }


  if(3==sscanf(url->m_start,"http://static.flickr.com/%d/%d_%s.jpg",
	       &spec->m_server_id,
	       &spec->m_id,
	       s)) {
    char *ptr = s;
    while(ptr[0]!='_' && ptr[0]!='\0') { ++ptr; }
    if(ptr[0]=='_') {
      ptr[0]='\0';
      c=ptr[1];
      goto CASE4;
    }
    
    String_InitWithString(spec->m_secret,s,strlen(s));
    return;
  }

}
