/* -*- C -*- */
#ifndef _String_H
#define _String_H

#include <expat.h>

typedef struct String String;

struct String {
  char *m_start;
  unsigned int m_buflen;
  unsigned int m_offset;
#define STRING_BUFFER_BUFSZ 100
  char m_buf[STRING_BUFFER_BUFSZ];
};


#ifdef __cplusplus
extern "C" {
#endif

extern void String_Init(String *sb);
extern void String_InitWithString(String *sb, const XML_Char *s, unsigned int len);
extern void String_InitWithOther(String *sb, const String *other);
extern void String_Reinit(String *sb);
extern void String_Destroy(String *sb);
extern void String_Append(String *sb, const XML_Char *s, unsigned int len);
extern void String_AppendOther(String *sb, const String *other);
extern void String_Copy(String *sb, const String *other);
extern void String_Duplicate(String *sb, String *other);
extern unsigned char String_Compare(const String *sb, const String *other);
extern unsigned char String_CompareCString(const String *sb, const char *other);
extern const char *String_GetString(const String *sb);
extern unsigned int String_Length(const String *sb);
extern void String_Format(String *dest, const char *fmt, ...);
extern void String_RTrimWhitespace(String *dest);
extern void String_LTrimWhitespace(String *dest);
extern void String_TrimWhitespace(String *dest);

/*
 * transfer the string data from 'from' to 'to', without any memory realloc.
 */
extern void String_Transfer(String *from, String *to);

#ifdef __cplusplus
}
#endif

#endif
