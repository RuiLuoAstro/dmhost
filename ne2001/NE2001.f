c 	program NE2001

c  calls dmdsm to get pulsar distance as a function of l, b, and DM,
c  or pulsar DM as a function of l, b, and distance.
        real function NE2001(ldeg, bdeg, dmd, ndir)
        implicit none
        real ldeg, bdeg, dmd
        integer ndir
        real dist
        real dm, sm, smtau, smtheta, smiso
        real tau, sbw, stime, theta_g, theta_x, transfreq, emsm 

        real nu

	character*1 limit

        real rad
        real vperp
        
c functions:

	integer iargc
	external iargc
        real em, tauiss, scintbw, scintime, theta_xgal, theta_gal
	real transition_frequency
        data nu/1./
        data rad/57.2957795/
        data vperp/100./


	write(*,*)'#NE2001 input: 4 parameters'
	write(*,"(f10.4, t20, a, t30, a, t55, a)") 
     .        ldeg, 'l', '(deg)', 'GalacticLongitude'
	write(*,"(f10.4, t20, a, t30, a, t55, a)") 
     .        bdeg, 'b', '(deg)', 'GalacticLatitude'
	write(*,"(f10.4, t20, a, t30, a, t55, a)") 
     .        dmd,  'DM/D', '(pc-cm^{-3}_or_kpc)', 
     .        'Input_DM_or_Distance'
	write(*,"(i10, t20, a, t30, a, t55, a)") 
     .        ndir, 'ndir', '1:DM->D;-1:D->DM', 'Which?(DM_or_D)'
	write(*,*)'#NE2001 output: 14 values'

	if(ndir.ge.0) then
          dm = dmd
	  call dmdsm(ldeg/rad,bdeg/rad,ndir, dm,
     .               dist,limit,sm,smtau,smtheta,
     .               smiso)

	  write(*,"(a,f9.4, t20, a, t30, a, t55,a)") 
     .         limit, dist, 'DIST', '(kpc)','ModelDistance'
	  write(*,"(f10.4, t20, a, t30, a, t55, a)") 
     .         dm, 'DM', '(pc-cm^{-3})', 'DispersionMeasure' 
	  write(*,"(f10.4, t20, a, t30, a, t55, a)") 
     .         dm*abs(sin(bdeg/rad)), 'DMz', 
     .            '(pc-cm^{-3})', 'DM_Zcomponent' 
	else
	  dist=dmd
	  call dmdsm(ldeg/rad,bdeg/rad,ndir, dm,
     .               dist,limit,sm,smtau,smtheta,
     .               smiso)
c	  write(6,*) 'dm,sm,smtau,smtheta = ', 
c    .               dm,sm,smtau,smtheta
c1020	  format(f8.2,3(1x,e8.3))
c	  write(6,*) 'dmz = ', dm*abs(sin(bdeg/rad))
	  write(*,"(f10.4, t20, a, t30, a, t55, a)") 
     .          dist, 'DIST', '(kpc)', 'Distance'
	  write(*,"(f10.4, t20, a, t30, a, t55,a)") dm, 'DM', 
     .            '(pc-cm^{-3})','ModelDM' 
	  write(*,"(f10.4, t20, a, t30, a, t55, a)") 
     .            dm*abs(sin(bdeg/rad)), 'DMz', 
     .            '(pc-cm^{-3})', 'model' 
	endif

c calculate scattering parameters

 
        tau = tauiss(dist, smtau, nu)
        sbw = scintbw(dist, smtau, nu)
        stime = scintime(smtau, nu, vperp)
        theta_x = theta_xgal(sm, nu)
        theta_g = theta_gal(smtheta, nu)
	transfreq = transition_frequency(sm,smtau,smtheta,dist)
        emsm = em(sm)
	write(*,"(e10.4, t20, a, t30, a, t55, a)") sm, 'SM', 
     .           '(kpc-m^{-20/3})', 'ScatteringMeasure' 
	write(*,"(e10.4, t20, a, t30, a, t55, a)") smtau, 'SMtau', 
     .           '(kpc-m^{-20/3})', 'SM_PulseBroadening' 
	write(*,"(e10.4, t20, a, t30, a, t55, a)") smtheta, 'SMtheta', 
     .           '(kpc-m^{-20/3})', 'SM_GalAngularBroadening' 
	write(*,"(e10.4, t20, a, t30, a, t55, a)") smiso, 'SMiso', 
     .           '(kpc-m^{-20/3})', 'SM_IsoplanaticAngle' 
	write(*,"(e10.4, t20, a, t30, a, t55, a)") emsm, 'EM', 
     .           '(pc-cm^{-6})','EmissionMeasure_from_SM' 

	write(*,"(e10.4, t20, a, t30, a, t55, a)") tau, 'TAU', 
     .           '(ms)', 
     .           'PulseBroadening @1GHz' 
	write(*,"(e10.4, t20, a, t30, a, t55, a)") sbw/1000., 'SBW', 
     .           '(MHz)', 
     .           'ScintBW @1GHz' 
	write(*,"(e10.4, t20, a, t30, a, t55, a)") stime, 'SCINTIME', 
     .           '(s)', 
     .           'ScintTime @1GHz @100 km/s' 
	write(*,"(e10.4, t20, a, t30, a, t55, a)") theta_g, 'THETA_G', 
     .           '(mas)', 
     .           'AngBroadeningGal @1GHz' 
	write(*,"(e10.4, t20, a, t30, a, t55, a)") theta_x, 'THETA_X', 
     .           '(mas)', 
     .           'AngBroadeningXgal @1GHz' 
	write(*,"(f10.2, t20, a, t30, a, t55, a)") transfreq, 
     .           'NU_T', 
     .           '(GHz)', 'TransitionFrequency' 

	stop
	end