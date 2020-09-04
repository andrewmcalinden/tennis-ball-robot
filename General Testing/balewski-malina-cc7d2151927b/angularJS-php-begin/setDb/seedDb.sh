#!/bin/bash
set -u ;  # exit  if you try to use an uninitialized variable
set -e ;    #  bash exits if any statement returns a non-true return value
set -o errexit ;  # exit if any statement returns a non-true return value
dbName=janDb1
tbName=run_lock
#hostName='127.0.0.1';
hostName=localhost
userName=root

MYSQL="mysql -h $hostName -u $userName -pbiala -D ${dbName}"

echo "4) =====seed table ${tbName} with few records"
for i in `seq 2  4` ; do
    echo inserting $i
    runId=132100$i
    oper=jan$i
    rem="autoAA BB-$i"
    $MYSQL -BNe "INSERT INTO  ${tbName} (runId,operator,timeStamp,remark) VALUES  ('${runId}','${oper}',NOW(),'${rem}')"
done
echo  "4) =====Dump all rows from table ${tbName}"
$MYSQL -BNe "show tables; select * from ${tbName};"
unset MYSQL


exit
