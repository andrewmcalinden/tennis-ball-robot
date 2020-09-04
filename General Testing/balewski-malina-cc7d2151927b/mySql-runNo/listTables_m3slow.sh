#!/bin/bash
dbName=onlM3
dbTable=janTest
#dbName=DMTPC_TEST
echo list existing tables in dbName=$dbName
hostName=m3slow.lns.mit.edu
echo ****  list databases and tables in dbName=$dbName
#mysql  --user=balewski --password=jan -h $hostName <<EOF
mysql  --user=dmatter2 --password=seedark -h $hostName <<EOF
# listing the names of existing databases
show databases;
use ${dbName};
show tables ;
quit
EOF

echo **** insert new record to table=$dbTable
oper='oper=Pinkio on '`date`
mysql  --user=dmatter2 --password=seedark -h $hostName <<EOF2
    use ${dbName};
    INSERT INTO  janTable (runId,operator) VALUES (102,'$oper');
select * from janTable;
     quit
EOF2
echo inserted $oper
exit
