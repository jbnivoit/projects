#include "FlickrClientImpl.h"

#include <string.h>

static void FlickrArgumentInfo_Transfer(FlickrArgumentInfo *from,
					FlickrArgumentInfo *to)
{
  if(from==to) return;

  String_Transfer(&from->m_name,&to->m_name);
  to->m_optional=from->m_optional;
  String_Transfer(&from->m_description,&to->m_description);
}

static void FlickrErrorInfo_Transfer(FlickrErrorInfo *from,
					FlickrErrorInfo *to)
{
  if(from==to) return;

  to->m_code=from->m_code;
  String_Transfer(&from->m_message,&to->m_message);
  String_Transfer(&from->m_explanation,&to->m_explanation);
}

static void FlickrArgumentInfo_InitWithArgs(FlickrArgumentInfo *arg,
					    const XML_Char *argname,
					    unsigned char opt,
					    const XML_Char *argdesc)
{
  memset(arg,0,sizeof(arg));
  String_InitWithString(&arg->m_name, argname, strlen(argname));
  arg->m_optional = opt;
  String_InitWithString(&arg->m_description, argdesc, strlen(argdesc));
}

static void FlickrErrorInfo_InitWithArgs(FlickrErrorInfo *arg,
					 int code,
					 const XML_Char *message,
					 const XML_Char *explanation)
{
  memset(arg,0,sizeof(arg));
  arg->m_code=code;
  String_InitWithString(&arg->m_message, message, strlen(message));
  String_InitWithString(&arg->m_explanation, explanation, strlen(explanation));
}
 
void FlickrArgumentInfo_Init(FlickrArgumentInfo *arg)
{
  memset(arg,0,sizeof(arg));
  String_Init(&arg->m_name);
  String_Init(&arg->m_description);
}
void FlickrErrorInfo_Init(FlickrErrorInfo *arg)
{
  memset(arg,0,sizeof(arg));
  String_Init(&arg->m_message);
  String_Init(&arg->m_explanation);
}
void FlickrMethodInfo_Init(FlickrMethodInfo *arg)
{
  memset(arg,0,sizeof(arg));
  String_Init(&arg->m_name);
  String_Init(&arg->m_description);
  String_Init(&arg->m_response);
  String_Init(&arg->m_explanation);
}

void FlickrArgumentInfo_Destroy(FlickrArgumentInfo *arg)
{
  memset(arg,0,sizeof(arg));
  String_Destroy(&arg->m_name);
  String_Destroy(&arg->m_description);
}
void FlickrErrorInfo_Destroy(FlickrErrorInfo *arg)
{
  memset(arg,0,sizeof(arg));
  String_Destroy(&arg->m_message);
  String_Destroy(&arg->m_explanation);
}
void FlickrMethodInfo_Destroy(FlickrMethodInfo *arg)
{
  unsigned int i=0;
  memset(arg,0,sizeof(arg));
  String_Destroy(&arg->m_name);
  String_Destroy(&arg->m_description);
  String_Destroy(&arg->m_response);
  String_Destroy(&arg->m_explanation);

  for(;i<arg->m_argsz;i++) {
    FlickrArgumentInfo_Destroy(&arg->m_args[i]);
  }
  free(arg->m_args);

  for(i=0;i<arg->m_errorsz;i++) {
    FlickrErrorInfo_Destroy(&arg->m_errors[i]);
  }
  free(arg->m_errors);
}

typedef enum {
  PARSING_UNKNOWN=0,
  PARSING_DESCRIPTION,
  PARSING_RESPONSE,
  PARSING_EXPLANATION,
  PARSING_ARGUMENT,
  PARSING_ERROR
} methodInfoParsing;

typedef struct methodInfoArg methodInfoArg;
struct methodInfoArg {
  rspParser m_super;
  FlickrMethodInfo *m_method_info;
  methodInfoParsing m_parsing_state;
};

static void appendArgumentInfo(FlickrMethodInfo *rp,
			       const XML_Char *argname,
			       unsigned char opt,
			       const XML_Char *argdesc)
{
  FlickrArgumentInfo *args = (FlickrArgumentInfo*)malloc(rp->m_argsz*sizeof(FlickrArgumentInfo));
  unsigned int i=0;
  for(;i<rp->m_argsz;i++) {
    FlickrArgumentInfo_Transfer(&rp->m_args[i],
				&args[i]);
  }

  FlickrArgumentInfo_InitWithArgs(&rp->m_args[rp->m_argsz],argname,opt,argdesc);
  
  free(rp->m_args);
  rp->m_args = args;
  rp->m_argsz++;
}


static void appendErrorInfo(FlickrMethodInfo *rp,
			    int code,
			    const XML_Char *message,
			    const XML_Char *explanation)
{
  FlickrErrorInfo *errors = (FlickrErrorInfo*)malloc(rp->m_errorsz*sizeof(FlickrErrorInfo));
  unsigned int i=0;
  for(;i<rp->m_errorsz;i++) {
    FlickrErrorInfo_Transfer(&rp->m_errors[i],
				&errors[i]);
  }

  FlickrErrorInfo_InitWithArgs(&rp->m_errors[rp->m_errorsz],code,message,explanation);
  
  free(rp->m_errors);
  rp->m_errors = errors;
  rp->m_errorsz++;
}

