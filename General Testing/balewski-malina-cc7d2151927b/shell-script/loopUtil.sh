#!/bin/bash
set -u ;  # exit  if you try to use an uninitialized variable

path0=permanent/DarkLight-events/g4-epEla-2015-06-15
inpPath=${path0}/data
outPath=${path0}/data_d
echo "move files from $inpPath to $outPath"
date0=`date`
nReq=0
nOK=0
for i in `seq 0 100` ; do
    core=epEla_AT_${i}d_dz80.DLg4.root.gz
    echo "i=$i move $core "
    nReq=$[ $nReq + 1 ]
     ~/dropbox_uploader.sh move ${inpPath}/$core ${outPath}/$core
    if [ $? -eq 0 ] ; then  
	nOK=$[ $nOK + 1 ]
    fi	
done
date1=`date`
echo ""
echo "DONE nReqested=$nReq  nOK=$nOK "
echo "  started  at $date0"
echo "  finished at $date1"
exit
