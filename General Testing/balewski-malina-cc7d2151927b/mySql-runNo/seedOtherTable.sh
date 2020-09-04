#!/bin/bash
dbName=onlM3
hostN=localhost ; dbUser=balewski ; dbPass=jan

echo  start
MYSQL="mysql -h $hostN -u $dbUser -p$dbPass -D ${dbName}"

# mysql -u balewski -pjan -h m3slow.lns.mit.edu 
# mysql -u balewski -pjan -h m3slow.lns.mit.edu -D onlM3
# mysql -u dmatter -pseedark

# switch to GMT time samp as default
# mysql> SET @@session.time_zone='+00:00';
# display what is the dafault time zone
#mysql> SELECT @@global.time_zone, @@session.time_zone;
#+--------------------+---------------------+
#| @@global.time_zone | @@session.time_zone |
#+--------------------+---------------------+
#| SYSTEM             | +00:00              |
#+--------------------+---------------------+




echo list all tables currently existing
$MYSQL  -BNe "show databases; "
$MYSQL  -BNe "show tables; "


if [ 0 -eq 1 ] ; then  # run_lock
    $MYSQL  -BNe "CREATE TABLE run_lock (runId INT, operator VARCHAR(20), timeStamp TIMESTAMP, remark VARCHAR(140));"
fi



if [ 0 -eq 1 ] ; then
    echo "--------- authorize dmatter from remote machines  ---"
    $MYSQL  -BNe " SELECT user, host FROM mysql.user;"
    #$MYSQL  -BNe "  "
    $MYSQL  -BNe "create user dmatter2@m3daq.lns.mit.edu identified by 'seedark'; "
    $MYSQL  -BNe "grant all privileges on *.* to dmatter2@m3daq.lns.mit.edu  with grant option;  "
    $MYSQL  -BNe " FLUSH PRIVILEGES; "
fi


if [ 0 -eq 1 ] ; then
    tableName=run_start
    echo "--------- initializing  ${tableName}  ---"
    $MYSQL  -BNe "CREATE TABLE ${tableName} (runId INT, setNumBias INT, setNumExpo INT, timeStamp TIMESTAMP , outName VARCHAR(140)) ;"
    $MYSQL  -BNe "INSERT INTO ${tableName} (runId,setNumBias,setNumExpo,timeStamp,outName) VALUES ( 111000,8,18,NOW(),'fake-m3-out.root') ;"
    $MYSQL  -BNe "select * from ${tableName} order by timeStamp desc limit 3;"

    unset tableName  
#to flush whole table:   delete from ${tableName} ;
#to delete table:  drop table  ${tableName} ;
fi


if [ 1 -eq 1 ] ; then
    tableName=run_start
    echo "--------- add new column  to  ${tableName}  ---"
    $MYSQL  -BNe "ALTER TABLE ${tableName}  ADD expoTimeMsec INT AFTER setNumExpo; "
    $MYSQL  -BNe "INSERT INTO ${tableName} (runId,setNumBias,setNumExpo,expoTimeMsec,timeStamp,outName) VALUES ( 111000,9,19,2000,NOW(),'fake-m4-out.root') ;"

    $MYSQL  -BNe "select * from ${tableName} order by timeStamp desc limit 3;"
    unset tableName  
fi







exit

tbName=run_lock
echo  create and seed table  ${tbName}

mysql  -ubalewski -pjan <<EOF
USE ${dbName};  # defines default DB
show tables;

CREATE TABLE  ${tbName} (runId INT, operator VARCHAR(20), remark VARCHAR(140));
SHOW TABLES;
INSERT INTO  ${tbName} (runId,operator,remark) VALUES (101,"Marin1","by 1 the seeder");
show tables;
select * from  ${tbName} ;
quit
EOF

exit

# to drop thi stable execute:
DROP TABLE  ${tbName} ;
