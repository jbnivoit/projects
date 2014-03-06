#TARGETOS=WIN95
#APPVER=4.0
TARGETOS=WINNT
APPVER=5.0

!include <win32.mak>

all: find.exe

candidate.obj: candidate.c candidate.h
    $(cc) $(cflags) $(cvars) $(cdebug) candidate.c

FindDVDDrive.obj: FindDVDDrive.c candidate.h
    $(cc) $(cflags) $(cvars) $(cdebug) FindDVDDrive.c

ntms_candidate.obj: ntms_candidate.c 
    $(cc) $(cflags) $(cvars) $(cdebug) ntms_candidate.c 

find.exe: FindDVDDrive.obj candidate.obj ntms_candidate.obj
    $(link) $(linkdebug) -out:find.exe FindDVDDrive.obj candidate.obj ntms_candidate.obj kernel32.lib user32.lib advapi32.lib

#gdi32.lib winspool.lib comdlg32.lib  shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib



