/* -*- C -*- */
#include "FlickrClientImpl.h"
#include "FlickrXmlHandler.h"

#include <string.h>

#include "Stack.h"

#define flickr_photos_request(c,m,r) flickr_photos_request_impl(c,m,r,sizeof(r)/sizeof(r[0]))

static FlickrResult flickr_photos_request_impl(FlickrClient *client,
					       const char *method,
					       const FlickrRequestArg *reqargs,
					       unsigned int sz)
{
  rspParser p;
  
  rsp_ParserCreate(&p);
  rsp_SetElementHandler(&p,NULL,noop_EndElementHandler);
  
  flickr_request(client, method,p.m_parser,&writeToParser,reqargs,sz);
  
  rsp_ParserFree(&p);
  return p.m_code;
}

FlickrResult flickr_photos_addTags(FlickrClient *client,
				   const FlickrPhotoId *photo_id,
				   unsigned int count,
				   String *tags)
{
  const FlickrRequestArg reqarg[] = {
    { "photo_id", photo_id->m_start },
    { "tags", commaSeparatedList(client,tags,count) }
  };

  return flickr_photos_request(client, "flickr.photos.addTags",reqarg);
  /* FIXME requires authentication with write permission */
}

FlickrResult flickr_photos_delete(FlickrClient *client,
				  const FlickrPhotoId *photo_id)
{
  const FlickrRequestArg reqarg[] = {
    { "photo_id", photo_id->m_start },
  };
  
  return flickr_photos_request(client, "flickr.photos.delete",reqarg);
  /* FIXME requires authentication with delete permission */
}

FlickrResult flickr_photos_removeTag(FlickrClient *client,
				     const String *tag_id)
{
  const FlickrRequestArg reqarg[] = {
    { "tag_id", tag_id->m_start },
  };

  return flickr_photos_request(client, "flickr.photos.removeTag",reqarg);
  /* FIXME requires authentication with delete permission */
}

static void setRequestArg(const FlickrRequestArg *what, FlickrRequestArg *where)
{
  where->m_arg = what->m_arg;
  where->m_value = what->m_value;
}

FlickrResult flickr_photos_setDates(FlickrClient *client,
				    const FlickrPhotoId *photo_id,
				    FlickrArgMask mask,
				    time_t date_posted,
				    time_t date_taken,
				    unsigned int date_taken_granularity)
{
  resetCursor(client);
  {
    FlickrRequestArg arg1 = { "date_posted" ,            date(client, date_posted) };
    FlickrRequestArg arg2 = { "date_taken" ,             date(client, date_taken)  };
    FlickrRequestArg arg3 = { "date_taken_granularity" , dateTakenGranularity(date_taken_granularity) };
    FlickrRequestArg reqarg[] = {
      { "photo_id", photo_id->m_start },
      { NULL, NULL },
      { NULL, NULL },
      { NULL, NULL }
    };
    unsigned int idx=1;
    
#define addToRequestArgs(a,r,i) { setRequestArg(&a,&r[i]); i++; }
    if(mask&ARG_1) addToRequestArgs(arg1,reqarg,idx);
    if(mask&ARG_2) addToRequestArgs(arg2,reqarg,idx);
    if(mask&ARG_3) addToRequestArgs(arg3,reqarg,idx);
    
    return flickr_photos_request_impl(client,"flickr.photos.setDate",reqarg,idx);
  }
  /* FIXME requires authentication with write permission */
}

FlickrResult flickr_photos_setMeta(FlickrClient *client,
				   const FlickrPhotoId *photo_id,
				   const String *title,
				   const String *description)
{
  const FlickrRequestArg reqarg[] = {
    { "photo_id",    photo_id->m_start },
    { "title",       title->m_start },
    { "description", description->m_start },
  };

  return flickr_photos_request(client, "flickr.photos.setMeta",reqarg);
  /* FIXME requires authentication with write permission */
}


FlickrResult flickr_photos_setPerms(FlickrClient *client,
				    const FlickrPhotoId *photo_id,
				    const FlickrPhotoVisibility *scope,
				    FlickrPermScope perm_comment,
				    FlickrPermScope perm_addmeta)
{
  const FlickrRequestArg reqarg[] = {
    { "photo_id",     photo_id->m_start },
    { "is_public",    booleanFlag(scope->m_is_public) },
    { "is_friend",    booleanFlag(scope->m_is_friend) },
    { "is_family",    booleanFlag(scope->m_is_family) },
    { "perm_comment", permFlag(perm_comment) },
    { "perm_addmeta", permFlag(perm_addmeta) },
  };
  
  return flickr_photos_request(client, "flickr.photos.setPerms",reqarg);
  /* FIXME requires authentication with write permission */
}

