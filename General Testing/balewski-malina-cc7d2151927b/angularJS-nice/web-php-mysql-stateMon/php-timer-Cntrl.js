 var app = angular.module('myApp3', []);
  app.controller('phpTimeCtrl', function($scope, $http, $timeout) {

  //---- variables used by PHP ---- 
  $scope.url="mysql.query.php";
  $scope.resultPhp="default55";
  $scope.statusPhp="status55";
  $scope.debug=0;
  console.log("phpCtrl: cnstr  result=", $scope.resultPhp);

  //----- timer variables ------
  var startTime = new Date();
  $scope.time_s = 0;
  $scope.pollPeriod_s=1.5;
  $scope.counter=0;
  $scope.pauseTimer=false;

      $scope.db_age_s=77;

  //.... PHP function .....
  $scope.actQuery = function() {
     var inpPhp={  "dbg": $scope.debug};
     if ($scope.debug>0) {
         console.log("phpCtrl:actQuery , inp=",inpPhp);    }
     $http.post($scope.url, inpPhp )
        .success(function(result, status) {
                $scope.statusPhp = status;
                $scope.resultPhp = result;
	        if ($scope.debug>0) {
                    console.log("customersCtrl: php-ok status=",status); }
	     $scope.db_age_s=(new Date() - new Date(result.timeStamp).getTime()) / 1000 ;
            })
        .error(function(result2, status2) {
                $scope.statusPhp = status2; 
                $scope.resultPhp = result2 || "mySql Request failed, status="+status2;
                console.log("customersCtrl: php-bad status=",status);
            });
      }


     
  //--------  timer functions ------
   var countUp = function() {
      if (  $scope.counter%1==0 ) {
          console.log( $scope.counter,"=counter, elaps sec=", $scope.time_s," period(s)=",$scope.pollPeriod_s); }
      $scope.counter+=1;
      $scope.time_s= (new Date() - startTime) / 1000;
      if ( $scope.pauseTimer ) {
            console.log( "Pause Timer");  
            return;
      }
      $scope.actQuery(); 
      $timeout(countUp, $scope.pollPeriod_s*1000.);
    }
   
    countUp(); // activate counter by cnstr

    $scope.restart  = function() {  
      console.log( "Timer Reactivated Activated, pause=",$scope.pauseTimer);  
      $scope.pauseTimer=false;
      countUp();
    }

  });
