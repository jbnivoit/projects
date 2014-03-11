@del d:\log1.txt
@del d:\log2.txt
@del d:\log3.txt

@rem release
@rem cl -c -I. -nologo -Gf -W3 -I..\perl\p561\lib\CORE -I..\perl\p561\include -I. -I.. -DWIN32 -D_CONSOLE -DNO_STRICT   -O1 -MD  -DPERL_MSVCRT_READFIX -Fo.\win32shellext.obj .\win32shellext.cpp

@rem debug
cl -c -I. -nologo -Gf -W3 -I..\perl\p561\lib\CORE -I..\perl\p561\include -I. -I.. -DWIN32 -D_CONSOLE -DNO_STRICT   -Od -MD -Zi  -DPERL_MSVCRT_READFIX  -DWITH_DEBUG -Fo.\win32shellext.obj .\win32shellext.cpp

@rem cl -c -I. -nologo -Gf -W3 -I..\perl\p561\lib\CORE -I..\perl\p561\include -I. -I.. -DWIN32 -D_CONSOLE -DNO_STRICT   -Od -MD -Zi  -DPERL_MSVCRT_READFIX  -DWITH_DEBUG -Fo.\PerlQueryInfoExt.obj PerlQueryInfoExt.cpp


cl -c -I. -nologo -Gf -W3 -DWIN32 -D_CONSOLE -DNO_STRICT -DWITH_DEBUG   -Od -MD -Zi -Fo.\debug.obj .\debug.cpp

@rem link -dll -def:Win32ShellExt.def  -out:.\perlext.dll @C:\DOCUME~1\jb\LOCALS~1\Temp\nm8E1.tmp

link -dll -def:Win32ShellExt.def -nologo  -out:.\perlshellext.dll Win32ShellExt.obj debug.obj d:\build\perl\p561\lib\CORE\perl56.lib user32.lib advapi32.lib shell32.lib ole32.lib -libpath:c:\perl\bin /SUBSYSTEM:windows
@rem  -verbose

@rem  -libpath:c:\perl\5.6.1\bin\MSWin32-x86

@rem link -out:..\..\lib\auto\attrs\attrs.dll -dll -nologo -nodefaultlib -release  -libpath:"c:\perl\5.6.1\lib\MSWin32-x86\CORE"  -machine:x86 attrs.obj   ..\..\lib\CORE\perl56.lib oldnames.lib kernel32.lib user32.lib gdi32.lib winspool.lib  comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib  netapi32.lib uuid.lib wsock32.lib mpr.lib winmm.lib version.lib odbc32.lib odbccp32.lib msvcrt.lib -def:attrs.def
