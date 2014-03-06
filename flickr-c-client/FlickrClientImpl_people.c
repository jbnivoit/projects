/* -*- C -*- */
#include "FlickrClientImpl.h"

#include <string.h>

typedef struct findByEmailArgs findByEmailArgs;
struct findByEmailArgs {
  unsigned char m_parsing_username;
  unsigned char m_username_set;
  XML_Parser m_parser;
  String m_nsid;
  String m_username;
};

static void findByEmail_CharacterDataHandler (void *userData,
				      const XML_Char *s,
				      int len)
{
  findByEmailArgs *rp = (findByEmailArgs*)userData;
  if(rp->m_parsing_username && rp->m_username_set==0) {
    String_InitWithString(&rp->m_username,s,len);
    rp->m_username_set=1;
  }
}

static void findByEmail_StartElementHandler(void *userData,
				   const XML_Char *name,
				   const XML_Char **atts)
{
  findByEmailArgs *rp = (findByEmailArgs*)userData;
  if(strcmp(name,"username")==0) {
    rp->m_parsing_username=1;
  } else {
    rp->m_parsing_username=0;
  }
  if(strcmp(name,"user")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"nsid")==0 ) {
	atts++;
	String_InitWithString(&rp->m_nsid,*atts,strlen(*atts));
	break;
      }
      atts++;
    }
  }
}

static size_t writeToFindByEmailParser(void *source, size_t sz, size_t nmemb, void *userData)
{
  findByEmailArgs *args = (findByEmailArgs*)userData;
  XML_Parse(args->m_parser,source,sz*nmemb,0);
  return sz*nmemb;
}

static FlickrResult flickr_people_find(FlickrClient *client,
				       const char *param,
				       const String *find_email,
				       String *nsid, String *username)
{
  const FlickrRequestArg reqarg = { param, find_email->m_start };
  unsigned char dummy=0;
  findByEmailArgs args = { 0, 0 };
  args.m_parser = XML_ParserCreate(NULL);
  XML_SetUserData(args.m_parser, &args);

  XML_SetElementHandler(args.m_parser,findByEmail_StartElementHandler,noop_EndElementHandler);
  XML_SetCharacterDataHandler(args.m_parser,findByEmail_CharacterDataHandler);

  flickr_request(client, "flickr.people.findByEmail",
		 &args, &writeToFindByEmailParser,
		 &reqarg, 1);
  
  XML_Parse(args.m_parser,&dummy,0,1);
  XML_ParserFree(args.m_parser);

  String_InitWithOther(nsid,&args.m_nsid);
  String_InitWithOther(username,&args.m_username);
  return 0;
}

FlickrResult flickr_people_findByEmail(FlickrClient *client,
				       const String *find_email,
				       String *nsid, String *username)
{
  return flickr_people_find(client,"find_email",find_email,nsid,username);
}

FlickrResult flickr_people_findByUsername(FlickrClient *client,
				       const String *iUsername,
				       String *nsid, String *oUsername)
{
  return flickr_people_find(client,"username",iUsername,nsid,oUsername);
}
					  
FlickrResult flickr_people_getPublicPhotos(FlickrClient *client, const String *nsid,
					   int extras,
					   unsigned int per_page, unsigned int page, 
					   void *userData,
					   void (*cb)(void *userData, const FlickrPhotos *photos)) {
  /*
api_key (Required)
    Your API application key. See here for more details.
user_id (Required)
    The NSID of the user who's photos to return.
extras (Optional)
    A comma-delimited list of extra information to fetch for each returned record. Currently supported fields are: license, date_upload, date_taken, owner_name, icon_server, original_format, last_update.
per_page (Optional)
    Number of photos to return per page. If this argument is omitted, it defaults to 100. The maximum allowed value is 500.
page (Optional)
    The page of results to return. If this argument is omitted, it defaults to 1.

Example Response

This method returns the standard photo list xml:

<photos page="2" pages="89" perpage="10" total="881">
	<photo id="2636" owner="47058503995@N01" 
		secret="a123456" server="2" title="test_04"
		ispublic="1" isfriend="0" isfamily="0" />
	<photo id="2635" owner="47058503995@N01"
		secret="b123456" server="2" title="test_03"
		ispublic="0" isfriend="1" isfamily="1" />
	<photo id="2633" owner="47058503995@N01"
		secret="c123456" server="2" title="test_01"
		ispublic="1" isfriend="0" isfamily="0" />
	<photo id="2610" owner="12037949754@N01"
		secret="d123456" server="2" title="00_tall"
		ispublic="1" isfriend="0" isfamily="0" />
</photos>
  */
  return 0;
}

