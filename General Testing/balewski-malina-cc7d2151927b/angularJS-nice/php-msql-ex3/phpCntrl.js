 var app = angular.module('myApp3', []);
  app.controller('phpCtrl', function($scope, $http) {
  // set defaults
  $scope.url="mysql.query.php";
  $scope.resultPhp="default55";
  $scope.statusPhp="status55";
  $scope.debug=0;
  $scope.sDir='desc';    
  console.log("phpCtrl: cnstr  result=", $scope.resultPhp);
 
 //.... function .....
 $scope.actQuery = function() {
  var inpPhp={ "val1" : $scope.sDir, "dbg": $scope.debug};
     console.log("phpCtrl:actQuery , inp=",inpPhp);    
  $http.post($scope.url, inpPhp )
        .success(function(result, status) {
                $scope.statusPhp = status;
                $scope.resultPhp = result;
                console.log("customersCtrl: php-ok status=",status);
            })
        .error(function(result2, status2) {
                $scope.statusPhp = status2; 
               $scope.resultPhp = result2 || "mySql Request failed, status="+status2;
                 console.log("customersCtrl: php-bad status=",status);
            });
}
  });
