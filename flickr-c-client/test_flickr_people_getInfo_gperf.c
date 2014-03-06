#include <stdio.h>
#include <stdlib.h>

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

#include "flickr_people_getInfo_gperf.c"

static const char *tab[] = 
{
   "username",
"realname",
"mbox_sha1sum",
"location",
"photosurl",
"profileurl",
"firstdate",
"firstdatetaken",
"count",
"person",
"nsid",
"isadmin",
"ispro",
"iconserver",
"rsp"
};

int main(int argc, char **argv)
{
   const int sz = sizeof(tab)/sizeof(tab[0]);
   int i=0;
   for(;i<sz;i++) 
     {
	printf("[%d]=%s=>%d\n",i,tab[i],
	       hashGetInfoElement (tab[i],strlen(tab[i])));
     }
   
   return EXIT_SUCCESS;
}

