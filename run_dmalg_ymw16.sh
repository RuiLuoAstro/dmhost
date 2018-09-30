#!/bin/sh
cd ymw16

for i in {1..50}
do
python dm_alg_ymw16.py dmalg_ymw16_${i}.txt
done
