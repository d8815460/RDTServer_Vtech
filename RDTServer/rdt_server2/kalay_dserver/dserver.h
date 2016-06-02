#ifndef __DSERVER_H__
#define __DSERVER_H__

	#include "../iotc/Include/IOTCAPIs.h"
	#include "../iotc/Include/RDTAPIs.h"

	
	#include "rdtcnnt.h"



	extern char *__myUID[20];
	extern const char *__emualtorVer;

	int kalay_device_server_agent_start(char *UID,char *unixsocket_path);
	int kalay_device_server_agent_stop();

#endif