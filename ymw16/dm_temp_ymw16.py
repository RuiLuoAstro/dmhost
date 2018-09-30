import sys
import numpy as np
import tempdm_ymw16 as ty

Ndm = 20000

print sys.argv[1]

f = open("../data/LTG/" + sys.argv[1], 'w')
for i in range(Ndm):
    frb = ty.frb_sel()
    x0 = frb[0]
    y0 = frb[1]
    z0 = frb[2]
    costheta0 = np.random.uniform(-1, 1)
    phi0 = np.random.uniform(0, 2*np.pi)
    theta0 = np.arccos(costheta0)
    dm_temp = ty.dmhost(x0, y0, z0, theta0, phi0)
    print >> f, x0, y0, z0, theta0, phi0, dm_temp
    pct = float(i+1)/Ndm*100
    print("%0.2f%% finished." %pct)
f.close()
