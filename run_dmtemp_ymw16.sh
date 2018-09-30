#!/bin/sh
cd ymw16/

for i in {1...50}
do 
    python dm_temp_ymw16.py dmtemp_ne2001_${i}.txt &
done
