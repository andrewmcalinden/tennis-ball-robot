 #!/bin/bash

# manual DB check
# mysql -h localhost -u root -pbiala -D janDb1
# select * from system_state2 order by timeStamp desc limit 5;

echo  started at`date` sleepTime/sec=$sleepTime
# if more then 1 instance of a task is running, the pid & cpu for only one (random) task is reported 

sleepTime=2 # (sec) between  scanning worker for jobs of interest  
totCycle=100000000 # max num of iterations - set it to 1e8 
blankReportCycle=30  # how often a record is made if no jobs are detected

taskName[0]=fakeJobA
taskName[1]=fakeJobB

dbName=janDb1
hostN=localhost
dbUser=root
dbPass=biala
tableName=system_state2
#---- end of parameters -----

echo scan for those jobs:  ${taskName[*]}
echo inifinite loop recording selected system info in mySQL DB, totCycle=$totCycle



#----------------------------------------------------
function evalOneTask {
    K=$1
    taskNameX=$2
    echo "   evalOneTask${K}=$taskNameX"
    # line=user-pid-name-uptime
    nProc=0
    pid=-1
    cpuSec=-1
    for line in $(ps -ef | grep -v grep | grep $taskNameX | awk '{print $1","$2","$8","$7}'); do
	nProc=$[ $nProc +1]  
	#echo $nProc $line
	if [ $nProc -gt 1 ] ; then continue; fi # store pid+cpu for the 1st one
	pid=`echo $line |   cut -f2 -d,`
	cpuHMS=`echo $line |   cut -f4 -d,`
	cpuSec=`echo $cpuHMS |awk -F: '{print 3600*$1+60*$2+$3}'`	
	# cpuSec=$[ $pid / 10 ]  # tmp
	# echo secCpu=$cpuSec cpuHMS=$cpuHMS
    done
    
    numTask[${K}]=$nProc
    pidTask[${K}]=$pid
    secTask[${K}]=$cpuSec
    numTaskTot=$[ $numTaskTot + $nProc]
    echo "   nProc=$nProc  pid=$pid  secCpu=$cpuSec"
}

#----------------------------------------------------
function scanMachine {
    echo  scanMachine at timeStamp=`date`
    # construct simple DB-record variables
    wLoad=`uptime | awk -F'[a-z]:' '{ print $2 }'  | cut -f1 -d,`
    xx=`df -BG . |tail -n 1 |awk '{print $4}'`
    freeDisc=${xx::-1}  # skip units 'G'

    unset numTask[1]
    unset pidTask[1]
    unset secTask[1]
    numTask=(0)
    pidTask=(0)
    secTask=(0)
    
    #echo acqure info about selected processes
    numTaskTot=0
    evalOneTask 0 ${taskName[0]}
    evalOneTask 1 ${taskName[1]}

    #echo numTask=${numTask[*]}
    #echo pidTask=${pidTask[*]}
    #echo secTask=${secTask[*]}
}

#----------------------------------------------------
function makeDbEntry() {
     
    #echo  enter record  to  table=${tableName} in DB=${dbName}
    MYSQL="mysql -h $hostN -u $dbUser -p$dbPass -D ${dbName}"

    $MYSQL  -BNe "INSERT INTO ${tableName} ( 
       timeStamp, wLoad, freeDisc, 
       numTask0, pidTask0, secTask0, 
       numTask1, pidTask1, secTask1, 
       remark ) VALUES ( 
       NOW(), ${wLoad}, ${freeDisc}, 
       ${numTask[0]}, ${pidTask[0]}, ${secTask[0]},
       ${numTask[1]}, ${pidTask[1]}, ${secTask[1]},
       '${remark}') ;"
}


#==============================================
#============   INFINITE LOOP  START============
#==============================================

nLoop=0  # running loop counter
lastNumTotTask=0
while [  $nLoop -lt $totCycle ]; do
    blankReport=$[ $nLoop % $blankReportCycle ]
    echo "========= The loop counter is $nLoop  "
    scanMachine
    echo "    summary numTaskTot=$numTaskTot for loop counter is $nLoop"
    #echo "Task0: n="${numTask[0]}", pid="${pidTask[0]}", sec="${secTask[0]}

    remark=$numTaskTot" of ${taskName[*]}"

    if ((  numTaskTot >0   || blankReport == 0 || lastNumTotTask>0 )); then
	echo  RECORD DB  blankReport=$blankReport  numTaskTot=$numTaskTot
	makeDbEntry
    else 
	echo  SKIP DB  blankReport=$blankReport  numTaskTot=$numTaskTot
    fi
    lastNumTotTask=$numTaskTot
    let nLoop=nLoop+1
    echo "   sleep $sleepTime sec ...."
    sleep $sleepTime
done



