import ne2001
import numpy as np
import ltgtemp as lt
import ltgscale as ls

def frb_sel():
    prob = np.random.uniform()
    if prob < 3.0e-5:
        frb = lt.ns_sel()
    else:
        frb = lt.nd_sel()
    return frb
'''
def eta_sel():
    ltggal = ls.ltg_sel()
    T = ltggal[0]
    R = ltggal[1]
    lha = ltggal[2]
    eta = ls.scalefactor(T,R,lha)
    return eta
'''
# Trapezoidal integration, uniform integration step in distance
dl = 0.001
l = np.arange(0,2*lt.rnemax,dl)
Nl = len(l)
dln = np.ones(Nl)*dl
dln[0] = dl/2.0
dln[len(dln)-1] = dl/2.0

def dmhost():
    ne = []
    #eta = eta_sel()
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
        x = x0+l[j]*sintheta*cosphi
        y = y0+l[j]*sintheta*sinphi
        z = z0+l[j]*costheta
        ne.append(ne2001.negal(x,y,z))
    dm = np.inner(ne,dln) * 1000
    return dm
