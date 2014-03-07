/*
// This file is 'scores.c'
// It is part of the 'gms' distribution.
//
//    gms (Gtk MineSweeper), yet another mine sweeper program
//    Copyright (C) 1999 Jean-Baptiste Nivoit <jbn@multimania.com>
//    The full LICENSE can be found in the 'License' file of the 
//    distribution.
//
//    This program is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program; if not, write to the Free Software
//    Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//
// Creation : 		03/01/1999 by JBN
// Last Modification : 	03/01/1999 by JBN
*/ 
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include "scores.h"
#include "callbacks.h"

GSList *currentScores = (GSList*)NULL;
char *currentScoresFile = (char*)NULL;

static void parseScores(char *buf, int len)
{ /* read string buffer and make adequate 'currentScores' structure */
  char *ptr = buf;
  char *end = buf+len;
  
#define isWhitespace(c) (c==' '||c=='\t')

  currentScores = g_slist_alloc();
  
  while (ptr<end) 
    {
      switch(*ptr) {
      case ' ':
      case '\t':
      case '\n':
	ptr++;
	break;
      case '#':
	{
	  while(*ptr!='\n') { ++ptr; }
	  ptr++;
	  break;
	}
      default:
	{
	  int l;
	  char *n, *s, *p = ptr;
	  
	  while(!(isWhitespace(*p)) && *p!='\n') { p++; }
	  l = p-ptr;
	  n = (char*)g_malloc(sizeof(char)*l);
	  strncpy(n,ptr,l);
	  n[l]='\0';
	  while(isWhitespace(*p)) { p++; }
	  ptr = p;
	  while(!(isWhitespace(*p)) && *p!='\n') { p++; }
	  l = p-ptr;
	  s = (char*)g_malloc(sizeof(char)*l);
	  strncpy(s,ptr,l);
	  s[l]='\0';
	  ptr = p;

	  DEBUG(("\t '%s'-->'%s'\n",n,s));
	  {
	    ScoreRecord *record;
	    
	    record = (ScoreRecord*)g_malloc(sizeof(ScoreRecord));
	    record->name  = n;
	    record->score = s;
	    
	    currentScores = g_slist_append(currentScores,record);
	  }
	}
      }
    }
 DONE:
}

void readScores(char *scorefile)
{
  if(scorefile!=(char*)NULL)
    {
      char *buf;
      struct stat sb;
      FILE *file = fopen(scorefile,"r");
      
      currentScoresFile = scorefile;
      {
	/*if(stat(scorefile,&sb)==0) /* could use fstat(fileno(file),&sb) instead */
	if(fstat(fileno(file),&sb)!=0)
	  {
	    printf("can't stat file '%s'!\n",scorefile);
	    exit(EXIT_FAILURE);
	  }
      }
      {
	buf = (char*)g_malloc(sizeof(char)*(sb.st_size+1));
	if(buf==NULL)
	  {
	    printf("can't malloc memory!\n");
	    exit(EXIT_FAILURE);
	  }
	(void)fread(buf,sb.st_size,1,file);
	parseScores(buf,sb.st_size);
      }
      fclose(file);
    }
}

void saveScores(GSList *rec, char *filename)
{
  FILE *file;
  
  if(filename==(char*)NULL)
    filename = currentScoresFile;
  if(filename==(char*)NULL)
    filename = "~/.gms-scores";
  if(strcasecmp(filename,"stdout"))
    file = stdout;
  else
    file = fopen(filename,"w"); /* replace the contents of this file ! */
  if(file==(FILE*)NULL)
    {
      char *msg;
      
      msg = (char*)g_malloc(sizeof(char)*(strlen(filename)+20));
      sprintf(msg,"Can't open file '%s'",filename);
      ModalInfoBox(msg,"Error!");
      g_free(msg);
      return;
    }
  
  fprintf(file,"# File generated by "NAME", do not edit!\n");
  {
#if 0
    ScoreRecord *r = rec;
    while(r!=(ScoreRecord*)NULL)
      {
	fprintf(file,"%s\t%s\n",r->name,r->score);
	r++;
      }
#else
    GSList *lst = rec;
    while(lst = g_slist_next(lst)) 
      {
	ScoreRecord *record = (ScoreRecord*)lst->data;
	fprintf(file,"%s\t%s\n",record->name,record->score);
      }
#endif
  }
  fclose(file);
}



