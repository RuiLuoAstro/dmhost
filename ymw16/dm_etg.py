import sys
import numpy as np
import etgdm as ed

Ndm = 23700

print sys.argv[1]

f = open("./alg_etg/" + sys.argv[1], 'w')
for i in range(Ndm):
    dm_etg = ed.dmhost()
    print >> f, dm_etg
    pct = float(i+1)/Ndm*100
    if pct%1==0:
        print("%0.1f%% finished." %pct)
f.close()
