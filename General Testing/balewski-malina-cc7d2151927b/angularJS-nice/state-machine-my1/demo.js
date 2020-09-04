Demo = function() {

  // text printed as a scroll at the bottom  
  var output = document.getElementById('output');

  // action list:  
  var demo   = document.getElementById('demo'); 
  var panic  = document.getElementById('panic'), 
      walk   = document.getElementById('walk'),
      drive  = document.getElementById('drive'),
      count  = 0;

  var log = function(msg, separate) {
    count = count + (separate ? 1 : 0);
    output.value = count + ": " + msg + "\n" + (separate ? "\n" : "") + output.value;
    demo.className = fsm.current;
    panic.disabled = fsm.cannot('panic');
    walk.disabled  = fsm.cannot('walk');
    drive.disabled  = fsm.cannot('drive');
  };

  var fsm = StateMachine.create({
    events: [ //transitions
      { name: 'start', from: 'none',   to: 'home'  },
      { name: 'walk',  from: 'home',  to: 'work' },
      { name: 'walk',  from: 'work',  to: 'gim' },
      { name: 'panic', from: 'home',  to: 'hospital' },
      { name: 'drive', from: 'gim', to: 'home'    },
    ],

    callbacks: {
      onbeforestart: function(event, from, to) { log("STARTING UP2,to="+to); },
      onstart:       function(event, from, to) { log("READY-start");       },

      onbeforewalk:  function(event, from, to) { log("START   EVENT: walk!",  true);  },
      onbeforepanic: function(event, from, to) { log("START   EVENT: panic!", true);  },
      onbefordrive:  function(event, from, to) { log("START   EVENT: drive!",  true);  },

      onwalk:        function(event, from, to) { log("FINISH  EVENT1: "+event);         },
      onpanic:       function(event, from, to) { log("FINISH  EVENT: panic!");        },
      ondrive:        function(event, from, to) { log("FINISH  EVENT: drive!");         },

      onleavehome:  function(event, from, to) { log("LEAVE   STATE: home");  },
      onleavehospital: function(event, from, to) { log("LEAVE   STATE: hospital"); },
      onleavgim:    function(event, from, to) { log("LEAVE   STATE:"+from+" heading to "+to);    
						 },

      onhome:       function(event, from, to) { log("ENTER   STATE: home");  },
      onhospital:      function(event, from, to) { log("ENTER   STATE: hospital"); },
      onwork:         function(event, from, to) { log("ENTER   STATE: work");    },
      ongim:       function(event, from, to) { log("ENTER   STATE: gim12");  
					     async(to); return StateMachine.ASYNC; },

      onchangestate: function(event, from, to) { log("CHANGED STATE: " + from + " to " + to);
					        }
    }
  });

  var async = function(to) {
    pending(to, 3);

    setTimeout(function() {
      pending(to, 2);

      setTimeout(function() {
        pending(to, 1);
        setTimeout(function() {
          fsm.transition(); // trigger deferred state transition
        }, 1000);
      }, 1000);
    }, 1000);
  };

  var pending = function(to, n) { log("PENDING STATE: " + to + " in ..." + n); };

  fsm.start();
  return fsm;

}();

