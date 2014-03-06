/* -*- C -*- */
#include "FlickrClientImpl.h"

#include <string.h>
#include <stdlib.h>

#define MD5Init   MD5_Init
#define MD5Update MD5_Update
#define MD5Final  MD5_Final
#include <sys/md5.h>

/* the following was lifted from curl-7.15.0/docs/examples/debug.c */
struct data {
  char trace_ascii; /* 1 or 0 */
};

static
void dump(const char *text,
          FILE *stream, unsigned char *ptr, size_t size,
          char nohex)
{
  size_t i;
  size_t c;

  unsigned int width=0x10;

  if(nohex)
    /* without the hex output, we can fit more on screen */
    width = 0x40;

  fprintf(stream, "%s, %zd bytes (0x%zx)\n", text, size, size);

  for(i=0; i<size; i+= width) {

    fprintf(stream, "%04zx: ", i);

    if(!nohex) {
      /* hex not disabled, show it */
      for(c = 0; c < width; c++)
        if(i+c < size)
          fprintf(stream, "%02x ", ptr[i+c]);
        else
          fputs("   ", stream);
    }

    for(c = 0; (c < width) && (i+c < size); c++) {
      /* check for 0D0A; if found, skip past and start a new line of output */
      if (nohex && (i+c+1 < size) && ptr[i+c]==0x0D && ptr[i+c+1]==0x0A) {
        i+=(c+2-width);
        break;
      }
      fprintf(stream, "%c",
              (ptr[i+c]>=0x20) && (ptr[i+c]<0x80)?ptr[i+c]:'.');
      /* check again for 0D0A, to avoid an extra \n if it's at width */
      if (nohex && (i+c+2 < size) && ptr[i+c+1]==0x0D && ptr[i+c+2]==0x0A) {
        i+=(c+3-width);
        break;
      }
    }
    fputc('\n', stream); /* newline */
  }
  fflush(stream);
}

static
int my_trace(CURL *handle, curl_infotype type,
             unsigned char *data, size_t size,
             void *userp)
{
  struct data *config = (struct data *)userp;
  const char *text;
  (void)handle; /* prevent compiler warning */

  switch (type) {
  case CURLINFO_TEXT:
    fprintf(stderr, "== Info: %s", data);
  default: /* in case a new one is introduced to shock us */
    return 0;

  case CURLINFO_HEADER_OUT:
    text = "=> Send header";
    break;
  case CURLINFO_DATA_OUT:
    text = "=> Send data";
    break;
  case CURLINFO_HEADER_IN:
    text = "<= Recv header";
    break;
  case CURLINFO_DATA_IN:
    text = "<= Recv data";
    break;
  }

  dump(text, stderr, data, size, config->trace_ascii);
  return 0;
}

void build_postfields(struct curl_httppost *formpost, String *sb)
{
  while(formpost!=NULL) {
    
    String_Append(sb, formpost->name, strlen(formpost->name));
    String_Append(sb, "=", 1);
    String_Append(sb, formpost->contents, strlen(formpost->contents));
    if(formpost->next!=NULL)
      String_Append(sb, "&", 1);
    formpost=formpost->next;
  }
  
}

size_t printReplyCb(void *source, size_t sz, size_t nmemb, void *userData)
{
  printf("%s",(char*)source);
  return sz*nmemb;
}

void FlickrRequest(const char *uri,
		   struct curl_httppost *formpost, 
		   void *userData, 
		   size_t (*cb)(void *source, size_t sz, size_t nmemb, void *userData),
		   unsigned char multipart,
		   void *pUserData,
		   void (*progress_cb)(void *pUserData, size_t sz))

