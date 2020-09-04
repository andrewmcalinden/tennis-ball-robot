#!/bin/sh
path1=../pp500-spread/good/st_W-daq-all/
id=0
sumEve=0
mxEve=0
while [ true ]; do
    read line
    if [ $? -ne 0 ]; then break; fi
    #echo "LINE IS " $line
    run=`echo $line | cut -f3 -d_`
    listF=$path1/$run.daq.list
    #echo $run, $listF
    #echo grep $line $listF
    out=`grep $line $listF`
    n=`echo $out | cut -f1 -d\ `
    echo $out 
    id=$[ $id + 1 ]
    sumEve=$[ $sumEve + $n]
    if [ $n -gt $mxEve ]; then mxEve=$n ; fi
done

#!/bin/sh
njobs=0
for partid in  6 14 9 1 3 ; do
    for pT in 1.0 2.0 3.0 4.0 5.0 10.0 20.0 30.0 40.0 50.0 ; do
        for eta in 1.20 1.75 ; do
          echo "bsub_staf.sh -i $partid -p $pT -e $eta -n 1000 -I $njobs"
                bsub_staf.sh -i $partid -p $pT -e $eta -n 1000 -I $njobs"
          njobs=$[ $njobs + 1 ]
        done
    done
done
echo "info: $njobs jobs submitted"


echo nrun=$ sumEve=$sumEve mxEve=$mxEve