FlickrResult flickr_photos_setTags(FlickrClient *client,
				   const FlickrPhotoId *photo_id,
				   const String *tags,
				   unsigned int tagssz)
{
  const FlickrRequestArg reqarg[] = {
    { "photo_id", photo_id->m_start },
    { "tags", spaceSeparatedList(client,tags,tagssz) }
  };

  return flickr_photos_request(client, "flickr.photos.setTags",reqarg);
  /* FIXME requires authentication with write permission */
}

typedef enum {
  PARSING_UNKNOWN=0,

  PARSING_PHOTO,
  PARSING_OWNER,
  PARSING_VISIBILITY,
  PARSING_DATES,
  PARSING_PERMISSIONS,
  PARSING_EDITABILITY,

  PARSING_TITLE,
  PARSING_DESCRIPTION,
  PARSING_COMMENTS,
  PARSING_NOTE,
  PARSING_TAG,
  PARSING_URL
} getInfoParsing;

#define in_word_set flickr_photos_getInfo_in_word_set
#include "flickr_photos_getInfo_gperf.c"

static getInfoParsing StateFromElement(const XML_Char *tag) {
  const struct GetInfoElement * key = in_word_set (tag, strlen(tag));
  if(key==NULL) return PARSING_UNKNOWN;
  return key->val;
}

typedef struct getInfoArg getInfoArg;
struct getInfoArg {
  rspParser m_super;
  getInfoParsing m_parsing_state;
  
  FlickrPhotoInfo m_info;

  /* working area for note/tag lists */
  Stack m_notes_stack;
  Stack m_tags_stack;
};

static void getInfoArg_Init(getInfoArg *p) {
  memset(p,0,sizeof(p));
  FlickrPhotoInfo_Init(&p->m_info);
  Stack_Init(&p->m_notes_stack);
  Stack_Init(&p->m_tags_stack);
}

static void getInfoArg_Destroy(getInfoArg *p) {
  FlickrPhotoInfo_Destroy(&p->m_info);  
  Stack_destroy(&p->m_notes_stack, (void (*)(void *))&FlickrPhotoNote_Destroy);
  Stack_destroy(&p->m_tags_stack, (void (*)(void *))&FlickrTag_Destroy);
}

static void getInfo_EndElementHandler(void *userData,
				      const XML_Char *name)
{
  getInfoArg *rp = (getInfoArg*)userData;

  switch(rp->m_parsing_state) {
  case PARSING_TAG:  break;
  case PARSING_NOTE: break;

  case PARSING_UNKNOWN:
  case PARSING_PHOTO:
  case PARSING_OWNER:
  case PARSING_VISIBILITY:
  case PARSING_DATES:
  case PARSING_PERMISSIONS:
  case PARSING_EDITABILITY:
  case PARSING_TITLE:
  case PARSING_DESCRIPTION:
  case PARSING_COMMENTS:
  case PARSING_URL:
  default:;
  }
  
  rp->m_parsing_state=PARSING_UNKNOWN;
}

