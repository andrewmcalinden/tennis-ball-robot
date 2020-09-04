<?php

        // set up the connection variables
        $db_name  = 'janDb1';
	$db_table = 'run_lock';
        //$hostname = '127.0.0.1';
	$hostname = 'localhost';
        $username = 'root';
        $password = 'biala';

        // connect to the database
        $dbh = new PDO("mysql:host=$hostname;dbname=$db_name", $username, $password);

        // a query get all the records from the users table
	 $sql = "SELECT runId ,operator,timeStamp,remark FROM $db_table";
        //$sql = 'SELECT * FROM run_lock'; // WRONG quotation

        // use prepared statements, even if not strictly required is good practice
        $stmt = $dbh->prepare( $sql );
	// echo "aa2 $db_table ";

        // execute the query
        $stmt->execute();

        // fetch the results into an array
        $result = $stmt->fetchAll( PDO::FETCH_ASSOC );

	//echo "res=$result=";
        // convert to json
        $json = json_encode( $result );

        // echo the json string
        echo $json;
?>