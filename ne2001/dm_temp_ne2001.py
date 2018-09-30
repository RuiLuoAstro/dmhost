import sys
import numpy as np
import tempdm_ne2001 as tn

Ndm = 20000

print sys.argv[1]

f = open("../data/LTG/" + sys.argv[1], 'w')
for i in range(Ndm):
    dm_temp = tn.dmhost()
    print >> f, dm_temp
    pct = float(i+1)/Ndm*100
    print("%0.2f%% finished." %pct)
f.close()
