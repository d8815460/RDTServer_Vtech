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
#include "dtable.h"
#include "device_api.h"




using namespace std;

int sendto_rdt_client (int session,unsigned int rdt_ticket,char *data)
{
	unsigned char szBuff[1024*16];
	int send_length;
	int option_len = 0;
	int rc;
	int data_length;

	data_length  = strlen(data);


	szBuff[0]= 0xfe;
	szBuff[1]= 0xef;

	if ( rdt_ticket > 0 )
	{
		option_len = 4;

		szBuff[2]= option_len/256;
		szBuff[3]= option_len%256;

		szBuff[3+1] = 0x00;
		szBuff[3+2] = 0x01;
		szBuff[3+3] = ((rdt_ticket&0xff00)>>8);
		szBuff[3+4] = (rdt_ticket)&0xff;
	}
	else
	{
		option_len = 0;

		szBuff[2]= 0x00;
		szBuff[3]= 0x00;
	}

	szBuff[4+option_len]= (data_length&0xff00)>>8;
	szBuff[5+option_len]= (data_length&0x00ff);
	memcpy(&szBuff[6+option_len],data,data_length);
	send_length = 6+option_len+data_length;
		


	//printf("Dump RDT json: \n%s\n",payload.c_str());

	rc =  RDT_Write(__rdt_cnnt[session].rdt_id,(char*)szBuff,send_length); 

	if ( rc < 0 )
	{
		
	}

	return rc;

}

// Implemente API functions -----------------------------

