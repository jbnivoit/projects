/* -*- C -*- */
#include "FlickrClient.h"
#include "FlickrClientImpl.h"

#include <stdlib.h>
#include <string.h>

const int flickr_debugging=0;

FlickrClient *newFlickrClient(const char apiKey[32], const char secret[16])
{
  FlickrClient *c = (FlickrClient*)malloc(sizeof(FlickrClient));
  memcpy(c->m_apiKey,apiKey,32);
  memcpy(c->m_secret,secret,16);
  c->m_apiKey[32]=0;
  c->m_secret[16]=0;

  strncpy(c->m_extras_scratchpad,
	  "license,date_upload,date_taken,owner_name,icon_server,original_format,last_update",
	  EXTRAS_SCRATCHPAD_LEN);

  c->m_auth_token_set=0;
  String_Init(&c->m_auth_token);

  return c;
}

void deleteFlickrClient(FlickrClient *client)
{
  String_Destroy(&client->m_auth_token);
  free(client);
}

const char *const flickr_REST_URI = "http://www.flickr.com/services/rest/";
const char *const flickr_UPLOAD_URI = "http://www.flickr.com/services/upload/";
const char *const flickr_AUTH_URI = "http://www.flickr.com/services/auth/";

void FlickrPerson_Init(FlickrPerson *person) {
  memset(person,0,sizeof(FlickrPerson));
  String_Init(&person->m_nsid);
  String_Init(&person->m_username);
  String_Init(&person->m_realname);
  String_Init(&person->m_location);
  String_Init(&person->m_photosurl);
  String_Init(&person->m_profileurl);
  String_Init(&person->m_firstdatetaken);
}
void FlickrPerson_Destroy(FlickrPerson *person)
{
  String_Destroy(&person->m_nsid);
  String_Destroy(&person->m_username);
  String_Destroy(&person->m_realname);
  String_Destroy(&person->m_location);
  String_Destroy(&person->m_photosurl);
  String_Destroy(&person->m_profileurl);
  String_Destroy(&person->m_firstdatetaken);
}

void noop_StartElementHandler(void *userData,
			      const XML_Char *name,
			      const XML_Char **atts)
{}

void noop_EndElementHandler(void *userData, const XML_Char *name)
{
/*   printf("end<%s>\n",name); */
}

typedef struct ExtraFlagDef ExtraFlagDef;
struct ExtraFlagDef {
  int m_flag;
  const char *m_str;
};

void buildExtrasParam(FlickrClient *c, int extras)
{
  const ExtraFlagDef flagdefs[] = {
    { LICENSE         , "license" },
    { DATE_UPLOAD     , "date_upload" },
    { DATE_TAKEN      , "date_taken" },
    { OWNER_NAME      , "owner_name" },
    { ICON_SERVER     , "icon_server" },
    { ORIGINAL_FORMAT , "original_format" },
    { LAST_UPDATE     , "last_update" }
  };
  const int sz = sizeof(flagdefs)/sizeof(flagdefs[0]);
  int i=0;

  memset(c->m_extras_scratchpad,0,EXTRAS_SCRATCHPAD_LEN);
  
  for(;i<sz;i++) {
    if(extras & flagdefs[i].m_flag)
      strcat(c->m_extras_scratchpad,flagdefs[i].m_str);
  }
}

void FlickrPhotoContext_Destroy(FlickrPhotoContext *ctx) {
  String_Destroy(&ctx->m_secret);
  String_Destroy(&ctx->m_title);
  String_Destroy(&ctx->m_url);
}
void FlickrPhotoContextResponse_Destroy(FlickrPhotoContextResponse *rp)
{
  FlickrPhotoContext_Destroy(&rp->m_prev);  
  FlickrPhotoContext_Destroy(&rp->m_next);  
}

void FlickrTag_Init(FlickrTag *tag)
{
  String_Init(&tag->m_author);
  String_Init(&tag->m_authorname);
  String_Init(&tag->m_raw);
  String_Init(&tag->m_tagbody);
}