static void getMethodInfo_EndElementHandler(void *userData,
					 const XML_Char *name)
{
  methodInfoArg *rp = (methodInfoArg*)userData;
  rp->m_parsing_state=PARSING_UNKNOWN;
}

static void getMethodInfo_StartElementHandler(void *userData,
					 const XML_Char *name,
					 const XML_Char **atts)
{
  methodInfoArg *rp = (methodInfoArg*)userData;

  if(strcmp(name,"method")==0) {
    while(*atts!=NULL) {
      if( strcmp(*atts,"needslogin")==0 ) {
	atts++;
	rp->m_method_info->m_needslogin = atoi(*atts);
	break;
      }
      atts++;
    }
    
  } else if(strcmp(name,"description")==0) {
    rp->m_parsing_state=PARSING_DESCRIPTION;
  } else if(strcmp(name,"response")==0) {
    rp->m_parsing_state=PARSING_RESPONSE;
  } else if(strcmp(name,"explanation")==0) {
    rp->m_parsing_state=PARSING_EXPLANATION;
  } else if(strcmp(name,"argument")==0) {
    rp->m_parsing_state=PARSING_ARGUMENT;

    unsigned char opt=0;
    const XML_Char *argname = NULL, *argdesc=NULL;
    appendArgumentInfo(rp->m_method_info, argname, opt, argdesc);

  } else if(strcmp(name,"error")==0) {
    rp->m_parsing_state=PARSING_ERROR;

    int code=0;
    const XML_Char *message = NULL, *explanation = NULL;
    appendErrorInfo(rp->m_method_info, code, message, explanation);
    
  } 
}

static void getMethodInfo_CharacterDataHandler (void *userData,
				      const XML_Char *s,
				      int len)
{
  methodInfoArg *rp = (methodInfoArg*)userData;
  switch(rp->m_parsing_state) {
  case PARSING_DESCRIPTION:
    String_Append(&rp->m_method_info->m_description,s,len);
    break;
  case PARSING_RESPONSE:
    String_Append(&rp->m_method_info->m_response,s,len);
    break;
  case PARSING_EXPLANATION:
    String_Append(&rp->m_method_info->m_explanation,s,len);
    break;
  case PARSING_ARGUMENT:
    String_Append(&rp->m_method_info->m_args[rp->m_method_info->m_argsz-1].m_description,s,len);
    break;
  case PARSING_ERROR:
    String_Append(&rp->m_method_info->m_errors[rp->m_method_info->m_errorsz-1].m_explanation,s,len);
    break;
  default:;
  }
}

FlickrResult flickr_reflection_methodInfoArg(FlickrClient *client,
					     const char *method_name,
					     FlickrMethodInfo *oMethodInfo)
{
  const FlickrRequestArg reqarg[] = {
    { "method_name", method_name }
  };
  methodInfoArg p;
  memset(&p,0,sizeof(methodInfoArg));

  p.m_method_info = oMethodInfo;
  rsp_ParserCreate(&p.m_super);
  rsp_SetElementHandler(&p.m_super,getMethodInfo_StartElementHandler,getMethodInfo_EndElementHandler);
  rsp_SetCharacterDataHandler(&p.m_super, &getMethodInfo_CharacterDataHandler);
  
  flickr_request_rsp(client, "flickr.reflection.getMethodInfo",
		 p.m_super,
		 reqarg);
  
  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}

typedef struct getMethodsArg getMethodsArg;
struct getMethodsArg {
  rspParser m_super;
  String m_method;
  void *m_userData;
  void (*m_cb)(void *userData,
	     const String *method);
};

static void getMethods_EndElementHandler(void *userData,
					 const XML_Char *name)
{
  getMethodsArg *rp = (getMethodsArg*)userData;
  
  (*rp->m_cb)(rp->m_userData,&rp->m_method);
  String_Destroy(&rp->m_method);
}

static void getMethods_StartElementHandler(void *userData,
					 const XML_Char *name,
					 const XML_Char **atts)
{
  getMethodsArg *rp = (getMethodsArg*)userData;

  if(strcmp(name,"method")==0) {
    String_Init(&rp->m_method);
  }
}

static void getMethods_CharacterDataHandler (void *userData,
				      const XML_Char *s,
				      int len)
{
  getMethodsArg *rp = (getMethodsArg*)userData;
  String_Append(&rp->m_method,s,len);
}

FlickrResult flickr_reflection_getMethods(FlickrClient *client,
					  void *userData,
					  void (*cb)(void *userData,
						     const String *method))
{
  getMethodsArg p;
  memset(&p,0,sizeof(getMethodsArg));

  p.m_userData=userData;
  p.m_cb=cb;

  rsp_ParserCreate(&p.m_super);
  rsp_SetElementHandler(&p.m_super,getMethods_StartElementHandler,getMethods_EndElementHandler);
  rsp_SetCharacterDataHandler(&p.m_super, &getMethods_CharacterDataHandler);
  
  flickr_request_rsp0(client,"flickr.reflection.getMethods",p.m_super);

  rsp_ParserFree(&p.m_super);
  return p.m_super.m_code;
}
