# dmhost

Simulations of FRB host galaxy dispersion measures (DMs) in the nearby universe, each simulation contains 1,000,000 FRBs

## NOTICE

If you would like to use the code to simulate DM of FRB host galaxies in any cases, please cite the paper [Luo et al. 2018, MNRAS, 481, 2320](http://adsabs.harvard.edu/abs/2018MNRAS.481.2320L)

## Dependencies
### Numpy, Scipy, gcc (4.8.x), gfortran(4.8.x)


## Directions
### A large sample of Early-type Galaxies (ETGs):

```./run_dmetg.sh```

### Luminous Halpha ETGs (LHEGs):

```./run_dmlheg.sh```

### Template of ETGs: M87

```./run_dmetgtemp.sh```

### A large sample of Late-type Galaxies (LTGs):

```./run_dmltg_ne2001.sh```  &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;   Using NE2001 electron density model ([Cordes & Lazio 2002](http://adsabs.harvard.edu/cgi-bin/bib_query?arXiv:astro-ph/0207156)) as template

```./run_dmltg_ymw16.sh``` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;   Using YMW16 electron density model ([Yao, Manchester, Wang, 2017, ApJ, 835, 29](http://adsabs.harvard.edu/abs/2017ApJ...835...29Y)) as template

### Template of LTGs: the Milky Way

```./run_dmtemp_ne2001.sh``` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  Using NE2001 electron density model as template

```./run_dmtemp_ymw16.sh``` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;  Using YMW16 electron density model as template

### A large sample of All the galaxies (ALGs):

```./run_dmalg_ne2001.sh``` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Including ETGs and LTGs according to the results from SDSS, using NE2001 electron density model as LTG template, M87 as ETG template. 

```./run_dmalg_ymw16.sh``` &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp; Including ETGs and LTGs according to the results from SDSS, using YMW16 electron density model as LTG template, M87 as ETG template. 

### Updates on acceleration of YMW16 integration
**To avoid consuming time on reading parameters for large number of DMs calculation, e.g. reading parameters once in one DM integration, we regenerated the executable file of YMW16 by reconstructing the main function. You can accomplish the simulations by these commands as following:**
```
cd ymw16/
./runltg.sh 
```
 Simulating FRB DMs of LTGs in the case that LTGs as hosts

```./runalg.sh ```       
Simulating FRB DMs of LTGs in the case that ALGs as hosts.

**This just includes the LTGs DMs, in order to get the DM of ETGs in the ALGs case, you still need to run**

``` ./run_dmetg_ymw16.sh ```