static void getInfo_StartElementHandler(void *userData,
					const XML_Char *name,
					const XML_Char **atts)
{
  getInfoArg *rp = (getInfoArg*)userData;
  rp->m_parsing_state = StateFromElement(name);

  switch(rp->m_parsing_state) {
  case PARSING_PHOTO:
    {
      matchXmlAttr matches[] = {
	{ "id",             XML_STRING, { &rp->m_info.m_id } },
	{ "secret",         XML_STRING, { &rp->m_info.m_secret } }, 
	{ "server",         XML_STRING, { &rp->m_info.m_server } }, 
	{ "isfavorite",     XML_UC,     { uc: &rp->m_info.m_isfavorite } },
	{ "license",        XML_UI,     { ui: &rp->m_info.m_license } },
	{ "rotation",       XML_UI,     { ui: &rp->m_info.m_rotation } }, 
	{ "originalformat", XML_UI,     { ui: &rp->m_info.m_originalformat } }, 
      };
      extractAttrValues(matches,atts);
    } break;
  case PARSING_OWNER:
    {
      matchXmlAttr matches[] = {
	{ "nsid",             XML_STRING, { &rp->m_info.m_owner.m_nsid } },
	{ "username",         XML_STRING, { &rp->m_info.m_owner.m_username } }, 
	{ "realname",         XML_STRING, { &rp->m_info.m_owner.m_realname } }, 
	{ "location",         XML_STRING, { &rp->m_info.m_owner.m_location } }, 
      };
      extractAttrValues(matches,atts);
    } break;
  case PARSING_VISIBILITY:
    {
      matchXmlAttr matches[] = {
	{ "ispublic", XML_UC, { uc: &rp->m_info.m_visibility.m_is_public } },
	{ "isfriend", XML_UC, { uc: &rp->m_info.m_visibility.m_is_friend } },
	{ "isfamily", XML_UC, { uc: &rp->m_info.m_visibility.m_is_family } },
      };
      extractAttrValues(matches,atts);
    } break;
  case PARSING_DATES:
    {
      matchXmlAttr matches[] = {
	{ "posted",           XML_TIME,   { t: &rp->m_info.m_dates.m_posted } },
	{ "taken" ,           XML_STRING, { &rp->m_info.m_dates.m_taken } },
	{ "takengranularity", XML_UC,     { uc: &rp->m_info.m_dates.m_takengranularity } },
	{ "lastupdate",       XML_TIME,   { t: &rp->m_info.m_dates.m_lastupdate } }
      };
      extractAttrValues(matches,atts);
    } break;
  case PARSING_PERMISSIONS:
    {
      matchXmlAttr matches[] = {
	{ "permcomment", XML_UC, { uc: (unsigned char*)&rp->m_info.m_permcomment } },
	{ "permaddmeta", XML_UC, { uc: (unsigned char*)&rp->m_info.m_permaddmeta } }
      };
      extractAttrValues(matches,atts);
    } break;
  case PARSING_EDITABILITY:
    {
      matchXmlAttr matches[] = {
	{ "cancomment", XML_UC, { uc: &rp->m_info.m_cancomment } },
	{ "canaddmeta", XML_UC, { uc: &rp->m_info.m_canaddmeta } }
      };
      extractAttrValues(matches,atts);
    } break;
  case PARSING_NOTE:
    {
      FlickrPhotoNote *note = (FlickrPhotoNote*)malloc(sizeof(FlickrPhotoNote));
      matchXmlAttr matches[] = {
	{ "id",         XML_STRING, { &note->m_id } },
	{ "author",     XML_STRING, { &note->m_author } },
	{ "authorname", XML_STRING, { &note->m_authorname } },
	{ "x",          XML_UI,     { ui: &note->x } },
	{ "y",          XML_UI,     { ui: &note->y } },
	{ "w",          XML_UI,     { ui: &note->w } },
	{ "h",          XML_UI,     { ui: &note->h } },
      };
      extractAttrValues(matches,atts);

      /* <note id="313" author="12037949754@N01" authorname="Bees" x="10" y="10" w="50" h="50">foo</note> */
      Stack_push(&rp->m_notes_stack,note);
      
    } break;
  case PARSING_TAG:
    {
      FlickrTag *tag = (FlickrTag*)malloc(sizeof(FlickrTag));
      matchXmlAttr matches[] = {
	{ "id",         XML_UI,     { ui: &tag->m_id } },
	{ "author",     XML_STRING, { &tag->m_author } },
	{ "raw",        XML_STRING, { &tag->m_authorname } },
      };
      extractAttrValues(matches,atts);

      Stack_push(&rp->m_tags_stack,tag);
      
      /* <tag id="1234" author="12037949754@N01" raw="woo yay">wooyay</tag> */
    } break;
  case PARSING_URL:
    /*
      {
      matchXmlAttr matches[] = {
      { "type", XML_STRING, { &rp->m_info.m_photopage } }
      };
      extractAttrValues(matches,atts);
      } break; 
      <url>http://www.flickr.com/photos/bees/2733/</url> 
    */
  default:;
  }
}

static void getInfo_CharacterDataHandler (void *userData,
					  const XML_Char *s,
					  int len)
{
  getInfoArg *rp = (getInfoArg*)userData;
  switch(rp->m_parsing_state) {
#define HANDLE_CASE(a,b) case PARSING_##a: String_Append(&rp->m_info.m_##b,s,len); break
    HANDLE_CASE(TITLE,title);
    HANDLE_CASE(DESCRIPTION,description);
    /*     HANDLE_CASE(COMMENTS,comments); */
    HANDLE_CASE(URL,photopage);
#undef HANDLE_CASE

  case PARSING_NOTE: {
    FlickrPhotoNote *note = (FlickrPhotoNote*)Stack_top(&rp->m_notes_stack);
    String_Append(&note->text,s,len); 
  } break;
  case PARSING_TAG: {
    FlickrTag *tag = (FlickrTag*)Stack_top(&rp->m_tags_stack);
    String_Append(&tag->m_tagbody,s,len); 
  } break;

  default:;
  }
}

