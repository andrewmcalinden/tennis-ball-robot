#!/bin/bash
dbName=onlM3
echo list existing tables in dbName=$dbName

mysql  --user=balewski --password=jan <<EOF
# listing the names of existing databases
show databases;
use ${dbName};
show tables ;
quit
EOF

exit
