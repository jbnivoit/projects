# This Makefile is for the Win32::ShellExt extension to perl.
#
# It was generated automatically by MakeMaker version
# 5.49_01 (Revision: 1.6) from the contents of
# Makefile.PL. Don't edit this file, edit Makefile.PL instead.
#
#       ANY CHANGES MADE HERE WILL BE LOST!
#
#   MakeMaker ARGV: ()
#
#   MakeMaker Parameters:

#     ABSTRACT => q[Allows to write Windows shell extensions in Perl]
#     AUTHOR => q[Jean-Baptiste Nivoit <jbnivoit@hotmail.com>]
#     C => q[Win32ShellExt.cpp debug.cpp]
#     DEFINE => q[]
#     H => q[PerlQueryInfoExt.h Win32ShellExt.h debug.h exports.h PerlQueryInfoExt.cpp]
#     INC => q[]
#     INST_BIN => [q[perlshellext.dll]]
#     LIBS => [q[]]
#     NAME => q[Win32::ShellExt]
#     PMLIBDIRS => [q[ShellExt], q[ShellExt/CopyHook], q[ShellExt/ColumnProvider], q[ShellExt/QueryInfo], q[ShellExt/CtxtMenu], q[ShellExt/DragAndDropHandler]]
#     PREREQ_PM => { Win32::TieRegistry=>q[0.23] }
#     VERSION_FROM => q[ShellExt.pm]
#     XS => { ShellExt/CopyHook.xs=>q[ShellExt/CopyHook.c] }
#     dist => { COMPRESS=>q[gzip -9f], SUFFIX=>q[gz] }

# --- MakeMaker post_initialize section:


# --- MakeMaker const_config section:

# These definitions are from config.sh (via C:/Perl/lib/Config.pm)

# They may have been overridden via Makefile.PL or on the command line
AR = lib
CC = cl
CCCDLFLAGS =  
CCDLFLAGS =  
DLEXT = dll
DLSRC = dl_win32.xs
LD = link
LDDLFLAGS = -dll -nologo -nodefaultlib -debug -pdb:none  -libpath:"c:\perl\lib\CORE"  -machine:x86
LDFLAGS = -nologo -nodefaultlib -debug -pdb:none  -libpath:"c:\perl\lib\CORE"  -machine:x86
LIBC = msvcrt.lib
LIB_EXT = .lib
OBJ_EXT = .obj
OSNAME = MSWin32
OSVERS = 4.0
RANLIB = rem
SO = dll
EXE_EXT = .exe
FULL_AR = 


# --- MakeMaker constants section:
AR_STATIC_ARGS = cr
NAME = Win32::ShellExt
DISTNAME = Win32-ShellExt
NAME_SYM = Win32_ShellExt
VERSION = 0.1
VERSION_SYM = 0_1
XS_VERSION = 0.1
INST_BIN = ARRAY(0x1b9b89c)
INST_EXE = blib\script
INST_LIB = blib\lib
INST_ARCHLIB = blib\arch
INST_SCRIPT = blib\script
PREFIX = c:\perl
INSTALLDIRS = site
INSTALLPRIVLIB = c:\perl\lib
INSTALLARCHLIB = c:\perl\lib
INSTALLSITELIB = c:\perl\site\lib
INSTALLSITEARCH = c:\perl\site\lib
INSTALLBIN = c:\perl\bin
INSTALLSCRIPT = c:\perl\bin
PERL_LIB = c:\perl\lib
PERL_ARCHLIB = c:\perl\lib
SITELIBEXP = c:\perl\site\lib
SITEARCHEXP = c:\perl\site\lib
LIBPERL_A = libperl.lib
FIRST_MAKEFILE = Makefile
MAKE_APERL_FILE = Makefile.aperl
PERLMAINCC = $(CC)
PERL_INC = C:\perl\lib\CORE
PERL = C:\Perl\bin\perl.exe
FULLPERL = C:\Perl\bin\perl.exe
PERLRUN = C:\Perl\bin\perl.exe
PERLRUNINST = C:\Perl\bin\perl.exe -I$(INST_ARCHLIB) -I$(INST_LIB)
TEST_LIBS =  -ID:\build\Win32-ShellExt-0.1\blib\arch -ID:\build\Win32-ShellExt-0.1\blib\lib
FULL_AR = 
PERL_CORE = 0

VERSION_MACRO = VERSION
DEFINE_VERSION = -D$(VERSION_MACRO)=\"$(VERSION)\"
XS_VERSION_MACRO = XS_VERSION
XS_DEFINE_VERSION = -D$(XS_VERSION_MACRO)=\"$(XS_VERSION)\"

MAKEMAKER = C:/Perl/lib/ExtUtils/MakeMaker.pm
MM_VERSION = 5.49_01

# FULLEXT = Pathname for extension directory (eg Foo/Bar/Oracle).
# BASEEXT = Basename part of FULLEXT. May be just equal FULLEXT. (eg Oracle)
# ROOTEXT = Directory part of FULLEXT with leading slash (eg /DBD)  !!! Deprecated from MM 5.32  !!!
# PARENT_NAME = NAME without BASEEXT and no trailing :: (eg Foo::Bar)
# DLBASE  = Basename part of dynamic library. May be just equal BASEEXT.
FULLEXT = Win32\ShellExt
BASEEXT = ShellExt
PARENT_NAME = Win32
DLBASE = $(BASEEXT)
VERSION_FROM = ShellExt.pm
INC = 
DEFINE = 
OBJECT = 
LDFROM = $(OBJECT)
LINKTYPE = dynamic

# Handy lists of source code files:
XS_FILES= ShellExt/CopyHook.xs
C_FILES = 
O_FILES = 
H_FILES = 
HTMLLIBPODS    = 
HTMLSCRIPTPODS = 
MAN1PODS = 
MAN3PODS = ShellExt.pm \
	ShellExt/ColumnProvider.pm \
	ShellExt/CopyHook.pm \
	ShellExt/CtxtMenu.pm \
	ShellExt/DragAndDropHandler.pm \
	ShellExt/QueryInfo.pm
HTMLEXT = html
INST_MAN1DIR = blib\man1
INSTALLMAN1DIR = c:\perl\man\man1
MAN1EXT = 1
INST_MAN3DIR = blib\man3
INSTALLMAN3DIR = c:\perl\man\man3
MAN3EXT = 3

# work around a famous dec-osf make(1) feature(?):
makemakerdflt: all

.SUFFIXES: .xs .c .C .cpp .cxx .cc $(OBJ_EXT)

