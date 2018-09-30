/* density.NE2001.f -- translated by f2c (version 20100827).
   You must link the resulting object file with libf2c:
	on Microsoft Windows system, link with libf2c.lib;
	on Linux or Unix systems, link with .../path/to/libf2c.a -lm
	or, if you install libf2c.a in a standard place, with -lf2c -lm
	-- in that order, at the end of the command line, as in
		cc *.o -lf2c -lm
	Source for libf2c is in /netlib/f2c/libf2c.zip, e.g.,

		http://www.netlib.org/f2c/libf2c.zip
*/

#include "f2c.h"

/* Common Block Declarations */

struct {
    integer wg1, wg2, wga, wggc, wglism, wgcn, wgvn;
} modelflags_;

#define modelflags_1 modelflags_

struct {
    real n1h1, h1, a1, f1, n2, h2, a2, f2, na, ha, wa, aa, fa;
} galparams_;

#define galparams_1 galparams_

struct {
    real harm[5], narm[5], warm[5], farm[5];
} armfactors_;

#define armfactors_1 armfactors_

struct {
    real negc0, fgc0;
} gcparms_;

#define gcparms_1 gcparms_

struct mw_1_ {
    real rsun;
};

#define mw_1 (*(struct mw_1_ *) &mw_)

/* Initialized data */

struct {
    real e_1;
    } mw_ = { 8.5f };


/* Table of constant values */

static integer c__3 = 3;
static integer c__1 = 1;
static integer c__4 = 4;
static integer c__9 = 9;
static doublereal c_b83 = 4.;

/* density.NE2001.f */
/* final version of NE2001 */
/* returns densities, F parameters and weights of the various components */
/* mods: */
/* 28 July 02: */
/*   put in 'if' statements in subroutine density_2001 so that */
/*        function calls are not done if particular weights */
/*        (wg1, wg2, etc.) are set to zero in gal01.inp */
/*        This is (a) cleaner and (b) much more efficient if */
/*        the clump or void component is flagged out. */
/* Subroutine */ int density_2001__(real *x, real *y, real *z__, real *ne1, 
	real *ne2, real *nea, real *negc, real *nelism, real *necn, real *
	nevn, real *f1, real *f2, real *fa, real *fgc, real *flism, real *fcn,
	 real *fvn, integer *whicharm, integer *wlism, integer *wldr, integer 
	*wlhb, integer *wlsb, integer *wloopi, integer *hitclump, integer *
	hitvoid, integer *wvoid)
{
    /* Initialized data */

    static logical first = TRUE_;

    extern doublereal ne_inner__(real *, real *, real *, real *), ne_outer__(
	    real *, real *, real *, real *);
    extern /* Subroutine */ int neclumpn_(real *, real *, real *, real *, 
	    real *, integer *);
    extern doublereal ne_gc__(real *, real *, real *, real *);
    extern /* Subroutine */ int get_parameters__(void);
    extern doublereal ne_lism__(real *, real *, real *, real *, integer *, 
	    integer *, integer *, integer *, integer *);
    extern /* Subroutine */ int nevoidn_(real *, real *, real *, real *, real 
	    *, integer *, integer *);
    extern doublereal ne_arms_log_mod__(real *, real *, real *, integer *, 
	    real *);

/* ---------------------------------------------------------------------------- */
/*  Returns seven components of the free electron density of the */
/*  interstellar medium at Galactic location (x,y,z). */
/*  Calling arguments: */
/*  input: */
/*        x, y, z = galactocentric location (kpc) */
/*       Right-handed coordinate system */
/*       x is in l=90 direction */
/*       y is in l=180 direction */
/*       The sun is at (x,y,z) = (0,R0,0) */
/*  output: */
/*    electron densities in cm^{-3}: */
/*        ne1:        outer, thick disk */
/*        ne2:        inner, thin disk (annular in form) */
/*        nea:        spiral arms */
/*        negc:   galactic center component */
/*       nelism: local ISM component */
/*       necN:   contribution from discrete 'clumps' */
/*       nevN:   contribution from voids */
/*    fluctuation parameters (one for each ne component): */
/*       F1, F2, Fa, Fgc, Flism, FcN, FvN */
/*    flags: */
/*       whicharm: which of the 5 arms x,y,z is in (0 for interarm region) */
/*          wlism: 1 if x,y,z is in any of the four LISM components */
/*           wLDR: 1 if in LDR, 0 if not */
/*           wLHB: 1 if in LHB, 0 if not */
/*           wLSB: 1 if in LSB, 0 if not */
/*         wLOOPI: 1 if in LoopI, 0 if not */
/*       (nb: nelism is calculated according to LHB:LOOPI:LSB:LDR) */
/*       hitclump: clump number that x,y,z is in (0 if none) */
/*        hitvoid: void number that x,y,z is in (0 if none) */
/* 25 May 2002 */
/* based on routines from TC93 and test routines from 1999-2002 by JMC. */
/* ---------------------------------------------------------------------------- */
/* functions: */
/* subroutines needed: */
/*        neclumpN */
/*        nevoidN */
    if (first) {
/* get parameters first tim */
	get_parameters__();
	first = FALSE_;
    }
/* need to initiate values in case components are flagged out */
    *ne1 = 0.f;
    *ne2 = 0.f;
    *nea = 0.f;
    *negc = 0.f;
    *nelism = 0.f;
    *necn = 0.f;
    *nevn = 0.f;
    *wlism = 0.f;
    *wldr = 0.f;
    *wlhb = 0.f;
    *wlsb = 0.f;
    *wloopi = 0.f;
    *hitclump = 0;
    *hitvoid = 0;
    *wvoid = 0;
    *whicharm = 0;
    if (modelflags_1.wg1 == 1) {
	*ne1 = ne_outer__(x, y, z__, f1);
    }
    if (modelflags_1.wg2 == 1) {
	*ne2 = ne_inner__(x, y, z__, f2);
    }
    if (modelflags_1.wga == 1) {
	*nea = ne_arms_log_mod__(x, y, z__, whicharm, fa);
    }
    if (modelflags_1.wggc == 1) {
	*negc = ne_gc__(x, y, z__, fgc);
    }
    if (modelflags_1.wglism == 1) {
	*nelism = ne_lism__(x, y, z__, flism, wlism, wldr, wlhb, wlsb, wloopi)
		;
    }
    if (modelflags_1.wgcn == 1) {
	neclumpn_(x, y, z__, necn, fcn, hitclump);
    }
    if (modelflags_1.wgvn == 1) {
	nevoidn_(x, y, z__, nevn, fvn, hitvoid, wvoid);
    }
/*       write(21, "(3(f8.2,1x),5(f8.4,1x),i2)") */
/*    .       x,y,z,ne1,ne2,nea,nelism,negc, */
/*    .       whicharm */
    return 0;
} /* density_2001__ */

