
@rem dont use -DWITH_DEBUG, as it clashes with PerlIO...

@del d:\log1.txt
@del d:\log2.txt

cl -c -I. -nologo -Gf -W3 -I..\perl\p561\lib\CORE -I..\perl\p561\include -I. -I.. -DWIN32 -D_CONSOLE -DNO_STRICT   -Od -MD -Zi   -DDEBUGGING  -DPERL_IMPLICIT_CONTEXT -DPERL_MSVCRT_READFIX  -DPERLCORE -UPERLDLL -Fo.\perlshellexe.obj .\perlshellexe.cpp
@rem -DPERL_IMPLICIT_SYS

link  -nologo -debug  -out:.\perlshellexe.exe perlshellexe.obj d:\build/perl/p561/lib/CORE/perl56.lib user32.lib advapi32.lib shell32.lib ole32.lib -libpath:c:\perl\bin

perlshellexe.exe