FlickrResult flickr_photos_getInfo(FlickrClient *client,
				   const FlickrPhotoId *photo_id,
				   const String *secret,
				   void *userData,
				   void (*cb)(void *userData,
					      const FlickrPhotoInfo *info))
{
  getInfoArg p;
  const FlickrRequestArg reqarg[] = {
    { "photo_id", photo_id->m_start },
    { "secret",   secret==NULL?"":secret->m_start }
  };
  const unsigned int reqargsz = secret==NULL?1:2;
  CHECK_ARG(photo_id!=NULL);
  
  getInfoArg_Init(&p);
  rsp_ParserCreate(&p.m_super);

  rsp_SetElementHandler(&p.m_super,getInfo_StartElementHandler,getInfo_EndElementHandler);
  rsp_SetCharacterDataHandler(&p.m_super, &getInfo_CharacterDataHandler);
  
  flickr_request(client, "flickr.photos.getInfo",
		 p.m_super.m_parser, &writeToParser,
		 reqarg, reqargsz);
  
  rsp_ParserFree(&p.m_super);

  p.m_info.m_notes = NULL;
  p.m_info.m_notes_sz = Stack_size(&p.m_notes_stack);
  if(p.m_info.m_notes_sz>0)
    p.m_info.m_notes = (FlickrPhotoNote **)malloc(sizeof(FlickrPhotoNote *)*p.m_info.m_notes_sz);

  p.m_info.m_tags = NULL;
  p.m_info.m_tags_sz = Stack_size(&p.m_tags_stack);
  if(p.m_info.m_tags_sz>0)
    p.m_info.m_tags = (FlickrTag **)malloc(sizeof(FlickrTag *)*p.m_info.m_tags_sz);

  (*cb)(userData,&p.m_info);
  
  getInfoArg_Destroy(&p);
  return p.m_super.m_code;
}

typedef struct getSizesArg getSizesArg;
struct getSizesArg {
  rspParser m_super;
  void *m_userData;
  void (*m_cb)(void *userData, const FlickrSize *sz);
};

static void getSizesArg_Init(getSizesArg *p,
			     void *userData,
			     void (*cb)(void *userData, const FlickrSize *sz))
{
  rsp_ParserCreate(&p->m_super);
  p->m_userData = userData;
  p->m_cb = cb;
}

static void getSizes_StartElementHandler(void *userData,
					 const XML_Char *name,
					 const XML_Char **atts)
{
  getSizesArg *rp = (getSizesArg*)userData;
  
  if(strcmp(name,"size")==0) {
    FlickrSize sz;
    FlickrSize_Init(&sz);    
    
    {
      matchXmlAttr matches[] = {
	{ "label",  XML_STRING, { &sz.m_label } },
	{ "width",  XML_UI,     { ui: &sz.m_width } }, 
	{ "height", XML_UI,     { ui: &sz.m_height } }, 
	{ "source", XML_STRING, { &sz.m_source } },
	{ "url",    XML_STRING, { &sz.m_url } },
      };
      extractAttrValues(matches,atts);
    }
    (*rp->m_cb)(rp->m_userData,&sz);
    FlickrSize_Destroy(&sz);    
  }
}  

FlickrResult flickr_photos_getSizes(FlickrClient *client,
				    const FlickrPhotoId *photo_id,
				    void *userData,
				    void (*cb)(void *userData, const FlickrSize *sz))
{
  getSizesArg p;
  const FlickrRequestArg reqarg[] = {
    { "photo_id", photo_id->m_start },
  };
  CHECK_ARG(photo_id!=NULL);
  
  getSizesArg_Init(&p,userData,cb);

  rsp_SetElementHandler(&p.m_super,getSizes_StartElementHandler,noop_EndElementHandler);
  
  flickr_request_rsp(client, "flickr.photos.getSizes", p.m_super, reqarg);
  
  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}

static FlickrResult flickr_photos_get(FlickrClient *client,
				      const char *method,
				      FlickrDateSearchCriteria *criteria,
				      FlickrPhotoExtras extras,
				      unsigned int per_page,
				      unsigned int page,
				      void *userData,
				      void (*cb)(void *userData, 
						 const FlickrResultPage *page,
						 unsigned int offset, 
						 const FlickrPhoto *photo))
