// -*- c++ -*- 

#define INC_OLE2        // WIN32, get ole2 from windows.h

#include <windows.h>
#include <windowsx.h>
#include <shlobj.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>

UINT      g_cRefThisDll = 0;    // Reference count of this DLL.
HINSTANCE g_hmodThisDll = NULL;	// Handle to this DLL itself.

extern "C" int APIENTRY
DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
  if (dwReason == DLL_PROCESS_ATTACH)
    {
      // Extension DLL one-time initialization

      g_hmodThisDll = hInstance;
    }

  return 1;   // ok
}

STDAPI DllCanUnloadNow(void)
{
  return (g_cRefThisDll == 0 ? S_OK : S_FALSE);
}

STDAPI DllGetClassObject(REFCLSID rclsid, REFIID riid, LPVOID *ppvOut)
{
  *ppvOut = NULL;
  {
    FILE *f = fopen("d:\\log3.txt","w");
    fprintf(f,"DllGetClassObject\n");
    fflush(f);
    fclose(f);
    return E_FAIL;
  }
}
