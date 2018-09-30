# Here is the template building for Early-type Galaxies

import numpy as np

# Basic Parameters of ETG template
# Using M87 as template
ns0 = 4.1632e-2/2
kappa = 0.8
b = 7.66925
RE = 7.7
n0 = 0.165
R0 = 1.544
index = 1.164/2

rnemax = 35
#nsmax = 0.00025
nsmax = 0.003
rsmax = 30

# FRBs distribution of template assuming they trace star formation and evolution
def ns_etg(R):
    RJ = np.power(R/RE, 0.25)
    dens = ns0*np.exp(-b*RJ)/(RJ*RJ*RJ)*np.sqrt(np.pi/8/b/RJ)
    return dens

# Electron density profile of template
def ne_etg(x,y,z):
    R = np.sqrt(x*x+y*y+z*z)
    if R < rnemax:
        ne = n0 * np.power(1+(R/R0)*(R/R0), -index)
    else:
        ne = 0
    return ne

# Monte Carlo sampling for FRBs in template
def ns_sel():
    s = [1,2,3]
    while(True):
        r = np.random.uniform(0,rsmax)
        ns = np.random.uniform(0,nsmax)
        if ns_etg(r)*r*r > ns:
            break
    costheta = np.random.uniform(-1,1)
    phi = np.random.uniform(0, 2*np.pi)
    theta = np.arccos(costheta)
    s[0] = r*np.sin(theta)*np.cos(phi)
    s[1] = r*np.sin(theta)*np.sin(phi)
    s[2] = r*np.cos(theta)*kappa
    return np.array(s)
