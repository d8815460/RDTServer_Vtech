var io = require('socket.io-client');
var util = require('util');

var socketURL = 'http://127.0.0.1:4663';

//var socketURL = 'http://10.42.0.11:4663';

var options ={
  transports: ['websocket'],
};

var emulator_cmd = {

  "mobileId": "1kVJFmIbEKelhX9KUEvN",
  "data": {
    "action": "rpc",
    "data": {
      "broker": "devicemanager",
      "id": "0298ed5e25",
      "functionName": "toggle",
      "args": [
        true
      ]
    }
  }
}



var send_on_off_command = {

//  "mobileId": "1kVJFmIbEKelhX9KUEvN",
  "data": {
    "action": "rpc",
    "data": {
      "broker": "devicemanager",
      "id": "0298ed48a6",
//      "refid": "1401459091675.3675828189589083",
      "functionName": "toggle",
      "args": [
        false
      ]
    }
  }

}


var init_command = {
//  "mobileId": "1kVJFmIbEKelhX9KUEvN",
"mobileId": "ubuntu_pc1",
  "data": {
    "action": "rpc",
    "data": {
      "broker": "devicemanager"
    }
  }
}

var test_command = {
  "mobileId": "1kVJFmIbEKelhX9KUEvN",
	"00e35800": "testing",
  "data": {
    "action": "rpc",
    "data": {
      "broker": "devicemanager",
	  "args": [
        		false
      			]

    }
  }
}


//var client1 = io.connect(socketURL, options);

var client1 = io.connect(socketURL);

var args = process.argv.slice(2);

var AC_action = args=='1' ? true : false;

//console.log(AC_action);

  client1.on('connect', function(){
	console.log('Baldwin check its connected to client side');

	emulator_cmd.data.data.args[0] = AC_action; // mark out for testing only
	client1.emit('command',emulator_cmd,function(data){
		console.log('Send on/off command');
		console.log(data);
	}
	)

		client1.on('refid', function(){
			console.log('received something back from server');
		}
		);



	client1.on('disconnect', function(){
		console.log('disconnected from server here');

	});


  });


    


