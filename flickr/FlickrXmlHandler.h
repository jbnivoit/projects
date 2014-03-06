#ifndef _Flickr_Xml_Handler_H
#define _Flickr_Xml_Handler_H

#include <time.h>

#include "String.h"

typedef enum {
  XML_STRING,
  XML_UC,
  XML_UI,
  XML_TIME
} xmlAttrType;

typedef struct matchXmlAttr matchXmlAttr;
struct matchXmlAttr {
  const char *id;
  xmlAttrType type;
  union {
    String *s;
    unsigned char *uc;
    unsigned int *ui;
    time_t *t;
  } addr;
};      

extern void extractAttrValuesImpl(matchXmlAttr *attrs, unsigned int sz,
			      const XML_Char **atts);

#define extractAttrValues(attrs,atts) extractAttrValuesImpl(attrs,sizeof(attrs)/sizeof(attrs[0]),atts)

#endif