void deviceapi_get_gateway_about (int session,Json::Value &request)
{

	Json::Value root;
	Json::Value response;
	unsigned int rdt_ticket;
	int rc;
	int err = 1;
	string err_str;


	rdt_ticket = request["rdt_ticket"].asUInt();


	response["uid"] = (char*) __myUID;
	response["api"] = "get_gateway_about";


	try {
		CMyObject *pGateway = __allObjects.m_mapAllObjects[0x70000001];
		

		if ( pGateway != NULL )
		{
			map<string,int>::iterator iNum;
			map<string,string>::iterator iStr;

			for(iNum = pGateway->m_attr_num.begin(); iNum!=pGateway->m_attr_num.end(); ++iNum)
			{
				//printf("eddy test attr:%s value:%d \n",iNum->first.c_str(),iNum->second);

				response[iNum->first.c_str()] = iNum->second;
			}

			for(iStr = pGateway->m_attr_str.begin(); iStr!=pGateway->m_attr_str.end(); ++iStr)
			{
				//printf("eddy test attr:%s value:%s \n",iStr->first.c_str(),iStr->second.c_str());

				response[iStr->first.c_str()] = iStr->second.c_str();
			}

			err = 0;
		}
		else
		{
			err = -1;
			err_str = "not found";
		}
	


    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	root["error"] = err;
	if ( err_str.length() != 0 )
		root["error_str"] = err_str;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_get_accessory_about (int session,Json::Value &request)
{

	Json::Value root;
	Json::Value response;
	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	response["uid"] = (char*) __myUID;;
	response["api"] = "get_gateway_about";
	response["udid"] = "0035482900";	
	response["type"] = 1;
	response["firmware_version"] = "1.0.0";


	root["error"] = 0;

	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_get_accessory_detail (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value color_hsb;
	Json::Value color_brightness;
	Json::Value location;

	unsigned int rdt_ticket;
	int rc;
	unsigned int id;


	rdt_ticket = request["rdt_ticket"].asUInt();



	id = request["id"].asUInt();

	if ( id == 1 )  // Light
	{
		location["id"] = 0x13000001;
		location["name"] = "Bedroom";

		color_hsb["hue"] = 23;
		color_hsb["saturation"] = 0.5;
		color_hsb["brightness"] = 0.5;

		color_brightness["brightness"] = 23;
		color_brightness["temperature"] = 5000;



		response["uid"] = (char*) __myUID;;
		response["api"] = "get_accessory_detail";

		response["id"] = 0x01000002;
		response["name"] = "Light 01";
		response["type"] = 0,
		response["icon"] = 0;	
		response["status"] = 1;
		response["location"] = location;
		response["color_hsb"] = color_hsb;
		response["color_brightness"] = color_brightness;


		root["error"] = 0;
		root["response"] = response;

		rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());
	}
	else if ( id == 2 )  // wall switch
	{
		response["uid"] = (char*) __myUID;;
		response["api"] = "get_accessory_detail";

		response["id"] = 0x01000002;
		response["name"] = "Wall Switch";
		response["type"] = 4,
		response["icon"] = 0;	
		response["status"] = 1;
		response["low_battery"] = 1;


		root["error"] = 0;
		root["response"] = response;

		rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());
	}



	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_get_group_free_lights (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();


	objects[0]["id"] = "a01";
	objects[0]["name"] = "Light 1";

	objects[1]["id"] = "a02";
	objects[1]["name"] = "Light 2";

	objects[2]["id"] = "a03";
	objects[2]["name"] = "Light 3";


	response["uid"] = (char*) __myUID;;
	response["id"] = "a01";
	response["objects"] = objects;


	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_set_detail (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	Json::Value location;

	Json::Value color_hsb;
	Json::Value color_brightness;	

	unsigned int rdt_ticket;
	int rc;
	unsigned int id;
	int status;

	rdt_ticket = request["rdt_ticket"].asUInt();

	id = request["id"].asUInt();

	status = request["status"].asInt();

	if ( id == 1 )  // Light
	{

	}

		location["id"] = 0x13000001;
		location["name"] = "Bedroom";


	color_hsb["hue"] = 23;
	color_hsb["saturation"] = 0.5;
	color_hsb["brightness"] = 0.5;

	color_brightness["brightness"] = 23;
	color_brightness["temperature"] = 5000;	

	response["uid"] = (char*) __myUID;;
	response["api"] = "set_detail";
	response["id"] = 0x01000002;


	response["icon"] = 0;
	response["status"] = status;
	response["color_hsb"] = color_hsb;
	response["color_brightness"] = color_brightness;
	response["location"] = location;


	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_remove (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();


	response["api"] = "remove";
	response["id"] = "a01";


	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}


	return;
}

void deviceapi_get_activities (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();


	response["uid"] = (char*) __myUID;;

	objects[0]["unix_time"] = "122739743";
	objects[0]["message"] = "Garage Door is open";

	objects[1]["unix_time"] = "122753243";
	objects[1]["message"] = "Garage Door is close";

	response["objects"] = objects;


	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}


	return;
}

void deviceapi_get_light_effects (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();


	objects[0]["id"] = "e01";
	objects[0]["name"] = "Effect 01";
	objects[0]["is_selected"] = true;

	objects[1]["id"] = "e02";
	objects[1]["name"] = "Effect 02";
	objects[1]["is_selected"] = false;

	objects[2]["id"] = "e03";
	objects[2]["name"] = "Effect 03";
	objects[2]["is_selected"] = false;


	response["uid"] = (char*) __myUID;;
	response["objects"] = objects;
 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}


	return;
}

void deviceapi_set_light_effects (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();


	objects[0]["id"] = "e01";


	response["api"] = "set_light_effects";
	response["id"] = "a01";
	response["objects"] = objects;
 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}



void deviceapi_get_gateway (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value locations;
	Json::Value accessories;

	int rc;					
	unsigned int rdt_ticket;		


	rdt_ticket = request["rdt_ticket"].asUInt();

	response["uid"] = (char*) __myUID;
	response["api"] = "get_gateway";
	response["name"] = "Getway 01";

	locations[0]["id"] = 0x13000001,
	locations[0]["name"] = "Bedroom";

	accessories.clear();

	accessories[0]["id"] = 0x01000001;
	accessories[0]["name"] = "Switch 01";
	accessories[0]["status"] = 0;
	accessories[0]["type"] =  4;
	accessories[0]["icon"] = 0; // 0 is use default icon
	accessories[0]["trigger"] = 0;

	accessories[1]["id"] = 0x01000002;
	accessories[1]["name"] = "Light 01";
	accessories[1]["status"] = 1;
	accessories[1]["type"] = 0;
	accessories[1]["icon"] = 0;
	accessories[1]["trigger"] = 0;

	locations[0]["accessories"] = accessories;

	locations[1]["id"] = 0x13000002;
	locations[1]["name"] = "Bathroom";

	accessories.clear();

	accessories[0]["id"] = 0x01000003;
	accessories[0]["name"] = "Switch 02";
	accessories[0]["status"] = 0;
	accessories[0]["type"] = 4;
	accessories[0]["icon"] = 0;
	accessories[0]["trigger"] = 0;

	accessories[1]["id"] = 0x12000001;
	accessories[1]["name"] = "Group 01";
	accessories[1]["status"] = 0;
	accessories[1]["type"] = 5;
	accessories[1]["icon"] = 0;
	accessories[1]["trigger"] = 0;

	locations[1]["accessories"] = accessories;

	locations[2]["id"] = 0x13000002;
	locations[2]["name"] = "Kitchen";

	accessories.clear();

	accessories[0]["id"] = 0x01000004;
	accessories[0]["name"] = "Garage Door Sensor 01";
	accessories[0]["status"] = 2;
	accessories[0]["type"] = 2;
	accessories[0]["icon"] = 0;
	accessories[0]["trigger"] = 1;

	accessories[1]["id"] = 0x01000005;
	accessories[1]["name"] = "Light 02";
	accessories[1]["status"] = 1;
	accessories[1]["type"] = 0;
	accessories[1]["icon"] = 0;
	accessories[1]["trigger"] = 0;

	accessories[2]["id"] = 0x01000006;
	accessories[2]["name"] = "Light 03";
	accessories[2]["status"] = 1;
	accessories[2]["type"] = 0;
	accessories[2]["icon"] = 0;
	accessories[2]["trigger"] = 0;

	accessories[3]["id"] = 0x01000007;
	accessories[3]["name"] = "Light 04";
	accessories[3]["status"] = 1;
	accessories[3]["type"] = 0;
	accessories[3]["icon"] = 0;
	accessories[3]["trigger"] = 0;

	locations[2]["accessories"] = accessories;

	response["locations"] = locations;

	root["error"] = 0;
	root["response"] = response;


	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{
		
	}


	return;
}

void deviceapi_add_accessories (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();


	objects[0]["id"] = "a01";
	objects[1]["id"] = "a02";


	response["api"] = "add_accessories";
	response["objects"] = objects;
 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_merge_accessories (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();


	objects[0]["id"] = "a01";
	objects[1]["id"] = "a02";


	response["api"] = "merge_accessories";
	response["objects"] = objects;
 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_backup_gateway (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();



	response["api"] = "backup_gateway";
 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_restore_gateway (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();



	response["api"] = "restore_gateway";
 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_reset_gateway (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();



	response["api"] = "reset_gateway";
 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_update_gateway (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();



	response["api"] = "update_gateway";
 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_get_detail (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value location;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["uid"] = (char*) __myUID;
	response["id"] = "g01";
	response["status"] = 1;
	response["name"] = "Group 1";

	location["id"] = "l01";
	location["name"] = "Location 01";

	response["location"] = location;


	objects[0]["id"] = "a01";
	objects[0]["name"] = "name";
	objects[0]["type"] = 0;
	objects[0]["icon"] = 0;
	objects[0]["status"] = 1;


	objects[1]["id"] = "a02";
	objects[1]["name"] = "Light 2";
	objects[1]["type"] = 0;
	objects[1]["icon"] = 0;
	objects[1]["status"] = 1;


	objects[2]["id"] = "a03";
	objects[2]["name"] = "Light 3";
	objects[2]["type"] = 0;
	objects[2]["icon"] = 0;
	objects[2]["status"] = 1;

	response["objects"] = objects;

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}


	return;
}

void deviceapi_get_other_groups (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["uid"] = (char*) __myUID;


	objects[0]["id"] = "g01";
	objects[0]["name"] = "Group 1";


	objects[1]["id"] = "g02";
	objects[1]["name"] = "Group 2";


	objects[2]["id"] = "g03";
	objects[2]["name"] = "Group 2";

	response["objects"] = objects;

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

//void deviceapi_set_detail (int session,Json::Value &request)


void deviceapi_add_an_accessory_to_group (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["api"] = "add_an_accessory_to_group";

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_remove_accessories_from_group (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["api"] = "remove_accessories_from_group";

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_get_locations (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["uid"] = (char*) __myUID;


	objects[0]["id"] = "l00";
	objects[0]["name"] = "Bedroom";
	objects[0]["is_editable"] = true;


	objects[1]["id"] = "l01";
	objects[1]["name"] = "Garage";
	objects[1]["is_editable"] = false;

	objects[2]["id"] = "l02";
	objects[2]["name"] = "Kitchen";
	objects[2]["is_editable"] = false;

	
	response["objects"] = objects;

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_add_accessories_to_location (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["uid"] = (char*) __myUID;


	objects[0]["id"] = "a01";
	objects[0]["name"] = "Accessory 01";


	objects[1]["id"] = "a01";
	objects[1]["name"] = "Accessory Sensor";

	objects[2]["id"] = "a03";
	objects[2]["name"] = "Accessory Light";

	objects[3]["id"] = "a02";
	objects[3]["name"] = "Accessory 02";

	
	response["objects"] = objects;

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_create_a_location (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["uid"] = (char*) __myUID;
	response["id"] = "l00";
	response["name"] = "Location 0";


 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_remove_locations (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["api"] = "remove_locations";

	
 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;	
}
//void deviceapi_get_detail (int session,Json::Value &request)
void deviceapi_set_schedule_detail (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["api"] = "set_schedule_detail";

	

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_add_a_schedule (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["api"] = "add_a_schedule";

	

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}
	
	return;
}

//void deviceapi_remove_a_schedule (int session,Json::Value &request)
void deviceapi_get_accessory_setting (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["api"] = "remove_a_schedule";

	

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}
	
	return;
}

void deviceapi_get_gateway_setting (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group

	response["uid"] = (char*) __myUID;
	response["home"] = "appl";
	response["led_light_status"] = true;
	
	response["objects"] = objects;

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}
	
	return;
}

void deviceapi_set_accessory_setting (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group

	response["api"] = "set_accessory_setting";
	response["id"] = "s01";
	
	response["objects"] = objects;

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}


	return;
}

//void deviceapi_set_accessory_setting (int session,Json::Value &request)
void deviceapi_set_gateway_setting (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group

	response["api"] = "set_gateway_setting";
	
	response["objects"] = objects;

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_get_objects (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["uid"] = (char*) __myUID;


	objects[0]["id"] = "s011";
	objects[0]["name"] = "Switch 1";


	objects[1]["id"] = "s012";
	objects[1]["name"] = "Switch 2";

	objects[2]["id"] = "s013";
	objects[2]["name"] = "Switch 3";

	objects[3]["id"] = "s014";
	objects[3]["name"] = "Switch 4";

	
	response["objects"] = objects;

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

//void deviceapi_get_detail (int session,Json::Value &request)
//void deviceapi_set_detail (int session,Json::Value &request)
void deviceapi_remove_a_switch_accessory (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group

	response["api"] = "remove_a_switch_accessory";
	

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}	
	return;
}

void deviceapi_get_tasks (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["uid"] = (char*) __myUID;


	objects[0]["id"] = "t01";
	objects[0]["name"] = "Task 1";
	objects[0]["is_activated"] = true;


	objects[1]["id"] = "t02";
	objects[1]["name"] = "Task 2";
	objects[1]["is_activated"] = false;


	
	response["objects"] = objects;

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}


	return;
}

//void deviceapi_get_detail (int session,Json::Value &request)
//void deviceapi_set_detail(session,value);
void deviceapi_add_a_task (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group

	response["api"] = "add_a_task";
 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}


	return;
}

//void deviceapi_remove (int session,Json::Value &request)

