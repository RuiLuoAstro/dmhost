# Here is the scaling for a large sample of Late-type Galaxies
import numpy as np

# Basic scaling parameters of the LTG template
#Tmw = 1e4
lhamw = 5e40
Reffmw = 3.5
#lhamw = 1e41
#Reffmw = 11.5

# The average radii of LTGs resulting from r-band LF and R-M relation
#Ravg = 0.83

#size-magnitude relation parameters (Shen et al. 2003)
mag_r0=-20.52
alpha=0.21
beta=0.53
gamma=-1.31

# r-band LF (Nakamura et al. 2003)
mags_spr=-20.3
alf_spr1=-1.15
alf_spr2=-0.71
phis_spr1=0.95*0.01
phis_spr2=0.43*0.01

mags_irr=-20.0
alf_irr=-1.9
phis_irr=0.04*0.01

# Halpha LF of LTGs
logls_spr1 = 41.7
aha_spr1 = -1.4
phihas_spr1 = 1.03*0.001

logls_spr2 = 41.71
aha_spr2 = -1.53
phihas_spr2 = 0.96*0.001

logls_irr = 42.76
aha_irr = -1.77
phihas_irr = 0.006*0.001

# Halpha LF of LTGs
def LFlogHa(loglha,logls,phis,alpha):
    ls = np.power(10., logls)
    lha = np.power(10., loglha)
    phi = phis * np.log(10) * np.power(lha/ls, alpha+1) * np.exp(-lha/ls)
    return phi

def LF(mag,mag_s,phi_s,alpha):
    m2l = 10**(0.4*(mag_s-mag))
    phi = 0.4*np.log(10)*phi_s*m2l**(alpha+1)*np.exp(-m2l)
    return phi

def Reff(mag, mag0):
    m2l = 10**(-0.4*(mag-mag0))
    r50 = 10**(-0.4*alpha*mag+(beta-alpha)*np.log10(1+m2l)+gamma)
    reff = r50   # SDSS Petrosian ratio is 1.0
    return reff

# Scaling formula
def scalefactor(R,l_ha):
    #Tratio = T/Tmw
    Rratio = R/Reffmw
    lratio = l_ha/lhamw
    eta = np.power(lratio/Rratio, 0.5)
    return eta

# Monte Carlo sampling for LTGs
def ltg_sel():
    s = [1,2]
    while(True):
        mag = np.random.uniform(-24, -18)
        phi_lf = np.random.uniform(0, 0.2)
        lf1 = LF(mag, mags_spr, phis_spr1, alf_spr1)
        lf2 = LF(mag, mags_spr, phis_spr2, alf_spr2)
        lf3 = LF(mag, mags_irr, phis_irr, alf_irr)
        if lf1+lf2+lf3 > phi_lf:
            loglha = np.random.uniform(39, 43)
            phi_lfha = np.random.uniform(0, 1)
            lfha1 = LFlogHa(loglha,logls_spr1,phihas_spr1,aha_spr1)
            lfha2 = LFlogHa(loglha,logls_spr2,phihas_spr2,aha_spr2) 
            lfha3 = LFlogHa(loglha,logls_irr,phihas_irr,aha_irr) 
            if lfha1+lfha2+lfha3 > phi_lfha:
                break
    lha = np.power(10., loglha)
    #T = np.random.uniform(5000, 10000)
    R = Reff(mag, mag_r0)
    s[0] = R
    s[1] = lha
    return np.array(s)