/*
 * almost the same 'flickr_favorites_get'.
 */
{
  getListArg fav;
  char buf_per_page[20], buf_page[20];

  if(per_page==0) per_page=500;
  if(page==0) page=1;
  memset(&fav,0,sizeof(getListArg));
  fav.m_userData=userData;
  fav.m_cb=cb;

  sprintf(&buf_per_page[0],"%d",per_page);
  sprintf(&buf_page[0],"%d",page);
  buildExtrasParam(client, extras);
  {
    const FlickrRequestArg reqarg[] = {
      { "extras",   client->m_extras_scratchpad },
      { "per_page", &buf_per_page[0] },
      { "page",     &buf_page[0] },

      { "min_upload_date", criteria==NULL?"":makeTimeString(client,criteria->m_min_upload_date) },
      { "max_upload_date", criteria==NULL?"":makeTimeString(client,criteria->m_max_upload_date) },
      { "min_taken_date",  criteria==NULL?"":makeTimeString(client,criteria->m_min_taken_date) },
      { "max_taken_date",  criteria==NULL?"":makeTimeString(client,criteria->m_max_taken_date) }
    };
    unsigned int sz = criteria==NULL?3:7;
    unsigned char dummy=0;

    fav.m_super.m_parser = XML_ParserCreate(NULL);
    rsp_SetUserData(&fav.m_super, &fav);

    rsp_SetElementHandler(&fav.m_super,favorites_getPublicList_StartElementHandler,noop_EndElementHandler);
    
    flickr_request(client, method,
		   &fav.m_super.m_parser,&writeToParser,reqarg,sz);
  
    XML_Parse(fav.m_super.m_parser,&dummy,0,1);
    XML_ParserFree(fav.m_super.m_parser);
    return 0;
  }
}

FlickrResult flickr_photos_getRecent(FlickrClient *client,
				     FlickrPhotoExtras extras,
				     unsigned int per_page,
				     unsigned int page,
				     void *userData,
				     void (*cb)(void *userData, 
						const FlickrResultPage *page,
						unsigned int offset, 
						const FlickrPhoto *photo))
{
  return flickr_photos_get(client,"flickr.photos.getRecent",NULL,
			   extras,per_page,page,
			   userData,cb);
}

FlickrResult flickr_photos_getUntagged(FlickrClient *client,
				       FlickrDateSearchCriteria *criteria,
				       FlickrPhotoExtras extras,
				       unsigned int per_page,
				       unsigned int page,
				       void *userData,
				       void (*cb)(void *userData, 
						  const FlickrResultPage *page,
						  unsigned int offset, 
						  const FlickrPhoto *photo))
{
  return flickr_photos_get(client,"flickr.photos.getUntagged",criteria,
			   extras,per_page,page,
			   userData,cb);
}

typedef struct getCountsArg getCountsArg;
struct getCountsArg {
  rspParser m_super;
  FlickrPhotoCount m_count;
  void *m_userData;
  void (*m_cb)(void *userData, FlickrPhotoCount *photocount);
};

static void getCounts_StartElementHandler(void *userData,
					  const XML_Char *name,
					  const XML_Char **atts)
{
  getCountsArg *rp = (getCountsArg*)userData;
  if(strcmp(name,"photocount")==0) {

    matchXmlAttr matches[] = {
      { "count",    XML_UI,   { ui: &rp->m_count.m_count } },
      { "fromdate", XML_TIME, { t:  &rp->m_count.m_fromdate } }, 
      { "todate",   XML_TIME, { t:  &rp->m_count.m_todate } }, 
    };
    extractAttrValues(matches,atts);

  }
}

static void getCountsArg_Init(getCountsArg *p,
			      void *userData,
			      void (*cb)(void *userData, FlickrPhotoCount *photocount)) {
  memset(p,0,sizeof(getCountsArg));
  p->m_userData=userData;
  p->m_cb=cb;
  rsp_ParserCreate(&p->m_super);
}

FlickrResult flickr_photos_getCounts(FlickrClient *client,
				     unsigned int dates_count,
				     time_t *dates,
				     unsigned int taken_dates_count,
				     time_t *taken_dates,
				     void *userData,
				     void (*cb)(void *userData, FlickrPhotoCount *photocount))
{
  getCountsArg p;
  const FlickrRequestArg reqarg[] = {
    { "dates",       commaSeparatedListOfDates(client,dates_count,dates) },
    { "taken_dates", commaSeparatedListOfDates(client,taken_dates_count,taken_dates) },
  };
  getCountsArg_Init(&p,userData,cb);

  rsp_SetElementHandler(&p.m_super,getCounts_StartElementHandler,noop_EndElementHandler);
  
  flickr_request_rsp(client, "flickr.photos.getCounts", p.m_super, reqarg);
  
  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}

