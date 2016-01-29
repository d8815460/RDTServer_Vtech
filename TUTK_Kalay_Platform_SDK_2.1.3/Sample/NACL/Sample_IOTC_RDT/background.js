function makeURL(toolchain, config) {
	return 'index.html?tc=' + toolchain + '&config=' + config;
}

function createWindow(url) {
	console.log('loading ' + url);
	chrome.app.window.create(url, {
		width: 1024,
		height: 840,
		frame: 'none'
	});
}

function onLaunched(launchData) {
	var xhr = new XMLHttpRequest();
	xhr.open('GET', 'run_package_config', true);
	xhr.onload = function() {
		var toolchain_config = this.responseText.split(' ');
		createWindow(makeURL.apply(null, toolchain_config));
	};
	xhr.onerror = function() {
		createWindow('index.html');
	};
	xhr.send();
}

chrome.app.runtime.onLaunched.addListener(onLaunched);
