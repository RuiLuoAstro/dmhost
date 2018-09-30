import sys
import numpy as np
import etgdm_temp as et

Ndm = 20000

print sys.argv[1]

f = open("../data/ETG/" + sys.argv[1], 'w')
for i in range(Ndm):
    dm_temp = et.dmhost()
    print >> f, dm_temp
    pct = float(i+1)/Ndm*100
    print("%0.2f%% finished." %pct)
f.close()
