#!/bin/sh
njobs=0
for partid in  6 14 9 1 3 ; do
    For pT in 1.0 2.0 3.0 4.0 5.0 10.0 20.0 30.0 40.0 50.0 ; do
        for eta in 1.20 1.75 ; do
          echo "bsub_staf.sh -i $partid -p $pT -e $eta -n 1000 -I $njobs"
                bsub_staf.sh -i $partid -p $pT -e $eta -n 1000 -I $njobs"
          njobs=$[ $njobs + 1 ]
        done
    done
done
echo "info: $njobs jobs submitted"
