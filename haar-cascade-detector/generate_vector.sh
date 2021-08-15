#!/bin/bash

DIM=$1

POS=36
NEG=3600
NEG_PER_POS=100
NEG_PER_POS_2_3=67
SAMPLES=2412

mkdir all
touch all/info.lst

for (( i=1; i<=$POS; i++)) do
	START=(i-1)*$NEG_PER_POS
	mkdir net$i
	for (( j=$START + 1; j<=$START+$NEG_PER_POS; j++)) do
		cp neg/$j.jpg net$i
	done
	find net$i -iname "*.jpg" > net$i.txt
	opencv_createsamples -img pos_sample/$i.png -bg net$i.txt -info info$i/info.lst -pngoutput info$i -maxxangle 0.5 -maxyangle 0.5 -maxzangle 0.5 -num $NEG_PER_POS_2_3
	sed "s/^/$i|/" info$i/info.lst >> all/info.lst
	cd info$i
	for file in *.jpg; do
		mv "$file" "../all/$i|$file"
	done
	cd ..
done

rm -rf net*
opencv_createsamples -info all/info.lst -num $SAMPLES -w $DIM -h $DIM -vec positives.vec 
rm -rf info*
rm -rf all




