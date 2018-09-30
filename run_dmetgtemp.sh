#!/bin/sh
cd etg/

for i in {1..50}
do 
   python dm_etgtemp.py dmetgtemp_${i}.txt &
done
