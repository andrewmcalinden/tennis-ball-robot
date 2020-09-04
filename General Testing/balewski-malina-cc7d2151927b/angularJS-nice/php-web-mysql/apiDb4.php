<?php

// echo example of unpacking PHP input from JSON

$dataIn = file_get_contents("php://input");
$objDataIn = json_decode($dataIn);
$dbg2 = $objDataIn->dbg2;


if ( $dbg2 >0 ) {
  echo "\n44 PHP dataIn=";
  var_dump($dataIn);
  echo " 66\n dbg2="; echo "$dbg2";
  echo " 77\n-------- end unpacking JASON in PHP\n NOTE - output from PHP is not JSON any more \n------" ;
}

// set up the connection variables  
$db_name  = 'onlM3';
$hostname = '127.0.0.1';
$username = 'dmatter';
$password = 'seedark';

// connect to the database
$dbh = new PDO("mysql:host=$hostname;dbname=$db_name", $username, $password);

// a query get all the records from the users table
$sql = 'SELECT runId,operator,timestamp,remark FROM run_lock order by timestamp desc  limit 2';

// use prepared statements, even if not strictly required is good practice
$stmt = $dbh->prepare( $sql );

// execute the query
$stmt->execute();

// fetch the results into an array
$result = $stmt->fetchAll( PDO::FETCH_ASSOC );

// convert to json
$json = json_encode( $result );

// echo the json string
echo $json;
?>
