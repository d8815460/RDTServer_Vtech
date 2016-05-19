#include "../headers/unixclientstream.hpp"
#include "../headers/exception.hpp"
#include <string>
#include <iostream>
#include <string.h>
#include <unistd.h>

#include <iomanip> 
#include <json/json.h>


#include "kalay_dserver.h"
#include "dserver.h"
#include "device_parser.h"
#include "device_api.h"

using namespace std;


int device_parser(int session,unsigned char *option,unsigned char *data)
{
	Json::Reader reader;
	Json::Value value;
	

	if (reader.parse((char*) data, value))
	{
		string uid = value["uid"].asString();
		string api = value["api"].asString();

		printf("UID:%s\n",uid.c_str());
		printf("api:%s\n",api.c_str());

		if ( strcmp(api.c_str(),"get_gateway") == 0 ) //
		{
			deviceapi_get_gateway(session,value);
		}
		else if ( strcmp(api.c_str(),"get_accessory_detail") == 0 ) //
		{
			deviceapi_get_accessory_detail(session,value);
		}
	}
	else
	{
		printf("Receive a non-json format string\n");
	}

	return 0;

}
