#ifndef __FWAPI_H__
#define __FWAPI_H__

	#include <json/json.h>


	int fwapi_connect(char *path);
	int fwapi_cnnt_check_status(); // will try to recovery connection state
	int fwapi_cnnt_get_status(); // query status only


	int fwapi_getall();
	int fwapi_set(Json::Value &objects);
	int fwapi_get(Json::Value &objects);
#endif