function JSprogJanA($scope, $http) {
    // set defaults
    $scope.php_codeA = 'readRunIdMysql.php'; // star/stop m3 pre-run     
    // $scope.php_codeA = "apiDb3.php"; // star/stop m3 pre-run     
    $scope.operator="LordVader";
    $scope.debug=1;
    //$scope.tableJSON="NO data1";

    //.... function .....
    $scope.actJanA1 = function() {
	console.log("actJanA1:  operator="+$scope.operator+" debug="+ $scope.debug);;	
	$scope.tableJSON="NO data2";
	if ( $scope.operator == "jan" ) {
	    console.log("actJanA1: hellow Jan");
	}	
	if ( $scope.operator == undefined ) {
	    console.log(" actJanA1: Must pick operator");
	    $scope.result = "{Invalid request: select operator}";
	    return;
	}	

       $http.post($scope.php_codeA, { "action":"start", "debug":$scope.debug})
        .success(function(data, status) {
                $scope.status = status;
                $scope.data =  "preRun-start";
                //$scope.tableJSON = data;
		
		$scope.tableJSON = "bb cc dd";
            })
        .error(function(data, status) {
                $scope.data = data || "Request failed";
                $scope.status = status;
		$scope.tableJSON = "ff gg hh";
            });


	$scope.result = " dbg="+ $scope.debug+" from exec PHP="+ $scope.php_codeA;

    }

    //.... function .....
    $scope.actJanA2 = function() {
	console.log("actJanA2:  debug="+ $scope.debug);
	if ( $scope.debug >0 ) {
	    $scope.actJanA3(); // call inernal func
	} else {
	    $scope.result = " another output from  actJanA2";
	}
    }

    //.... function .....
    $scope.actJanA3 = function() {
	console.log("actJanA3:  debug="+ $scope.debug);
	$scope.result = " form internall call of  actJanA3";
    }


}//end of function

