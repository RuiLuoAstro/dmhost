#!/bin/sh
cd ymw16/

for i in {1..10}
do 
   python dm_etg.py dmetg_${i}.txt &
done
