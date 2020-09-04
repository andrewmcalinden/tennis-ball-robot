#!/bin/sh
core=outE_g3C2
inPath=friday/3C2
ext=.hist.root

echo merge core=*core from $inPath
sumCore=$core\Sum
partCore=$core\Part
echo sum=$sumCore  part=$partCore

y=4
for x in 0 1 2 3 4 5 6 7 8 9 ; do
    #break
    njobs=$[ $njobs + 1 ]
    echo working on part=$x ....
    hadd -f tmp/$partCore$y$x$ext $inPath/$core\_*$y$x$ext &
    sleep 5
done
echo give me 10 seconds to equilibrate ....
sleep 10
ps
echo hadd -f $sumCore$ext tmp/$partCore\*
echo root -l plEleE.C\''("$sumCore",1)'\'
echo "info: $njobs jobs submitted"

exit
 tar cf all_3A2.tar *root