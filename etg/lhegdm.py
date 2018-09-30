import numpy as np
import etgtemp as et
import lhegscale as ls

def frb_sel():
    frb = et.ns_sel()
    return frb

def eta_sel():
    etggal = ls.etg_sel()
    #T = etggal[0]
    R = etggal[0]
    lha = etggal[1]
    eta = ls.scalefactor(R, lha)
    return eta

# Trapezoidal integration, uniform integration step in distance
'''
dl = 0.001
l = np.arange(0, 2*et.lmax, dl)
Nl = len(l)
dln = np.ones(Nl)*dl
dln[0] = dl/2.0
dln[len(dln)-1] = dl/2.0
'''

# Trapezoidal integration, uniform integration step in logarithmic distance
dlogl = 0.001
logl = np.arange(-10, np.log10(2*et.rnemax), dlogl)
l = np.power(10., logl)
l = np.insert(l, 0, 0)
dl = l[1:] - l[:-1]
Nl = len(l)
dln = np.ones(Nl)
dln = (dl[1:] + dl[:-1]) * 0.5
dln = np.insert(dln, 0, dl[0]/2.0)
dln = np.insert(dln, len(dln), dl[-1]/2.0)

def dmhost():
    ne = []
    eta = eta_sel()
    frb = frb_sel()
    x0 = frb[0]
    y0 = frb[1]
    z0 = frb[2]
    costheta0 = np.random.uniform(-1, 1)
    phi0 = np.random.uniform(0, 2*np.pi)
    theta0 = np.arccos(costheta0)
    sintheta = np.sin(theta0)
    costheta = np.cos(theta0)
    sinphi = np.sin(phi0)
    cosphi = np.cos(phi0)
    for j in range(Nl):
        x = x0 + l[j]*sintheta*cosphi
        y = y0 + l[j]*sintheta*sinphi
        z = z0 + l[j]*costheta
        ne.append(et.ne_etg(x,y,z))
    dm = eta * np.inner(ne, dln) * 1000
    return dm
