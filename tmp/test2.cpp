
STATIC void
S_init_perllib(pTHX)
{
    char *s;
    if (!PL_tainting) {

	s = PerlEnv_getenv("PERL5LIB");
	if (s)
	    incpush(s, TRUE, TRUE);
	else
	    incpush(PerlEnv_getenv("PERLLIB"), FALSE, FALSE);
    }

/* Use the ~-expanded versions of APPLLIB (undocumented),
    ARCHLIB PRIVLIB SITEARCH SITELIB VENDORARCH and VENDORLIB
*/
#ifdef APPLLIB_EXP
    incpush(APPLLIB_EXP, TRUE, TRUE);
#endif

#ifdef ARCHLIB_EXP
    incpush(ARCHLIB_EXP, FALSE, FALSE);
#endif

    incpush(PRIVLIB_EXP, TRUE, FALSE);

    incpush(SITELIB_EXP, TRUE, FALSE);	/* this picks up sitearch as well */

    incpush(PERL_VENDORLIB_EXP, TRUE, FALSE);	/* this picks up vendorarch as well */

    if (!PL_tainting)
	incpush(".", FALSE, FALSE);
}

#    define PERLLIB_SEP ';'

STATIC void
S_incpush(pTHX_ char *p, int addsubdirs, int addoldvers)
{
    SV *subdir = Nullsv;

    if (!p || !*p)
	return;

    if (addsubdirs || addoldvers) {
	subdir = sv_newmortal();
    }

    /* Break at all separators */
    while (p && *p) {
	SV *libdir = NEWSV(55,0);
	char *s;

	/* skip any consecutive separators */
	while ( *p == PERLLIB_SEP ) {
	    /* Uncomment the next line for PATH semantics */
	    /* av_push(GvAVn(PL_incgv), newSVpvn(".", 1)); */
	    p++;
	}

	if ( (s = strchr(p, PERLLIB_SEP)) != Nullch ) {
	    sv_setpvn(libdir, PERLLIB_MANGLE(p, (STRLEN)(s - p)),
		      (STRLEN)(s - p));
	    p = s + 1;
	}
	else {
	    sv_setpv(libdir, PERLLIB_MANGLE(p, 0));
	    p = Nullch;	/* break out */
	}

	/*
	 * BEFORE pushing libdir onto @INC we may first push version- and
	 * archname-specific sub-directories.
	 */
	if (addsubdirs || addoldvers) {
#ifdef PERL_INC_VERSION_LIST
	    /* Configure terminates PERL_INC_VERSION_LIST with a NULL */
	    const char *incverlist[] = { PERL_INC_VERSION_LIST };
	    const char **incver;
#endif
	    struct stat tmpstatbuf;
	    if (addsubdirs) {
#ifdef MACOS_TRADITIONAL
#define PERL_AV_SUFFIX_FMT	""
#define PERL_ARCH_FMT 		"%s:"
#define PERL_ARCH_FMT_PATH	PERL_FS_VER_FMT PERL_AV_SUFFIX_FMT
#else
#define PERL_AV_SUFFIX_FMT 	"/"
#define PERL_ARCH_FMT 		"/%s"
#define PERL_ARCH_FMT_PATH	PERL_AV_SUFFIX_FMT PERL_FS_VER_FMT
#endif
		/* .../version/archname if -d .../version/archname */
		Perl_sv_setpvf(aTHX_ subdir, "%"SVf PERL_ARCH_FMT_PATH PERL_ARCH_FMT,
				libdir,
			       (int)PERL_REVISION, (int)PERL_VERSION,
			       (int)PERL_SUBVERSION, ARCHNAME);
		if (PerlLIO_stat(SvPVX(subdir), &tmpstatbuf) >= 0 &&
		      S_ISDIR(tmpstatbuf.st_mode))
		    av_push(GvAVn(PL_incgv), newSVsv(subdir));

		/* .../version if -d .../version */
		Perl_sv_setpvf(aTHX_ subdir, "%"SVf PERL_ARCH_FMT_PATH, libdir,
			       (int)PERL_REVISION, (int)PERL_VERSION,
			       (int)PERL_SUBVERSION);
		if (PerlLIO_stat(SvPVX(subdir), &tmpstatbuf) >= 0 &&
		      S_ISDIR(tmpstatbuf.st_mode))
		    av_push(GvAVn(PL_incgv), newSVsv(subdir));

		/* .../archname if -d .../archname */
		Perl_sv_setpvf(aTHX_ subdir, "%"SVf PERL_ARCH_FMT, libdir, ARCHNAME);
		if (PerlLIO_stat(SvPVX(subdir), &tmpstatbuf) >= 0 &&
		      S_ISDIR(tmpstatbuf.st_mode))
		    av_push(GvAVn(PL_incgv), newSVsv(subdir));
	    }

#ifdef PERL_INC_VERSION_LIST
	    if (addoldvers) {
		for (incver = incverlist; *incver; incver++) {
		    /* .../xxx if -d .../xxx */
		    Perl_sv_setpvf(aTHX_ subdir, "%"SVf PERL_ARCH_FMT, libdir, *incver);
		    if (PerlLIO_stat(SvPVX(subdir), &tmpstatbuf) >= 0 &&
			  S_ISDIR(tmpstatbuf.st_mode))
			av_push(GvAVn(PL_incgv), newSVsv(subdir));
		}
	    }
#endif
	}

	/* finally push this lib directory on the end of @INC */
	av_push(GvAVn(PL_incgv), libdir);
    }
}

