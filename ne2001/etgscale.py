# Here is the scaling for a large sample of Early-type Galaxies
import numpy as np
import random

# Basic scaling parameters of the ETG template
#T_M87 = 1e4
lha_M87 = 1e40
Reff_M87 = 7.7

# The average radii of ETGs resulting from r-band LF and R-M relation
#Ravg = 0.76

# Halpha LF1 of ETGs
loglha_etg = 41.02
#lha_etg = np.power(10., loglha_etg)
aha_etg = 0.79
phihas_etg2 = 0.78*0.001
phihas_etg1 = 0.0047

# Halpha LF2 of ETGs
phi0_etg = 0.000850217606586
logphi0_etg = np.log10(phi0_etg)
logls0_etg = 41.272853031
#beta_etg = -0.617
beta_etg = -0.362

# size-magnitude relation parameters (Shen et al. 2003)
mag_r0 = -20.52
a = 0.60
b = -4.63

# r-band LF (Nakamura et al. 2003)
mags_etg = -20.75
alf_etg = -0.83
phis_etg = 0.47*0.01

# Halpha LF
def LFlogHa(loglha, phis1, logls, phis2, alpha):
    if 36 < loglha < 39:
        phi = phis1
    elif 39 <= loglha <= 43:
        lha = np.power(10, loglha)
        ls = np.power(10, logls)
        phi = phis2 * np.log(10) * np.power(lha/ls, alpha+1) * np.exp(-lha/ls)
    else:
        phi=0
    return phi


def LF(mag,mag_s,phi_s,alpha):
    m2l = np.power(10, 0.4*(mag_s-mag))
    phi = 0.4 * np.log(10) * phi_s * np.power(m2l, alpha+1) * np.exp(-m2l)
    return phi

def Reff(mag, mag0):
    r50 = np.power(10, -0.4*a*mag+b)
    reff = r50/0.7  # 0.7 is the SDSS Petrosian ratio (Graham et al. 2005)
    return reff

# Scaling formula
def scalefactor(R,l_ha):
    #Tratio = T/T_M87
    Rratio = R/Reff_M87
    lratio = l_ha/lha_M87
    eta = np.power(lratio/Rratio, 0.5)
    return eta

# Monte Carlo sampling for ETGs
def etg_sel():
    s = [1,2]
    #for i in range(n):
    while(True):
        mag = np.random.uniform(-24, -18)
        phi_lf = np.random.uniform(0, 0.01)
        if LF(mag, mags_etg, phis_etg, alf_etg) > phi_lf:
            loglha = np.random.uniform(36, 42.4)
            phi_lfha = np.random.uniform(0, 0.01)
            if LFlogHa(loglha, phihas_etg1, loglha_etg, phihas_etg2, aha_etg) > phi_lfha:
                break
    lha = np.power(10., loglha)
    #R = Ravg
    R = Reff(mag, mag_r0)
    s[0] = R
    s[1] = lha
    return np.array(s)
