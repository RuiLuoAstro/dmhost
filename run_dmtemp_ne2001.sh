#!/bin/sh
cd ne2001/

for i in {1..50}
do 
   python dm_temp_ne2001.py dmtemp_ne2001_${i}.txt &
done
