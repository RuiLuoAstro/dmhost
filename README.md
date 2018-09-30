# dmhost

Simulations of FRB host galaxy dispersion measures (DMs) in nearby universe.

## Notice

If you would like to use the code to simulate DM of FRB host galaxies in any cases, please cite the paper [Luo et al. 2018, MNRAS, 481, 2320](http://adsabs.harvard.edu/abs/2018MNRAS.481.2320L)

## Dependencies

### Numpy, Scipy, gcc (4.8.x), gfortran(4.8.x)


## Directions

### A large sample of Early-type Galaxies (ETGs):

$ ./run_dmetg.sh

### Luminous Halpha ETGs (LHEGs):

$ ./run_dmlheg.sh

### Template of ETGs: M87

$ ./run_dmetgtemp.sh

-----------------------------------------------------

### A large sample of Late-type Galaxies (LTGs):

$ ./run_dmltg_ne2001.sh  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;   Using NE2001 electron density model ([Cordes & Lazio 2002](http://adsabs.harvard.edu/cgi-bin/bib_query?arXiv:astro-ph/0207156)) as template

$ ./run_dmltg_ymw16.sh  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;   Using YMW16 electron density model ([Yao, Manchester, Wang, 2017, ApJ](http://adsabs.harvard.edu/cgi-bin/bib_query?arXiv:1610.09448)) as template

### Template of LTGs: the Milky Way

$ ./run_dmtemp_ne2001.sh &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  Using NE2001 electron density model as template

$ ./run_dmtemp_ymw16.sh &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  Using YMW16 electron density model as template

-----------------------------------------------------

### A large sample of All the galaxies (ALGs):

$ ./run_dmalg_ne2001.sh  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Including ETGs and LTGs according to the results from SDSS, using NE2001 electron density model as LTG template, M87 as ETG template. 

$ ./run_dmalg_ymw16.sh  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Including ETGs and LTGs according to the results from SDSS, using YMW16 electron density model as LTG template, M87 as ETG template. 


