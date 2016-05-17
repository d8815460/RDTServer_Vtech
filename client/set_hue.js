var io = require('socket.io-client');
var util = require('util');

var socketURL = 'http://127.0.0.1:4663';

//var socketURL = 'http://192.168.1.194:4663';

var options ={
  transports: ['websocket'],
};

//var emulator_cmd = {

//      "broker": "devicemanager",
//      "id": "0298ed5e25",
//      "functionName": "setHue",
//      "args": [
//        20,
//		0
//      ]
//}

var emulator_cmd = {

      "broker": "devicemanager",
      "id": "0298ed5e25",
      "functionName": "setHue",
      "args": [
        20
      ]
}


var client1 = io.connect(socketURL);

var hue = parseInt(process.argv.slice(2));

if (isNaN(hue))
	hue = 0;

  client1.on('connect', function(){
	console.log('Baldwin check its connected to client side');

	emulator_cmd.args[0] = hue; // mark out for testing only
	client1.emit('command',emulator_cmd,function(data){
		console.log('send sethue command');
		console.log(data);
	}
	)


	client1.on('disconnect', function(){
		console.log('disconnected from server here');

	});


  });


    


