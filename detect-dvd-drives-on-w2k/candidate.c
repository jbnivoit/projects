/* -*- c -*-
 * (C) 2002 Jean-Baptiste Nivoit
 */

#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <winioctl.h>

#include "candidate.h"
extern void ntms_match_candidate_drive(CandidateDrive *c); /* defined in ntms_candidate.c */

static CandidateDrive *new_candidate_drive(char l, DriveType t, CandidateDrive *n)
{
	CandidateDrive *p = (CandidateDrive*)malloc(sizeof(CandidateDrive));
	p->letter = l;
	p->type   = t;
	p->next   = n;
	p->name   = NULL;
	return p;
}
void print_candidate_drive(CandidateDrive *c) {
	while(c!=NULL) {
		CandidateDrive *n = c->next;
		const char *t = "unknown";
		switch(c->type) {
			case DRIVE_TYPE_CDROM:  t = "CDROM" ; break;
			case DRIVE_TYPE_DVDROM: t = "DVDROM"; break;
			case DRIVE_TYPE_UNKNOWN:
			default:;
		}
		printf("%c %s %s\n",c->letter,t,c->name);
		c = n;
	}
}
void free_candidate_drive(CandidateDrive *c) {
	while(c!=NULL) {
		CandidateDrive *n = c->next;
		if(c->name!=NULL)
			free(c->name);
		free(c);
		c = n;
	}
}

static char *query_device_in_registry(HKEY key, char c)
{
	wchar_t val[500];
	DWORD valsz=sizeof(val);
	DWORD type=0;
	char name[17];
	char buf[100];
	char *ret, *ptr;
	int cnt=0;
	HRESULT rc;

	memset(val,0,sizeof(val));

	memcpy(&name[0],"\\DosDevices\\A:",15);
	name[/* index of 'A' */ 12] = c;

	rc = RegQueryValueExA(key,name,NULL,&type,(LPBYTE)&val[0],&valsz);

	sprintf(&buf[0],"%S",&val[0]); 
	ret = strdup(buf+strlen("\\??\\IDE#CdRom")); /* another ugly hack, skip over the raw device type part */

	/* replace all the underscores with spaces, so that the name extracted out of the 
	   registry match the one returned by the NTMS API, this is a ugly hack, i know */
	ptr = ret;
	while(*ptr!='\0') {
		if(*ptr=='_') { 
			if(cnt<2) {
				*ptr = ' ';
				cnt++;
			} else {
				*ptr = '\0'; /* only allow 2 underscores. the format of the name is 
								vendor-type-model, followed by a number of underscores and some other text we don't care about */
			}
		}
		ptr++;
	}

	return ret;
}

static int name_candidate_drive(CandidateDrive *c) {
	HKEY key;
	HKEY syskey;
	LONG rc = RegOpenKey(HKEY_LOCAL_MACHINE,"SYSTEM",&syskey);
	if(rc!=ERROR_SUCCESS) {
		printf("cant open HKEY_LOCAL_MACHINE\\SYSTEM key\n");
		return EXIT_FAILURE;
	}
	rc = RegOpenKeyEx(syskey,"MountedDevices",0,KEY_READ,&key);
	if(rc!=ERROR_SUCCESS) {
		printf("cant open HKEY_LOCAL_MACHINE\\SYSTEM\\MountedDevices key\n");
		return EXIT_FAILURE;
	}

	while(c!=NULL) {
		CandidateDrive *n = c->next;
		if(c->name==NULL) {
			c->name = query_device_in_registry(key,c->letter);
		}
		c = n;
	}

	RegCloseKey(key);
	RegCloseKey(syskey);
	return EXIT_SUCCESS;
}

CandidateDrive *candidate_drives() {
	DWORD len = GetLogicalDriveStrings(0,NULL);
	CandidateDrive *head = NULL;
	LPTSTR buf = (LPTSTR)malloc(sizeof(char)*len);
	DWORD idx=0;
	
	len = GetLogicalDriveStrings(len,buf);
	for(;idx<len;idx+=4) {
		if(GetDriveType(&buf[idx])==DRIVE_CDROM) {
			head = new_candidate_drive(buf[idx],DRIVE_TYPE_CDROM,head);
		}
	}

#if(_WIN32_WINNT >= 0x0500)
	{ /* this makes it compile on W2k, but work at runtime on Win9X too */
		OSVERSIONINFO 	ver;
		ver.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
		GetVersionEx(&ver);
		if (VER_PLATFORM_WIN32_NT == ver.dwPlatformId) {
			/* this queries the registry for keys that don't exist on Win9X, i think */
			name_candidate_drive(head);

			/* the following requires Windows 2000 to compile */
			ntms_match_candidate_drive(head);
		}
	}
#else
#error "compiling this must be done on NT > 5.0"
#endif
	return head;
}

void sort_candidate_drive(CandidateDrive **head)
/* sort 'head', so that all DVDs appear first (sorted alphabetically), then all CDs... */
{
	CandidateDrive *dvds = NULL, *dvds_tail = NULL;
	CandidateDrive *cds = NULL,  *cds_tail = NULL;
	CandidateDrive *unknowns = NULL;

	CandidateDrive *c = *head;
	while(c!=NULL) {
		CandidateDrive *n = c->next;
		switch(c->type) {
			case DRIVE_TYPE_CDROM:   
				c->next = cds;           
				cds = c; 
				if(cds->next==NULL) cds_tail = cds;
				break;
			case DRIVE_TYPE_DVDROM:  
				c->next = dvds;         
				dvds = c; 
				if(dvds->next==NULL) dvds_tail = dvds;
				break;
			case DRIVE_TYPE_UNKNOWN: 
				c->next = unknowns; 
				unknowns = c; 
				break;
		}
		c = n;
	}

	/* relink list of CDs at the end of DVDs */
	if(dvds_tail!=NULL)
		dvds_tail->next = cds;
	
	/* relink list of unknowns at the end of CDs */
	if(cds_tail!=NULL)
		cds_tail->next = unknowns;

	if(dvds!=NULL)
		*head = dvds;
	else if(cds!=NULL)
		*head = cds;
	else 
		*head = unknowns;
}

void for_each_candidate(CandidateDrive *head, void (*f)(CandidateDrive *head))
{
	if(f==NULL) 
		return;
	else {
		CandidateDrive *c = head;
		while(c!=NULL) {
			(*f)(c);
			c = c->next;
		}
	}
}