typedef struct getPermsArg getPermsArg;
struct getPermsArg {
  rspParser m_super;
  FlickrPhotoPerms *m_perms;
};

static void getPerms_StartElementHandler(void *userData,
					 const XML_Char *name,
					 const XML_Char **atts)
{
  getPermsArg *rp = (getPermsArg*)userData;
  
  if(strcmp(name,"perms")==0) {

    matchXmlAttr matches[] = {
      { "ispublic", XML_UC, { uc: &rp->m_perms->m_visibility.m_is_public } },
      { "isfriend", XML_UC, { uc: &rp->m_perms->m_visibility.m_is_friend } },
      { "isfamily", XML_UC, { uc: &rp->m_perms->m_visibility.m_is_family } },
      { "permcomment", XML_UC, { uc: (unsigned char*)&rp->m_perms->m_permcomment } },
      { "permaddmeta", XML_UC, { uc: (unsigned char*)&rp->m_perms->m_permaddmeta } }
    };

    extractAttrValues(matches,atts);
  }
}  

FlickrResult flickr_photos_getPerms(FlickrClient *client,
				    const String *photo_id,
				    FlickrPhotoPerms *perms)
{
  getPermsArg p;
  const FlickrRequestArg reqarg[] = {
    { "photo_id", photo_id->m_start },
  };

  p.m_perms=perms;
  rsp_ParserCreate(&p.m_super);
  
  rsp_SetElementHandler(&p.m_super,getPerms_StartElementHandler,noop_EndElementHandler);
  
  flickr_request_rsp(client, "flickr.photos.getPerms", p.m_super, reqarg);
  
  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}

FlickrResult flickr_photos_search(FlickrClient *client,
				  const FlickrSearchCriteria *criteria,
				  void *userData,
				  void (*cb)(void *userData, 
					     const FlickrResultPage *page,
					     unsigned int offset, 
					     const FlickrPhoto *photo))
{
  getListArg p;
  const FlickrRequestArg *reqarg=NULL;
  FlickrRequestArg tab[13];
  int reqargsz=0;
  
  memset(&tab[0],0,sizeof(tab));
  p.m_userData=userData;
  p.m_cb=cb;
  
  if(criteria!=NULL) {
    reqarg= &tab[0];

    if(String_Length(&criteria->m_user_id)>0) {
      tab[reqargsz].m_arg = "user_id";
      tab[reqargsz].m_value = criteria->m_user_id.m_start;
      reqargsz++;
    }
    
    if(criteria->m_tags!=NULL && criteria->m_tagsz>0) {
      tab[reqargsz].m_arg = "tags";
      tab[reqargsz].m_value = commaSeparatedList(client,criteria->m_tags,criteria->m_tagsz);
      reqargsz++;
    }
    
    tab[reqargsz].m_arg = "tag_mode";
    switch(criteria->m_tagmode) {
    case TAG_MODE_AND:
      tab[reqargsz].m_value = "all";
      break;
    case TAG_MODE_OR:
    default:
      tab[reqargsz].m_value = "any";
    }
    reqargsz++;
  
    if(String_Length(&criteria->m_text)>0) {
      tab[reqargsz].m_arg = "text";
      tab[reqargsz].m_value = criteria->m_text.m_start;
      reqargsz++;
    }
  
    time_t d = criteria->m_date_criteria.m_min_upload_date;
    if(d>0) {
      tab[reqargsz].m_arg = "min_upload_date";
      tab[reqargsz].m_value = date(client,d);
      reqargsz++;
    }
  
    d = criteria->m_date_criteria.m_max_upload_date;
    if(d>0) {
      tab[reqargsz].m_arg = "max_upload_date";
      tab[reqargsz].m_value = date(client,d);
      reqargsz++;
    }
  
    d = criteria->m_date_criteria.m_min_taken_date;
    if(d>0) {
      tab[reqargsz].m_arg = "min_taken_date";
      tab[reqargsz].m_value = date(client,d);
      reqargsz++;
    }
  
    d = criteria->m_date_criteria.m_max_taken_date;
    if(d>0) {
      tab[reqargsz].m_arg = "max_taken_date";
      tab[reqargsz].m_value = date(client,d);
      reqargsz++;
    }
  
    if(criteria->m_license>0) {
      tab[reqargsz].m_arg = "license";
      tab[reqargsz].m_value = makeIntString(client,criteria->m_license);
      reqargsz++;
    }

    if(criteria->m_sort!=SORT_UNSET) {
      tab[reqargsz].m_arg = "sort";
      tab[reqargsz].m_value = sortOrder(criteria->m_sort);
      reqargsz++;
    }
    if(criteria->m_extras>0) {
      tab[reqargsz].m_arg = "extras";
      tab[reqargsz].m_value = makeIntString(client,criteria->m_extras);
      reqargsz++;
    }
    if(criteria->m_per_page>0) {
      tab[reqargsz].m_arg = "per_page";
      tab[reqargsz].m_value = makeIntString(client,criteria->m_per_page);
      reqargsz++;
    }
    if(criteria->m_page>0) {
      tab[reqargsz].m_arg = "page";
      tab[reqargsz].m_value = makeIntString(client,criteria->m_page);
      reqargsz++;
    }
  }
  rsp_ParserCreate(&p.m_super);
  
  rsp_SetElementHandler(&p.m_super,favorites_getPublicList_StartElementHandler,noop_EndElementHandler);
  
  flickr_request(client, "flickr.photos.search", p.m_super.m_parser, &writeToParser, reqarg, reqargsz);
  
  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}