{
  struct data config;
  CURLcode res;
  const char buf[] = "Expect:";
  CURL *curl = curl_easy_init();
  /* initalize custom header list (stating that Expect: 100-continue is not wanted */
  struct curl_slist *headerlist = NULL;
  String postfields;
  String_Init(&postfields);

  headerlist = curl_slist_append(headerlist, buf);
  if(curl) {

  /* use the same User-Agent as jwz's webcollage, as it fools some of our websites to not treat us like a robot
   * (for instance imdb.com returns a 403 error when it sees a 'cURL' user-agent!)
   */
  curl_easy_setopt( curl, CURLOPT_USERAGENT, "Mozilla/5.0 (X11; U; Linux i686; en-US; rv:1.7.5)");
\
    /* what URL that receives this POST */
    curl_easy_setopt(curl, CURLOPT_URL, uri);

    if(multipart)
      curl_easy_setopt(curl, CURLOPT_HTTPPOST, formpost);
    else
      {
	int postfieldsize=0;
	build_postfields(formpost,&postfields);
	postfieldsize=String_Length(&postfields);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, String_GetString(&postfields));
	curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, postfieldsize);
      }

  // (sending response headers to stderr)
  curl_easy_setopt( curl , CURLOPT_WRITEDATA, userData ) ;
  curl_easy_setopt( curl , CURLOPT_WRITEFUNCTION, cb ) ;

  if(flickr_debugging) {
    config.trace_ascii = 1; /* enable ascii tracing */
    curl_easy_setopt(curl, CURLOPT_DEBUGFUNCTION, my_trace);
    curl_easy_setopt(curl, CURLOPT_DEBUGDATA, &config);

  /* the DEBUGFUNCTION has no effect until we enable VERBOSE */
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 1);
  }

  if(progress_cb!=NULL) {
    curl_easy_setopt( curl , CURLOPT_PROGRESSDATA, pUserData);
    curl_easy_setopt( curl , CURLOPT_PROGRESSFUNCTION, progress_cb);
  }
  
    res = curl_easy_perform(curl);

    /* always cleanup */
    curl_easy_setopt( curl, CURLOPT_USERAGENT, NULL); /* needed, otherwise cURL attempts to free our static string passed above! */
    curl_easy_cleanup(curl);

    /* then cleanup the formpost chain */
    curl_formfree(formpost);
    /* free slist */
    curl_slist_free_all (headerlist);

    String_Destroy(&postfields);
  }
}

static int compareFlickrRequestArgs(void *ignored, const void *pa, const void *pb)
{
  FlickrRequestArg *a = *(FlickrRequestArg**)pa;
  FlickrRequestArg *b = *(FlickrRequestArg**)pb;
  return strcmp(a->m_arg,b->m_arg);
}

void hex(unsigned char in[16], char out[32]) {
  const char *x="0123456789abcdef";
  unsigned int i=0;
  
  for(;i<16;i++) {
    out[2*i]   = x[ (in[i] & 0xF0) >> 4 ];
    out[2*i+1] = x[ in[i] & 0x0F ];
  }
}

void sign(String *sb, char sig[32]) {
  MD5_CTX ctx;
  unsigned char s[16];
  
  MD5_Init(&ctx);
  MD5_Update(&ctx,sb->m_start, sb->m_offset);
  MD5_Final(s,&ctx);
  hex(s,sig);
}

static void printTab(const FlickrRequestArg *args[], const unsigned int argsz) {
  unsigned int i=0;
  for(;i<argsz;i++) {
    printf("%s => %s\n",args[i]->m_arg,args[i]->m_value);
  }
}

static void sign_args(FlickrClient *client, const char *method,
	       const FlickrRequestArg args[], unsigned int argsz,
	       char sig[32])
{
  String sb;
  const FlickrRequestArg a = { "method", method };
  const FlickrRequestArg b = { "api_key", client->m_apiKey };
  const FlickrRequestArg c = { "auth_token", client->m_auth_token.m_start };

  String_InitWithString(&sb,client->m_secret,FLICKR_SECRET_LEN);

  const FlickrRequestArg **tab = (const FlickrRequestArg**)malloc(sizeof(FlickrRequestArg*)*(argsz+3));
  {
    unsigned int i=0;
    for(;i<argsz;i++) 
      tab[i] = &args[i];
    
    if(client->m_auth_token_set==0) {
      if(method!=NULL) {
	tab[argsz]= &a;
	tab[argsz+1]= &b;
	argsz+=2;
      } else {
	tab[argsz]= &b;
	tab[argsz+1]= NULL;
	argsz+=1;
      }
    } else {
      if(method!=NULL) {
	tab[argsz]= &a;
	tab[argsz+1]= &b;
	tab[argsz+2]= &c;
	argsz+=3;
      } else {
	tab[argsz]= &b;
	tab[argsz+1]= &c;
	tab[argsz+2]= NULL;
	argsz+=2;
      }
    }
    
/*     printTab(tab,argsz+2); */
    qsort_r(tab,argsz,sizeof(FlickrRequestArg*),NULL,&compareFlickrRequestArgs);
/*     printTab(tab,argsz+2); */

    for(i=0;i<argsz;i++) {
      if(tab[i]==NULL) continue;
      String_Append(&sb, tab[i]->m_arg, strlen(tab[i]->m_arg));
      String_Append(&sb, tab[i]->m_value, strlen(tab[i]->m_value));
    }
    
    sign(&sb,sig);
/*     printf("%s\napi_sig='%s'(%d)\n",String_GetString(&sb),sig,strlen(sig)); */
  }
  free(tab);
}

