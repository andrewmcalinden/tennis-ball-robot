#!/bin/bash
dbName=janDb1
hostN=localhost
dbUser=root
dbPass=biala
tableName=system_state2

# manual access:
# MYSQL="mysql -h localhost -u root -pbiala -D janDb1 "
# select * from system_state2 order by timeStamp desc limit 5;

echo  operate on  table=${tableName} in DB=${dbName}
MYSQL="mysql -h $hostN -u $dbUser -p$dbPass -D ${dbName}"

echo "------- list all tables currently existing:"
$MYSQL  -BNe "show tables; "

#to delete table:  
#$MYSQL  -BNe "drop table  ${tableName} ;"; echo "dropped table=${tableName}, EXIT"; exit;


if [ 0 -eq 1 ] ; then 
    echo "--------- authorize new user  from remote machines  ---"
    $MYSQL  -BNe " SELECT user, host FROM mysql.user;"
    $MYSQL  -BNe "create user yy@m3daq.lns.mit.edu identified by 'xx'; "
    $MYSQL  -BNe "grant all privileges on *.* to yy@m3daq.lns.mit.edu  with grant option;  "
    $MYSQL  -BNe " FLUSH PRIVILEGES; "
    
fi



if [ 1 -eq 1 ] ; then    
    echo "--------- initializing  ${tableName}  ---"
    $MYSQL  -BNe "CREATE TABLE ${tableName} (  \
        timeStamp TIMESTAMP, wLoad FLOAT, freeDisc FLOAT,\
        numTask0 INT, pidTask0 INT, secTask0 INT, \
        numTask1 INT, pidTask1 INT, secTask1 INT, \
        remark VARCHAR(140)) ;"
fi

if [ 1 -eq 1 ] ; then    
    echo "--------- seeding  ${tableName}  ---"

    $MYSQL  -BNe "INSERT INTO ${tableName} ( \
       timeStamp, wLoad, freeDisc, \
       numTask0, pidTask0, secTask0, \
       numTask1, pidTask1, secTask1, \
       remark ) VALUES ( \
       NOW(), 0.55, 334.5, \
       5, 3456, 3600,  \
       2, 2456, 7200,  \
       'auto-seed4') ;"

#    unset tableName  
#to flush whole table:   delete from ${tableName} ;
fi
echo "--------- select last records from  ${tableName}  ---"
$MYSQL  -BNe "select * from ${tableName} order by timeStamp desc limit 5;"
