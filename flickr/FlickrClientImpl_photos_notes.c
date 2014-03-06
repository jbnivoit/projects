#include "FlickrClientImpl.h"

#include <string.h>

typedef struct notesAddArg notesAddArg;
struct notesAddArg {
  rspParser m_super;
  String *m_id;
};

static void note_StartElementHandler(void *userData,
					 const XML_Char *name,
					 const XML_Char **atts)
{
  notesAddArg *rp = (notesAddArg*)userData;

  if(strcmp(name,"note")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"id")==0 ) {
	atts++;
	String_InitWithString(rp->m_id,*atts,strlen(*atts));
	break;
      } 
      atts++;
    }
  }
}

FlickrResult flickr_photos_notes_add(FlickrClient *client,
				     const FlickrPhotoId *photo_id,
				     const FlickrPhotoNote *note,
				     String *id)
{
  resetCursor(client);
  {
    notesAddArg p;
    const FlickrRequestArg reqarg[] = {
      { "photo_id", photo_id->m_start },
      { "note_x", makeIntString(client,note->x) },
      { "note_y", makeIntString(client,note->y) },
      { "note_w", makeIntString(client,note->w) },
      { "note_h", makeIntString(client,note->h) },
      { "note_text", note->text.m_start },
    };
    memset(&p,0,sizeof(notesAddArg));
    p.m_id = id;

    rsp_ParserCreate(&p.m_super);
    rsp_SetElementHandler(&p.m_super,note_StartElementHandler,noop_EndElementHandler);
  
    flickr_request_rsp(client, "flickr.photos.notes.add",
		       p.m_super,
		       reqarg);

    rsp_ParserFree(&p.m_super);
    return p.m_super.m_code;
    /* FIXME requires authentication with write permission */
  }
}

FlickrResult flickr_photos_notes_delete(FlickrClient *client, const String *note_id)
{
  rspParser p;
  const FlickrRequestArg reqarg[] = {
    { "note_id", note_id->m_start }
  };

  rsp_ParserCreate(&p);
  rsp_SetElementHandler(&p,NULL,noop_EndElementHandler);
  
  flickr_request_rsp(client, "flickr.photos.notes.delete",
		     p, reqarg);
  
  rsp_ParserFree(&p);
  return p.m_code;
  /* FIXME requires authentication with write permission */
}

FlickrResult flickr_photos_notes_edit(FlickrClient *client,
				      const String *note_id,
				      const FlickrPhotoNote *note,
				      String *id)
{
  resetCursor(client);
  {
    notesAddArg p;
    const FlickrRequestArg reqarg[] = {
      { "note_id", note_id->m_start },
      { "note_x", makeIntString(client,note->x) },
      { "note_y", makeIntString(client,note->y) },
      { "note_w", makeIntString(client,note->w) },
      { "note_h", makeIntString(client,note->h) },
      { "note_text", note->text.m_start },
    };
    memset(&p,0,sizeof(notesAddArg));
    p.m_id = id;

    rsp_ParserCreate(&p.m_super);
    rsp_SetElementHandler(&p.m_super,note_StartElementHandler,noop_EndElementHandler);
  
    flickr_request_rsp(client, "flickr.photos.notes.edit",
		   p.m_super,
		   reqarg);

    rsp_ParserFree(&p.m_super);
    return p.m_super.m_code;
    /* FIXME requires authentication with write permission */
  }
}
