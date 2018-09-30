import sys
import numpy as np
import ltgdm_ymw16 as ldy

Ndm = 20000

print sys.argv[1]

f = open("../data/LTG/YMW16/" + sys.argv[1], 'w')
for i in range(Ndm):
    dm_ltg = ldy.dmhost()
    print >> f, dm_ltg
    pct = float(i+1)/Ndm*100
    print("%0.2f%% finished." %pct)
f.close()