# Nick wanted to get rid of .PRECIOUS. I don't remember why. I seem to 
# recall, that some make implementations will delete the Makefile when we 
# rebuild it. Because we call false(1) when we rebuild it. So make(1) is 
# not completely wrong when it does so. Our milage may vary.
# .PRECIOUS: Makefile    # seems to be not necessary anymore

.PHONY: all config static dynamic test linkext manifest

# Where is the Config information that we are using/depend on
CONFIGDEP = $(PERL_ARCHLIB)\Config.pm $(PERL_INC)\config.h

# Where to put things:
INST_LIBDIR      = $(INST_LIB)\Win32
INST_ARCHLIBDIR  = $(INST_ARCHLIB)\Win32

INST_AUTODIR     = $(INST_LIB)\auto\$(FULLEXT)
INST_ARCHAUTODIR = $(INST_ARCHLIB)\auto\$(FULLEXT)

INST_STATIC  =
INST_DYNAMIC =
INST_BOOT    =

EXPORT_LIST = ShellExt.def

PERL_ARCHIVE = $(PERL_INC)\perl56.lib

TO_INST_PM = ShellExt.pm \
	ShellExt/ColumnProvider.pm \
	ShellExt/ColumnProvider.pm~ \
	ShellExt/ColumnProvider/JpgSize.pm \
	ShellExt/ColumnProvider/JpgSize.pm~ \
	ShellExt/CopyHook.c \
	ShellExt/CopyHook.pm \
	ShellExt/CopyHook.pm~ \
	ShellExt/CopyHook.xs \
	ShellExt/CopyHook/Veto.pm \
	ShellExt/CopyHook/Veto.pm~ \
	ShellExt/CopyHook/constants.h \
	ShellExt/CopyHook/constants.h~ \
	ShellExt/CopyHook/constants.pl \
	ShellExt/CopyHook/constants.xs \
	ShellExt/CopyHook/constants.xs~ \
	ShellExt/CtxtMenu.pm \
	ShellExt/CtxtMenu.pm~ \
	ShellExt/CtxtMenu/Base64Decode.pm \
	ShellExt/CtxtMenu/Base64Encode.pm \
	ShellExt/CtxtMenu/BinHex.pm \
	ShellExt/CtxtMenu/CopyMP3InfoToClipboard.pm \
	ShellExt/CtxtMenu/CopyPath.pm \
	ShellExt/CtxtMenu/CopyPath.pm~ \
	ShellExt/CtxtMenu/ExpandTabs.pm \
	ShellExt/CtxtMenu/FIGlet.pm \
	ShellExt/CtxtMenu/Gunzip.pm \
	ShellExt/CtxtMenu/Gzip.pm \
	ShellExt/CtxtMenu/Join.pm \
	ShellExt/CtxtMenu/LinkExtor.pm \
	ShellExt/CtxtMenu/MD5.pm \
	ShellExt/CtxtMenu/MagickConvert.pm \
	ShellExt/CtxtMenu/MagickConvertGIF.pm \
	ShellExt/CtxtMenu/MagickConvertJPG.pm \
	ShellExt/CtxtMenu/PDF.pm \
	ShellExt/CtxtMenu/RegisterDll.pm \
	ShellExt/CtxtMenu/RenameMP3.pm \
	ShellExt/CtxtMenu/RenameWithPrefix.pm \
	ShellExt/CtxtMenu/RenameWithPrefix.pm~ \
	ShellExt/CtxtMenu/SwapFileNames.pm \
	ShellExt/CtxtMenu/Tar.pm \
	ShellExt/CtxtMenu/UnexpandTabs.pm \
	ShellExt/CtxtMenu/UnregisterDll.pm \
	ShellExt/CtxtMenu/Whitespace.pm \
	ShellExt/CtxtMenu/XML.pm \
	ShellExt/CtxtMenu/Zip.pm \
	ShellExt/DragAndDropHandler.pm \
	ShellExt/DragAndDropHandler.pm~ \
	ShellExt/DragAndDropHandler/Zip.pm \
	ShellExt/QueryInfo.pm \
	ShellExt/QueryInfo.pm~ \
	ShellExt/QueryInfo/ELisp.pm \
	ShellExt/QueryInfo/ELisp.pm~ \
	ShellExt/QueryInfo/JpgSize.pm \
	ShellExt/QueryInfo/JpgSize.pm~ \
	ShellExt/QueryInfo/LineCount.pm \
	ShellExt/QueryInfo/LineCount.pm~ \
	ShellExt/QueryInfo/MP3.pm \
	ShellExt/QueryInfo/MP3.pm~ \
	ShellExt/QueryInfo/PDF.pm \
	ShellExt/QueryInfo/PDF.pm~ \
	ShellExt/QueryInfo/PM.pm \
	ShellExt/QueryInfo/PM.pm~ \
	ShellExt/QueryInfo/Shortcut.pm \
	ShellExt/QueryInfo/Shortcut.pm~ \
	ShellExt/QueryInfo/TeX.pm \
	ShellExt/QueryInfo/TeX.pm~ \
	ShellExt/QueryInfo/Zip.pm \
	ShellExt/QueryInfo/Zip.pm~ \
	ShellExt/Search.pm \
	ShellExt/Search.pm~ \
	ShellExt/typemap \
	test2.pl \
	test3.pl \
	test4.pl

