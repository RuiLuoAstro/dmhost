import numpy as np
import ctypes
import os
import ltgtemp as lt
import ltgscale as ls

dirname = os.path.dirname(os.path.abspath(__file__))
#print a
lib_dir = os.path.join(dirname, "libymw16.so")
#print b

ymw16 = ctypes.cdll.LoadLibrary(lib_dir)
#ymw16 = ctypes.cdll.LoadLibrary("/home/luorui/Code/dmhost/ymw16/libymw16.so")
C1024 = ctypes.c_char*1024
dirname = './'
dirname = [ch for ch in dirname]
dirname = C1024(*dirname)

ymw16.negal.restype = ctypes.c_double

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
l = np.arange(0, 2*lt.rnemax, dl)
Nl = len(l)
dln = np.ones(Nl)*dl
dln[0] = dl/2.0
dln[len(dln)-1] = dl/2.0

def dmhost(x0, y0, z0, theta0, phi0):
    ne = []
    sintheta = np.sin(theta0)
    costheta = np.cos(theta0)
    sinphi = np.sin(phi0)
    cosphi = np.cos(phi0)
    for j in range(Nl):
        x = x0 + l[j]*sintheta*cosphi
        y = y0 + l[j]*sintheta*sinphi
        z = z0 + l[j]*costheta
        xx = ctypes.c_double(x*1000)
        yy = ctypes.c_double(y*1000)
        zz = ctypes.c_double(z*1000)
        ne.append(ymw16.negal(xx, yy, zz))
    dm = np.inner(ne,dln) * 1000
    return dm
