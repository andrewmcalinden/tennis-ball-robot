#!/bin/bash
hostName=m3slow.lns.mit.edu
#hostName=localhost
dbName=onlM3
tbName=run_lock

m3Year=1
oper=janBal
rem="test entry from pullNewRun "

#echo pull new run number based on last record in DB=${tbName} table=${tbName}
MYSQL="mysql -h  $hostName -ubalewski2 -pjan -D ${dbName}"

# select last record:
# SELECT fields FROM table ORDER BY id DESC LIMIT 1;
lastFullRun=`$MYSQL -BNe " select runId from ${tbName} ORDER BY  timestamp DESC LIMIT 1;"`
#echo lastDB=$line
#exit

#lastFullRun=1324007

#echo get the last run number $lastFullRun
lRun=$[ $lastFullRun % 1000]
lDay=$[ ($lastFullRun /1000) % 1000]
#echo lastRun : day=$lDay  run=$lRun  

day=`date +%j`

# change day manually
#day=$[ $day+2 ]

if  [ $day -eq $lDay ] ; then
    run=$[ $lRun +1]
    #echo same day $day
else
    run=0
    #echo new day 
fi

#timestamp=`date "+%Y-%m-%d %H:%M:%S"`
fullRunNo=$[ $m3Year*1000000 + $day*1000 + $run ]
#echo now day=$day run=$run

# enter new record
$MYSQL -BNe "INSERT INTO  ${tbName} (runId,operator,timestamp,remark) VALUES  ('${fullRunNo}','${oper}',NOW(),'${rem}')"

echo $fullRunNo
exit

echo -n 'new run_lock row: '
$MYSQL -BNe " select * from ${tbName} ORDER BY  runId DESC LIMIT 1;"

exit


delete from onlM3.run_lock where runId=1327001;

  
