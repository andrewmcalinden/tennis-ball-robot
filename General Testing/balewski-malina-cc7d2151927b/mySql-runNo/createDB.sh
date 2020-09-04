#!/bin/bash
dbName=onlM3
echo create new  dbName=$dbName and allow user=balewski to write there
mysql  --user=root --password=kot <<EOF
#mysql  --user=balewski --password=jan <<EOF
# cerate new DB
create database ${dbName};
# listing the names of existing databases
show databases;
GRANT ALL PRIVILEGES ON ${dbName}.* TO 'balewski'@'localhost';
quit
EOF
echo done
exit

# to delet whole database activate the line below:
drop database ${dbName};
