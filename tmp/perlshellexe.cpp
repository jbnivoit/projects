// -*- c++ -*-
#include <stdlib.h>
#include <stdio.h>

//
// There are 2 ways to compile this program: 
//    1/ using Win32ShellExt in a DLL (perlshellext.dll)
//    2/ building Win32ShellExt within this .cpp (for testing).
//
#ifdef Win32ShellExt_DLL
 #define WIN32SHELLEXTAPI_IMPORT
 #include "Win32ShellExt.h"
#else
 #define DllMain            dummyDllMain          
 #define DllCanUnloadNow	   dummyDllCanUnloadNow  
 #define DllGetClassObject  dummyDllGetClassObject

 static void debug_printf(void *f, char *fmt, ...);
 #define _DEBUG_H
 #define EXTDEBUG(x) { void *f=NULL; debug_printf x; }

 #include "Win32ShellExt.cpp"
#endif

#pragma data_seg(".text")
#define INITGUID
#include <initguid.h>
#include <shlguid.h>
// {9054D564-CBB4-48b4-9DAE-146A1CFDCDE5}
// {3FEE610F-2262-4d0b-85A4-68F733538022}
DEFINE_GUID(clsid_renmp3, 0x3FEE610F, 0x2262, 0x4d0b, 0x85, 0xA4, 0x68, 0xF7, 0x33, 0x53, 0x80, 0x22);
//DEFINE_GUID(clsid, 0x9054d564, 0xcbb4, 0x48b4, 0x9d, 0xae, 0x14, 0x6a, 0x1c, 0xfd, 0xcd, 0xe5);
#pragma data_seg()

static void debug_printf(void *f, char *fmt, ...) {
  va_list ap;

  va_start(ap,fmt);
  win32_printf(fmt, ap);
  va_end(ap);
}

int main(int argc, char **argv)
{
  PL_debug=64;
  /*
        1  p  Tokenizing and parsing
        2  s  Stack snapshots
        4  l  Context (loop) stack processing
        8  t  Trace execution
       16  o  Method and overloading resolution
       32  c  String/numeric conversions
       64  P  Print preprocessor command for -P, source file input state
      128  m  Memory allocation
      256  f  Format processing
      512  r  Regular expression parsing and execution
     1024  x  Syntax tree dump
     2048  u  Tainting checks
     4096  L  Memory leaks (needs -DLEAKTEST when compiling Perl)
     8192  H  Hash dump -- usurps values()
    16384  X  Scratchpad allocation
    32768  D  Cleaning up
    65536  S  Thread synchronization
   131072  T  Tokenising
  */
  PL_debug |= 0x80000000;

  printf("%s main begin\n",argv[0]);
  IClassFactory *factory=0;

#ifdef Win32ShellExt_DLL
  HRESULT (*DllGetClassObject)(REFCLSID rclsid, REFIID riid, LPVOID *ppvOut);
  HMODULE dll = LoadLibrary("perlshellext.dll");
  DllGetClassObject = (HRESULT (*)(REFCLSID , REFIID , LPVOID *))GetProcAddress(dll,"DllGetClassObject");
#endif
  DllGetClassObject(clsid_renmp3, IID_IClassFactory, (void**)&factory);
  
  if(factory==0) {
    printf("cannot get class factory\n");
    return EXIT_FAILURE;
  }
  
  IUnknown *ext=0;
  factory->CreateInstance(NULL,IID_IUnknown,(void**)&ext);
  
  static char *item = "c:\\mounted\\mp3\\freedom.mp3";
  ((PerlShellExt*)ext)->Initialize(1,&item);
  
  IContextMenu *sh=0;
  ext->QueryInterface(IID_IContextMenu,(void**)&sh);
  if(sh==0) {
    printf("cannot get IContextMenu interface\n");
    return EXIT_FAILURE;
  }
  ext->Release();

  printf("%s main before IContextMenu::QueryContextMenu call\n",argv[0]);
  sh->QueryContextMenu(NULL,0,0,0,CMF_NORMAL);

  CMINVOKECOMMANDINFO info;
  memset(&info,0,sizeof(CMINVOKECOMMANDINFO));
  printf("%s main before IContextMenu::InvokeCommand call\n",argv[0]);
  sh->InvokeCommand(&info);
  
  sh->Release();
  factory->Release();
#ifdef Win32ShellExt_DLL
  FreeLibrary(dll);
#endif
  printf("%s main end\n",argv[0]);
  
  // This didn't work out. the program still core dumps in crt...
  //  extern int _nstream;
  //_nstream=0; // this keeps CRT from flushing all FILE objects, thereby preventing a core dump due to Perl's mingling with IOs.
  exit(EXIT_SUCCESS);
  return EXIT_SUCCESS;
}