void FlickrTag_Destroy(FlickrTag *tag)
{
  String_Destroy(&tag->m_author);
  String_Destroy(&tag->m_authorname);
  String_Destroy(&tag->m_raw);
  String_Destroy(&tag->m_tagbody);
}

void FlickrUser_Init(FlickrUser *user) {
  String_Init(&user->m_nsid);
  String_Init(&user->m_username);
  String_Init(&user->m_fullname);
}
void FlickrUser_Destroy(FlickrUser *user) {
  String_Destroy(&user->m_nsid);
  String_Destroy(&user->m_username);
  String_Destroy(&user->m_fullname);
}
void FlickrUser_Copy(FlickrUser *dest, const FlickrUser *src) {
  String_Copy(&dest->m_nsid,&src->m_nsid);
  String_Copy(&dest->m_username,&src->m_username);
  String_Copy(&dest->m_fullname,&src->m_fullname);
}

void FlickrBlog_Init(FlickrBlog *p)
{
  String_Init(&p->m_id);
  String_Init(&p->m_name);
  p->m_needspassword=0;
  String_Init(&p->m_url);
}

void FlickrBlog_Destroy(FlickrBlog *p)
{
  String_Destroy(&p->m_id);
  String_Destroy(&p->m_name);
  p->m_needspassword=0;
  String_Destroy(&p->m_url);
}

size_t writeToParser(void *source, size_t sz, size_t nmemb, void *userData)
{
/*   XML_Parser parser = ((rspParser*)userData)->m_parser; */
  XML_Parser parser = (XML_Parser)userData;
/*   printf("%s",(char*)source); */
  XML_Parse(parser,source,sz*nmemb,0);
  return sz*nmemb;
}

void rsp_StartElementHandler(void *userData,
					   const XML_Char *name,
					   const XML_Char **atts)
/* parse errors such as:
<?xml version="1.0" encoding="utf-8" ?>
<rsp stat="fail">
        <err code="96" msg="Invalid signature" />
</rsp>
*/
{
  rspParser *rp = (rspParser*)userData;

  if(strcmp(name,"err")==0) {

    while(*atts!=NULL) {
      if( strcmp(*atts,"code")==0 ) {
	atts++;
	rp->m_code = atoi(*atts);
	break;
      }
      atts++;
    }
  }     
}

void FlickrContact_Init(FlickrContact *contact)
{
  memset(contact,0,sizeof(FlickrContact));
  String_Init(&contact->m_nsid);
  String_Init(&contact->m_username);
  String_Init(&contact->m_realname);
}

void FlickrContact_Destroy(FlickrContact *contact)
{
  String_Destroy(&contact->m_nsid);
  String_Destroy(&contact->m_username);
  String_Destroy(&contact->m_realname);
}

static void rsp_response_StartElementHandler(void *userData,
					     const XML_Char *name,
					     const XML_Char **atts)
{
  rspParser *rp = (rspParser*)userData;

  if(strcmp(name,"rsp")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"stat")==0 ) {
	atts++;
	rp->m_code = strcmp(*atts,"ok")==0?0:1;
	break;
      }
      atts++;
    }
  }
  if(rp->m_start!=NULL)
    (*rp->m_start)(userData,name,atts);
}

void rsp_SetElementHandler(rspParser *p,
			   XML_StartElementHandler start,
			   XML_EndElementHandler end)
{
  p->m_start = start;
  XML_SetElementHandler(p->m_parser,
			&rsp_response_StartElementHandler,
			end);
}

void rsp_SetUserData(rspParser *p, void *userData)
{
  XML_SetUserData(p->m_parser,userData);
}

void rsp_ParserCreate(rspParser *p)
{
  p->m_parser = XML_ParserCreate(NULL);
  XML_SetUserData(p->m_parser, p);
}

void rsp_ParserFree(rspParser *p)
{
  XML_Parse(p->m_parser,&p->dummy,0,1);
  XML_ParserFree(p->m_parser);
  p->m_parser=NULL;
}

void rsp_SetCharacterDataHandler(rspParser *p,
				 XML_CharacterDataHandler handler)
{
  XML_SetCharacterDataHandler(p->m_parser,handler);
}

