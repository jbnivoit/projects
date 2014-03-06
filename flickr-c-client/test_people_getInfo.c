/* -*- C -*- */
#include "FlickrClient.h"
#include "test.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static const char *FMT = 
"<person nsid=\"%s\" isadmin=\"%d\" ispro=\"%d\" iconserver=\"%d\">\n" \
"	<username>%s</username>\n" \
"	<realname>%s</realname>\n" \
"        <mbox_sha1sum>%s</mbox_sha1sum>\n" \
"	<location>%s</location>\n" \
"	<photosurl>%s</photosurl>\n" \
"	<profileurl>%s</profileurl>\n" \
"	<photos>\n" \
"		<firstdate>%d</firstdate>\n" \
"		<firstdatetaken>%s</firstdatetaken>\n" \
"		<count>%d</count>\n" \
"	</photos>\n" \
"</person>";

static void printInfo(void *userData, FlickrPerson *person) {
#define X(a) (a.m_start==NULL?"":a.m_start)
#if 0
  printf(FMT,
	 X(person->m_nsid),
	 person->m_isadmin,
	 person->m_ispro,
	 person->m_iconserver,
	 X(person->m_username),
	 X(person->m_realname),
	 person->m_mbox_sha1sum,
	 X(person->m_location),
	 X(person->m_photosurl),
	 X(person->m_profileurl),
	 person->m_firstdate,
	 X(person->m_firstdatetaken),
	 person->m_count);
#else
  printf("<person nsid=\"%s\" isadmin=\"%d\" ispro=\"%d\" iconserver=\"%d\">\n",
	 X(person->m_nsid),
	 person->m_isadmin,
	 person->m_ispro,
	 person->m_iconserver);
  printf("	<username>%s</username>\n",
	 X(person->m_username));
  printf("	<realname>%s</realname>\n",
	 X(person->m_realname));
  printf("        <mbox_sha1sum>%s</mbox_sha1sum>\n",
	 person->m_mbox_sha1sum);
  printf("	<a  printf(location>%s</location>\n",
	 X(person->m_location));
  printf("	<photosurl>%s</photosurl>\n",
	 X(person->m_photosurl));
  printf("	<profileurl>%s</profileurl>\n",
	 X(person->m_profileurl));
  printf("	<photos>\n");
  printf("		<firstdate>%d</firstdate>\n",
	 person->m_firstdate);
  printf("		<firstdatetaken>%s</firstdatetaken>\n",
	 X(person->m_firstdatetaken));
  printf("		<count>%d</count>\n",
	 person->m_count);
  printf("	</photos>\n");
  printf("</person>");
#endif
}

int main(int argc, char **argv)
{
  curl_global_init( CURL_GLOBAL_ALL ) ;
  FlickrClient *c = newFlickrClient(flickr_API_key, flickr_API_secret);
  String nsid;
  String_InitWithString(&nsid,findByEmail_output_nsid,strlen(findByEmail_output_nsid));
  flickr_people_getInfo(c,&nsid,NULL,&printInfo);
  deleteFlickrClient(c);
  curl_global_cleanup() ;
  return EXIT_SUCCESS;
}
