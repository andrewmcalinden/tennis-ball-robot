<?php 
echo "exec script START <hr>";
$command = escapeshellcmd('pwd');
$output = shell_exec($command);
echo $output;

echo "<br>";
$command = escapeshellcmd('df -h');
$output = shell_exec($command);
echo $output;

echo "<br>";
$command = escapeshellcmd('./testShell.sh');
$output = shell_exec($command);
echo $output;

echo "<br>";
$command = escapeshellcmd('./testShell.sh 12');
$output = shell_exec($command);
echo $output;

echo "<br>";
$command = escapeshellcmd('./testPython.py 33xx44');
$output = shell_exec($command);
echo $output;

echo "<hr> exec script STOP";
?>