void resetCursor(FlickrClient *client) { client->m_cursor=0; }

const char *makeIntString(FlickrClient *client, unsigned int val) {
  char *p = client->m_extras_scratchpad+client->m_cursor;
  sprintf(p,"%d",val);
  client->m_cursor += strlen(p);
  return p;
}
const char *makeTimeString(FlickrClient *client, time_t val) {
  return makeIntString(client,val);
}

static const char *separatedList(const char *separator,
			  FlickrClient *client,
			  const String *tickets,
			  unsigned int sz)
{
  unsigned int i=0;
  resetCursor(client);
  {
    char *p = client->m_extras_scratchpad+client->m_cursor;
    for(;i<sz;i++) {
      strcpy(p, tickets[i].m_start);
      if(i<sz-1)
	strcat(p,separator);
    }
    return client->m_extras_scratchpad+client->m_cursor;
  }
}

const char *commaSeparatedList(FlickrClient *client,
			       const String *tickets,
			       unsigned int sz)
{
  return separatedList(",",client,
		       tickets,
		       sz);
}

static int compareTime_t(const void *a, const void *b)
{
  return *(time_t*)a > *(time_t*)b ;
}

const char *commaSeparatedListOfDates(FlickrClient *client,
				      unsigned int dates_count,
				      time_t *dates)
{
  if(dates_count==0) return NULL;

  qsort(dates, dates_count, sizeof(time_t),&compareTime_t);

  resetCursor(client);
  {
    unsigned int i=0;
    char *p = client->m_extras_scratchpad+client->m_cursor;
    for(;i<dates_count;i++) {
      char buf[20];
      sprintf(&buf[0],"%ld",dates[i]);
      strcpy(p, &buf[0]);
      if(i<dates_count-1)
	strcat(p,",");
    }
    return client->m_extras_scratchpad+client->m_cursor;
  }
}

const char *spaceSeparatedList(FlickrClient *client,
			       const String *tickets,
			       unsigned int sz)
{
  return separatedList(" ",client,
		       tickets,
		       sz);
}

void rsp_SetDefaultElementHandler(rspParser *p)
/* using these default tag handlers, we can parse the rsp tag for ok/fail return code */
{
  rsp_SetElementHandler(p,NULL,noop_EndElementHandler);
}

FlickrPerm permFromString(const String *p)
{
  if(strcmp(p->m_start,"none")==0) return PERM_NONE;
  if(strcmp(p->m_start,"read")==0) return PERM_READ;
  if(strcmp(p->m_start,"write")==0) return PERM_WRITE;
  if(strcmp(p->m_start,"delete")==0) return PERM_DELETE;
  
  return PERM_NONE;
}

const char *booleanFlag(unsigned char val)
{
  return val==0?"0":"1";
}

const char *permFlag(FlickrPermScope val) {
  switch(val) {
  case PERM_EVERYBODY:          return "3";
  case PERM_CONTACTS:           return "2";
  case PERM_FRIENDS_AND_FAMILY: return "1";
  case PERM_NOBODY: default:    return "0";
  }
}

const char *sortOrder(FlickrSortOrder s)
{
  switch(s) {
  case SORT_DATE_POSTED_ASC:
    return "date-posted-asc";
  case SORT_DATE_TAKEN_ASC:
    return "date-taken-asc";
  case SORT_DATE_TAKEN_DESC:
    return "date-taken-desc";
  case SORT_INTERESTINGNESS_DESC:
    return "interestingness-desc";
  case SORT_INTERESTINGNESS_ASC:
    return "interestingness-asc";
  case SORT_RELEVANCE:
    return "relevance";
    
  case SORT_DATE_POSTED_DESC: // this one is the default, per http://www.flickr.com/services/api/flickr.photos.search.html
  default: 
    return "date-posted-desc";
  }  
}

void FlickrPhotoOwner_Init(FlickrPhotoOwner *p) {
  String_Init(&p->m_nsid);
  String_Init(&p->m_username);
  String_Init(&p->m_realname);
  String_Init(&p->m_location);
}

