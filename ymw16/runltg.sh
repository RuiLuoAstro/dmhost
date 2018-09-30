#!/bin/sh

for i in {1..50}
do
	mkdir ltg_ymw_${i}
	cd ltg_ymw_${i}
	cp ../ltg*.py ./
	cp ../*.exe ./
	cp ../ltgdm.sh ./
	cp ../ymw16par.txt ./
	cp ../spiral.txt ./
	sh ltgdm.sh &
	cd ..
done
