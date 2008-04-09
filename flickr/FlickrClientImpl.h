/* -*- C -*- */
#ifndef _FlickrClientImpl_H
#define _FlickrClientImpl_H

#include "FlickrClient.h"

#include <stdlib.h> /* provides size_t */
#include <curl/curl.h>
#include <curl/types.h>
#include <curl/easy.h>

#include <expat.h>

struct FlickrClient
{
  char m_apiKey[32+1];
#define FLICKR_SECRET_LEN 16
  char m_secret[FLICKR_SECRET_LEN+1];
#define EXTRAS_SCRATCHPAD_LEN 100
  char m_extras_scratchpad[EXTRAS_SCRATCHPAD_LEN]; /* 100 because it's an upper bound for the max length of the 'extras' flags. */
  unsigned int m_cursor;
  
  unsigned char m_auth_token_set;
  String m_auth_token;
};

/* when this is set to 1, it turns on curl debugging */
extern const int flickr_debugging;

extern void resetCursor(FlickrClient *client);
extern const char *makeIntString(FlickrClient *client, unsigned int val);
extern const char *makeTimeString(FlickrClient *client, time_t val);

extern const char *const flickr_REST_URI;
extern const char *const flickr_UPLOAD_URI;
extern const char *const flickr_AUTH_URI;

extern size_t printReplyCb(void *source, size_t sz, size_t nmemb, void *userData);

extern void FlickrRequest(const char *uri,
		   struct curl_httppost *formpost, 
		   void *userData, 
		   size_t (*cb)(void *source, size_t sz, size_t nmemb, void *userData),
		   unsigned char multipart,
		   void *pUserData,
		   void (*progress_cb)(void *pUserData, size_t sz));

extern void flickr_request(FlickrClient *client, const char *method,
			   void *userData, 
			   size_t (*cb)(void *source, size_t sz, size_t nmemb, void *userData),
			   const FlickrRequestArg args[], const unsigned int argsz);

extern void flickr_request_upload(FlickrClient *client, const char *uri,
			   const String *file,
			   void *userData,
			   size_t (*parse_output_cb)(void *source, 
						     size_t sz, size_t nmemb, void *userData),
			   void *pUserData,
			   void (*progress_cb)(void *pUserData, size_t sz),
			   const FlickrRequestArg args[], const unsigned int argsz);

extern void FlickrPerson_Init(FlickrPerson *person);
extern void FlickrPerson_Destroy(FlickrPerson *person);

extern void FlickrBlog_Init(FlickrBlog *person);
extern void FlickrBlog_Destroy(FlickrBlog *person);

extern void noop_StartElementHandler(void *userData,
				     const XML_Char *name,
				     const XML_Char **atts);
extern void noop_EndElementHandler(void *userData, const XML_Char *name);

extern void buildExtrasParam(FlickrClient *c, int extras);

typedef struct FlickrPhotoContextResponse FlickrPhotoContextResponse;
struct FlickrPhotoContextResponse {
  FlickrPhotoContext m_prev;
  FlickrPhotoContext m_next;
};
extern void FlickrPhotoContextResponse_Destroy(FlickrPhotoContextResponse *rp);
extern void FlickrPhotoContext_Destroy(FlickrPhotoContext *ctx);

extern void FlickrTag_Init(FlickrTag *tag);
extern void FlickrTag_Destroy(FlickrTag *tag);

extern void FlickrContact_Init(FlickrContact *contact);
extern void FlickrContact_Destroy(FlickrContact *contact);

extern void FlickrPhotoInfo_Init(FlickrPhotoInfo *info);
extern void FlickrPhotoInfo_Destroy(FlickrPhotoInfo *info);

extern void FlickrPhotoOwner_Init(FlickrPhotoOwner *p);
extern void FlickrPhotoOwner_Destroy(FlickrPhotoOwner *p);

extern void FlickrPhotoDates_Init(FlickrPhotoDates *p);
extern void FlickrPhotoDates_Destroy(FlickrPhotoDates *p);

extern void FlickrPhotoNote_Init(FlickrPhotoNote *p);
extern void FlickrPhotoNote_Destroy(FlickrPhotoNote *p);

extern void FlickrSize_Init(FlickrSize *p);
extern void FlickrSize_Destroy(FlickrSize *p);

extern void hex(unsigned char in[16], char out[32]);

typedef struct rspParser rspParser;
struct rspParser {
  char dummy;
  XML_Parser m_parser;
  XML_StartElementHandler m_start;
  unsigned int m_code;
};

extern size_t writeToParser(void *source, size_t sz, size_t nmemb, void *userData);

extern void rsp_ParserCreate(rspParser *p);
extern void rsp_ParserFree(rspParser *p);

extern void rsp_StartElementHandler(void *userData,
				    const XML_Char *name,
				    const XML_Char **atts);

extern void rsp_SetDefaultElementHandler(rspParser *p);

extern void rsp_SetElementHandler(rspParser *p,
				  XML_StartElementHandler start,
				  XML_EndElementHandler end);
extern void rsp_SetUserData(rspParser *p, void *userData);

extern void rsp_SetCharacterDataHandler(rspParser *p,
					XML_CharacterDataHandler handler);

extern const char *commaSeparatedList(FlickrClient *client,
				      const String *tickets,
				      unsigned int sz);

extern const char *spaceSeparatedList(FlickrClient *client,
				      const String *tickets,
				      unsigned int sz);

extern const char *commaSeparatedListOfDates(FlickrClient *client,
					     unsigned int dates_count,
					     time_t *dates);

extern const char *concatenateStrings(const unsigned int photo_ids_sz,
				      const String *photo_ids,
				      String *scratch);

#define flickr_request_rsp(c,m,p,r) flickr_request(c,m,p.m_parser,&writeToParser,r,sizeof(r)/sizeof(r[0]))
#define flickr_request_rsp0(c,m,p) flickr_request(c,m,p.m_parser,&writeToParser,NULL,0)

extern FlickrPerm permFromString(const String *p);			       

extern const char *dateTakenGranularity(unsigned int date_taken_granularity);
extern const char *date(FlickrClient *client, time_t dateval);
extern const char *intFlag(FlickrClient *client, unsigned int val);
extern const char *booleanFlag(unsigned char val);
extern const char *permFlag(FlickrPermScope val);
extern const char *perm(FlickrPerm val);
extern const char *sortOrder(FlickrSortOrder s);

#define CHECK_ARG(x) { if(!(x)) return FLICKR_INVALID_ARG; }

typedef struct getListArg getListArg;
struct getListArg {
  rspParser m_super;
  void *m_userData;
  void (*m_cb)(void *userData, const FlickrResultPage *page,
	       unsigned int offset, const FlickrPhoto *photo);

  FlickrResultPage m_page;
  unsigned int m_offset;
  FlickrPhoto m_photo;
};

extern void favorites_getPublicList_StartElementHandler(void *userData,
							const XML_Char *name,
							const XML_Char **atts);

#endif
