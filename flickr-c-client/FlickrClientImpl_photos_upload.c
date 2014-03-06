#include "FlickrClientImpl.h"

#include <string.h>

typedef struct checkTicketArg checkTicketArg;
struct checkTicketArg {
  rspParser m_super;
  FlickrTicket m_ticket;
  void *m_userData;
  void (*m_cb)(void *userData, const FlickrTicket *ticket);
};

static void FlickrTicket_Init(FlickrTicket *p) {
  memset(p,0,sizeof(FlickrTicket));
  String_Init(&p->m_id);
  String_Init(&p->m_photoid);
}

static void FlickrTicket_Destroy(FlickrTicket *p) {
  String_Destroy(&p->m_id);
  String_Destroy(&p->m_photoid);
}

static void checkTicketArg_Init(checkTicketArg *p,
			   void *userData,
			   void (*cb)(void *userData, const FlickrTicket *ticket))
{
  FlickrTicket_Init(&p->m_ticket);
  p->m_userData=userData;
  p->m_cb=cb;
}

static void ticket_StartElementHandler(void *userData,
					 const XML_Char *name,
					 const XML_Char **atts)
{
  checkTicketArg *rp = (checkTicketArg*)userData;

  if(strcmp(name,"ticket")==0) {
    FlickrTicket_Destroy(&rp->m_ticket);
    FlickrTicket_Init(&rp->m_ticket);

    while(*atts!=NULL) {
      if( strcmp(*atts,"id")==0 ) {
	atts++;
	String_InitWithString(&rp->m_ticket.m_id,*atts,strlen(*atts));
	break;
      } else if( strcmp(*atts,"photoid")==0 ) {
	atts++;
	String_InitWithString(&rp->m_ticket.m_photoid,*atts,strlen(*atts));
	break;
      } else if( strcmp(*atts,"complete")==0 ) {
	atts++;
	rp->m_ticket.m_complete = atoi(*atts);
	break;
      } else if( strcmp(*atts,"invalid")==0 ) {
	atts++;
	rp->m_ticket.m_complete = atoi(*atts);
	break;
      }
      atts++;
    }
  }
}

FlickrResult flickr_photos_upload_checkTickets(FlickrClient *client,
					       const String *tickets,
					       unsigned int sz,
					       void *userData,
					       void (*cb)(void *userData, const FlickrTicket *ticket))
{
  resetCursor(client);
  {
    checkTicketArg p;
    const FlickrRequestArg reqarg[] = {
      { "tickets", commaSeparatedList(client,tickets,sz) }
    };
    
  memset(&p,0,sizeof(checkTicketArg));
  checkTicketArg_Init(&p,userData,cb);

  rsp_ParserCreate(&p.m_super);
  rsp_SetElementHandler(&p.m_super,ticket_StartElementHandler,noop_EndElementHandler);
  
  flickr_request_rsp(client, "flickr.photos.upload.checkTickets",
		 p.m_super,
		 reqarg);
  
  rsp_ParserFree(&p.m_super);
  FlickrTicket_Destroy(&p.m_ticket);
  return p.m_super.m_code;
  }
}
