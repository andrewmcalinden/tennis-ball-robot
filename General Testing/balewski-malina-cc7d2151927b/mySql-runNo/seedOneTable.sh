#!/bin/bash
dbName=onlM3
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
