<?php
  // The request is a JSON request.
  // We must read the input.
  // $_POST or $_GET will not work!

$data = file_get_contents("php://input");

echo "data=$data= \n";
$objData = json_decode($data);


// perform query or whatever you wish, sample:

// Static array for this demo
$values = array('php', 'web', 'angularjs', 'js');

/*
  $query = 'SELECT * FROM
  tbl_content
  WHERE
  title="'. $objData->data .'"';
*/


// Check if the keywords are in our array
if(in_array($objData->data, $values)) {
  echo 'I have found what you\'re looking for in hardoced array!';
}
else {
  echo 'Sorry, no match!';
}
echo "\n additionaly exec a shell script passing inp= $objData->data :\n";
$command = escapeshellcmd("./testShell.sh $objData->data ");
$output = shell_exec($command );
echo $output;

