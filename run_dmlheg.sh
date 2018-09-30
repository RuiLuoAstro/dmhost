#!/bin/sh
cd etg/

for i in {1..50}
do 
   python dm_lheg.py dmlheg_${i}.txt &
done
