This set of programs allows to  monitor load & certain tasks runnig on machine A 
using web-browser on machine X  conencted to other web-server on machine B.
The dedicated mySQL (on machine C) tabel is keeping track of history and decouples 
web-browser from monitored machine.


1) =============  SETUP of DB (machine C)
The hardcoded DB 
dbName=janDb1
hostN=localhost
tableName=system_state2

Those are the columns in the table, capacity for 2 processes:
       timeStamp, wLoad, freeDisc, \
       numTask0, pidTask0, secTask0, \
       numTask1, pidTask1, secTask1, \
       remark 


****Execute once this macro:

seedDbTable_stateMon.sh


**** testing:
mysql -h localhost -u root -pbiala -D janDb1
 select * from system_state2 order by timeStamp desc limit 5;
+---------------------+-------+----------+----------+----------+----------+----------+----------+----------+------------+
| timeStamp           | wLoad | freeDisc | numTask0 | pidTask0 | secTask0 | numTask1 | pidTask1 | secTask1 | remark     |
+---------------------+-------+----------+----------+----------+----------+----------+----------+----------+------------+
| 2015-12-06 16:10:41 |  0.55 |    334.5 |        5 |     3456 |     3600 |        2 |     2456 |     7200 | auto-seed4 |
+---------------------+-------+----------+----------+----------+----------+----------+----------+----------+------------+


2)============  on worker machine A  execute this macro inside screen, so it runs indefinitely

****Prepare fake jobs for testing:
 g++ vet_v2.cxx -o fakeJobA

In the script  recordStateInDb_deamon.sh (to be run in an oo-loop )
make sure it contain the correct table name and  the names of monitpred task (fakeJobA), Check those variables:
---
sleepTime=2 # (sec) between  scanning worker for jobs of interest  
totCycle=100 # max num of iterations - set it to 1e8 
blankReportCycle=10  # how often a record is made if no jobs are detected
taskName[0]=fakeJobA
taskName[1]=fakeJobB
dbName=janDb1
hostN=localhost
dbUser=root
dbPass=biala
tableName=system_state2
----

Also, the mySql insert command in function makeDbEntry()
must match the created DB-table


*****Execute in screen the monitoring script:
    recordStateInDb_deamon.sh
Note, if more then 1 instance of a task is running, the pid & cpu for only one (random) task is reported 


3)=============  SETUP of web-server on machine B ====
In the /var/www/html/mon/ directory copy the following scripts

cp index.html  mysql.* php-timer-Cntrl.js pageStyle.css

Make sure, mySql credentials in mysql.config.php are correct
<?php
define('MYSQL_HOST','localhost');
define('MYSQL_USER','root');
define('MYSQL_PASSWORD','biala');
define('MYSQL_DATABASE','janDb1');
?>

Make sure the mySql request in mysql.query.php is valid
$result = $conn->query("SELECT ......

Correct name of task used to decorate in table 2

Note, whne debug>0 the output table in the web-browser will not unpack correctly
  
Point browser to the URL of web-server