PM_TO_BLIB = ShellExt.pm \
	blib\lib\Win32\ShellExt.pm \
	ShellExt/QueryInfo/MP3.pm~ \
	blib\lib\Win32\ShellExt\QueryInfo\MP3.pm~ \
	ShellExt/CtxtMenu/Base64Encode.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\Base64Encode.pm \
	ShellExt/CtxtMenu/Gzip.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\Gzip.pm \
	ShellExt/CtxtMenu/XML.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\XML.pm \
	ShellExt/CopyHook/constants.h \
	blib\lib\Win32\ShellExt\CopyHook\constants.h \
	ShellExt/CopyHook.pm~ \
	blib\lib\Win32\ShellExt\CopyHook.pm~ \
	ShellExt/QueryInfo/PM.pm \
	blib\lib\Win32\ShellExt\QueryInfo\PM.pm \
	ShellExt/CtxtMenu/RegisterDll.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\RegisterDll.pm \
	ShellExt/CopyHook/constants.pl \
	blib\lib\Win32\ShellExt\CopyHook\constants.pl \
	ShellExt/CopyHook.xs \
	blib\lib\Win32\ShellExt\CopyHook.xs \
	test2.pl \
	blib\lib\Win32\test2.pl \
	ShellExt/CtxtMenu/Join.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\Join.pm \
	ShellExt/CopyHook/constants.h~ \
	blib\lib\Win32\ShellExt\CopyHook\constants.h~ \
	ShellExt/ColumnProvider/JpgSize.pm~ \
	blib\lib\Win32\ShellExt\ColumnProvider\JpgSize.pm~ \
	ShellExt/CtxtMenu/CopyPath.pm~ \
	blib\lib\Win32\ShellExt\CtxtMenu\CopyPath.pm~ \
	ShellExt/QueryInfo/Shortcut.pm~ \
	blib\lib\Win32\ShellExt\QueryInfo\Shortcut.pm~ \
	ShellExt/CtxtMenu.pm \
	blib\lib\Win32\ShellExt\CtxtMenu.pm \
	test4.pl \
	blib\lib\Win32\test4.pl \
	ShellExt/QueryInfo/MP3.pm \
	blib\lib\Win32\ShellExt\QueryInfo\MP3.pm \
	ShellExt/CtxtMenu/MagickConvertJPG.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\MagickConvertJPG.pm \
	ShellExt/CtxtMenu/MD5.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\MD5.pm \
	ShellExt/QueryInfo/ELisp.pm \
	blib\lib\Win32\ShellExt\QueryInfo\ELisp.pm \
	ShellExt/CtxtMenu/UnexpandTabs.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\UnexpandTabs.pm \
	ShellExt/QueryInfo/PDF.pm \
	blib\lib\Win32\ShellExt\QueryInfo\PDF.pm \
	ShellExt/Search.pm \
	blib\lib\Win32\ShellExt\Search.pm \
	ShellExt/CtxtMenu/RenameWithPrefix.pm~ \
	blib\lib\Win32\ShellExt\CtxtMenu\RenameWithPrefix.pm~ \
	ShellExt/ColumnProvider.pm~ \
	blib\lib\Win32\ShellExt\ColumnProvider.pm~ \
	ShellExt/QueryInfo/LineCount.pm~ \
	blib\lib\Win32\ShellExt\QueryInfo\LineCount.pm~ \
	ShellExt/CopyHook/constants.xs \
	blib\lib\Win32\ShellExt\CopyHook\constants.xs \
	ShellExt/ColumnProvider/JpgSize.pm \
	blib\lib\Win32\ShellExt\ColumnProvider\JpgSize.pm \
	ShellExt/CopyHook/Veto.pm~ \
	blib\lib\Win32\ShellExt\CopyHook\Veto.pm~ \
	ShellExt/CtxtMenu/MagickConvert.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\MagickConvert.pm \
	ShellExt/QueryInfo/ELisp.pm~ \
	blib\lib\Win32\ShellExt\QueryInfo\ELisp.pm~ \
	ShellExt/CtxtMenu/UnregisterDll.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\UnregisterDll.pm \
	ShellExt/CtxtMenu.pm~ \
	blib\lib\Win32\ShellExt\CtxtMenu.pm~ \
	ShellExt/CtxtMenu/Base64Decode.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\Base64Decode.pm \
	ShellExt/CtxtMenu/RenameWithPrefix.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\RenameWithPrefix.pm \
	ShellExt/CtxtMenu/CopyMP3InfoToClipboard.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\CopyMP3InfoToClipboard.pm \
	ShellExt/CopyHook.c \
	blib\lib\Win32\ShellExt\CopyHook.c \
	ShellExt/QueryInfo.pm \
	blib\lib\Win32\ShellExt\QueryInfo.pm \
	ShellExt/DragAndDropHandler.pm \
	blib\lib\Win32\ShellExt\DragAndDropHandler.pm \
	ShellExt/QueryInfo/Zip.pm \
	blib\lib\Win32\ShellExt\QueryInfo\Zip.pm \
	ShellExt/CtxtMenu/SwapFileNames.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\SwapFileNames.pm \
	ShellExt/QueryInfo.pm~ \
	blib\lib\Win32\ShellExt\QueryInfo.pm~ \
	ShellExt/QueryInfo/JpgSize.pm \
	blib\lib\Win32\ShellExt\QueryInfo\JpgSize.pm \
	ShellExt/CtxtMenu/Gunzip.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\Gunzip.pm \
	ShellExt/CtxtMenu/MagickConvertGIF.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\MagickConvertGIF.pm \
	ShellExt/DragAndDropHandler.pm~ \
	blib\lib\Win32\ShellExt\DragAndDropHandler.pm~ \
	ShellExt/DragAndDropHandler/Zip.pm \
	blib\lib\Win32\ShellExt\DragAndDropHandler\Zip.pm \
	ShellExt/CopyHook/Veto.pm \
	blib\lib\Win32\ShellExt\CopyHook\Veto.pm \
	ShellExt/CtxtMenu/RenameMP3.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\RenameMP3.pm \
	ShellExt/CtxtMenu/Whitespace.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\Whitespace.pm \
	ShellExt/CtxtMenu/FIGlet.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\FIGlet.pm \
	ShellExt/QueryInfo/PDF.pm~ \
	blib\lib\Win32\ShellExt\QueryInfo\PDF.pm~ \
	ShellExt/CopyHook/constants.xs~ \
	blib\lib\Win32\ShellExt\CopyHook\constants.xs~ \
	test3.pl \
	blib\lib\Win32\test3.pl \
	ShellExt/CtxtMenu/PDF.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\PDF.pm \
	ShellExt/CtxtMenu/BinHex.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\BinHex.pm \
	ShellExt/CtxtMenu/LinkExtor.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\LinkExtor.pm \
	ShellExt/QueryInfo/PM.pm~ \
	blib\lib\Win32\ShellExt\QueryInfo\PM.pm~ \
	ShellExt/QueryInfo/LineCount.pm \
	blib\lib\Win32\ShellExt\QueryInfo\LineCount.pm \
	ShellExt/typemap \
	blib\lib\Win32\ShellExt\typemap \
	ShellExt/QueryInfo/Shortcut.pm \
	blib\lib\Win32\ShellExt\QueryInfo\Shortcut.pm \
	ShellExt/QueryInfo/TeX.pm \
	blib\lib\Win32\ShellExt\QueryInfo\TeX.pm \
	ShellExt/ColumnProvider.pm \
	blib\lib\Win32\ShellExt\ColumnProvider.pm \
	ShellExt/QueryInfo/Zip.pm~ \
	blib\lib\Win32\ShellExt\QueryInfo\Zip.pm~ \
	ShellExt/QueryInfo/TeX.pm~ \
	blib\lib\Win32\ShellExt\QueryInfo\TeX.pm~ \
	ShellExt/CtxtMenu/Tar.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\Tar.pm \
	ShellExt/CtxtMenu/Zip.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\Zip.pm \
	ShellExt/QueryInfo/JpgSize.pm~ \
	blib\lib\Win32\ShellExt\QueryInfo\JpgSize.pm~ \
	ShellExt/CopyHook.pm \
	blib\lib\Win32\ShellExt\CopyHook.pm \
	ShellExt/CtxtMenu/ExpandTabs.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\ExpandTabs.pm \
	ShellExt/Search.pm~ \
	blib\lib\Win32\ShellExt\Search.pm~ \
	ShellExt/CtxtMenu/CopyPath.pm \
	blib\lib\Win32\ShellExt\CtxtMenu\CopyPath.pm


