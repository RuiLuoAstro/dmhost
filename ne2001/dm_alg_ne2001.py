import sys
import numpy as np
import etgdm as ed
import ltgdm_ne2001 as ldn

def DM_ALG():
    while(True):
        prob = np.random.uniform()
        if prob < 0.763:
            dm = ldn.dmhost()
        else:
            dm = ed.dmhost()
        return dm

Ndm = 20000

print sys.argv[1]

f = open("../data/ALG/" + sys.argv[1], 'w')
for i in range(Ndm):
    dm_alg = DM_ALG()
    print >> f, dm_alg
    pct = float(i+1)/Ndm*100
    print("%0.2f%% finished." %pct)
f.close()

