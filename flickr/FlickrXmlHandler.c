#include "FlickrXmlHandler.h"
#include "FlickrClientImpl.h"

#include <string.h>

void extractAttrValuesImpl(matchXmlAttr *attrs, unsigned int sz,
			   const XML_Char **atts)
{
  unsigned int i=0;
  while(*atts!=NULL) {
    for(i=0;i<sz;i++) {
      if( strcmp(*atts, attrs[i].id)==0) {
	atts++;
	switch(attrs[i].type) {
	case XML_STRING:
	  String_InitWithString(attrs[i].addr.s,*atts,strlen(*atts));
	  break;
	case XML_UC:
	  *attrs[i].addr.uc = atoi(*atts)==0?0:1;
	  break;
	case XML_UI:
	  *attrs[i].addr.ui = atoi(*atts);
	  break;
	case XML_TIME:
	  *attrs[i].addr.t = (time_t)atoi(*atts);
	  break;
	default:;
	}
	continue;
      }
    }
    atts++;
  }
}
  
