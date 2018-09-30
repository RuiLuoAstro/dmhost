import numpy as np
import os
import ltgtemp as lt
import ltgscale as ls

def frb_sel():
    prob = np.random.uniform()
    if prob < 3.0e-5:
        frb = lt.ns_sel()
    else:
        frb = lt.nd_sel()
    return frb

def eta_sel():
    ltggal = ls.ltg_sel()
    #T = ltggal[0]
    R = ltggal[0]
    lha = ltggal[1]
    eta = ls.scalefactor(R,lha)
    return eta

# Trapezoidal integration, uniform integration step in distance
veta=[]
vx=[]
vy=[]
vz=[]
vt=[]
vphi=[]

for i in range(0, 15260):
    veta.append(eta_sel())
    frb = frb_sel()
    vx.append(frb[0])
    vy.append(frb[1])
    vz.append(frb[2])
    costheta0 = np.random.uniform(-1, 1)
    vphi.append(np.random.uniform(0, 2*np.pi))
    vt.append( np.arccos(costheta0))
    if i%1000==0:
        print i
        np.savetxt('eta', veta)
        np.savetxt('x', vx)
        np.savetxt('y', vy)
        np.savetxt('z', vz)
        np.savetxt('t', vt)
        np.savetxt('phi', vphi)

np.savetxt('eta', veta)
np.savetxt('x', vx)
np.savetxt('y', vy)
np.savetxt('z', vz)
np.savetxt('t', vt)
np.savetxt('phi', vphi)