typedef struct getAllContextsArg getAllContextsArg;
struct getAllContextsArg {
  rspParser m_super;
  void *m_userData;
  void (*m_setCb)(void *userData, const String *id, const String *title);
  void (*m_poolCb)(void *userData, const String *id, const String *title);
  String m_id;
  String m_title;
};  

static void getAllContextsArg_Init(getAllContextsArg *p,
				   void *userData,
				   void (*setCb)(void *userData, const String *id, const String *title),
				   void (*poolCb)(void *userData, const String *id, const String *title))
{
  p->m_userData=userData;
  p->m_setCb=setCb;
  p->m_poolCb=poolCb;
  rsp_ParserCreate(&p->m_super);
  String_Init(&p->m_id);
  String_Init(&p->m_title);
}

static void getAllContextsArg_Destroy(getAllContextsArg *p)
{
  rsp_ParserFree(&p->m_super);
  String_Destroy(&p->m_id);
  String_Destroy(&p->m_title);
}

static void getAllContexts_StartElementHandler(void *userData,
					const XML_Char *name,
					const XML_Char **atts)
{
  getAllContextsArg *p = (getAllContextsArg *)userData;

  matchXmlAttr matches[] = {
    { "id",            XML_STRING, { &p->m_id } },
    { "title",         XML_STRING, { &p->m_title } }, 
  };
  extractAttrValues(matches,atts);

  if(strcmp(name,"set")==0) {
    (*p->m_setCb)(p->m_userData,&p->m_id,&p->m_title);
  } else if(strcmp(name,"pool")==0) {
    (*p->m_poolCb)(p->m_userData,&p->m_id,&p->m_title);
  }
}

FlickrResult flickr_photos_getAllContexts(FlickrClient *client,
					  const FlickrPhotoId *photo_id,
					  void *userData,
					  void (*setCb)(void *userData, const String *id, const String *title),
					  void (*poolCb)(void *userData, const String *id, const String *title))
{
  const FlickrRequestArg reqarg[] = {
    { "photo_id", photo_id->m_start },
  };
  getAllContextsArg p;
  getAllContextsArg_Init(&p,userData,setCb,poolCb);

  rsp_SetElementHandler(&p.m_super,getAllContexts_StartElementHandler,noop_EndElementHandler);
  
  flickr_request(client, "flickr.photos.getAllContexts",
		 p.m_super.m_parser, &writeToParser,
		 reqarg, sizeof(reqarg)/sizeof(reqarg[0]));
  
  getAllContextsArg_Destroy(&p);
  return p.m_super.m_code;
}

static FlickrResult flickr_photos_fetchContactsPhotos(FlickrClient *client,
						      const char *method,
					     unsigned int count,
					     int flags_and_extras,
					     void *userData,
					     void (*cb)(void *userData, 
							const FlickrResultPage *page,
							unsigned int offset, 
							const FlickrPhoto *photo))
