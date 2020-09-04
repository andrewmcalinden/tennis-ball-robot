#!/bin/bash
set -u ;  # exit  if you try to use an uninitialized variable
outFile="mac-list.csv"
rootName=balewski
echo "produce list of MAC addresses for selected IPs , rootName=$rootName,  save as $outFile"
njobs=0
echo "DNS-name, DNS-IP, MAC-eth0, MAC-eth1 ">$outFile
#for i in `seq 11 67` ; do
for i in `seq 63 65` ; do
  skip=0
  for j in 12 13 14 56 57 58 ; do  
    if [ $i -eq $j ] ; then  skip=1; break; fi
  done  
  if [[ $i -gt 17  &&    $i -lt 30 ]] ; then skip=1;  fi
  if [ $skip -eq 1 ] ; then  echo skip IP=$i ; continue; fi  

  name=reuse$i.lns.mit.edu
  echo -n DNS_name=$name
  rec=$name
  #host $name

  HOSTIP=`host $name |cut -f 4 -d\ `
  if [ $? -ne 0  ]; then echo "unable to proceed, aborting, fix it" ; exit 1; fi
  #echo DNS_IP=$HOSTIP
  rec=$rec", "$HOSTIP
  for ethX in eth0 eth1; do
      com="ssh -o ConnectTimeout=10  $rootName@$name ifconfig $ethX |grep HWaddr"
      #echo $com
      line=`$com`
      if [ $? -ne 0  ]; then echo "failed ssh to $name, skip it" ; break; fi
      #echo $line
      mac=`echo $line | cut -f5 -d\ `
      #echo mac=$mac
      rec=$rec", "$mac
      echo -n " ok-$ethX, "
  done
  njobs=$[ $njobs + 1 ]
  echo "$njobs rec=$rec "
  echo $rec>>$outFile
done

echo ""
echo "to list all $njobs found hosts exe:  cat $outFile"
exit
