var myAppModule = angular.module("myApp", []);

myAppModule.controller('MyController', function($scope, pollingService) {    
    $scope.data = pollingService.data;
    $scope.mySwitch=true;
    $scope.hour = 7;
    pollingService.period1=800;
});

myAppModule.factory("pollingService", function ($http, $timeout) {    
    var data = { resp: {}, count: 0};
    var count = 0;
    var period=500;
    var poller = function() {
	count++;
	$http.get('data77.json').then(function(r) { // reads this file each time	    
	    data.resp = r.data;
	    data.count=count;
	    if ( count%10==2) { console.log(data," period=",period); }
	    $timeout(poller, period);
	});
	
    };
    poller();
    
    return {
	data: data
    };
      
});


/*
  return { 
    
          function success(r) {
              var random = Math.floor((Math.random()*10)+1);
              console.log(r.data);
              deferred.resolve(Number(r.data) + random);
              $timeout(GetData, 500);
          },
          function error(r) {
              console.log("err" + r);
              deferred.reject();
              //$timeout(GetData, 3000);
          }
    
  */
