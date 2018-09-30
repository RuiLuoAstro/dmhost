import sys
import numpy as np
import lhegdm as ld

Ndm = 20000

print sys.argv[1]

f = open("../data/ETG/" + sys.argv[1], 'w')
for i in range(Ndm):
    dm_lheg = ld.dmhost()
    print >> f, dm_lheg
    pct = float(i+1)/Ndm*100
    if pct%1==0:
        print("%0.2f%% finished." %pct)
f.close()
