#!/bin/bash
dbName=onlM3
echo keep db but drop all tables from db=${dbName}

MYSQL="mysql -h localhost -ubalewski -pjan -D ${dbName}"
echo list tables before:
$MYSQL -BNe "show tables" 

# use list of tables to drop
for tbName in run_lock  ; do
    echo drop table: $tbName
    $MYSQL -BNe "drop  table ${tbName};"
done
echo after
$MYSQL -BNe "show tables" 
unset MYSQL
echo done
exit

#$MYSQL -BNe "show tables" | awk '{print "set foreign_key_checks=0; drop table `" $1 "`;"}' | $MYSQL