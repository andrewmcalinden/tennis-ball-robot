#!/bin/bash
# purpose is to examin hardware configuration of a mashine 
 echo 'jas tu byl'
inp=$1
date
uname -a

is64bit=0
nCore=0
ramMBtot=0
ramMBfree=0
isMacOsX=0
myIP='none'

echo "examineCPU  (ver 1.1) ..."
# the file below exist on Mac
cpuInfoFile=/proc/cpuinfo
#ls $cpuInfoFile

if [  -f $cpuInfoFile  ] ; then
   grep vendor_id /proc/cpuinfo | head -1 | awk '{print $3}'
   grep --color=always -iw lm $cpuInfoFile  >/dev/null
   if [ $? == 0 ] ; then   is64bit=1 ; fi

   line=` cat /proc/cpuinfo  |grep processor|nl|tail -n 1`
   #echo A:$line
   nCore=`echo $line | cut -f1 -d\ `

   line=`free -mt|head -n2|tail -n 1 `
   #echo B:$line
   ramMBtot=`echo $line | cut -f2 -d\ `
   ramMBfree=`echo $line | cut -f4 -d\ `
   myIP=`/sbin/ifconfig|grep "inet "|grep Bcast|cut -f2 -d:| cut -f1 -d\ `

else
    echo "Try Mac OS test"
    isMacOsX=1
    sysctl -n machdep.cpu.brand_string |grep i7
   if [ $? == 0 ] ; then echo "is 64 bit ";  is64bit=1 ; fi
   myIP=`ifconfig|grep "inet "|head -n2 |tail -n 1|cut -f2 -d\ `
fi

# common for any OS
myName=`hostname`

line=`w |head -n 1`
#echo $line
x1=`echo $line| cut -f1 -d,`
myUptime=`echo $x1| cut -f3,4 -d\ `
x1=`echo $line| cut -f4 -d,`
myLoad=`echo $x1| cut -f3 -d\ `


echo
echo examineCPU summary:
echo is64bit=$is64bit, isMac OSX=$isMacOsX , myIP=$myIP , myName=$myName
echo nCore=$nCore  RAM/MB total=$ramMBtot,  free=$ramMBfree

echo myUptime=$myUptime myLoad=$myLoad

echo input=$inp=
if [ x$inp == x ]; then exit; fi
pwd
nTop=$[ $nCore + 10 ]
df -h .
du -hs .
top -b | head -n $nTop
echo '------------ end of examine CPU ----------'
#exit
echo  'If siblings = cpu cores for all sections, than *most likely* HT is disabled - depends on processor type. "processor" tells you how many logical cores exposed, and "physical id" will tell you how many CPUs are installed. - encode it later'
cat /proc/cpuinfo | egrep "processor|physical id|siblings|cpu cores"

echo
