/*
 * This file was generated automatically by xsubpp version 1.9508 from the 
 * contents of CopyHook.xs. Do not edit this file, edit CopyHook.xs instead.
 *
 *	ANY CHANGES MADE HERE WILL BE LOST! 
 *
 */

#line 1 "CopyHook.xs"
/* -*- c -*- */
/* 
 *   CopyHook.xs
 *
 *   Copyright (c) 2002 Jean-Baptiste Nivoit. All rights reserved.
 *   This program is free software; you can redistribute it and/or
 *   modify it under the same terms as Perl itself.
 *
 */

#include "EXTERN.h"
#include "perl.h"
#include "XSUB.h"

#include <shellapi.h> 

#ifndef PERL_VERSION
#include "patchlevel.h"
#define PERL_REVISION	5
#define PERL_VERSION	PATCHLEVEL
#define PERL_SUBVERSION	SUBVERSION
#endif

#if PERL_REVISION == 5 && (PERL_VERSION < 4 || (PERL_VERSION == 4 && PERL_SUBVERSION <= 75 ))

#    define PL_sv_undef		sv_undef
#    define PL_na		na
#    define PL_curcop		curcop
#    define PL_compiling	compiling

#endif

// that header is generated using the CopyHook/constants.pl script. you need a recent 
// ExtUtils::MakeMaker for that, it seems.
#include "CopyHook/constants.h"

#line 47 "CopyHook.c"

/* INCLUDE:  Including 'CopyHook/constants.xs' from 'CopyHook.xs' */

XS(XS_Win32__ShellExt__CopyHook_constant)
{
    dXSARGS;
    if (items != 1)
	Perl_croak(aTHX_ "Usage: Win32::ShellExt::CopyHook::constant(sv)");
    SP -= items;
    {
#line 6 "CopyHook/constants.xs"
#ifdef dXSTARG
	dXSTARG; /* Faster if we have it.  */
#else
	dTARGET;
#endif
	STRLEN		len;
        int		type;
	IV		iv;
	/* NV		nv;	Uncomment this if you need to return NVs */
	const char	*pv;
#line 69 "CopyHook.c"
	SV *	sv = ST(0);
	const char *	s = SvPV(sv, len);
#line 20 "CopyHook/constants.xs"
        /* Change this to constant(aTHX_ s, len, &iv, &nv);
           if you need to return both NVs and IVs */
	type = constant(aTHX_ s, len, &iv, &pv);
      /* Return 1 or 2 items. First is error message, or undef if no error.
           Second, if present, is found value */
        switch (type) {
        case PERL_constant_NOTFOUND:
          sv = sv_2mortal(newSVpvf("%s is not a valid Win32::ShellExt::CopyHook macro", s));
          PUSHs(sv);
          break;
        case PERL_constant_NOTDEF:
          sv = sv_2mortal(newSVpvf(
	    "Your vendor has not defined Win32::ShellExt::CopyHook macro %s, used", s));
          PUSHs(sv);
          break;
        case PERL_constant_ISIV:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHi(iv);
          break;
	/* Uncomment this if you need to return NOs
        case PERL_constant_ISNO:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHs(&PL_sv_no);
          break; */
	/* Uncomment this if you need to return NVs
        case PERL_constant_ISNV:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHn(nv);
          break; */
        case PERL_constant_ISPV:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHp(pv, strlen(pv));
          break;
	/* Uncomment this if you need to return PVNs
        case PERL_constant_ISPVN:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHp(pv, iv);
          break; */
	/* Uncomment this if you need to return SVs
        case PERL_constant_ISSV:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHs(sv);
          break; */
	/* Uncomment this if you need to return UNDEFs
        case PERL_constant_ISUNDEF:
          break; */
	/* Uncomment this if you need to return UVs
        case PERL_constant_ISUV:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHu((UV)iv);
          break; */
	/* Uncomment this if you need to return YESs
        case PERL_constant_ISYES:
          EXTEND(SP, 1);
          PUSHs(&PL_sv_undef);
          PUSHs(&PL_sv_yes);
          break; */
        default:
          sv = sv_2mortal(newSVpvf(
	    "Unexpected return type %d while processing Win32::ShellExt::CopyHook macro %s, used",
               type, s));
          PUSHs(sv);
        }
#line 143 "CopyHook.c"
	PUTBACK;
	return;
    }
}


/* INCLUDE: Returning to 'CopyHook.xs' from 'CopyHook/constants.xs' */

#ifdef __cplusplus
extern "C"
#endif
XS(boot_Win32__ShellExt__CopyHook)
{
    dXSARGS;
    char* file = __FILE__;

    XS_VERSION_BOOTCHECK ;

        newXS("Win32::ShellExt::CopyHook::constant", XS_Win32__ShellExt__CopyHook_constant, file);
    XSRETURN_YES;
}