void flickr_request(FlickrClient *client, const char *method,
			    void *userData, 
			    size_t (*cb)(void *source, size_t sz, size_t nmemb, void *userData),
			    const FlickrRequestArg args[], const unsigned int argsz)
{
  unsigned int i=0;
  struct curl_httppost *formpost=NULL;
  struct curl_httppost *lastptr=NULL;

  /* FIXME use CURLFORM_PTRCONTENTS instead of CURLFORM_COPYCONTENTS here, we dont need to make a copy of stuff whose lifetime is guaranteed */
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "method",
               CURLFORM_COPYCONTENTS, method,
               CURLFORM_END);

  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "api_key",
               CURLFORM_COPYCONTENTS, client->m_apiKey,
               CURLFORM_END);

  /* after experimenting and turning on debugging both in curl & Flickr::API, i saw that i shouldnt put the secret as form data.
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "secret",
               CURLFORM_COPYCONTENTS, client->m_secret,
               CURLFORM_END);
  */

  for(;i<argsz;i++) {
    /* Fill in the filename field */
    curl_formadd(&formpost,
		 &lastptr,
		 CURLFORM_COPYNAME, args[i].m_arg,
		 CURLFORM_COPYCONTENTS, args[i].m_value,
		 CURLFORM_END);
  }

  
  {
    char sig[33];
    const unsigned char signedmethod=1;
    if(signedmethod) {
      memset(sig,0,sizeof(sig));
      sign_args(client,method,args,argsz,sig);
      curl_formadd(&formpost,
		   &lastptr,
		   CURLFORM_COPYNAME, "api_sig",
		   CURLFORM_COPYCONTENTS, sig,
		   CURLFORM_END);
      /*     printf("api_sig='%s'(%d)\n",sig,strlen(sig)); */
    }

    FlickrRequest(flickr_REST_URI,
		  formpost, userData, cb, 0, 
		  NULL, NULL); /* this also takes care of freeing 'formpost' */
  }
}

void flickr_request_upload(FlickrClient *client, const char *uri,
			   const String *file,
			   void *userData,
			   size_t (*parse_output_cb)(void *source, 
						     size_t sz, size_t nmemb, void *userData),
			   void *pUserData,
			   void (*progress_cb)(void *pUserData, size_t sz),
			   const FlickrRequestArg args[], const unsigned int argsz)
{

  unsigned int i=0;
  struct curl_httppost *formpost=NULL;
  struct curl_httppost *lastptr=NULL;

  /* FIXME use CURLFORM_PTRCONTENTS instead of CURLFORM_COPYCONTENTS here, we dont need to make a copy of stuff whose lifetime is guaranteed */

  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "api_key",
               CURLFORM_COPYCONTENTS, client->m_apiKey,
               CURLFORM_END);

  /* after experimenting and turning on debugging both in curl & Flickr::API, i saw that i shouldnt put the secret as form data.
  curl_formadd(&formpost,
               &lastptr,
               CURLFORM_COPYNAME, "secret",
               CURLFORM_COPYCONTENTS, client->m_secret,
               CURLFORM_END);
  */

  for(;i<argsz;i++) {
    /* Fill in the filename field */
    curl_formadd(&formpost,
		 &lastptr,
		 CURLFORM_COPYNAME, args[i].m_arg,
		 CURLFORM_COPYCONTENTS, args[i].m_value,
		 CURLFORM_END);
  }

  
  {
    char sig[33];
    memset(sig,0,sizeof(sig));
    sign_args(client,NULL,args,argsz,sig);
    curl_formadd(&formpost,
		 &lastptr,
		 CURLFORM_COPYNAME, "api_sig",
		 CURLFORM_COPYCONTENTS, sig,
		 CURLFORM_END);

    /* Fill in the file upload field */
    curl_formadd(&formpost,
		 &lastptr,
		 CURLFORM_COPYNAME, "photo",
		 CURLFORM_FILE, file->m_start,
		 CURLFORM_END);
    
    FlickrRequest(flickr_REST_URI,
		  formpost, userData, parse_output_cb, 0, 
		  pUserData, progress_cb); /* this also takes care of freeing 'formpost' */
  }
}