typedef enum {
  PARSING_NOT_STARTED=-1,
  PARSING_USERNAME=0,
  PARSING_REALNAME=1,
  PARSING_MBOX=2,
  PARSING_LOCATION=3,
  PARSING_PHOTOSURL=4,
  PARSING_PROFILEURL=5,
  PARSING_FIRSTDATE=6,
  PARSING_FIRSTDATETAKEN=7,
  PARSING_COUNT=8,
  PARSING_PERSON=9,
  PARSING_NSID,
  PARSING_ISADMIN,
  PARSING_ISPRO,
  PARSING_ICONSERVER

} ParsingState; /* this enum must be synchronized with the contents of flickr_people_getInfo.g */

#define in_word_set flickr_people_getInfo_in_word_set
#include "flickr_people_getInfo_gperf.c"

static unsigned int StateFromElement(const XML_Char *tag) {
  const struct GetInfoElement * key = in_word_set (tag, strlen(tag));
  if(key==NULL) return PARSING_NOT_STARTED;
  return key->val;
}

typedef struct getInfoArgs getInfoArgs;
struct getInfoArgs {
  XML_Parser m_parser;
  unsigned int m_state;
  FlickrPerson *m_info;
};

static size_t writeToGetInfoParser(void *source, size_t sz, size_t nmemb, void *userData)
{
  getInfoArgs *args = (getInfoArgs*)userData;
  XML_Parse(args->m_parser,source,sz*nmemb,0);
  return sz*nmemb;
}

static void getInfo_CharacterDataHandler (void *userData,
				      const XML_Char *s,
				      int len)
{
  getInfoArgs *args = (getInfoArgs*)userData;
  FlickrPerson *rp = args->m_info;  

  switch(args->m_state) {
  case PARSING_USERNAME:   String_Append(&rp->m_username,s,len); break;
  case PARSING_REALNAME:   String_Append(&rp->m_realname,s,len); break;
  case PARSING_MBOX:       String_Append(&rp->m_mbox_sha1sum,s,len); break;
  case PARSING_LOCATION:   String_Append(&rp->m_location,s,len); break;
  case PARSING_PHOTOSURL:  String_Append(&rp->m_photosurl,s,len); break;
  case PARSING_PROFILEURL: String_Append(&rp->m_profileurl,s,len); break;
  case PARSING_FIRSTDATE:  rp->m_firstdate = atoi(s); break; /* FIXME not accurate since this could be broken down into several callbacks */
  case PARSING_FIRSTDATETAKEN: String_Append(&rp->m_firstdatetaken,s,len); break;
  case PARSING_COUNT: rp->m_count = atoi(s); break;
  default:;
  }
}

static void getInfo_StartElementHandler(void *userData,
				   const XML_Char *name,
				   const XML_Char **atts)
{
  getInfoArgs *rp = (getInfoArgs*)userData;

  rp->m_state = StateFromElement(name);
  if(rp->m_state == PARSING_PERSON) {
    while(*atts!=NULL) {
      unsigned int h = hashGetInfoElement(*atts,strlen(*atts));
      atts++;
      switch(h) {
      case PARSING_NSID:     String_InitWithString(&rp->m_info->m_nsid,*atts,strlen(*atts)); break;
      case PARSING_ISADMIN:     rp->m_info->m_isadmin    = atoi(*atts); break;
      case PARSING_ISPRO:       rp->m_info->m_ispro      = atoi(*atts); break;
      case PARSING_ICONSERVER:  rp->m_info->m_iconserver = atoi(*atts); break;
      default:;
      }
    }
  }
}

