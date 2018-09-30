#!/bin/sh
cd ne2001/

for i in {1..50}
do 
   python dm_ltg_ne2001.py dmltg_ne2001_${i}.txt &
done
