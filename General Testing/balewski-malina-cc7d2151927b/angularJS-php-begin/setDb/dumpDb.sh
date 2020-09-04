#!/bin/bash
set -u ;  # exit  if you try to use an uninitialized variable
set -e ;    #  bash exits if any statement returns a non-true return value
set -o errexit ;  # exit if any statement returns a non-true return value
dbName=janDb1
tbName=run_lock
userName=root
#hostName='127.0.0.1';
hostName=localhost
MYSQL="mysql -h $hostName -u  $userName -pbiala -D ${dbName}"


echo  "4) =====Dump all rows from table ${tbName} in DB=${dbName}"
$MYSQL -BNe "show tables; select * from ${tbName};"
unset MYSQL


exit