/* Subroutine */ int get_parameters__(void)
{
    /* Format strings */
    static char fmt_1020[] = "(7x,f8.0)";

    /* System generated locals */
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsle(cilist *), e_rsle(void), do_lio(integer *,
	     integer *, char *, ftnlen), s_rsfe(cilist *), do_fio(integer *, 
	    char *, ftnlen), e_rsfe(void), f_clos(cllist *);

    /* Fortran I/O blocks */
    static cilist io___2 = { 0, 11, 0, 0, 0 };
    static cilist io___3 = { 0, 11, 0, 0, 0 };
    static cilist io___4 = { 0, 11, 0, fmt_1020, 0 };


/* ----------------------------------------------------------------------- */
/* control flags for turning components on and off: */
/* parameters of large-scale components (inner+outer+arm components): */
/* factors for controlling individual spiral arms: */
/*        narm: multiplies electron density (in addition to the`fac' */
/*                      quantities) */
/*        warm:        arm width factors that multiply nominal arm width */
/*        harm:        arm scale height factors */
/*        farm:        factors that multiply n_e^2 when calculating SM */
    o__1.oerr = 0;
    o__1.ounit = 11;
    o__1.ofnmlen = 9;
    o__1.ofnm = "gal01.inp";
    o__1.orl = 0;
    o__1.osta = "old";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    s_rsle(&io___2);
    e_rsle();
    s_rsle(&io___3);
    do_lio(&c__3, &c__1, (char *)&modelflags_1.wg1, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&modelflags_1.wg2, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&modelflags_1.wga, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&modelflags_1.wggc, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&modelflags_1.wglism, (ftnlen)sizeof(integer)
	    );
    do_lio(&c__3, &c__1, (char *)&modelflags_1.wgcn, (ftnlen)sizeof(integer));
    do_lio(&c__3, &c__1, (char *)&modelflags_1.wgvn, (ftnlen)sizeof(integer));
    e_rsle();
    s_rsfe(&io___4);
    do_fio(&c__1, (char *)&galparams_1.n1h1, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.h1, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.a1, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.f1, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.n2, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.h2, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.a2, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.f2, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.na, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.ha, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.wa, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.aa, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&galparams_1.fa, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.narm[0], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.narm[1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.narm[2], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.narm[3], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.narm[4], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.warm[0], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.warm[1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.warm[2], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.warm[3], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.warm[4], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.harm[0], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.harm[1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.harm[2], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.harm[3], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.harm[4], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.farm[0], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.farm[1], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.farm[2], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.farm[3], (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&armfactors_1.farm[4], (ftnlen)sizeof(real));
    e_rsfe();
    cl__1.cerr = 0;
    cl__1.cunit = 11;
    cl__1.csta = 0;
    f_clos(&cl__1);
/*          write(6,*) 'get_parms: weights: ', */
/*    .           wg1, wg2, wga, wggc, wglism, wgcN, wgvN */
/*          write(6,*) 'get_parms: ', */
/*    .           n1h1,h1,A1,F1,n2,h2,A2,F2, */
/*    .           na,ha,wa,Aa,Fa, */
/*    .           narm(1), narm(2), narm(3), narm(4), narm(5), */
/*    .           warm(1), warm(2), warm(3), warm(4), warm(5), */
/*    .           harm(1), harm(2), harm(3), harm(4), harm(5), */
/*    .           farm(1), farm(2), farm(3), farm(4), farm(5) */
    return 0;
} /* get_parameters__ */

doublereal ne_arms_log_mod__(real *x, real *y, real *z__, integer *whicharm, 
	real *farms)
{
    /* Initialized data */

    static integer nnj[5] = { 20,20,20,20,20 };
    static logical first = TRUE_;
    static integer armmap[5] = { 1,3,4,2,5 };
    static integer ks = 3;

    /* System generated locals */
    integer i__1, i__2;
    real ret_val, r__1, r__2;
    doublereal d__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    double sqrt(doublereal);
    integer f_open(olist *), s_rsle(cilist *), e_rsle(void), do_lio(integer *,
	     integer *, char *, ftnlen), f_clos(cllist *);
    double exp(doublereal), cos(doublereal);
    integer s_wsle(cilist *), e_wsle(void);
    double sin(doublereal);
    integer s_wsfe(cilist *), do_fio(integer *, char *, ftnlen), e_wsfe(void);
    double atan2(doublereal, doublereal), pow_dd(doublereal *, doublereal *);

    /* Local variables */
    static integer j, k, n;
    static real r__, r1[100]	/* was [20][5] */, ga;
    static integer jj, kk, kl;
    static real th, rr, sq, th1[100]	/* was [20][5] */, sq1, sq2, ebb, fac,
	     nea;
    static integer kma;
    static real arg, emm, arm[5000]	/* was [5][500][2] */, dth;
    static integer kmi;
    static real exx, eyy, th2a, th3a, th3b, th2b, aarm[5];
    static integer kmax[5];
    static real rmin[5], smin, test, thxy;
    extern doublereal sech2_(real *);
    static real test2, test3;
    static integer whicharm_spiralmodel__;
    static real thmin[5], sqmin, extent[5], fac2min, fac3min;
    extern /* Subroutine */ int cspline_(real *, real *, integer *, real *, 
	    real *);
    static real sminmin;

    /* Fortran I/O blocks */
    static cilist io___11 = { 0, 11, 0, 0, 0 };
    static cilist io___12 = { 0, 11, 0, 0, 0 };
    static cilist io___14 = { 0, 11, 0, 0, 0 };
    static cilist io___22 = { 0, 11, 0, 0, 0 };
    static cilist io___28 = { 0, 11, 0, "(1x,i2,1x,i3,1x,2(f7.3,1x))", 0 };


/* ----------------------------------------------------------------------- */
/*  Spiral arms are defined as logarithmic spirals using the */
/*    parameterization in Wainscoat et al. 1992, ApJS, 83, 111-146. */
/*  But arms are modified selectively at various places to distort them */
/*    as needed (08 Aug 2000). */
/*  Note that arm numbering follows that of TC93 for the four large arms */
/* (after remapping). */
/*  The local spiral arm is number 5. */
/*  06 Apr 02:   removed TC type modifications of arms 2,3 (fac calculations) */
/*                  and replaced with new versions.  Data for these are hard wired. */
/* see get_parameters for definitions of narm, warm, harm. */
/*        for remapping from Wainscoat */
/* from GC outwards toward Sun. */
/* order to TC93 order, which i */
/* function: */
/* Computing 2nd power */
    r__1 = *x;
/* Computing 2nd power */
    r__2 = *y;
    rr = sqrt(r__1 * r__1 + r__2 * r__2);
    if (first) {
/* read arm parameters: */
/* Reconstruct spiral arm a */
	o__1.oerr = 0;
	o__1.ounit = 11;
	o__1.ofnmlen = 19;
	o__1.ofnm = "ne_arms_log_mod.inp";
	o__1.orl = 0;
	o__1.osta = "old";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
/*       write(6,*) 'ne_arms_log_mod.inp:' */
	s_rsle(&io___11);
	e_rsle();
	s_rsle(&io___12);
	e_rsle();
	for (j = 1; j <= 5; ++j) {
	    s_rsle(&io___14);
	    do_lio(&c__4, &c__1, (char *)&aarm[j - 1], (ftnlen)sizeof(real));
	    do_lio(&c__4, &c__1, (char *)&rmin[j - 1], (ftnlen)sizeof(real));
	    do_lio(&c__4, &c__1, (char *)&thmin[j - 1], (ftnlen)sizeof(real));
	    do_lio(&c__4, &c__1, (char *)&extent[j - 1], (ftnlen)sizeof(real))
		    ;
	    e_rsle();
/*         write(6,*) aarm(j), rmin(j), thmin(j), extent(j) */
	}
	cl__1.cerr = 0;
	cl__1.cunit = 11;
	cl__1.csta = 0;
	f_clos(&cl__1);
	for (j = 1; j <= 5; ++j) {
/* fill sampling array */
	    i__1 = nnj[j - 1];
	    for (n = 1; n <= i__1; ++n) {
		th1[n + j * 20 - 21] = thmin[j - 1] + (n - 1) * extent[j - 1] 
			/ (nnj[j - 1] - 1.f);
/* rad */
		r1[n + j * 20 - 21] = rmin[j - 1] * exp((th1[n + j * 20 - 21] 
			- thmin[j - 1]) / aarm[j - 1]);
		th1[n + j * 20 - 21] *= 57.2957795130823f;
/* *** begin sculpting spiral arm 2 == TC arm 3*** */
/* deg */
		if (armmap[j - 1] == 3) {
		    if (th1[n + j * 20 - 21] > 370.f && th1[n + j * 20 - 21] 
			    <= 410.f) {
			r1[n + j * 20 - 21] *= cos((th1[n + j * 20 - 21] - 
				390.f) * 180.f / 2291.831180523292f) * .04f + 
				1.f;
/*    .           (1. + 0.01*cos((th1(n,j)-390.)*180./(40.*rad))) */
		    }
		    if (th1[n + j * 20 - 21] > 315.f && th1[n + j * 20 - 21] 
			    <= 370.f) {
			r1[n + j * 20 - 21] *= 1.f - cos((th1[n + j * 20 - 21]
				 - 345.f) * 180.f / 3151.2678732195268f) * 
				.07f;
/*    .           (1.0 - 0.08*cos((th1(n,j)-345.)*180./(55.*rad))) */
		    }
		    if (th1[n + j * 20 - 21] > 180.f && th1[n + j * 20 - 21] 
			    <= 315.f) {
			r1[n + j * 20 - 21] *= cos((th1[n + j * 20 - 21] - 
				260.f) * 180.f / 7734.9302342661103f) * .16f 
				+ 1;
/*    ,           (1 + 0.13*cos((th1(n,j)-260.)*180./(135.*rad))) */
		    }
		}
/* *** begin sculpting spiral arm 4 == TC arm 2*** */
		if (armmap[j - 1] == 2) {
		    if (th1[n + j * 20 - 21] > 290.f && th1[n + j * 20 - 21] 
			    <= 395.f) {
			r1[n + j * 20 - 21] *= 1.f - cos((th1[n + j * 20 - 21]
				 - 350.f) * 180.f / 6016.0568488736417f) * 
				.11f;
/*    .            1. */
		    }
		}
/* *** end arm sculpting *** */
/*           write(6,*) j,n, th1(n,j), r1(n,j) */
	    }
	}
	o__1.oerr = 0;
	o__1.ounit = 11;
	o__1.ofnmlen = 12;
	o__1.ofnm = "log_arms.out";
	o__1.orl = 0;
	o__1.osta = "unknown";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
	s_wsle(&io___22);
	do_lio(&c__9, &c__1, "arm  n   xa     ya", (ftnlen)18);
	e_wsle();
	for (j = 1; j <= 5; ++j) {
	    dth = 5.f / r1[j * 20 - 20];
	    th = th1[j * 20 - 20] - dth * .999f;
	    i__1 = -nnj[j - 1];
	    cspline_(&th1[j * 20 - 20], &r1[j * 20 - 20], &i__1, &th, &r__);
/*              write(6,*) 'doing arm ', j, ' with ', NNj(j), ' points', */
/*    .               dth */
/*              write(6,*) (th1(k,j), r1(k,j), k=1,NNj(j)) */
	    for (k = 1; k <= 499; ++k) {
		th += dth;
		if (th > th1[nnj[j - 1] + j * 20 - 21]) {
		    goto L20;
		}
		cspline_(&th1[j * 20 - 20], &r1[j * 20 - 20], &nnj[j - 1], &
			th, &r__);
		arm[j + (k + 500) * 5 - 2506] = -r__ * sin(th / 
			57.2957795130823f);
		arm[j + (k + 1000) * 5 - 2506] = r__ * cos(th / 
			57.2957795130823f);
		s_wsfe(&io___28);
		do_fio(&c__1, (char *)&j, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&k, (ftnlen)sizeof(integer));
		do_fio(&c__1, (char *)&arm[j + (k + 500) * 5 - 2506], (ftnlen)
			sizeof(real));
		do_fio(&c__1, (char *)&arm[j + (k + 1000) * 5 - 2506], (
			ftnlen)sizeof(real));
		e_wsfe();
/* L10: */
	    }
L20:
	    kmax[j - 1] = k;
/* L21: */
	}
	cl__1.cerr = 0;
	cl__1.cunit = 11;
	cl__1.csta = 0;
	f_clos(&cl__1);
	first = FALSE_;
    }

/* Get spiral arm component:  30 do loop finds a coarse minimum distance */
/* from line of sight to arm; 40 do loop finds a fine minimum distance */
/* from line of sight to arm; line 35 ensures that arm limits are not */
/* exceeded; linear interpolation beginning at line 41 finds the */
/* minimum distance from line of sight to arm on a finer scale than gridding */
/* of arms allows (TJL) */
    nea = 0.f;
    ga = 0.f;
    *whicharm = 0;
    whicharm_spiralmodel__ = 0;
    sminmin = 1e10f;
    thxy = atan2(-(*x), *y) * 57.2957795130823f;
/* (different from tc93 t */
/* measured ccw from +y */
    if (thxy < 0.f) {
	thxy += 360.f;
    }
    if ((r__1 = *z__ / galparams_1.ha, dabs(r__1)) < 10.f) {
	for (j = 1; j <= 5; ++j) {
	    jj = armmap[j - 1];
	    sqmin = 1e10f;
	    i__1 = kmax[j - 1] - ks;
	    i__2 = (ks << 1) + 1;
	    for (k = ks + 1; i__2 < 0 ? k >= i__1 : k <= i__1; k += i__2) {
/* Computing 2nd power */
		r__1 = *x - arm[j + (k + 500) * 5 - 2506];
/* Computing 2nd power */
		r__2 = *y - arm[j + (k + 1000) * 5 - 2506];
		sq = r__1 * r__1 + r__2 * r__2;
		if (sq < sqmin) {
		    sqmin = sq;
		    kk = k;
		}
/* L30: */
	    }
/* L35: */
/* Computing MAX */
	    i__2 = kk - (ks << 1);
	    kmi = max(i__2,1);
/* Computing MIN */
	    i__2 = kk + (ks << 1), i__1 = kmax[j - 1];
	    kma = min(i__2,i__1);
	    i__2 = kma;
	    for (k = kmi; k <= i__2; ++k) {
/* Computing 2nd power */
		r__1 = *x - arm[j + (k + 500) * 5 - 2506];
/* Computing 2nd power */
		r__2 = *y - arm[j + (k + 1000) * 5 - 2506];
		sq = r__1 * r__1 + r__2 * r__2;
		if (sq < sqmin) {
		    sqmin = sq;
		    kk = k;
		}
/* L40: */
	    }
/* L41: */
	    if (kk > 1 && kk < kmax[j - 1]) {
/* Computing 2nd power */
		r__1 = *x - arm[j + (kk + 499) * 5 - 2506];
/* Computing 2nd power */
		r__2 = *y - arm[j + (kk + 999) * 5 - 2506];
		sq1 = r__1 * r__1 + r__2 * r__2;
/* Computing 2nd power */
		r__1 = *x - arm[j + (kk + 501) * 5 - 2506];
/* Computing 2nd power */
		r__2 = *y - arm[j + (kk + 1001) * 5 - 2506];
		sq2 = r__1 * r__1 + r__2 * r__2;
		if (sq1 < sq2) {
		    kl = kk - 1;
		} else {
		    kl = kk + 1;
		}
		emm = (arm[j + (kk + 1000) * 5 - 2506] - arm[j + (kl + 1000) *
			 5 - 2506]) / (arm[j + (kk + 500) * 5 - 2506] - arm[j 
			+ (kl + 500) * 5 - 2506]);
		ebb = arm[j + (kk + 1000) * 5 - 2506] - emm * arm[j + (kk + 
			500) * 5 - 2506];
/* Computing 2nd power */
		r__1 = emm;
		exx = (*x + emm * *y - emm * ebb) / (r__1 * r__1 + 1.f);
		test = (exx - arm[j + (kk + 500) * 5 - 2506]) / (arm[j + (kl 
			+ 500) * 5 - 2506] - arm[j + (kk + 500) * 5 - 2506]);
		if (test < 0.f || test > 1.f) {
		    exx = arm[j + (kk + 500) * 5 - 2506];
		}
		eyy = emm * exx + ebb;
	    } else {
		exx = arm[j + (kk + 500) * 5 - 2506];
		eyy = arm[j + (kk + 1000) * 5 - 2506];
	    }
/* Computing 2nd power */
	    r__1 = *x - exx;
/* Computing 2nd power */
	    r__2 = *y - eyy;
	    sqmin = r__1 * r__1 + r__2 * r__2;
	    smin = sqrt(sqmin);
/*           write(23,"(4(f5.2,1x),i2,1x,3(f8.3,1x))") */
/*    .        x,y,z,rr,j,exx,eyy,smin */
/* Distance of (x,y,z) from */
	    if (smin < galparams_1.wa * 3) {
/* If (x,y,z) is close t */
/* Computing 2nd power */
		r__1 = smin / (armfactors_1.warm[jj - 1] * galparams_1.wa);
		ga = exp(-(r__1 * r__1));
/* arm, get the arm */
		if (smin < sminmin) {
		    whicharm_spiralmodel__ = j;
		    sminmin = smin;
		}
		if (rr > galparams_1.aa) {
/* Galactocentric radial dependen */
		    r__1 = (rr - galparams_1.aa) / 2.f;
		    ga *= sech2_(&r__1);
/*                write(6,*) 'd99a: rr,Aa,sech2() = ', */
/*                 rr, Aa, sech2((rr-Aa)/2.0) */
		}
/* arm3 reweighting: */
		th3a = 320.f;
		th3b = 390.f;
		th3b = 370.f;
		th3a = 290.f;
		th3b = 363.f;
		th3b = 363.f;
		fac3min = 0.f;
		test3 = thxy - th3a;
		if (test3 < 0.f) {
		    test3 += 360.f;
		}
		if (jj == 3 && 0.f <= test3 && test3 < th3b - th3a) {
		    arg = (thxy - th3a) * 6.2831853f / (th3b - th3a);
/*                fac = (3.0 + cos(arg))/4.0 */
		    fac = (fac3min + 1.f + (1.f - fac3min) * cos(arg)) / 2.f;
		    d__1 = (doublereal) fac;
		    fac = pow_dd(&d__1, &c_b83);
/*                write(90,*) x, y, thxy, th3a, th3b, test3, fac */
		    ga *= fac;
		}
/* arm2 reweighting: */
/*    first: as in tc93 (note different definition of theta) */
		th2a = 35.f;
		th2b = 55.f;
		test2 = thxy - th2a;
		fac = 1.f;
		if (jj == 2 && 0.f <= test2 && test2 < th2b - th2a) {
		    fac = test2 / (th2b - th2a) + 1.f;
		    fac = 1.f;
/* **** note turned off */
		    ga *= fac;
		}
		if (jj == 2 && test2 > th2b - th2a) {
		    fac = 2.f;
		    fac = 1.f;
/* **** note turned off */
		    ga *= fac;
		}
/*    second:  weaken the arm in a short range: */
		th2a = 340.f;
		th2b = 370.f;
/* note fix does nothing if fac2min = 1.0 */
		fac2min = .1f;
		test2 = thxy - th2a;
		if (test2 < 0.f) {
		    test2 += 360.f;
		}
		if (jj == 2 && 0.f <= test2 && test2 < th2b - th2a) {
		    arg = (thxy - th2a) * 6.2831853f / (th2b - th2a);
		    fac = (fac2min + 1.f + (1.f - fac2min) * cos(arg)) / 2.f;
/*                fac = fac**3.5 */
/*                write(90,*) x, y, thxy, th2a, th2b, test2, fac */
		    ga *= fac;
		}
		r__1 = *z__ / (armfactors_1.harm[jj - 1] * galparams_1.ha);
		nea += armfactors_1.narm[jj - 1] * galparams_1.na * ga * 
			sech2_(&r__1);
/* Add this arm */
	    }
/* L50: */
	}
    }
    ret_val = nea;
    *farms = 0.f;
    if (whicharm_spiralmodel__ == 0) {
	*whicharm = 0;
    } else {
	*whicharm = armmap[whicharm_spiralmodel__ - 1];
/* remap arm num */
	*farms = galparams_1.fa * armfactors_1.farm[*whicharm - 1];
    }
    return ret_val;
} /* ne_arms_log_mod__ */

doublereal ne_outer__(real *x, real *y, real *z__, real *f_outer__)
{

    /* System generated locals */
    real ret_val, r__1, r__2;

    /* Builtin functions */
    double sqrt(doublereal), cos(doublereal);

    /* Local variables */
    static real g1, rr, ne1;
    extern doublereal sech2_(real *);
    static real suncos;

/* ----------------------------------------------------------------------- */
/* Thick disk component: */
/*         g1=sech2(rr/A1)/sech2(8.5/A1)                ! TC93 function */
/* Computing 2nd power */
    r__1 = *x;
/* Computing 2nd power */
    r__2 = *y;
    rr = sqrt(r__1 * r__1 + r__2 * r__2);
    suncos = cos(mw_1.rsun * 1.5707963267948966f / galparams_1.a1);
    if (rr > galparams_1.a1) {
	g1 = 0.f;
    } else {
	g1 = cos(rr * 1.5707963267948966f / galparams_1.a1) / suncos;
    }
    r__1 = *z__ / galparams_1.h1;
    ne1 = galparams_1.n1h1 / galparams_1.h1 * g1 * sech2_(&r__1);
    ret_val = ne1;
    *f_outer__ = galparams_1.f1;
    return ret_val;
} /* ne_outer__ */

doublereal ne_inner__(real *x, real *y, real *z__, real *f_inner__)
{
    /* System generated locals */
    real ret_val, r__1, r__2;

    /* Builtin functions */
    double sqrt(doublereal), exp(doublereal);

    /* Local variables */
    static real g2, rr, ne2;
    extern doublereal sech2_(real *);
    static real rrarg;

/* ----------------------------------------------------------------------- */
/* Thin disk (inner Galaxy) component: */
/* (referred to as 'Galactic center component' in circa TC93 density.f) */
    g2 = 0.f;
/* Computing 2nd power */
    r__1 = *x;
/* Computing 2nd power */
    r__2 = *y;
    rr = sqrt(r__1 * r__1 + r__2 * r__2);
/* Computing 2nd power */
    r__1 = (rr - galparams_1.a2) / 1.8f;
    rrarg = r__1 * r__1;
    if (rrarg < 10.f) {
	g2 = exp(-rrarg);
    }
    r__1 = *z__ / galparams_1.h2;
    ne2 = galparams_1.n2 * g2 * sech2_(&r__1);
    ret_val = ne2;
    *f_inner__ = galparams_1.f2;
    return ret_val;
} /* ne_inner__ */

doublereal ne_gc__(real *x, real *y, real *z__, real *f_gc__)
{
    /* Initialized data */

    static logical first = TRUE_;

    /* System generated locals */
    real ret_val, r__1, r__2;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_rsle(cilist *), e_rsle(void), do_lio(integer *,
	     integer *, char *, ftnlen), f_clos(cllist *);
    double sqrt(doublereal);

    /* Local variables */
    static real rr, zz, hgc, arg, rgc, xgc, ygc, zgc;

    /* Fortran I/O blocks */
    static cilist io___70 = { 0, 11, 0, 0, 0 };
    static cilist io___71 = { 0, 11, 0, 0, 0 };
    static cilist io___75 = { 0, 11, 0, 0, 0 };
    static cilist io___77 = { 0, 11, 0, 0, 0 };
    static cilist io___79 = { 0, 11, 0, 0, 0 };
    static cilist io___80 = { 0, 11, 0, 0, 0 };


/* ----------------------------------------------------------------------- */
/*     Determines the contribution of the Galactic center to the free */
/*     electron density of the interstellar medium at Galactic location */
/*     (x,y,z).  Combine with `fluctuation' parameter to obtain the */
/*     scattering measure. */

/*     NOTE: This is for the hyperstrong scattering region in the */
/*     Galactic center.  It is distinct from the inner Galaxy */
/*     (component 2) of the TC93 model. */

/*     Origin of coordinate system is at Galactic center; the Sun is at */
/*     (x,y,z) = (0,R0,0), x is in l=90 direction */

/*     Based on Section 4.3 of Lazio & Cordes (1998, ApJ, 505, 715) */

/* Input: */
/* REAL X - location in Galaxy [kpc] */
/* REAL Y - location in Galaxy [kpc] */
/* REAL Z - location in Galaxy [kpc] */

/* COMMON: */
/* REAL NEGC0 - nominal central density */

/* PARAMETERS: */
/* REAL RGC - radial scale length of Galactic center density enhancement */
/* REAL HGC - z scale height of Galactic center density enhancement */

/* Output: */
/* REAL NE_GC - Galactic center free electron density contribution [cm^-3] */
/* ----------------------------------------------------------------------- */

/*     parameter (xgc=-0.010, ygc=0., zgc=-0.020) */
/*     parameter (rgc=0.145) */
/*     parameter (hgc=0.026) */
    ret_val = 0.f;
    *f_gc__ = 0.f;
    if (first) {
	o__1.oerr = 0;
	o__1.ounit = 11;
	o__1.ofnmlen = 9;
	o__1.ofnm = "ne_gc.inp";
	o__1.orl = 0;
	o__1.osta = "old";
	o__1.oacc = 0;
	o__1.ofm = 0;
	o__1.oblnk = 0;
	f_open(&o__1);
	s_rsle(&io___70);
	e_rsle();
	s_rsle(&io___71);
	do_lio(&c__4, &c__1, (char *)&xgc, (ftnlen)sizeof(real));
	do_lio(&c__4, &c__1, (char *)&ygc, (ftnlen)sizeof(real));
	do_lio(&c__4, &c__1, (char *)&zgc, (ftnlen)sizeof(real));
	e_rsle();
	s_rsle(&io___75);
	do_lio(&c__4, &c__1, (char *)&rgc, (ftnlen)sizeof(real));
	e_rsle();
	s_rsle(&io___77);
	do_lio(&c__4, &c__1, (char *)&hgc, (ftnlen)sizeof(real));
	e_rsle();
	s_rsle(&io___79);
	do_lio(&c__4, &c__1, (char *)&gcparms_1.negc0, (ftnlen)sizeof(real));
	e_rsle();
	s_rsle(&io___80);
	do_lio(&c__4, &c__1, (char *)&gcparms_1.fgc0, (ftnlen)sizeof(real));
	e_rsle();
	cl__1.cerr = 0;
	cl__1.cunit = 11;
	cl__1.csta = 0;
	f_clos(&cl__1);
	first = FALSE_;
    }
/* GALACTOCENTRIC RADIUS */
/* Computing 2nd power */
    r__1 = *x - xgc;
/* Computing 2nd power */
    r__2 = *y - ygc;
    rr = sqrt(r__1 * r__1 + r__2 * r__2);
    if (rr > rgc) {
	return ret_val;
    }
/* Z-HEIGHT. */
/* truncate a */
    zz = (r__1 = *z__ - zgc, dabs(r__1));
    if (zz > hgc) {
	return ret_val;
    }
/* Computing 2nd power */
    r__1 = rr / rgc;
/* Computing 2nd power */
    r__2 = zz / hgc;
    arg = r__1 * r__1 + r__2 * r__2;
    if (arg <= 1.f) {
	ret_val = gcparms_1.negc0;
	*f_gc__ = gcparms_1.fgc0;
/*        write(21,*) 'ne_gc: rr,zz,arg,ne_gc,F_gc ', */
/*    .                rr, zz, arg, ne_gc, F_gc */
    }
    return ret_val;
} /* ne_gc__ */


/* %%%%%%%%%%%%%%%%%%%%%%%%%  cspline.f  %%%%%%%%%%%%%%%%%%%%%%%%%%%%% */

/* Subroutine */ int cspline_(real *x, real *y, integer *nn, real *xout, real 
	*yout)
{
    /* System generated locals */
    integer i__1;
    real r__1, r__2, r__3;

    /* Builtin functions */
    integer s_wsle(cilist *), do_lio(integer *, integer *, char *, ftnlen), 
	    e_wsle(void);
    /* Subroutine */ int s_paus(char *, ftnlen);

    /* Local variables */
    static real a, b, h__;
    static integer i__, k, n;
    static real p, u[20], y2[20], qn, un;
    static integer khi;
    static real sig;
    static integer klo;

    /* Fortran I/O blocks */
    static cilist io___84 = { 0, 6, 0, 0, 0 };
    static cilist io___85 = { 0, 6, 0, 0, 0 };


    /* Parameter adjustments */
    --y;
    --x;

    /* Function Body */
    if (*nn > 20) {
	s_wsle(&io___84);
	do_lio(&c__9, &c__1, " too many points to spline. Change parameter s"
		"tatement", (ftnlen)54);
	e_wsle();
	s_wsle(&io___85);
	do_lio(&c__9, &c__1, " in cspline", (ftnlen)11);
	e_wsle();
    }
    n = abs(*nn);
    if (*nn < 0) {
	y2[0] = 0.f;
	u[0] = 0.f;
	i__1 = n - 1;
	for (i__ = 2; i__ <= i__1; ++i__) {
	    sig = (x[i__] - x[i__ - 1]) / (x[i__ + 1] - x[i__ - 1]);
	    p = sig * y2[i__ - 2] + 2.f;
	    y2[i__ - 1] = (sig - 1.f) / p;
	    u[i__ - 1] = (((y[i__ + 1] - y[i__]) / (x[i__ + 1] - x[i__]) - (y[
		    i__] - y[i__ - 1]) / (x[i__] - x[i__ - 1])) * 6.f / (x[
		    i__ + 1] - x[i__ - 1]) - sig * u[i__ - 2]) / p;
/* L10: */
	}
	qn = 0.f;
	un = 0.f;
	y2[n - 1] = (un - qn * u[n - 2]) / (qn * y2[n - 2] + 1.f);
	for (k = n - 1; k >= 1; --k) {
/* L20: */
	    y2[k - 1] = y2[k - 1] * y2[k] + u[k - 1];
	}
    }
    klo = 1;
    khi = n;
L30:
    if (khi - klo > 1) {
	k = (khi + klo) / 2;
	if (x[k] > *xout) {
	    khi = k;
	} else {
	    klo = k;
	}
	goto L30;
    }
    h__ = x[khi] - x[klo];
    if (h__ == 0.f) {
	s_paus("bad x input.", (ftnlen)12);
    }
    a = (x[khi] - *xout) / h__;
    b = (*xout - x[klo]) / h__;
/* Computing 3rd power */
    r__1 = a;
/* Computing 3rd power */
    r__2 = b;
/* Computing 2nd power */
    r__3 = h__;
    *yout = a * y[klo] + b * y[khi] + ((r__1 * (r__1 * r__1) - a) * y2[klo - 
	    1] + (r__2 * (r__2 * r__2) - b) * y2[khi - 1]) * (r__3 * r__3) / 
	    6.f;
    return 0;
} /* cspline_ */

doublereal sech2_(real *z__)
{
    /* System generated locals */
    real ret_val, r__1;

    /* Builtin functions */
    double exp(doublereal);

/* ----------------------------------------------------------------------- */
    ret_val = 0.f;
    if (dabs(*z__) < 20.f) {
/* Computing 2nd power */
	r__1 = 2.f / (exp(*z__) + exp(-(*z__)));
	ret_val = r__1 * r__1;
    }
    return ret_val;
} /* sech2_ */

