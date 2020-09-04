<?php
require_once 'mysql.config.php';

$conn = new mysqli(MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE);


// unpacking PHP input from JSON
$dataIn = file_get_contents("php://input");
//var_dump($dataIn); return;

$objDataIn = json_decode($dataIn);
$dbg = $objDataIn->dbg;

if ( $dbg >0 ) {
  echo "44 PHP dataIn=";
  var_dump($dataIn);
  echo "  dbg=",$dbg;
  echo " -------- end unpacking JASON in PHP, NOTE,output from PHP is not JSON any more ------" ;
}


//-------- table  query ------
$result = $conn->query("SELECT 
       timeStamp, wLoad, freeDisc, 
       numTask0, pidTask0, secTask0,
       numTask1, pidTask1, secTask1, remark
       FROM  system_state2 order by timeStamp desc limit 1") or die($mysqli->error.__LINE__);

$raw = $result->fetch_array(MYSQLI_ASSOC);

// convert to json
$json = json_encode( $raw );

$conn->close();

echo $json;
return;
?>