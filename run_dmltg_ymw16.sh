#!/bin/sh
cd ymw16/

for i in {1..50}
do
python dm_ltg_ymw16.py dmltg_ymw16_${i}.txt &
done
