# Here is the template building for Late-type Galaxies

import numpy as np

# Basic Parameters of LTG template
# Using the Milky Way as template
ns0 = 4.1632e-2/2
kappa = 0.8
b = 7.66925
RE = 2.67

rsmax = 15
rnemax = 20

nd0 = 0.13
rsun = 8.0
h = 3.5
H = 0.3
#ndmax=nd0*1*np.exp(8/3.5)
ndmax = 8.5
nsmax = 0.00035

# FRBs distribution of template assuming they trace star formation and evolution
# Disk component
def ndisk(r,z):
    nd = nd0*np.exp(-abs(z)/H)*np.exp(-(abs(r)-rsun)/h)
    return nd

# Spheroid component
def nsph(R):
    RJ = np.power(R/RE, 0.25)
    dens = ns0*np.exp(-b*RJ)/(RJ*RJ*RJ)*np.sqrt(np.pi/8/b/RJ)
    return dens

# Monte Carlo sampling for FRBs in template
# MC for disk
def nd_sel():
    s = [1,2,3]
    while(True):
        r = np.random.uniform(0, rsmax)
        z = np.random.uniform(-3, 3)
        nd = np.random.uniform(0, ndmax)
        if ndisk(r,z)*r > nd:
            break
    theta = np.random.uniform(0, 2*np.pi)
    s[0] = r*np.cos(theta)
    s[1] = r*np.sin(theta)
    s[2] = z
    return np.array(s)

# MC for spheriod
def ns_sel():
    s = [1,2,3]
    while(True):
        r = np.random.uniform(0, rsmax)
        ns = np.random.uniform(0, nsmax)
        if nsph(r)*r*r > ns:
            break
    costheta = np.random.uniform(-1, 1)
    phi = np.random.uniform(0, 2*np.pi)
    theta = np.arccos(costheta)
    s[0] = r*np.sin(theta)*np.cos(phi)
    s[1] = r*np.sin(theta)*np.sin(phi)
    s[2] = r*np.cos(theta)*kappa
    return np.array(s)
