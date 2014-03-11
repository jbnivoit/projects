all : testColumnProvider.exe

testColumnProvider.exe : testColumnProvider.cpp
	cl -I. -nologo -Gf -W3 -I..\..\perl\p561\lib\CORE -I..\..\perl\p561\include -I. -I.. -DWIN32 -D_CONSOLE -DNO_STRICT  -Od -MD -Zi   -DPERL_MSVCRT_READFIX -otestColumnProvider.exe testColumnProvider.cpp d:\build\perl\p561\lib\CORE\perl56.lib user32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib -libpath:c:\perl\bin /SUBSYSTEM:windows


