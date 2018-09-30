#!/bin/sh
cd etg/

for i in {1..50}
do 
   python dm_etg.py dmetg_${i}.txt &
done
