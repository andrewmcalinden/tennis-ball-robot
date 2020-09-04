function JSprogJanB($scope, $http) {
    // set defaults
    $scope.url="apiDb4.php";
    $scope.operator="PrincesLeya2";
    $scope.debug=2;
    $scope.result="default55";
    console.log("actJanB: cnstr 0 php result=", $scope.result);
 		
    //.... function .....
    $scope.actJanB1 = function() {
	console.log("actJanB1:  operator="+$scope.operator+" debug="+ $scope.debug);;		
	$scope.result = "out actJanB1: dbg="+ $scope.debug;
	$http.post($scope.url, { "val1" : "ABC22", "dbg2": $scope.debug})
	.success(function(result1, status1) {
		$scope.status = status1;
		$scope.result = result1; 
	    })
	.error(function(result2, status2) {
		$scope.result = result2 || "Request failed";
	    });
    }

    //.... function .....
    $scope.actJanB2 = function() {
	console.log("actJanB2:  debug="+ $scope.debug);
	$scope.result = "output from  actJanB2";	
    }

}//end of function