# --- MakeMaker tool_autosplit section:

# Usage: $(AUTOSPLITFILE) FileToSplit AutoDirToSplitInto
AUTOSPLITFILE = $(PERL) "-I$(PERL_ARCHLIB)" "-I$(PERL_LIB)" -MAutoSplit  -e "autosplit($$ARGV[0], $$ARGV[1], 0, 1, 1);"


# --- MakeMaker tool_xsubpp section:


# --- MakeMaker tools_other section:

SHELL = cmd /x /c
CHMOD = $(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e chmod
CP = $(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e cp
LD = link
MV = $(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e mv
NOOP = rem
RM_F = $(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f
RM_RF = $(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_rf
TEST_F = $(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e test_f
TOUCH = $(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e touch
UMASK_NULL = umask 0
DEV_NULL = > NUL

# The following is a portable way to say mkdir -p
# To see which directories are created, change the if 0 to if 1
MKPATH = $(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e mkpath

# This helps us to minimize the effect of the .exists files A yet
# better solution would be to have a stable file in the perl
# distribution with a timestamp of zero. But this solution doesn't
# need any changes to the core distribution and works with older perls
EQUALIZE_TIMESTAMP = $(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e eqtime

# Here we warn users that an old packlist file was found somewhere,
# and that they should call some uninstall routine
WARN_IF_OLD_PACKLIST = $(PERL) -lwe "exit unless -f $$ARGV[0];" \
-e "print 'WARNING: I have found an old package in';" \
-e "print '	', $$ARGV[0], '.';" \
-e "print 'Please make sure the two installations are not conflicting';"

UNINST=0
VERBINST=1

MOD_INSTALL = $(PERL) -I$(INST_LIB) -I$(PERL_LIB) -MExtUtils::Install \
-e "install({ @ARGV },'$(VERBINST)',0,'$(UNINST)');"

DOC_INSTALL = $(PERL) -e "$$\=\"\n\n\";" \
-e "print '=head2 ', scalar(localtime), ': C<', shift, '>', ' L<', $$arg=shift, '|', $$arg, '>';" \
-e "print '=over 4';" \
-e "while (defined($$key = shift) and defined($$val = shift)) { print '=item *';print 'C<', \"$$key: $$val\", '>'; }" \
-e "print '=back';"

UNINSTALL =   $(PERL) -MExtUtils::Install \
-e "uninstall($$ARGV[0],1,1); print \"\nUninstall is deprecated. Please check the";" \
-e "print \" packlist above carefully.\n  There may be errors. Remove the\";" \
-e "print \" appropriate files manually.\n  Sorry for the inconveniences.\n\""


# --- MakeMaker dist section:

DISTVNAME = $(DISTNAME)-$(VERSION)
TAR  = tar
TARFLAGS = cvf
ZIP  = zip
ZIPFLAGS = -r
COMPRESS = gzip -9f
SUFFIX = gz
SHAR = shar
PREOP = @$(NOOP)
POSTOP = @$(NOOP)
TO_UNIX = @$(NOOP)
CI = ci -u
RCS_LABEL = rcs -Nv$(VERSION_SYM): -q
DIST_CP = best
DIST_DEFAULT = tardist


# --- MakeMaker macro section:


# --- MakeMaker depend section:


# --- MakeMaker cflags section:


# --- MakeMaker const_loadlibs section:


# --- MakeMaker const_cccmd section:


# --- MakeMaker post_constants section:


# --- MakeMaker pasthru section:
PASTHRU = -nologo

# --- MakeMaker c_o section:


# --- MakeMaker xs_c section:


# --- MakeMaker xs_o section:


# --- MakeMaker top_targets section:

#all ::	config $(INST_PM) subdirs linkext manifypods

all :: pure_all htmlifypods manifypods
	@$(NOOP)

pure_all :: config pm_to_blib subdirs linkext
	@$(NOOP)

subdirs :: $(MYEXTLIB)
	@$(NOOP)

config :: Makefile $(INST_LIBDIR)\.exists
	@$(NOOP)

config :: $(INST_ARCHAUTODIR)\.exists
	@$(NOOP)

config :: $(INST_AUTODIR)\.exists
	@$(NOOP)

$(INST_AUTODIR)\.exists :: C:\perl\lib\CORE\perl.h
	@$(MKPATH) $(INST_AUTODIR)
	@$(EQUALIZE_TIMESTAMP) C:\perl\lib\CORE\perl.h $(INST_AUTODIR)\.exists

	-@$(CHMOD) $(PERM_RWX) $(INST_AUTODIR)

$(INST_LIBDIR)\.exists :: C:\perl\lib\CORE\perl.h
	@$(MKPATH) $(INST_LIBDIR)
	@$(EQUALIZE_TIMESTAMP) C:\perl\lib\CORE\perl.h $(INST_LIBDIR)\.exists

	-@$(CHMOD) $(PERM_RWX) $(INST_LIBDIR)

$(INST_ARCHAUTODIR)\.exists :: C:\perl\lib\CORE\perl.h
	@$(MKPATH) $(INST_ARCHAUTODIR)
	@$(EQUALIZE_TIMESTAMP) C:\perl\lib\CORE\perl.h $(INST_ARCHAUTODIR)\.exists

	-@$(CHMOD) $(PERM_RWX) $(INST_ARCHAUTODIR)

config :: $(INST_MAN3DIR)\.exists
	@$(NOOP)


$(INST_MAN3DIR)\.exists :: C:\perl\lib\CORE\perl.h
	@$(MKPATH) $(INST_MAN3DIR)
	@$(EQUALIZE_TIMESTAMP) C:\perl\lib\CORE\perl.h $(INST_MAN3DIR)\.exists

	-@$(CHMOD) $(PERM_RWX) $(INST_MAN3DIR)

help:
	perldoc ExtUtils::MakeMaker

Version_check:
	@$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) \
		-MExtUtils::MakeMaker=Version_check \
		-e "Version_check('$(MM_VERSION)')"


# --- MakeMaker linkext section:

linkext :: $(LINKTYPE)
	@$(NOOP)


# --- MakeMaker dlsyms section:

ShellExt.def: Makefile.PL
	$(PERL) "-I$(PERL_ARCHLIB)" "-I$(PERL_LIB)" -MExtUtils::Mksymlists \
     -e "Mksymlists('NAME'=>\"Win32::ShellExt\", 'DLBASE' => '$(BASEEXT)', 'DL_FUNCS' => {  }, 'FUNCLIST' => [], 'IMPORTS' => {  }, 'DL_VARS' => []);"


# --- MakeMaker dynamic section:

## $(INST_PM) has been moved to the all: target.
## It remains here for awhile to allow for old usage: "make dynamic"
#dynamic :: Makefile $(INST_DYNAMIC) $(INST_BOOT) $(INST_PM)
dynamic :: Makefile $(INST_DYNAMIC) $(INST_BOOT)
	@$(NOOP)


# --- MakeMaker dynamic_bs section:

BOOTSTRAP =


# --- MakeMaker dynamic_lib section:


# --- MakeMaker static section:

## $(INST_PM) has been moved to the all: target.
## It remains here for awhile to allow for old usage: "make static"
#static :: Makefile $(INST_STATIC) $(INST_PM)
static :: Makefile $(INST_STATIC)
	@$(NOOP)


# --- MakeMaker static_lib section:


# --- MakeMaker htmlifypods section:

htmlifypods : pure_all
	@$(NOOP)


# --- MakeMaker manifypods section:

manifypods :
	@$(NOOP)


# --- MakeMaker processPL section:


# --- MakeMaker installbin section:


# --- MakeMaker subdirs section:

# none

# --- MakeMaker clean section:

# Delete temporary files but do not touch installed files. We don't delete
# the Makefile here so a later make realclean still has a makefile to use.

clean ::
	-$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_rf ShellExt/CopyHook.c ./blib $(MAKE_APERL_FILE) $(INST_ARCHAUTODIR)/extralibs.all perlmain.c tmon.out mon.out core core.*perl.*.? *perl.core so_locations pm_to_blib *$(OBJ_EXT) *$(LIB_EXT) perl.exe perl perl$(EXE_EXT) $(BOOTSTRAP) $(BASEEXT).bso $(BASEEXT).def lib$(BASEEXT).def $(BASEEXT).exp $(BASEEXT).x
	-$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e mv Makefile Makefile.old $(DEV_NULL)
clean ::
	-$(RM_F) *.pdb



# --- MakeMaker realclean section:
LLIBPERL = 

# Delete temporary files (via clean) and also delete installed files
realclean purge ::  clean
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_rf $(INST_AUTODIR) $(INST_ARCHAUTODIR)
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f  blib\lib\Win32\ShellExt.pm blib\lib\Win32\ShellExt\QueryInfo\MP3.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\Base64Encode.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\Gzip.pm blib\lib\Win32\ShellExt\CtxtMenu\XML.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CopyHook\constants.h blib\lib\Win32\ShellExt\CopyHook.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\PM.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\RegisterDll.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CopyHook\constants.pl blib\lib\Win32\ShellExt\CopyHook.xs
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\test2.pl blib\lib\Win32\ShellExt\CtxtMenu\Join.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CopyHook\constants.h~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\ColumnProvider\JpgSize.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\CopyPath.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\Shortcut.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu.pm blib\lib\Win32\test4.pl
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\MP3.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\MagickConvertJPG.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\MD5.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\ELisp.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\UnexpandTabs.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\PDF.pm blib\lib\Win32\ShellExt\Search.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\RenameWithPrefix.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\ColumnProvider.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\LineCount.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CopyHook\constants.xs
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\ColumnProvider\JpgSize.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CopyHook\Veto.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\MagickConvert.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\ELisp.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\UnregisterDll.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\Base64Decode.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\RenameWithPrefix.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\CopyMP3InfoToClipboard.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CopyHook.c blib\lib\Win32\ShellExt\QueryInfo.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\DragAndDropHandler.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\Zip.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\SwapFileNames.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\JpgSize.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\Gunzip.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\MagickConvertGIF.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\DragAndDropHandler.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\DragAndDropHandler\Zip.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CopyHook\Veto.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\RenameMP3.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\Whitespace.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\FIGlet.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\PDF.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CopyHook\constants.xs~ blib\lib\Win32\test3.pl
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\PDF.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\BinHex.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\LinkExtor.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\PM.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\LineCount.pm blib\lib\Win32\ShellExt\typemap
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\Shortcut.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\TeX.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\ColumnProvider.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\Zip.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\TeX.pm~ blib\lib\Win32\ShellExt\CtxtMenu\Tar.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\Zip.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\QueryInfo\JpgSize.pm~ blib\lib\Win32\ShellExt\CopyHook.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\ExpandTabs.pm blib\lib\Win32\ShellExt\Search.pm~
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_f blib\lib\Win32\ShellExt\CtxtMenu\CopyPath.pm
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Command -e rm_rf Makefile Makefile.old


# --- MakeMaker dist_basics section:

distclean :: realclean distcheck

distcheck :
	$(PERLRUN) -MExtUtils::Manifest=fullcheck \
		-e fullcheck

skipcheck :
	$(PERLRUN) -MExtUtils::Manifest=skipcheck \
		-e skipcheck

manifest :
	$(PERLRUN) -MExtUtils::Manifest=mkmanifest \
		-e mkmanifest

veryclean : realclean
	$(RM_F) *~ *.orig */*~ */*.orig


# --- MakeMaker dist_core section:

dist : $(DIST_DEFAULT)
	@$(PERL) -le "print \"Warning: Makefile possibly out of date with $$vf\" if " \
	    -e "-e ($$vf=\"$(VERSION_FROM)\") and -M $$vf < -M \"Makefile\";"

tardist : $(DISTVNAME).tar$(SUFFIX)

zipdist : $(DISTVNAME).zip

$(DISTVNAME).tar$(SUFFIX) : distdir
	$(PREOP)
	$(TO_UNIX)
	$(TAR) $(TARFLAGS) $(DISTVNAME).tar $(DISTVNAME)
	$(RM_RF) $(DISTVNAME)
	$(COMPRESS) $(DISTVNAME).tar
	$(POSTOP)

$(DISTVNAME).zip : distdir
	$(PREOP)
	$(ZIP) $(ZIPFLAGS) $(DISTVNAME).zip $(DISTVNAME)
	$(RM_RF) $(DISTVNAME)
	$(POSTOP)

uutardist : $(DISTVNAME).tar$(SUFFIX)
	uuencode $(DISTVNAME).tar$(SUFFIX) \
		$(DISTVNAME).tar$(SUFFIX) > \
		$(DISTVNAME).tar$(SUFFIX)_uu

shdist : distdir
	$(PREOP)
	$(SHAR) $(DISTVNAME) > $(DISTVNAME).shar
	$(RM_RF) $(DISTVNAME)
	$(POSTOP)


# --- MakeMaker dist_dir section:

distdir :
	$(RM_RF) $(DISTVNAME)
	$(PERLRUN) -MExtUtils::Manifest=manicopy,maniread \
		-e "manicopy(maniread(),'$(DISTVNAME)', '$(DIST_CP)');"


# --- MakeMaker dist_test section:

disttest : distdir
	cd $(DISTVNAME) && $(PERLRUN) Makefile.PL
	cd $(DISTVNAME) && $(MAKE)
	cd $(DISTVNAME) && $(MAKE) test


# --- MakeMaker dist_ci section:

ci :
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) -MExtUtils::Manifest=maniread \
		-e "@all = keys %{ maniread() };" \
		-e "print(\"Executing $(CI) @all\n\"); system(\"$(CI) @all\");" \
		-e "print(\"Executing $(RCS_LABEL) ...\n\"); system(\"$(RCS_LABEL) @all\");"


# --- MakeMaker install section:

install :: all pure_install doc_install install_registry

install_perl :: all pure_perl_install doc_perl_install

install_site :: all pure_site_install doc_site_install

install_ :: install_site
	@echo INSTALLDIRS not defined, defaulting to INSTALLDIRS=site

pure_install :: pure_$(INSTALLDIRS)_install

doc_install :: doc_$(INSTALLDIRS)_install
	@echo Appending installation info to $(INSTALLARCHLIB)/perllocal.pod

pure__install : pure_site_install
	@echo INSTALLDIRS not defined, defaulting to INSTALLDIRS=site

doc__install : doc_site_install
	@echo INSTALLDIRS not defined, defaulting to INSTALLDIRS=site

pure_perl_install ::
	@$(MOD_INSTALL) \
		read $(PERL_ARCHLIB)\auto\$(FULLEXT)\.packlist \
		write $(INSTALLARCHLIB)\auto\$(FULLEXT)\.packlist \
		$(INST_LIB) $(INSTALLPRIVLIB) \
		$(INST_ARCHLIB) $(INSTALLARCHLIB) \
		$(INST_BIN) $(INSTALLBIN) \
		$(INST_SCRIPT) $(INSTALLSCRIPT) \
		$(INST_HTMLLIBDIR) $(INSTALLHTMLPRIVLIBDIR) \
		$(INST_HTMLSCRIPTDIR) $(INSTALLHTMLSCRIPTDIR) \
		$(INST_MAN1DIR) $(INSTALLMAN1DIR) \
		$(INST_MAN3DIR) $(INSTALLMAN3DIR)
	@$(WARN_IF_OLD_PACKLIST) \
		$(SITEARCHEXP)\auto\$(FULLEXT)


pure_site_install ::
	@$(MOD_INSTALL) \
		read $(SITEARCHEXP)\auto\$(FULLEXT)\.packlist \
		write $(INSTALLSITEARCH)\auto\$(FULLEXT)\.packlist \
		$(INST_LIB) $(INSTALLSITELIB) \
		$(INST_ARCHLIB) $(INSTALLSITEARCH) \
		$(INST_BIN) $(INSTALLBIN) \
		$(INST_SCRIPT) $(INSTALLSCRIPT) \
		$(INST_HTMLLIBDIR) $(INSTALLHTMLSITELIBDIR) \
		$(INST_HTMLSCRIPTDIR) $(INSTALLHTMLSCRIPTDIR) \
		$(INST_MAN1DIR) $(INSTALLMAN1DIR) \
		$(INST_MAN3DIR) $(INSTALLMAN3DIR)
	@$(WARN_IF_OLD_PACKLIST) \
		$(PERL_ARCHLIB)\auto\$(FULLEXT)

doc_perl_install ::
	-@$(MKPATH) $(INSTALLARCHLIB)
	-@$(DOC_INSTALL) \
		"Module" "$(NAME)" \
		"installed into" "$(INSTALLPRIVLIB)" \
		LINKTYPE "$(LINKTYPE)" \
		VERSION "$(VERSION)" \
		EXE_FILES "$(EXE_FILES)" \
		>> $(INSTALLARCHLIB)\perllocal.pod

doc_site_install ::
	-@$(MKPATH) $(INSTALLARCHLIB)
	-@$(DOC_INSTALL) \
		"Module" "$(NAME)" \
		"installed into" "$(INSTALLSITELIB)" \
		LINKTYPE "$(LINKTYPE)" \
		VERSION "$(VERSION)" \
		EXE_FILES "$(EXE_FILES)" \
		>> $(INSTALLARCHLIB)\perllocal.pod


uninstall :: uninstall_from_$(INSTALLDIRS)dirs

uninstall_from_perldirs ::
	@$(UNINSTALL) $(PERL_ARCHLIB)\auto\$(FULLEXT)\.packlist

uninstall_from_sitedirs ::
	@$(UNINSTALL) $(SITEARCHEXP)\auto\$(FULLEXT)\.packlist


install_registry ::
	perl -MWin32::ShellExt::ColumnProvider::JpgSize -e "Win32::ShellExt::ColumnProvider::JpgSize->install;"
	perl -MWin32::ShellExt::ColumnProvider::PM -e "Win32::ShellExt::ColumnProvider::PM->install;"
	perl -MWin32::ShellExt::CtxtMenu::Base64Decode -e "Win32::ShellExt::CtxtMenu::Base64Decode->install;"
	perl -MWin32::ShellExt::CtxtMenu::Base64Encode -e "Win32::ShellExt::CtxtMenu::Base64Encode->install;"
	perl -MWin32::ShellExt::CtxtMenu::BinHex -e "Win32::ShellExt::CtxtMenu::BinHex->install;"
	perl -MWin32::ShellExt::CtxtMenu::CopyMP3InfoToClipboard -e "Win32::ShellExt::CtxtMenu::CopyMP3InfoToClipboard->install;"
	perl -MWin32::ShellExt::CtxtMenu::CopyPath -e "Win32::ShellExt::CtxtMenu::CopyPath->install;"
	perl -MWin32::ShellExt::CtxtMenu::FIGlet -e "Win32::ShellExt::CtxtMenu::FIGlet->install;"
	perl -MWin32::ShellExt::CtxtMenu::Gunzip -e "Win32::ShellExt::CtxtMenu::Gunzip->install;"
	perl -MWin32::ShellExt::CtxtMenu::Gzip -e "Win32::ShellExt::CtxtMenu::Gzip->install;"
	perl -MWin32::ShellExt::CtxtMenu::MD5 -e "Win32::ShellExt::CtxtMenu::MD5->install;"
	perl -MWin32::ShellExt::CtxtMenu::MagickConvert -e "Win32::ShellExt::CtxtMenu::MagickConvert->install;"
	perl -MWin32::ShellExt::CtxtMenu::MagickConvertGIF -e "Win32::ShellExt::CtxtMenu::MagickConvertGIF->install;"
	perl -MWin32::ShellExt::CtxtMenu::MagickConvertJPG -e "Win32::ShellExt::CtxtMenu::MagickConvertJPG->install;"
	perl -MWin32::ShellExt::CtxtMenu::PDF -e "Win32::ShellExt::CtxtMenu::PDF->install;"
	perl -MWin32::ShellExt::CtxtMenu::RegisterDll -e "Win32::ShellExt::CtxtMenu::RegisterDll->install;"
	perl -MWin32::ShellExt::CtxtMenu::RenameMP3 -e "Win32::ShellExt::CtxtMenu::RenameMP3->install;"
	perl -MWin32::ShellExt::CtxtMenu::RenameWithPrefix -e "Win32::ShellExt::CtxtMenu::RenameWithPrefix->install;"
	perl -MWin32::ShellExt::CtxtMenu::SwapFileNames -e "Win32::ShellExt::CtxtMenu::SwapFileNames->install;"
	perl -MWin32::ShellExt::CtxtMenu::Tar -e "Win32::ShellExt::CtxtMenu::Tar->install;"
	perl -MWin32::ShellExt::CtxtMenu::UnexpandTabs -e "Win32::ShellExt::CtxtMenu::UnexpandTabs->install;"
	perl -MWin32::ShellExt::CtxtMenu::UnregisterDll -e "Win32::ShellExt::CtxtMenu::UnregisterDll->install;"
	perl -MWin32::ShellExt::CtxtMenu::Whitespace -e "Win32::ShellExt::CtxtMenu::Whitespace->install;"
	perl -MWin32::ShellExt::CtxtMenu::Zip -e "Win32::ShellExt::CtxtMenu::Zip->install;"
	perl -MWin32::ShellExt::QueryInfo::ELisp -e "Win32::ShellExt::QueryInfo::ELisp->install;"
	perl -MWin32::ShellExt::QueryInfo::JpgSize -e "Win32::ShellExt::QueryInfo::JpgSize->install;"
	perl -MWin32::ShellExt::QueryInfo::LineCount -e "Win32::ShellExt::QueryInfo::LineCount->install;"
	perl -MWin32::ShellExt::QueryInfo::PDF -e "Win32::ShellExt::QueryInfo::PDF->install;"
	perl -MWin32::ShellExt::QueryInfo::PM -e "Win32::ShellExt::QueryInfo::PM->install;"
	perl -MWin32::ShellExt::QueryInfo::Shortcut -e "Win32::ShellExt::QueryInfo::Shortcut->install;"
	perl -MWin32::ShellExt::QueryInfo::TeX -e "Win32::ShellExt::QueryInfo::TeX->install;"
	perl -MWin32::ShellExt::QueryInfo::Zip -e "Win32::ShellExt::QueryInfo::Zip->install;"

uninstall_registry ::
	perl -MWin32::ShellExt::ColumnProvider::JpgSize -e "Win32::ShellExt::ColumnProvider::JpgSize->uninstall;"
	perl -MWin32::ShellExt::ColumnProvider::PM -e "Win32::ShellExt::ColumnProvider::PM->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::Base64Decode -e "Win32::ShellExt::CtxtMenu::Base64Decode->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::Base64Encode -e "Win32::ShellExt::CtxtMenu::Base64Encode->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::BinHex -e "Win32::ShellExt::CtxtMenu::BinHex->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::CopyMP3InfoToClipboard -e "Win32::ShellExt::CtxtMenu::CopyMP3InfoToClipboard->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::CopyPath -e "Win32::ShellExt::CtxtMenu::CopyPath->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::FIGlet -e "Win32::ShellExt::CtxtMenu::FIGlet->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::Gunzip -e "Win32::ShellExt::CtxtMenu::Gunzip->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::Gzip -e "Win32::ShellExt::CtxtMenu::Gzip->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::MD5 -e "Win32::ShellExt::CtxtMenu::MD5->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::MagickConvert -e "Win32::ShellExt::CtxtMenu::MagickConvert->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::MagickConvertGIF -e "Win32::ShellExt::CtxtMenu::MagickConvertGIF->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::MagickConvertJPG -e "Win32::ShellExt::CtxtMenu::MagickConvertJPG->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::PDF -e "Win32::ShellExt::CtxtMenu::PDF->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::RegisterDll -e "Win32::ShellExt::CtxtMenu::RegisterDll->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::RenameMP3 -e "Win32::ShellExt::CtxtMenu::RenameMP3->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::RenameWithPrefix -e "Win32::ShellExt::CtxtMenu::RenameWithPrefix->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::SwapFileNames -e "Win32::ShellExt::CtxtMenu::SwapFileNames->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::Tar -e "Win32::ShellExt::CtxtMenu::Tar->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::UnexpandTabs -e "Win32::ShellExt::CtxtMenu::UnexpandTabs->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::UnregisterDll -e "Win32::ShellExt::CtxtMenu::UnregisterDll->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::Whitespace -e "Win32::ShellExt::CtxtMenu::Whitespace->uninstall;"
	perl -MWin32::ShellExt::CtxtMenu::Zip -e "Win32::ShellExt::CtxtMenu::Zip->uninstall;"
	perl -MWin32::ShellExt::QueryInfo::ELisp -e "Win32::ShellExt::QueryInfo::ELisp->uninstall;"
	perl -MWin32::ShellExt::QueryInfo::JpgSize -e "Win32::ShellExt::QueryInfo::JpgSize->uninstall;"
	perl -MWin32::ShellExt::QueryInfo::LineCount -e "Win32::ShellExt::QueryInfo::LineCount->uninstall;"
	perl -MWin32::ShellExt::QueryInfo::PDF -e "Win32::ShellExt::QueryInfo::PDF->uninstall;"
	perl -MWin32::ShellExt::QueryInfo::PM -e "Win32::ShellExt::QueryInfo::PM->uninstall;"
	perl -MWin32::ShellExt::QueryInfo::Shortcut -e "Win32::ShellExt::QueryInfo::Shortcut->uninstall;"
	perl -MWin32::ShellExt::QueryInfo::TeX -e "Win32::ShellExt::QueryInfo::TeX->uninstall;"
	perl -MWin32::ShellExt::QueryInfo::Zip -e "Win32::ShellExt::QueryInfo::Zip->uninstall;"

# --- MakeMaker force section:
# Phony target to force checking subdirectories.
FORCE:
	@$(NOOP)


# --- MakeMaker perldepend section:


# --- MakeMaker makefile section:

# We take a very conservative approach here, but it\'s worth it.
# We move Makefile to Makefile.old here to avoid gnu make looping.
Makefile : Makefile.PL $(CONFIGDEP)
	@echo "Makefile out-of-date with respect to $?"
	@echo "Cleaning current config before rebuilding Makefile..."
	-@$(RM_F) Makefile.old
	-@$(MV) Makefile Makefile.old
	-$(MAKE) -f Makefile.old clean $(DEV_NULL) || $(NOOP)
	$(PERLRUN) Makefile.PL 
	@echo "==> Your Makefile has been rebuilt. <=="
	@echo "==> Please rerun the make command.  <=="
	false

# To change behavior to :: would be nice, but would break Tk b9.02
# so you find such a warning below the dist target.
#Makefile :: $(VERSION_FROM)
#	@echo "Warning: Makefile possibly out of date with $(VERSION_FROM)"


XSUBPPDIR = C:\perl\lib\ExtUtils
XSUBPP = $(XSUBPPDIR)/xsubpp
XSPROTOARG = 
XSUBPPDEPS = $(XSUBPPDIR)\typemap typemap $(XSUBPP)
XSUBPPARGS = -typemap $(XSUBPPDIR)\typemap -typemap typemap

.xs.c:
	$(PERL) -I$(PERL_ARCHLIB) -I$(PERL_LIB) $(XSUBPP) $(XSPROTOARG) $(XSUBPPARGS) $*.xs > $*.xsc && $(MV) $*.xsc $*.c

perlshellext.dll : Win32ShellExt.obj debug.obj
	link -dll -def:Win32ShellExt.def -nologo  -out:.\perlshellext.dll Win32ShellExt.obj debug.obj d:\build\perl\p561\lib\CORE\perl56.lib user32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib -libpath:c:\perl\bin /SUBSYSTEM:windows

Win32ShellExt.obj : Win32ShellExt.cpp PerlQueryInfoExt.cpp PerlMenu.cpp PerlColumnProviderExt.cpp PerlCopyHookExt.cpp PerlShellExtCtxtMenu.cpp PerlShellExt.cpp PerlDataObjectExt.cpp PerlDropTargetExt.cpp PerlShellExtInit.cpp PerlPersistFileExt.cpp PerlIconHandlerExt.cpp PerlPropSheetExt.cpp debug.h PerlShellExtInit.h exports.h Win32ShellExt.h PerlQueryInfoExt.h PerlColumnProviderExt.h PerlPropSheetExt.h PerlUnknownExt.h PerlCopyHookExt.h PerlMenu.h PerlShellExt.h PerlDataObjectExt.h PerlShellExtCtxtMenu.h PerlDropTargetExt.h PerlPersistFileExt.h PerlIconHandlerExt.h ShellExt/CopyHook.c PerlShellExtClassFactory.h PerlShellExtClassFactory.cpp
	cl -c -I. -nologo -Gf -W3 -I..\perl\p561\lib\CORE -I..\perl\p561\include -I. -I.. -DWIN32 -D_CONSOLE -DNO_STRICT   -Od -MD -Zi  -DPERL_MSVCRT_READFIX  -DWITH_DEBUG -UWITH_DEBUG -Fo.\win32shellext.obj .\win32shellext.cpp

debug.obj : debug.cpp debug.h
	cl -c -I. -nologo -Gf -W3 -DWIN32 -D_CONSOLE -DNO_STRICT -DWITH_DEBUG -UWITH_DEBUG   -Od -MD -Zi -Fo.\debug.obj .\debug.cpp



# --- MakeMaker staticmake section:

# --- MakeMaker makeaperl section ---
MAP_TARGET    = perl
FULLPERL      = C:\Perl\bin\perl.exe

$(MAP_TARGET) :: static $(MAKE_APERL_FILE)
	$(MAKE) -f $(MAKE_APERL_FILE) $@

$(MAKE_APERL_FILE) : $(FIRST_MAKEFILE)
	@echo Writing \"$(MAKE_APERL_FILE)\" for this $(MAP_TARGET)
	@$(PERLRUNINST) \
		Makefile.PL DIR= \
		MAKEFILE=$(MAKE_APERL_FILE) LINKTYPE=static \
		MAKEAPERL=1 NORECURS=1 CCCDLFLAGS=


# --- MakeMaker test section:

TEST_VERBOSE=0
TEST_TYPE=test_$(LINKTYPE)
TEST_FILE = test.pl
TEST_FILES = 
TESTDB_SW = -d

testdb :: testdb_$(LINKTYPE)

test :: $(TEST_TYPE)

test_dynamic :: pure_all
	$(PERLRUN) $(TEST_LIBS) $(TEST_FILE)

testdb_dynamic :: pure_all
	$(PERLRUN) $(TESTDB_SW) $(TEST_LIBS) $(TEST_FILE)

test_ : test_dynamic

test_static :: test_dynamic
testdb_static :: testdb_dynamic


# --- MakeMaker ppd section:
# Creates a PPD (Perl Package Description) for a binary distribution.
ppd:
	@$(PERL) -e "print qq{<SOFTPKG NAME=\"Win32-ShellExt\" VERSION=\"0,1,0,0\">\n}. qq{\t<TITLE>Win32-ShellExt</TITLE>\n}. qq{\t<ABSTRACT>Allows to write Windows shell extensions in Perl</ABSTRACT>\n}. qq{\t<AUTHOR>Jean-Baptiste Nivoit &lt;jbnivoit\@hotmail.com&gt;</AUTHOR>\n}. qq{\t<IMPLEMENTATION>\n}. qq{\t\t<DEPENDENCY NAME=\"Win32-TieRegistry\" VERSION=\"0,23,0,0\" />\n}. qq{\t\t<OS NAME=\"$(OSNAME)\" />\n}. qq{\t\t<ARCHITECTURE NAME=\"MSWin32-x86-multi-thread\" />\n}. qq{\t\t<CODEBASE HREF=\"\" />\n}. qq{\t</IMPLEMENTATION>\n}. qq{</SOFTPKG>\n}" > Win32-ShellExt.ppd

# --- MakeMaker pm_to_blib section:

pm_to_blib: $(TO_INST_PM)
	@$(PERL) "-I$(INST_ARCHLIB)" "-I$(INST_LIB)" \
	"-I$(PERL_ARCHLIB)" "-I$(PERL_LIB)" -MExtUtils::Install \
        -e "pm_to_blib(qw[ <<pmfiles.dat ],'$(INST_LIB)\auto','$(PM_FILTER)')"
	
$(PM_TO_BLIB)
<<
	@$(TOUCH) $@


# --- MakeMaker selfdocument section:


# --- MakeMaker postamble section:


# End.
