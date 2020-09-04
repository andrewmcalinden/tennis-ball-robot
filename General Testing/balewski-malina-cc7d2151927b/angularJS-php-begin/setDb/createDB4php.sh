#!/bin/bash
set -u ;  # exit  if you try to use an uninitialized variable
set -e ;    #  bash exits if any statement returns a non-true return value
set -o errexit ;  # exit if any statement returns a non-true return value
dbName=janDb1
tbName=run_lock
userName=root
#hostName='127.0.0.1';
hostName=localhost
MYSQL_0="mysql -h $hostName -u $userName -pbiala"
MYSQL="mysql -h $hostName -u $userName -pbiala -D ${dbName}"

echo  "1)====== create DB ${dbName}"
$MYSQL_0 -BNe "create database ${dbName};"
$MYSQL_0 -BNe "show databases;"
#to drop this DB:
#$MYSQL_0 -BNe "drop database ${dbName};"


echo "2) =====create table ${tbName} in DB=${dbName}"
$MYSQL -BNe "CREATE TABLE  ${tbName} (runId INT, operator VARCHAR(20), timeStamp DATETIME, remark VARCHAR(140));"
$MYSQL -BNe "select * from  ${tbName} ;"

#echo  "0)====== create user=DB ${dbName}"  not tested
#create user balewski@m3daq.lns.mit.edu identified by 'jan';
# grant all privileges on *.* to balewski@localhost  with grant option;


exit
