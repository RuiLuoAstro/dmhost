import sys
import numpy as np
import etgdm as ed

Ndm = 20000

print sys.argv[1]

f = open("../data/ETG/" + sys.argv[1], 'w')
for i in range(Ndm):
    dm_etg = ed.dmhost()
    print >> f, dm_etg
    pct = float(i+1)/Ndm*100
    print("%0.2f%% finished." %pct)
f.close()
