<?php
header("Access-Control-Allow-Origin: *");
header("Content-Type: application/json; charset=UTF-8");

$conn = new mysqli("localhost", "root", "biala", "janDb1");

$result = $conn->query("SELECT runId,operator FROM run_lock limit 5");

$outp = "";
while($rs = $result->fetch_array(MYSQLI_ASSOC)) {
    if ($outp != "") {$outp .= ",";}
    $outp .= '{"Name":"'  . $rs["runId"] . '",';
    $outp .= '"City":"'   . $rs["operator"]        . '"
    }';
}
$outp ='{"records":['.$outp.']}';
$conn->close();

echo($outp);

?>