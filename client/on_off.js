var io = require('socket.io-client');
var util = require('util');

var socketURL = 'http://127.0.0.1:4663';

//var socketURL = 'http://192.168.1.194:4663';

var options ={
  transports: ['websocket'],
};

var emulator_cmd = {

      "broker": "devicemanager",
      "id": "0298ed5e25",
      "functionName": "toggle",
      "args": [
        true
      ]
}

var client1 = io.connect(socketURL);

var args = process.argv.slice(2);

var AC_action = args=='1' ? true : false;

//console.log(AC_action);

  client1.on('connect', function(){
	console.log('Baldwin check its connected to client side');

	emulator_cmd.args[0] = AC_action; // mark out for testing only
	client1.emit('command',emulator_cmd,function(data){
		console.log('Send on/off command');
		console.log(data);
	}
	)


	client1.on('disconnect', function(){
		console.log('disconnected from server here');

	});


  });


    

