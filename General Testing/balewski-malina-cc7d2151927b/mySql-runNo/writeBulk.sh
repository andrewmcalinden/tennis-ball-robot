#!/bin/bash
dbName=onlM3
tbName=janTable
hostN=m3slow.lns.mit.edu
echo  write bulk data to table  ${tbName}

MYSQL="mysql -h $hostN -ubalewski -pjan -D ${dbName}"

for i in `seq 3  3` ; do
    echo inserting $i
    runId=140100$i
    oper=jan$i
    $MYSQL -BNe "INSERT INTO  ${tbName} (runId,operator) VALUES  ('${runId}','${oper}')"
done
echo  Dump all rows from table ${tbName}
$MYSQL -BNe "show tables; select * from ${tbName};" 
unset MYSQL
exit

#$MYSQL -BNe "show tables" | awk '{print "set foreign_key_checks=0; drop table `" $1 "`;"}' | $MYSQL