function attachListeners() {
	document.getElementById('connectForm').addEventListener('submit', doConnect);
}


function moduleDidLoad() {
	common.hideModule();
}


var msgIOTC = 'i;'
var msgRDT  = 'r;'


function doConnect(event) {
	event.preventDefault();
	var deviceUID = document.getElementById('deviceUID').value;
	var type = document.getElementById('connect_type').value;
	common.logMessage(type);
	if (type == 'IOTC') {
		common.naclModule.postMessage(msgIOTC + deviceUID);
	} else {
		common.naclModule.postMessage(msgRDT + deviceUID);
	}
}


function handleMessage(message) {
	common.logMessage(message.data);
}
