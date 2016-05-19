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
#include "device_api.h"


using namespace std;




void deviceapi_get_gateway(int session,Json::Value &request)
{
	std::string payload;

	Json::Value root;
	Json::Value response;
	Json::Value locations;
	Json::Value accessories;

	int rc;							

	unsigned char szBuff[1024*16];
	int send_length;

	response["id"] = (char*) __myUID;
	response["name"] = "Getway 01";

	locations[0]["id"] = "l01",
	locations[0]["name"] = "Bedroom";

	accessories.clear();

	accessories[0]["id"] = "a01";
	accessories[0]["name"] = "Switch 01";
	accessories[0]["status"] = 0;
	accessories[0]["type"] =  4;
	accessories[0]["icon"] = 0; // 0 is use default icon
	accessories[0]["trigger"] = 0;

	accessories[1]["id"] = "a02";
	accessories[1]["name"] = "Light 01";
	accessories[1]["status"] = 1;
	accessories[1]["type"] = 1;
	accessories[1]["icon"] = 0;
	accessories[1]["trigger"] = 0;

		locations[0]["accessories"] = accessories;

	locations[1]["id"] = "l02";
		locations[1]["name"] = "Bathroom";

	accessories.clear();

	accessories[0]["id"] = "a03";
	accessories[0]["name"] = "Switch 02";
	accessories[0]["status"] = 0;
	accessories[0]["type"] = 4;
	accessories[0]["icon"] = 0;
	accessories[0]["trigger"] = 0;

	accessories[1]["id"] = "g01";
	accessories[1]["name"] = "Group 01";
	accessories[1]["status"] = 0;
	accessories[1]["type"] = 5;
	accessories[1]["icon"] = 0;
	accessories[1]["trigger"] = 0;

		locations[1]["accessories"] = accessories;

	locations[2]["id"] = "l03";
	locations[2]["name"] = "Kitchen";

	accessories.clear();

	accessories[0]["id"] = "a04";
	accessories[0]["name"] = "Garage Door Sensor 01";
	accessories[0]["status"] = 2;
	accessories[0]["type"] = 2;
	accessories[0]["icon"] = 0;
	accessories[0]["trigger"] = 1;

	accessories[1]["id"] = "a05";
	accessories[1]["name"] = "Light 02";
	accessories[1]["status"] = 1;
	accessories[1]["type"] = 1;
	accessories[1]["icon"] = 0;
	accessories[1]["trigger"] = 0;

	accessories[2]["id"] = "a06";
	accessories[2]["name"] = "Light 03";
	accessories[2]["status"] = 1;
	accessories[2]["type"] = 1;
	accessories[2]["icon"] = 0;
	accessories[2]["trigger"] = 0;

	accessories[3]["id"] = "a07";
	accessories[3]["name"] = "Light 04";
	accessories[3]["status"] = 1;
	accessories[3]["type"] = 1;
	accessories[3]["icon"] = 0;
	accessories[3]["trigger"] = 0;

	locations[2]["accessories"] = accessories;

	response["locations"] = locations;

	root["error"] = 0;
	root["response"] = response;


	payload = root.toStyledString().c_str();
	//printf("Dump RDT json: \n%s\n",payload.c_str());



szBuff[0]= 0xfe;
szBuff[1]= 0xef;

szBuff[2]= 0x00; // option length
szBuff[3]= 0x00; // option length

szBuff[4]= payload.length()/256;
szBuff[5]= payload.length()%256;
memcpy(&szBuff[6],payload.c_str(),payload.length());
send_length = 6+payload.length();

	rc =  RDT_Write(__rdt_cnnt[session].rdt_id,(char*)szBuff,send_length);    		

	if ( rc < 0 )
	{

	}


	return;
}

void deviceapi_get_accessory_detail(int session,Json::Value &request)
{
	std::string payload;
	
	Json::Value root;
	Json::Value response;
	Json::Value color;

	int rc;

	unsigned char szBuff[1024*16];
	int send_length;


	color["hue"] = 23;
	color["saturation"] = 345;
	color["brightness"] = 2323;
	color["temperature"] = 24;


	response["id"] = "a01";
	response["name"] = "Light";
	response["status"] = 1,
	response["location"] = "location 1";	
	response["effects"] = "Default effect 2";
	response["color"] = color;

	root["error"] = 0;
	root["response"] = response;

	payload = root.toStyledString().c_str();



szBuff[0]= 0xfe;
szBuff[1]= 0xef;

szBuff[2]= 0x00; // option length
szBuff[3]= 0x00; // option length

szBuff[4]= payload.length()/256;
szBuff[5]= payload.length()%256;
memcpy(&szBuff[6],payload.c_str(),payload.length());
send_length = 6+payload.length();
	


	//printf("Dump RDT json: \n%s\n",payload.c_str());

	rc =  RDT_Write(__rdt_cnnt[session].rdt_id,(char*)szBuff,send_length); 

	if ( rc < 0 )
	{
		
	}


	return;
}

