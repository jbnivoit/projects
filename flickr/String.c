/* -*- C -*- */
#include "String.h"

#include <stdio.h>
#include <string.h>
#include <stdarg.h>

void String_Init(String *sb) {
  sb->m_start = &sb->m_buf[0];
  sb->m_buflen = STRING_BUFFER_BUFSZ;
  sb->m_offset=0;
  memset(&sb->m_buf[0],0,sb->m_buflen);
}

void String_InitWithOther(String *sb, const String *other)
{
  String_Init(sb);
  String_AppendOther(sb, other);
}

void String_InitWithString(String *sb, const XML_Char *s, unsigned int len)
{
  String_Init(sb);
  String_Append(sb,s,len);
}

void String_Reinit(String *sb) {
  if(sb->m_start!= &sb->m_buf[0]) {
    free(sb->m_start);
    sb->m_start = &sb->m_buf[0];
  }
  sb->m_buflen = STRING_BUFFER_BUFSZ;
  sb->m_offset=0;
  memset(&sb->m_buf[0],0,sb->m_buflen);
}

void String_Destroy(String *sb) {
  if(sb->m_start!= &sb->m_buf[0]) {
    free(sb->m_start);
  }
  sb->m_start = NULL;
  sb->m_offset=0;
};  

static unsigned int max_of(unsigned int a, unsigned int b) {
  return a>b ? a : b;
}

void String_Append(String *sb, const XML_Char *s, unsigned int len) {
#if 0
  {
    char buf[100];
    char *p = &buf[0];
    if(len>sizeof(buf))
      p = malloc(len);
    snprintf(p,len+1,"%s",s);
    printf("CDATA:'%s'\n",p);
    fflush(stdout);
    if(p!=&buf[0])
      free(p);
  }
#endif

  if(sb->m_buflen - sb->m_offset > len) {
    memcpy(sb->m_start+sb->m_offset,s,len+1);
  } else {
    char *start = malloc( max_of(2*sb->m_offset, sb->m_offset + len) );
    memcpy(start,sb->m_start,sb->m_offset);
    memcpy(start+sb->m_offset,s,len+1);
    sb->m_start = start;
    memset(&sb->m_buf[0],0,STRING_BUFFER_BUFSZ);
  }
  sb->m_offset += len;
  sb->m_start[sb->m_offset]=0;
}

void String_AppendOther(String *sb, const String *other)
{
  String_Append(sb,
		      other->m_start,other->m_offset);
}

void String_Copy(String *sb, const String *other) {
  String_Reinit(sb);
  String_AppendOther(sb,other);
}  

const char *String_GetString(const String *sb) {
  return sb->m_start;
}

void String_Duplicate(String *sb, String *other) {
  String_Init(sb);
  String_AppendOther(sb,other);
}

unsigned int String_Length(const String *sb) {
  return sb->m_offset;
}

unsigned char String_Compare(const String *a, const String *b)
{
  if(a->m_buflen==b->m_buflen) {
    return strcmp(a->m_start,b->m_start)==0;
  }
  return 0;
}

unsigned char String_CompareCString(const String *sb, const char *other)
{
  String o = { (char*)other, strlen(other), 0 };
  return String_Compare(sb,&o);
}

// from http://www.planetoid.org/technical/samples/va_args/va_args.c
void String_Format(String *dest, const char *fmt, ...)
#define MAXSTRING 100
{
    va_list args;
    char message[MAXSTRING];

    String_Reinit(dest);
    va_start(args, fmt);
    vsnprintf(message, MAXSTRING, fmt, args);
    va_end(args);

    String_Append(dest, message, strlen(message));
}

void String_RTrimWhitespace(String *dest)
{
  unsigned int i=dest->m_offset-1;
  for(;i>=0;i--) {
    switch(dest->m_start[i]) {
    case ' ':
    case '\t':
    case '\n':
      dest->m_start[i]=0;
      dest->m_offset--;
      break;
    default:
      return;
    }
  }
}

void String_LTrimWhitespace(String *dest) {
  unsigned int i=0;

  while(   dest->m_start[i]==' '
	|| dest->m_start[i]=='\t'
	|| dest->m_start[i]=='\n') { i++; }

  memmove(dest->m_start,dest->m_start+i,dest->m_offset-i);
  dest->m_start[dest->m_offset-i]=0;
  dest->m_offset -= i;
}

void String_TrimWhitespace(String *dest) {
  String_LTrimWhitespace(dest);
  String_RTrimWhitespace(dest);
}

void String_Transfer(String *from, String *to)
{
  if(from==to) return;
  to->m_buflen = from->m_buflen;
  to->m_offset = from->m_offset;

  if(from->m_start == &from->m_buf[0]) {
    to->m_start=&to->m_buf[0];
    memcpy(&to->m_buf[0], &from->m_buf[0], STRING_BUFFER_BUFSZ);
  } else {
    to->m_start = from->m_start;
  }
  memset(from,0,sizeof(from));
}
