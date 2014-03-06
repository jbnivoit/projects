/* -*- C -*- */
#include "FlickrClientImpl.h"

#include <string.h>

static const char *filter(FlickrContactFilter f) {
  switch(f) {
  case FLICKR_CONTACT_FRIENDS: return "friends";
  case FLICKR_CONTACT_FAMILY:  return "family";
  case FLICKR_CONTACT_BOTH:    return "both";
  case FLICKR_CONTACT_NEITHER: return "neither";
  default:;
  }
  return "";
}

typedef struct contactsGetListArg contactsGetListArg;
struct contactsGetListArg {
  rspParser m_super;
  FlickrContact m_contact;
  void *m_userData;
  void (*m_cb)(void *userData, const FlickrContact *contact);
};

static void contacts_getList_StartElementHandler(void *userData,
						 const XML_Char *name,
						 const XML_Char **atts)
{
  contactsGetListArg *rp = (contactsGetListArg*)userData;

  if(strcmp(name,"contact")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"nsid")==0 ) {
	atts++;
	String_InitWithString(&rp->m_contact.m_nsid,*atts,strlen(*atts));
	break;
      } else if( strcmp(*atts,"username")==0 ) {
	atts++;
	String_InitWithString(&rp->m_contact.m_username,*atts,strlen(*atts));
	break;
      } else if( strcmp(*atts,"realname")==0 ) {
	atts++;
	String_InitWithString(&rp->m_contact.m_realname,*atts,strlen(*atts));
	break;
      } else if( strcmp(*atts,"iconserver")==0 ) {
	atts++;
	rp->m_contact.m_iconserver = atoi(*atts);
	break;
      } else if( strcmp(*atts,"friend")==0 ) {
	atts++;
	rp->m_contact.m_friend = atoi(*atts);
	break;
      } else if( strcmp(*atts,"family")==0 ) {
	atts++;
	rp->m_contact.m_family = atoi(*atts);
	break;
      } else if( strcmp(*atts,"ignored")==0 ) {
	atts++;
	rp->m_contact.m_ignored = atoi(*atts);
	break;
      }
      atts++;
    }
    
    (*rp->m_cb)(rp->m_userData,&rp->m_contact);
  }
}

static FlickrResult flickr_contacts_get(FlickrClient *client, 
					const char *method,
					void *userData,
					void (*cb)(void *userData, const FlickrContact *contact),
					const FlickrRequestArg reqarg[],
					const unsigned int sz)
{

  unsigned char dummy=0;
  contactsGetListArg p;

  FlickrContact_Init(&p.m_contact);
  memset(&p,0,sizeof(contactsGetListArg));

  p.m_super.m_parser = XML_ParserCreate(NULL);
  p.m_userData=userData;
  p.m_cb=cb;
  XML_SetUserData(p.m_super.m_parser, &p);
  rsp_SetElementHandler(&p.m_super,contacts_getList_StartElementHandler,noop_EndElementHandler);
  
  flickr_request(client, method,
		 p.m_super.m_parser, &writeToParser,
		 reqarg, sz);
  
  XML_Parse(p.m_super.m_parser,&dummy,0,1);
  XML_ParserFree(p.m_super.m_parser);
  FlickrContact_Destroy(&p.m_contact);
  return p.m_super.m_code;
  /* FIXME requires authentication with read permission */
}

FlickrResult flickr_contacts_getList(FlickrClient *client, 
				     FlickrContactFilter f, 
				     void *userData,
				     void (*cb)(void *userData, const FlickrContact *contact))
{
  const FlickrRequestArg reqarg[] = {
    { "filter", filter(f) }
  };
  return flickr_contacts_get(client, 
			     "flickr.contacts.getList",
			     userData,cb,
			     reqarg, sizeof(reqarg)/sizeof(reqarg[0]));
}

FlickrResult flickr_contacts_getPublicList(FlickrClient *client,
				   const String *user_id,
				   void *userData,
				   void (*cb)(void *userData, const FlickrContact *contact))
{
  const FlickrRequestArg reqarg[] = {
    { "user_id", user_id->m_start }
  };
  return flickr_contacts_get(client, 
			     "flickr.contacts.getPublicList",
			     userData,cb,
			     reqarg, sizeof(reqarg)/sizeof(reqarg[0]));
}