void FlickrPhotoOwner_Destroy(FlickrPhotoOwner *p) {
  String_Destroy(&p->m_nsid);
  String_Destroy(&p->m_username);
  String_Destroy(&p->m_realname);
  String_Destroy(&p->m_location);
}

void FlickrPhotoDates_Init(FlickrPhotoDates *p) {
  String_Init(&p->m_taken);
}
void FlickrPhotoDates_Destroy(FlickrPhotoDates *p) {
  String_Destroy(&p->m_taken);
}

void FlickrPhotoInfo_Init(FlickrPhotoInfo *info)
{
  memset(info,0,sizeof(info));

  String_Init(&info->m_id);
  String_Init(&info->m_secret);
  String_Init(&info->m_server);
  
  FlickrPhotoOwner_Init(&info->m_owner);
  String_Init(&info->m_title);
  String_Init(&info->m_description);
  FlickrPhotoDates_Init(&info->m_dates);

  String_Init(&info->m_photopage);

  memset(info,0,sizeof(info));
}

void FlickrPhotoInfo_Destroy(FlickrPhotoInfo *info)
{
  String_Destroy(&info->m_id);
  String_Destroy(&info->m_secret);
  String_Destroy(&info->m_server);
  
  FlickrPhotoOwner_Destroy(&info->m_owner);
  String_Destroy(&info->m_title);
  String_Destroy(&info->m_description);
  FlickrPhotoDates_Destroy(&info->m_dates);

  String_Destroy(&info->m_photopage);

  free(&info->m_notes);
  free(&info->m_tags);
}

void FlickrPhotoNote_Init(FlickrPhotoNote *p) {
  memset(p,0,sizeof(FlickrPhotoNote));
  String_Init(&p->text);
  String_Init(&p->m_id);
  String_Init(&p->m_author);
  String_Init(&p->m_authorname);
}

void FlickrPhotoNote_Destroy(FlickrPhotoNote *p) {
  String_Destroy(&p->text);
  String_Destroy(&p->m_id);
  String_Destroy(&p->m_author);
  String_Destroy(&p->m_authorname);
}

void FlickrSize_Init(FlickrSize *p)
{
  memset(p,0,sizeof(p));
  String_Init(&p->m_label);
  String_Init(&p->m_source);
  String_Init(&p->m_url);
}

void FlickrSize_Destroy(FlickrSize *p) {
  String_Destroy(&p->m_label);
  String_Destroy(&p->m_source);
  String_Destroy(&p->m_url);
}


const char *concatenateStrings(const unsigned int sz,
			       const String *items,
			       String *scratch)
{
  unsigned int i=0;
  for(;i<sz;i++) {
    String_AppendOther(scratch, &items[i]);
    if(i+1<sz)
      String_Append(scratch, ",", 1);
  }
  return scratch->m_start;
}

const char *perm(FlickrPerm val) {

  switch(val) {
  case PERM_READ: return "read";
  case PERM_WRITE: return "write";
  case PERM_DELETE: return "delete";
  case PERM_NONE: 
  default:
    return "none";
  }
}

void FlickrSearchCriteria_Init(FlickrSearchCriteria *c)
{
  memset(c,0,sizeof(FlickrSearchCriteria));
  String_Init(&c->m_user_id);
  c->m_tagmode=TAG_MODE_ALL;
  String_Init(&c->m_text); 
  FlickrDateSearchCriteria_Init(&c->m_date_criteria);
}

void FlickrSearchCriteria_Destroy(FlickrSearchCriteria *c)
{
  String_Destroy(&c->m_user_id);
/*   free(c->m_tags); */
  String_Destroy(&c->m_text); 
  FlickrDateSearchCriteria_Destroy(&c->m_date_criteria);
}

void FlickrDateSearchCriteria_Init(FlickrDateSearchCriteria *c) {
  memset(c,0,sizeof(FlickrSearchCriteria));
}
void FlickrDateSearchCriteria_Destroy(FlickrDateSearchCriteria *c) {
  memset(c,0,sizeof(FlickrSearchCriteria));
}
