/* dmdsm.NE2001.f -- translated by f2c (version 20100827).
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
    real armpaths[6], armdistances[6];
} armpathlengths_;

#define armpathlengths_1 armpathlengths_

struct {
    real dx0, dy0, dz0;
} dxyz_;

#define dxyz_1 dxyz_

/* Table of constant values */

static integer c__4 = 4;
static integer c__1 = 1;
static integer c__9 = 9;
static doublereal c_b19 = 1.66667;

/* 15  Jan 2003: fixed whicharm bug (c.f. TWJL email of 12 Dec '02) */
/* 24 June 2002: added calculations of path lengths through LISM components */
/* 26  May 2002: modified for NE2001 routines which are cleaned-up */
/*           versions of development routines. */
/* Nov 1999 - May 2002: development versions */
/* 1992-1993: TC93 version */
/* Subroutine */ int dmdsm_(real *l, real *b, integer *ndir, real *dmpsr, 
	real *dist, char *limit, real *sm, real *smtau, real *smtheta, real *
	smiso, ftnlen limit_len)
{
    /* Initialized data */

    static real r0 = 8.5f;
    static real rrmax = 50.f;
    static real zmax = 25.f;
    static real dmax__ = 50.f;
    static logical first = TRUE_;

    /* Format strings */
    static char fmt_1000[] = "(\002    d       x       y       z       ne"
	    "\002,\002      dsm    arm  cl void\002)";

    /* System generated locals */
    integer i__1;
    real r__1, r__2, r__3, r__4, r__5, r__6, r__7;
    doublereal d__1;
    olist o__1;
    cllist cl__1;

    /* Builtin functions */
    integer f_open(olist *), s_wsle(cilist *);
    double acos(doublereal);
    integer do_lio(integer *, integer *, char *, ftnlen), e_wsle(void), 
	    s_wsfe(cilist *), e_wsfe(void);
    double sin(doublereal), cos(doublereal), sqrt(doublereal), pow_dd(
	    doublereal *, doublereal *);
    integer do_fio(integer *, char *, ftnlen);
    /* Subroutine */ int s_stop(char *, ftnlen);
    integer f_clos(cllist *);

    /* Local variables */
    static real lhb_path__, lhb_dist__, lsb_path__, ldr_path__, dstep_pc__;
    static integer whicharm;
    static real lsb_dist__, ldr_dist__;
    static integer hitclump;
    static real d__;
    static integer i__;
    static real r__, x, y, z__, cb, dd, cl, dm, ne, sb, sl, rr;
    extern /* Subroutine */ int density_2001__(real *, real *, real *, real *,
	     real *, real *, real *, real *, real *, real *, real *, real *, 
	    real *, real *, real *, real *, real *, integer *, integer *, 
	    integer *, integer *, integer *, integer *, integer *, integer *, 
	    integer *);
    static real dm1, dm2, ne1, ne2, loopi_path__, sm1, sm2, loopi_dist__, fgc,
	     dma, nea, fcn, sma, fvn, dsm1, dsm2, dmgc, negc, dmcn, necn, 
	    dsma, smgc;
    static integer wlhb;
    static real smcn, dmvn, sm_sum1_last__;
    static integer wlsb, wldr;
    static real nevn, sm_sum2_last__, sm_sum3_last__, sm_sum4_last__, smvn, 
	    f1val, f2val, faval, dsmgc, dsmcn, flism, dstep, dtest;
    static integer wvoid, wlism, wtemp, nstep;
    static real dsmvn, dmlism, nelism, dmstep, smlism;
    static integer ncount, wloopi, wtotal;
    static real sm_sum1__, sm_sum2__, sm_sum3__, sm_sum4__;
    static integer hitvoid;
    static real sm_term__, dsmlism;

    /* Fortran I/O blocks */
    static cilist io___6 = { 0, 25, 0, 0, 0 };
    static cilist io___7 = { 0, 25, 0, fmt_1000, 0 };
    static cilist io___90 = { 0, 25, 0, "(4(f7.3,1x),f8.4,1x,e10.3,1x,i1,1x,"
	    "i4,1x,i2)", 0 };
    static cilist io___92 = { 0, 24, 0, "(a,a)", 0 };
    static cilist io___93 = { 0, 24, 0, "(t15, a)", 0 };
    static cilist io___94 = { 0, 24, 0, "(t3, a, t15, 4(f6.3, 3x))", 0 };
    static cilist io___95 = { 0, 24, 0, "(t3, a, t15, 4(f6.3, 3x))", 0 };
    static cilist io___96 = { 0, 24, 0, "(a)", 0 };
    static cilist io___97 = { 0, 24, 0, "(a,a)", 0 };
    static cilist io___98 = { 0, 24, 0, "(7(f7.3,1x), f10.3)", 0 };
    static cilist io___99 = { 0, 24, 0, "(a)", 0 };
    static cilist io___100 = { 0, 24, 0, "(a,a)", 0 };
    static cilist io___101 = { 0, 24, 0, "(7(f7.3,1x), e10.3)", 0 };
    static cilist io___102 = { 0, 24, 0, "(a)", 0 };
    static cilist io___103 = { 0, 24, 0, "(t1,a,t10, a, t30, a)", 0 };
    static cilist io___104 = { 0, 24, 0, "(i2,t10,f8.3,t30,f8.3)", 0 };


/*  Computes pulsar distance and scattering measure */
/*  from model of Galactic electron distribution. */
/*  Input: real l      galactic longitude in radians */
/*       real b      galactic latitude in radians */
/*       integer ndir  >= 0 calculates dist from dmpsr */
/*                   < 0 for dmpsr from dist */
/* Input or output: */
/*        real dmpsr      (dispersion measure in pc/cm^3) */
/*       real dist      (distance in kpc) */
/*  Output: */
/*        char*1 limit      (set to '>' if only a lower distance limit can be */
/*                   given; otherwise set to ' ') */
/*       sm          (scattering measure, uniform weighting) (kpc/m^{20/3}) */
/*       smtau       (scattering measure, weighting for pulse broadening) */
/*       smtheta       (scattering measure, weighting for angular broadening */
/*                  of galactic sources) */
/*        smiso       (scattering measure appropriate for calculating the */
/*                  isoplanatic angle at the source's location */
/*       parameter(alpha = 11./3.) */
/*       parameter(pi = 3.14159) */
/*       parameter(c_sm = (alpha - 3.) / 2. * (2.*pi)**(4.-alpha) ) */
/*       ! constant in sm definition */
/*        ! units conversion for sm */
/* parameters of large-scale components (inner+outer+arm components): */
/* factors for controlling individual spiral arms: */
/*       narm:   multiplies electron density (in addition to the`fac' */
/*                 quantities) */
/*       warm:   arm width factors that multiply nominal arm width */
/*       harm:   arm scale height factors */
/*       farm:   factors that multiply n_e^2 when calculating SM */
/* Large scale components: */
/* Galactic center: */
/* LISM: */
/* clumps: */
/* voids: */
/* subroutines needed: */
/*      density_2001 (and those that it calls) in density.NE2001.f */
/*       scattering routines in scattering98.f */
/*      data rrmax/30.0/            ! Max radius for reliable ne */
/*      data zmax/1.76/                  ! Max |z| */
/*      data zmax/5.00/                  ! Max |z| */
/* Max radius for reliable ne */
/* Max |z| */
/* maximum distance calculated */
/* other variables */
    o__1.oerr = 0;
    o__1.ounit = 24;
    o__1.ofnmlen = 7;
    o__1.ofnm = "fort.24";
    o__1.orl = 0;
    o__1.osta = "unknown";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    o__1.oerr = 0;
    o__1.ounit = 25;
    o__1.ofnmlen = 7;
    o__1.ofnm = "fort.25";
    o__1.orl = 0;
    o__1.osta = "unknown";
    o__1.oacc = 0;
    o__1.ofm = 0;
    o__1.oblnk = 0;
    f_open(&o__1);
    s_wsle(&io___6);
    r__1 = *l * 180.f / acos(-1.f);
    do_lio(&c__4, &c__1, (char *)&r__1, (ftnlen)sizeof(real));
    r__2 = *b * 180.f / acos(-1.f);
    do_lio(&c__4, &c__1, (char *)&r__2, (ftnlen)sizeof(real));
    do_lio(&c__9, &c__1, " = l, b", (ftnlen)7);
    e_wsle();
    s_wsfe(&io___7);
    e_wsfe();
    if (first) {
/* initial call to density routine to set variable values */
/* through read-in of parameter file: */
	x = 0.f;
	y = r0;
	z__ = 0.f;
	density_2001__(&x, &y, &z__, &ne1, &ne2, &nea, &negc, &nelism, &necn, 
		&nevn, &f1val, &f2val, &faval, &fgc, &flism, &fcn, &fvn, &
		whicharm, &wlism, &wldr, &wlhb, &wlsb, &wloopi, &hitclump, &
		hitvoid, &wvoid);
/*       write(6,*) 'ne1,ne2,negc,nelism,necN,nevN = ', */
/*    .            ne1,ne2,negc,nelism,necN,nevN */
	first = FALSE_;
    }
    sl = sin(*l);
    cl = cos(*l);
    sb = sin(*b);
    cb = cos(*b);
    *(unsigned char *)limit = ' ';
/*      dstep=0.02                  ! Step size in kpc */
/*       dstep = min(h1, h2) / 10.       ! step size in terms of scale heights */
    dstep = .01f;
    if (*ndir < 0) {
	dtest = *dist;
    }
    if (*ndir >= 0) {
	dtest = *dmpsr / (galparams_1.n1h1 / galparams_1.h1);
    }
/* approximate test distance */
    nstep = dtest / dstep;
/* approximate number of steps */
    if (nstep < 10) {
	dstep = dtest / 10;
    }
/*  Sum until dm is reached (ndir >= 0) or dist is reached (ndir < 0). */
/*  Guard against too few terms by counting number of terms (ncount) so that */
/*  routine will work for n_e models with large n_e near the Sun. */
/* make # steps >= 10 */
L5:
    dstep_pc__ = dstep * 1e3f;
    dm = 0.f;
    sm_sum1__ = 0.f;
/* sum of C_n^2 */
    sm_sum2__ = 0.f;
/* sum of C_n^2 * s */
    sm_sum3__ = 0.f;
/* sum of C_n^2 * s^2 */
    sm_sum4__ = 0.f;
/* sum of C_n^2 * s^{5./3.} */
    for (i__ = 1; i__ <= 6; ++i__) {
	armpathlengths_1.armpaths[i__ - 1] = 0.f;
	armpathlengths_1.armdistances[i__ - 1] = 0.f;
    }
    dm1 = 0.f;
    dm2 = 0.f;
    dma = 0.f;
    dmgc = 0.f;
    dmlism = 0.f;
    dmcn = 0.f;
    dmvn = 0.f;
    sm1 = 0.f;
    sm2 = 0.f;
    sma = 0.f;
    smgc = 0.f;
    smlism = 0.f;
    smcn = 0.f;
    smvn = 0.f;
    ldr_path__ = 0.f;
    lhb_path__ = 0.f;
    lsb_path__ = 0.f;
    loopi_path__ = 0.f;
    ldr_dist__ = 0.f;
    lhb_dist__ = 0.f;
    lsb_dist__ = 0.f;
    loopi_dist__ = 0.f;
    ncount = 0;
    d__ = dstep * -.5f;
    for (i__ = 1; i__ <= 99999; ++i__) {
	++ncount;
	d__ += dstep;
/* Distance from Sun in kpc */
	r__ = d__ * cb;
	x = r__ * sl;
	y = r0 - r__ * cl;
	z__ = d__ * sb;
/* Computing 2nd power */
	r__1 = x;
/* Computing 2nd power */
	r__2 = y;
	rr = sqrt(r__1 * r__1 + r__2 * r__2);
/* Galactocentric radius */
	if (*ndir >= 0 && (d__ > dmax__ || dabs(z__) > zmax || rr > rrmax)) {
	    goto L20;
	}
	if (*ndir < 3) {
	    density_2001__(&x, &y, &z__, &ne1, &ne2, &nea, &negc, &nelism, &
		    necn, &nevn, &f1val, &f2val, &faval, &fgc, &flism, &fcn, &
		    fvn, &whicharm, &wlism, &wldr, &wlhb, &wlsb, &wloopi, &
		    hitclump, &hitvoid, &wvoid);
	}
	if (*ndir >= 3) {
	    r__1 = x + dxyz_1.dx0;
	    r__2 = y + dxyz_1.dy0;
	    r__3 = z__ + dxyz_1.dz0;
	    density_2001__(&r__1, &r__2, &r__3, &ne1, &ne2, &nea, &negc, &
		    nelism, &necn, &nevn, &f1val, &f2val, &faval, &fgc, &
		    flism, &fcn, &fvn, &whicharm, &wlism, &wldr, &wlhb, &wlsb,
		     &wloopi, &hitclump, &hitvoid, &wvoid);
	}
/* wlism = 1 causes the lism component to override smooth Galactic components */
/* wvoid = 1 overrides everything except clumps */
	ne = (1.f - modelflags_1.wglism * wlism) * (modelflags_1.wg1 * ne1 + 
		modelflags_1.wg2 * ne2 + modelflags_1.wga * nea + 
		modelflags_1.wggc * negc) + modelflags_1.wglism * wlism * 
		nelism;
	ne = (1 - modelflags_1.wgvn * wvoid) * ne + modelflags_1.wgvn * wvoid 
		* nevn + modelflags_1.wgcn * necn;
	dmstep = dstep_pc__ * ne;
	dm += dmstep;
/* Add DM for this step */
	wtotal = (1 - modelflags_1.wgvn * wvoid) * (1 - modelflags_1.wglism * 
		wlism);
	dm1 += wtotal * modelflags_1.wg1 * ne1;
	dm2 += wtotal * modelflags_1.wg2 * ne2;
	dma += wtotal * modelflags_1.wga * nea;
	dmgc += wtotal * modelflags_1.wggc * negc;
	dmlism += (1.f - modelflags_1.wgvn * wvoid) * modelflags_1.wglism * 
		wlism * nelism;
	dmcn += modelflags_1.wgcn * necn;
	dmvn += modelflags_1.wgvn * wvoid * nevn;
/*       write(24,"('n:',7f10.6,1x))") */
/*    .      ne1,ne2,nea,negc,nelism,necN,nevN */
/*      write(24,"(i2,1x,7(f10.5,1x))") */
/*    .      wtotal,dm1,dm2,dma,dmgc,dmlism,dmcN,dmvN */
/*       sm_term = */
/*    .       (1.-wglism*wlism)* */
/*    .       (wg1   * F1  * ne1**2 + */
/*    .      wg2   * F2  * ne2**2 + */
/*    .      wga   * Fa  * nea**2 + */
/*    .      wggc  * Fgc * negc**2) + */
/*    .      wglism*wlism * Flism * nelism**2 */
/*        sm_clumps = FcN * necN**2 */
/*        sm_voids  = FvN * nevN**2 */
/*       sm_term = (1-wgvN*wvoid) * sm_term */
/*    .          + wgvN * wvoid * sm_voids */
/*    .          + wgcN * sm_clumps */
/* Computing 2nd power */
	r__1 = ne1;
	dsm1 = wtotal * modelflags_1.wg1 * (r__1 * r__1) * galparams_1.f1;
/* Computing 2nd power */
	r__1 = ne2;
	dsm2 = wtotal * modelflags_1.wg2 * (r__1 * r__1) * galparams_1.f2;
/* Computing 2nd power */
	r__1 = nea;
	dsma = wtotal * modelflags_1.wga * (r__1 * r__1) * galparams_1.fa;
/* Computing 2nd power */
	r__1 = negc;
	dsmgc = wtotal * modelflags_1.wggc * (r__1 * r__1) * fgc;
/* Computing 2nd power */
	r__1 = nelism;
	dsmlism = (1.f - modelflags_1.wgvn * wvoid) * modelflags_1.wglism * 
		wlism * (r__1 * r__1) * flism;
/* Computing 2nd power */
	r__1 = necn;
	dsmcn = modelflags_1.wgcn * (r__1 * r__1) * fcn;
/* Computing 2nd power */
	r__1 = nevn;
	dsmvn = modelflags_1.wgvn * wvoid * (r__1 * r__1) * fvn;
	sm_term__ = dsm1 + dsm2 + dsma + dsmgc + dsmlism + dsmcn + dsmvn;
	sm1 += dsm1;
	sm2 += dsm2;
	sma += dsma;
	smgc += dsmgc;
	smlism += dsmlism;
	smcn += dsmcn;
	smvn += dsmvn;
	sm_sum1__ += sm_term__;
	sm_sum2__ += sm_term__ * d__;
/* Computing 2nd power */
	r__1 = d__;
	sm_sum3__ += sm_term__ * (r__1 * r__1);
	d__1 = (doublereal) d__;
	sm_sum4__ += sm_term__ * pow_dd(&d__1, &c_b19);
/* pathlengths through LISM components: */
/* take into account the weighting hierarchy, LHB:LOOPI:LSB:LDR */
	if (wlism == 1) {
	    if (wlhb == 1) {
		lhb_path__ += dstep;
		lhb_dist__ += d__;
	    }
	    if (wloopi == 1) {
		wtemp = 1 - wlhb;
		loopi_path__ += wtemp * dstep;
		loopi_dist__ += wtemp * d__;
	    }
	    if (wlsb == 1) {
		wtemp = (1 - wlhb) * (1 - wloopi);
		lsb_path__ += wtemp * dstep;
		lsb_dist__ += wtemp * d__;
	    }
	    if (wldr == 1) {
		wtemp = (1 - wlhb) * (1 - wloopi) * (1 - wlsb);
		ldr_path__ += wtemp * dstep;
		ldr_dist__ += wtemp * d__;
	    }
	}
/* pathlengths: whicharm = 0,5 (currently). */
/*                     1,4 for the equivalent of the TC93 arms */
/*                   5   for the local arm */
/*                   0   means interarm paths */
	armpathlengths_1.armpaths[whicharm] += dstep;
	armpathlengths_1.armdistances[whicharm] += d__;
/*       write(99,"(2(f8.3,1x), 7f10.6)") */
/*    .     d, dm, sm_term,  sm_sum1, sm_sum2, sm_sum3, */
/*    .     sm_sum1_last, sm_sum2_last, sm_sum3_last */
	if (*ndir >= 0 && dm >= *dmpsr) {
	    goto L30;
	}
/* Reached pulsar's DM? */
	if (*ndir < 0 && d__ >= *dist) {
	    goto L40;
	}
/* Reached pulsar's dist? */
	sm_sum1_last__ = sm_sum1__;
	sm_sum2_last__ = sm_sum2__;
	sm_sum3_last__ = sm_sum3__;
	sm_sum4_last__ = sm_sum4__;
	s_wsfe(&io___90);
	do_fio(&c__1, (char *)&d__, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&x, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&y, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&z__, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&ne, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&sm_term__, (ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&whicharm, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hitclump, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&hitvoid, (ftnlen)sizeof(integer));
	e_wsfe();
/* L10: */
    }
    s_stop("loop limit", (ftnlen)10);
L20:
    *(unsigned char *)limit = '>';
/* Only lower limit is possible */
    *dist = d__ - dstep * .5f;
    goto L999;
L30:
    *dist = d__ + dstep * .5f - dstep * (dm - *dmpsr) / dmstep;
/* Interpolate last s */
    if (ncount < 10) {
	dstep /= 10.f;
	goto L5;
    }
    goto L999;
L40:
    *dmpsr = dm - dmstep * (d__ + dstep * .5f - *dist) / dstep;
    if (ncount < 10) {
	dstep /= 10.f;
	goto L5;
    }
L999:
/* normalize the mean distances: */
    if (ldr_path__ > 0.f) {
	ldr_dist__ /= ldr_path__ / dstep;
    }
    if (lhb_path__ > 0.f) {
	lhb_dist__ /= lhb_path__ / dstep;
    }
    if (lsb_path__ > 0.f) {
	lsb_dist__ /= lsb_path__ / dstep;
    }
    if (loopi_path__ > 0.f) {
	loopi_dist__ /= loopi_path__ / dstep;
    }
    dd = d__ + dstep * .5f - *dist;
/* subtract dd from armpath for latest arm (or iterarm) at end of LOS */
/*       armpaths(whicharm) = armpaths(whicharm)-dd      ! < 16 Jan '03 */
    armpathlengths_1.armpaths[whicharm] -= dd;
/* >,= 16 Jan */
    for (i__ = 1; i__ <= 6; ++i__) {
/* Computing MAX */
	r__1 = 1.f, r__2 = armpathlengths_1.armpaths[i__ - 1] / dstep;
	armpathlengths_1.armdistances[i__ - 1] /= dmax(r__1,r__2);
/* mean d */
    }
    dm1 *= dstep_pc__;
    dm2 *= dstep_pc__;
    dma *= dstep_pc__;
    dmgc *= dstep_pc__;
    dmlism *= dstep_pc__;
    dmcn *= dstep_pc__;
    dmvn *= dstep_pc__;
/*       dsm = sm_term * (d+0.5*dstep - dist) */
/*       dsm = sm_term * dd */
/*       sm_sum2 = sm_sum2 - dsm * d */
/*       sm_sum3 = sm_sum3 - dsm * d**2 */
/*       sm_sum4 = sm_sum4 - dsm * d**1.67 */
/*       sm_sum1 = sm_sum1 - dsm */
/*       write(99,*) 'dmdsm: sm_term, sm_sum1, sm_sum1_last = ', */
/*    .    sm_term, sm_sum1, sm_sum1_last */
/*      write(6,*) 'dmdsm: dsum1, sm_term = ', */
/*    .     sm_sum1-sm_sum1_last, sm_term */
    sm_sum1__ -= dd * (sm_sum1__ - sm_sum1_last__) / dstep;
    sm_sum2__ -= dd * (sm_sum2__ - sm_sum2_last__) / dstep;
    sm_sum3__ -= dd * (sm_sum3__ - sm_sum3_last__) / dstep;
    sm_sum4__ -= dd * (sm_sum4__ - sm_sum4_last__) / dstep;
/*       sm_sum2 = sm_sum2 - dsm * dist */
/*       sm_sum3 = sm_sum3 - dsm * dist**2 */
/*       sm_sum4 = sm_sum4 - dsm * dist**1.67 */
    *sm = dstep * 1.8389599999999999f * sm_sum1__;
/* Computing 2nd power */
    r__1 = *dist;
    *smtau = dstep * 11.033759999999999f * (sm_sum2__ / *dist - sm_sum3__ / (
	    r__1 * r__1));
/* Computing 2nd power */
    r__1 = *dist;
    *smtheta = dstep * 5.5168799999999996f * (sm_sum1__ + sm_sum3__ / (r__1 * 
	    r__1) - sm_sum2__ * 2.f / *dist);
    *smiso = dstep * 1.8389599999999999f * sm_sum4__;
    sm1 = sm1 * 1.8389599999999999f * dstep;
    sm2 = sm2 * 1.8389599999999999f * dstep;
    sma = sma * 1.8389599999999999f * dstep;
    smgc = smgc * 1.8389599999999999f * dstep;
    smlism = smlism * 1.8389599999999999f * dstep;
    smcn = smcn * 1.8389599999999999f * dstep;
    smvn = smvn * 1.8389599999999999f * dstep;
/*       write(24,*) dm1, dm2, dma, dmgc, dmlism, dmcN, dmvN, dm */
    s_wsfe(&io___92);
    do_fio(&c__1, "LISM path lengths (kpc)", (ftnlen)23);
    do_fio(&c__1, " with weighting hierarchy LHB:LOOPI:LSB:LDR", (ftnlen)43);
    e_wsfe();
    s_wsfe(&io___93);
    do_fio(&c__1, "  LHB     LoopI     LSB      LDR", (ftnlen)32);
    e_wsfe();
    s_wsfe(&io___94);
    do_fio(&c__1, "Length", (ftnlen)6);
    do_fio(&c__1, (char *)&lhb_path__, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&loopi_path__, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&lsb_path__, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&ldr_path__, (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___95);
    do_fio(&c__1, "Mean Dist.", (ftnlen)10);
    do_fio(&c__1, (char *)&lhb_dist__, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&loopi_dist__, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&lsb_dist__, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&ldr_dist__, (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___96);
    do_fio(&c__1, "Fractional contributions to DM:", (ftnlen)31);
    e_wsfe();
    s_wsfe(&io___97);
    do_fio(&c__1, "  outer   inner    arms     gc    lism", (ftnlen)38);
    do_fio(&c__1, "    clumps  voids       DM", (ftnlen)26);
    e_wsfe();
    s_wsfe(&io___98);
    r__1 = dm1 / dm;
    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
    r__2 = dm2 / dm;
    do_fio(&c__1, (char *)&r__2, (ftnlen)sizeof(real));
    r__3 = dma / dm;
    do_fio(&c__1, (char *)&r__3, (ftnlen)sizeof(real));
    r__4 = dmgc / dm;
    do_fio(&c__1, (char *)&r__4, (ftnlen)sizeof(real));
    r__5 = dmlism / dm;
    do_fio(&c__1, (char *)&r__5, (ftnlen)sizeof(real));
    r__6 = dmcn / dm;
    do_fio(&c__1, (char *)&r__6, (ftnlen)sizeof(real));
    r__7 = dmvn / dm;
    do_fio(&c__1, (char *)&r__7, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&dm, (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___99);
    do_fio(&c__1, "Fractional contributions to SM:", (ftnlen)31);
    e_wsfe();
    s_wsfe(&io___100);
    do_fio(&c__1, "  outer   inner    arms     gc    lism", (ftnlen)38);
    do_fio(&c__1, "    clumps  voids       SM", (ftnlen)26);
    e_wsfe();
    s_wsfe(&io___101);
    r__1 = sm1 / *sm;
    do_fio(&c__1, (char *)&r__1, (ftnlen)sizeof(real));
    r__2 = sm2 / *sm;
    do_fio(&c__1, (char *)&r__2, (ftnlen)sizeof(real));
    r__3 = sma / *sm;
    do_fio(&c__1, (char *)&r__3, (ftnlen)sizeof(real));
    r__4 = smgc / *sm;
    do_fio(&c__1, (char *)&r__4, (ftnlen)sizeof(real));
    r__5 = smlism / *sm;
    do_fio(&c__1, (char *)&r__5, (ftnlen)sizeof(real));
    r__6 = smcn / *sm;
    do_fio(&c__1, (char *)&r__6, (ftnlen)sizeof(real));
    r__7 = smvn / *sm;
    do_fio(&c__1, (char *)&r__7, (ftnlen)sizeof(real));
    do_fio(&c__1, (char *)&(*sm), (ftnlen)sizeof(real));
    e_wsfe();
    s_wsfe(&io___102);
    do_fio(&c__1, "Path lengths through spiral arms:", (ftnlen)33);
    e_wsfe();
    s_wsfe(&io___103);
    do_fio(&c__1, "Arm", (ftnlen)3);
    do_fio(&c__1, "Mean Distance", (ftnlen)13);
    do_fio(&c__1, "Path Length    (arm=0 => interarm)", (ftnlen)34);
    e_wsfe();
    for (i__ = 1; i__ <= 6; ++i__) {
	s_wsfe(&io___104);
	i__1 = i__ - 1;
	do_fio(&c__1, (char *)&i__1, (ftnlen)sizeof(integer));
	do_fio(&c__1, (char *)&armpathlengths_1.armdistances[i__ - 1], (
		ftnlen)sizeof(real));
	do_fio(&c__1, (char *)&armpathlengths_1.armpaths[i__ - 1], (ftnlen)
		sizeof(real));
	e_wsfe();
    }
    cl__1.cerr = 0;
    cl__1.cunit = 24;
    cl__1.csta = 0;
    f_clos(&cl__1);
    cl__1.cerr = 0;
    cl__1.cunit = 25;
    cl__1.csta = 0;
    f_clos(&cl__1);
    return 0;
} /* dmdsm_ */