FlickrResult flickr_people_getInfo(FlickrClient *client, const String *nsid, 
				   void *userData,
				   void (*cb)(void *userData, const FlickrPerson *oInfo))
{
  const FlickrRequestArg reqarg[] = { { "user_id", nsid->m_start } };
  unsigned char dummy=0;
  FlickrPerson person;
  getInfoArgs args = { NULL, PARSING_NOT_STARTED, &person };

  FlickrPerson_Init(&person);
  args.m_parser = XML_ParserCreate(NULL);
  XML_SetUserData(args.m_parser, &args);

  XML_SetElementHandler(args.m_parser,getInfo_StartElementHandler,noop_EndElementHandler);
  XML_SetCharacterDataHandler(args.m_parser,getInfo_CharacterDataHandler);

  flickr_request(client, "flickr.people.getInfo",
		 &args, &writeToGetInfoParser,
		 reqarg, sizeof(reqarg)/sizeof(reqarg[0]));
  
  XML_Parse(args.m_parser,&dummy,0,1);
  XML_ParserFree(args.m_parser);

  String_RTrimWhitespace(&person.m_nsid);
  String_RTrimWhitespace(&person.m_username);
  String_RTrimWhitespace(&person.m_realname);
  String_RTrimWhitespace(&person.m_mbox_sha1sum);
  String_RTrimWhitespace(&person.m_location);
  String_RTrimWhitespace(&person.m_photosurl);
  String_RTrimWhitespace(&person.m_profileurl);
  String_RTrimWhitespace(&person.m_firstdatetaken);

  (*cb)(userData,&person);
  FlickrPerson_Destroy(&person);

  return 0;
}

FlickrResult flickr_people_getPublicGroups(FlickrClient *client, const String *nsid,
					   void *userData,
					   void (*groupsCb)(void *userData, const FlickrGroups *groups));

typedef struct getUploadStatusArg getUploadStatusArg;
struct getUploadStatusArg {
  rspParser m_super;
  String *m_id;
  unsigned char *m_ispro;
  String *m_username;
  FlickrUploadStatus *m_status;
  unsigned char m_parsing_username;
};

static void getUploadStatusArg_Init(getUploadStatusArg *p,
					   String *id,
					   unsigned char *ispro,
					   String *username,
					   FlickrUploadStatus *status)
{
  memset(p,0,sizeof(getUploadStatusArg));
  p->m_id=id;
  p->m_ispro=ispro;
  p->m_username=username;
  p->m_status=status;
}

static void getUploadStatus_CharacterDataHandler (void *userData,
						  const XML_Char *s,
						  int len)
{
  getUploadStatusArg *rp = (getUploadStatusArg*)userData;
  if(rp->m_parsing_username==0) return;

  String_Append(rp->m_username,s,len);
}

static void getUploadStatus_StartElementHandler(void *userData,
						const XML_Char *name,
						const XML_Char **atts)
{
  getUploadStatusArg *rp = (getUploadStatusArg*)userData;

  if(strcmp(name,"user")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"id")==0 ) {
	atts++;
	String_InitWithString(rp->m_id,*atts,strlen(*atts));
	break;
      } else if( strcmp(*atts,"ispro")==0 ) {
	atts++;
	*rp->m_ispro = atoi(*atts);
	break;
      }
      atts++;
    }
  }

  else if(strcmp(name,"username")==0) {
    rp->m_parsing_username=1;
  }

  else if(strcmp(name,"filesize")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"max")==0 ) {
	atts++;
	rp->m_status->m_max = atoi(*atts);
	break;
      } else if( strcmp(*atts,"used")==0 ) {
	atts++;
	rp->m_status->m_used = atoi(*atts);
	break;
      }
      atts++;
    }
  }

  else if(strcmp(name,"bandwidth")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"max")==0 ) {
	atts++;
	rp->m_status->m_filesize_max = atoi(*atts);
	break;
      }
      atts++;
    }
  }
}

FlickrResult flickr_people_getUploadStatus(FlickrClient *client,
					   String *id,
					   unsigned char *ispro,
					   String *username,
					   FlickrUploadStatus *status)
{
  getUploadStatusArg p;
  getUploadStatusArg_Init(&p,id,ispro,username,status);

  rsp_ParserCreate(&p.m_super);
  rsp_SetElementHandler(&p.m_super,getUploadStatus_StartElementHandler,noop_EndElementHandler);
  rsp_SetCharacterDataHandler(&p.m_super,
			      &getUploadStatus_CharacterDataHandler);

  flickr_request_rsp0(client, "flickr.people.getUploadStatus",p.m_super);
  
  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
  /* FIXME requires authentication with read permission */
}
