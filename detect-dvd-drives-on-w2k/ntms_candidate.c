
#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <winioctl.h>
#include "candidate.h"

#include <ntmsapi.h>
#define NTMS_LIST_SIZE 10

static void copy_guid(GUID *out, GUID *in)
{
  memcpy(out,in,sizeof(GUID));
}

typedef struct NtmsDll NtmsDll;
struct NtmsDll {
	HMODULE m_dll;
	HANDLE (WINAPI *m_open)(LPCSTR lpServer,
					 LPCSTR lpApplication,
					 DWORD   dwOptions);
	DWORD (WINAPI *m_close)(HANDLE hSession);
	DWORD (WINAPI *m_enumerate)(HANDLE hSession,
        			 const LPNTMS_GUID lpContainerId,
        			 LPNTMS_GUID lpList,
        			 LPDWORD lpdwListSize,
        			 DWORD dwType,
        			 DWORD dwOptions);
	DWORD (WINAPI *m_info)(HANDLE hSession,
					LPNTMS_GUID lpObjectId,
					LPNTMS_OBJECTINFORMATIONA lpInfo);
};

void ntms_match_candidate_drive(CandidateDrive *c) {
	NtmsDll NTMS;
	NTMS_GUID list[NTMS_LIST_SIZE];
	DWORD n = NTMS_LIST_SIZE;
	DWORD rc;
	HANDLE session;
	int i;

	NTMS.m_dll = LoadLibrary("ntmsapi.dll");
	if(NTMS.m_dll==NULL) return;

	NTMS.m_open = (HANDLE (WINAPI *)(LPCSTR lpServer,
					 LPCSTR lpApplication,
					 DWORD   dwOptions))GetProcAddress(NTMS.m_dll,"OpenNtmsSessionA");
	NTMS.m_close = (DWORD (WINAPI *)(HANDLE hSession))GetProcAddress(NTMS.m_dll,"CloseNtmsSession");
	NTMS.m_enumerate = (DWORD (WINAPI *)(HANDLE hSession,
        			 const LPNTMS_GUID lpContainerId,
        			 LPNTMS_GUID lpList,
        			 LPDWORD lpdwListSize,
        			 DWORD dwType,
        			 DWORD dwOptions))GetProcAddress(NTMS.m_dll,"EnumerateNtmsObject");
	NTMS.m_info = (DWORD (WINAPI *)(HANDLE hSession,
					LPNTMS_GUID lpObjectId,
					LPNTMS_OBJECTINFORMATIONA lpInfo))GetProcAddress(NTMS.m_dll,"GetNtmsObjectInformationA");


	session = (*NTMS.m_open)(NULL,"FindDVDDrive",0);

	for(i=0;i<NTMS_LIST_SIZE;i++) memset(&list[i],0,sizeof(NTMS_GUID));

	rc = (*NTMS.m_enumerate)(session, NULL, &list[0], &n, NTMS_DRIVE, 0);
	if(rc==ERROR_SUCCESS) {
	  DWORD i;
		for(i=0;i<n;i++) {
			NTMS_OBJECTINFORMATION info;
			memset(&info,0,sizeof(NTMS_OBJECTINFORMATION));
			info.dwSize = sizeof(NTMS_OBJECTINFORMATION);
			info.dwType = NTMS_DRIVE;

			copy_guid(&info.ObjectGuid, &list[i]);

			rc = (*NTMS.m_info)(session,&list[i],&info);
			if(rc==ERROR_SUCCESS && info.Enabled) {

				NTMS_OBJECTINFORMATION infotype;
				memset(&infotype,0,sizeof(NTMS_OBJECTINFORMATION));
				infotype.dwSize = sizeof(NTMS_OBJECTINFORMATION);
				infotype.dwType = NTMS_DRIVE_TYPE;

				copy_guid(&infotype.ObjectGuid, &info.Info.Drive.DriveType);

				rc = (*NTMS.m_info)(session,&info.Info.Drive.DriveType,&infotype);
				if(rc==ERROR_SUCCESS && 
					infotype.Info.DriveType.DeviceType == FILE_DEVICE_DVD) {

					while(c!=NULL) {
						CandidateDrive *n = c->next;
						if(strcmp(c->name,infotype.Info.DriveType.szProduct)==0) {
							c->type = DRIVE_TYPE_DVDROM;
						}
						c = n;
					}
				}
			}
		}
	}
	(*NTMS.m_close)(session);
	FreeLibrary(NTMS.m_dll);
}
