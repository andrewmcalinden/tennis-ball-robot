<?php

require_once 'mysql.config.php';

$conn = new mysqli(MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE);


// echo example of unpacking PHP input from JSON

$dataIn = file_get_contents("php://input");
//var_dump($dataIn);
$objDataIn = json_decode($dataIn);
$dbg = $objDataIn->dbg;
$sDir = $objDataIn->val1;

if ( $dbg >0 ) {
  echo "44 PHP dataIn=";
  var_dump($dataIn);
  echo "  dbg=",$dbg," sDir=",$sDir;
  echo " -------- end unpacking JASON in PHP, NOTE,output from PHP is not JSON any more ------" ;
}


$outp = "";


// return;
//-------- 1st table  query ------
$result = $conn->query("SELECT runId,operator FROM run_lock order by runId asc limit 1") or die($mysqli->error.__LINE__);


while($raw = $result->fetch_array(MYSQLI_ASSOC)) {
  if ($outp != "") {$outp .= ",";}		 
    $outp .= '{"Name1":"'  . $raw["runId"] . '",'; 
    $outp .= '"Name2":"'   . $raw["operator"] . '"}';
}

//-------- 2st table  query ------
$result = $conn->query("SELECT runId,operator FROM run_lock order by runId $sDir limit 1") or die($mysqli->error.__LINE__);


//
while($raw = $result->fetch_array(MYSQLI_ASSOC)) {
    if ($outp != "") {$outp .= ",";}		 
    $outp .= '{"Name1":"'  . $raw["runId"] . '",';
    $outp .= '"Name2":"'   . $raw["operator"] . '"}';
}

$outp ='{"records":['.$outp.']}';
$conn->close();

echo($outp);

?>