/* FIXME This method requires authentication with 'read' permission.*/
{
  const int mask = LICENSE
    |DATE_UPLOAD
    |DATE_TAKEN     
    |OWNER_NAME     
    |ICON_SERVER    
    |ORIGINAL_FORMAT
    |LAST_UPDATE
    ;
  buildExtrasParam(client, flags_and_extras&mask);
  {
    const FlickrRequestArg reqarg[] = {
      { "count",        makeIntString(client, count) },
      { "just_friends", flags_and_extras&JUST_FRIENDS ? "1":"0" },
      { "single_photo", flags_and_extras&SINGLE_PHOTO ? "1":"0" },
      { "include_self", flags_and_extras&INCLUDE_SELF ? "1":"0" },
      { "extras",   client->m_extras_scratchpad },
    };
    getListArg p;

    memset(&p,0,sizeof(getListArg));
    p.m_userData=userData;
    p.m_cb=cb;
    
    rsp_ParserCreate(&p.m_super);
    rsp_SetElementHandler(&p.m_super,favorites_getPublicList_StartElementHandler,noop_EndElementHandler);
    
    flickr_request_rsp(client,method,p.m_super,reqarg);
    
    rsp_ParserFree(&p.m_super);
    return p.m_super.m_code;
  }
}

FlickrResult flickr_photos_getContactsPhotos(FlickrClient *client,
					     unsigned int count,
					     int flags_and_extras,
					     void *userData,
					     void (*cb)(void *userData, 
							const FlickrResultPage *page,
							unsigned int offset, 
							const FlickrPhoto *photo))
{
  return flickr_photos_fetchContactsPhotos(client,"flickr.photos.getContactsPhotos",
					   count,flags_and_extras,userData,cb);
  /* FIXME requires authentication with read permission */
}

FlickrResult flickr_photos_getContactsPublicPhotos(FlickrClient *client,
						   unsigned int count,
						   int flags_and_extras,
						   void *userData,
						   void (*cb)(void *userData, 
							      const FlickrResultPage *page,
							      unsigned int offset, 
							      const FlickrPhoto *photo))
{
  return flickr_photos_fetchContactsPhotos(client,"flickr.photos.getContactsPublicPhotos",
					   count,flags_and_extras,userData,cb);
  /* FIXME requires authentication with read permission */
}

FlickrResult flickr_photos_getNotInSet(FlickrClient *client,
				       FlickrDateSearchCriteria *criteria,
				       unsigned int extras,
				       unsigned int per_page,
				       unsigned int page,
				       void *userData,
				       void (*cb)(void *userData, 
						  const FlickrResultPage *page,
						  unsigned int offset, 
						  const FlickrPhoto *photo))
{
  getListArg p;
  const FlickrRequestArg *reqarg=NULL;
  FlickrRequestArg tab[7];
  int reqargsz=0;
  
  memset(&tab[0],0,sizeof(tab));
  p.m_userData=userData;
  p.m_cb=cb;
  
  if(criteria!=NULL) {
    reqarg= &tab[0];
  
    time_t d = criteria->m_min_upload_date;
    if(d>0) {
      tab[reqargsz].m_arg = "min_upload_date";
      tab[reqargsz].m_value = date(client,d);
      reqargsz++;
    }
  
    d = criteria->m_max_upload_date;
    if(d>0) {
      tab[reqargsz].m_arg = "max_upload_date";
      tab[reqargsz].m_value = date(client,d);
      reqargsz++;
    }
  
    d = criteria->m_min_taken_date;
    if(d>0) {
      tab[reqargsz].m_arg = "min_taken_date";
      tab[reqargsz].m_value = date(client,d);
      reqargsz++;
    }
  
    d = criteria->m_max_taken_date;
    if(d>0) {
      tab[reqargsz].m_arg = "max_taken_date";
      tab[reqargsz].m_value = date(client,d);
      reqargsz++;
    }
    
    if(extras>0) {
      tab[reqargsz].m_arg = "extras";
      tab[reqargsz].m_value = makeIntString(client,extras);
      reqargsz++;
    }
    if(per_page>0) {
      tab[reqargsz].m_arg = "per_page";
      tab[reqargsz].m_value = makeIntString(client,per_page);
      reqargsz++;
    }
    if(page>0) {
      tab[reqargsz].m_arg = "page";
      tab[reqargsz].m_value = makeIntString(client,page);
      reqargsz++;
    }
  }
  rsp_ParserCreate(&p.m_super);
  
  rsp_SetElementHandler(&p.m_super,favorites_getPublicList_StartElementHandler,noop_EndElementHandler);
  
  flickr_request(client, "flickr.photos.getNotInSet", p.m_super.m_parser, &writeToParser, reqarg, reqargsz);
  
  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}
