#!/bin/sh

for i in {1..50}
do
    mkdir alg_ymw_${i}
    cd alg_ymw_${i}
    cp ../ltgdm*.py ./
    cp ../*.exe ./
    cp ../algdm.sh ./
    cp ../ymw16par.txt ./
    cp ../spiral.txt ./
    sh algdm.sh &
    cd ..
done
