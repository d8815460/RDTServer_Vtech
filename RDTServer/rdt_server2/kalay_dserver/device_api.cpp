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

#include "fw_api.h"


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

			for(iNum = pGateway->m_about_num.begin(); iNum!=pGateway->m_about_num.end(); ++iNum)
			{
				//printf("eddy test attr:%s value:%d \n",iNum->first.c_str(),iNum->second);

				response[iNum->first.c_str()] = iNum->second;
			}

			for(iStr = pGateway->m_about_str.begin(); iStr!=pGateway->m_about_str.end(); ++iStr)
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
	int id;
	int err = 1;
	string err_str;	


	rdt_ticket = request["rdt_ticket"].asUInt();

	response["uid"] = (char*) __myUID;;
	response["api"] = "get_accessory_about";

	id = request["id"].asUInt();

	printf("get_accessory_about id :%d \n",id);


	try {
		CMyObject *pAccessory = __allObjects.m_mapAllObjects[id];
		
		if ( pAccessory != NULL )
		{
			map<string,int>::iterator iNum;
			map<string,string>::iterator iStr;

			response["id"] 	= pAccessory->m_id;
			response["type"] = pAccessory->m_attr_num["type"];


			for(iNum = pAccessory->m_about_num.begin(); iNum!=pAccessory->m_about_num.end(); ++iNum)
			{
				//printf("eddy test attr:%s value:%d \n",iNum->first.c_str(),iNum->second);

				response[iNum->first.c_str()] = iNum->second;
			}

			for(iStr = pAccessory->m_about_str.begin(); iStr!=pAccessory->m_about_str.end(); ++iStr)
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

void deviceapi_get_accessory_detail (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value location;

	unsigned int rdt_ticket;
	int rc;
	unsigned int id;
	int err = 1;
	string err_str;	


	rdt_ticket = request["rdt_ticket"].asUInt();

	response["uid"] = (char*) __myUID;;
	response["api"] = "get_accessory_detail";

	id = request["id"].asUInt();

	printf("get_accessory_detail id :%d \n",id);







	try {
		CMyObject *pObject = __allObjects.m_mapAllObjects[id];
		
		if ( pObject != NULL )
		{
			map<string,int>::iterator iNum;
			map<string,string>::iterator iStr;
			//int accessoryType;

			response["id"] = pObject->m_id;

			//accessoryType = pAccessory->m_attr_num["type"];	



			if (    pObject->m_id >  0x01000000 
				 && pObject->m_id <  0x10000000  ) // Accessory
			{
				CAccessory *pAccessory = (CAccessory*) pObject;
				if ( pAccessory->m_pLocation != NULL ) 
				{
					location["id"] = pAccessory->m_pLocation->m_id;
					location["name"] = pAccessory->m_pLocation->m_attr_str["name"];

					response["location"] = location;
				}

			}
			else if (    (pObject->m_id >> 24) == 0x12 ) // Group
			{
				CGroup *pGroup = (CGroup*)pObject;
				if ( pGroup->m_pLocation != NULL ) 
				{
					location["id"] = pGroup->m_pLocation->m_id;
					location["name"] = pGroup->m_pLocation->m_attr_str["name"];

					response["location"] = location;
				}

			}				
				


			for(iNum = pObject->m_attr_num.begin(); iNum!=pObject->m_attr_num.end(); ++iNum)
			{
				//printf("eddy test attr:%s value:%d \n",iNum->first.c_str(),iNum->second);



				response[iNum->first.c_str()] = iNum->second;



				
			}

			for(iStr = pObject->m_attr_str.begin(); iStr!=pObject->m_attr_str.end(); ++iStr)
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


	unsigned int rdt_ticket;
	int rc;
	unsigned int id;
	int err = 1;
	string err_str;		
	

	rdt_ticket = request["rdt_ticket"].asUInt();


	response["uid"] = (char*) __myUID;;
	response["api"] = "set_detail";

	id = request["id"].asUInt();

	

		printf("get_accessory_detail id :%d \n",id);


	try {
		CMyObject *pObject = __allObjects.m_mapAllObjects[id];


		if ( pObject != NULL )
		{
			map<string,int>::iterator iNum;
			map<string,string>::iterator iStr;
			//int accessoryType;


			// Change Value +++
			{
				Json::ValueIterator itr;

				for(itr=request.begin();itr != request.end(); itr++)
				{
					Json::Value key = itr.key();
					Json::Value value = (*itr);

					if ( 	key.asString() != "api"
						 && key.asString() != "id"
						 && key.asString() != "rdt_ticket"
						 && key.asString() != "uid"			)
					{

						printf("Set key : %s       value:%s \n",key.asString().c_str(),value.asString().c_str());

						if ( value.isString() )
							pObject->m_attr_str[key.asString().c_str()] = value.asString();
						else if ( value.isDouble() )
							pObject->m_attr_num[key.asString().c_str()] = value.asDouble();
						else
							pObject->m_attr_num[key.asString().c_str()] = value.asUInt();
					}
				}


				// Set to FW
				//if ( pObject->m_about_str["udid"] == "0012345678" )
				{
		    		Json::Value objects;

		    		objects[0]["id"] = pObject->m_about_str["udid"]; // "0012345678";
		    		
		    		if ( request["status"].asInt() == 0 )
		    			objects[0]["on"] = 1;
		    		else
		    			objects[0]["on"] = 0;

		    		fwapi_set(objects);
				}


			}

			// Change Value ---





			response["id"] = pObject->m_id;

			//accessoryType = pAccessory->m_attr_num["type"];	



			if (    pObject->m_id >  0x01000000 
				 && pObject->m_id <  0x10000000  ) // Accessory
			{
				CAccessory *pAccessory = (CAccessory*) pObject;
				if ( pAccessory->m_pLocation != NULL ) 
				{
					location["id"] = pAccessory->m_pLocation->m_id;
					location["name"] = pAccessory->m_pLocation->m_attr_str["name"];

					response["location"] = location;
				}

			}
			else if (    (pObject->m_id >> 24) == 0x12 ) // Group
			{
				CGroup *pGroup = (CGroup*)pObject;
				if ( pGroup->m_pLocation != NULL ) 
				{
					location["id"] = pGroup->m_pLocation->m_id;
					location["name"] = pGroup->m_pLocation->m_attr_str["name"];

					response["location"] = location;
				}

			}				
				


			for(iNum = pObject->m_attr_num.begin(); iNum!=pObject->m_attr_num.end(); ++iNum)
			{
				//printf("eddy test attr:%s value:%d \n",iNum->first.c_str(),iNum->second);


				response[iNum->first.c_str()] = iNum->second;



				
			}

			for(iStr = pObject->m_attr_str.begin(); iStr!=pObject->m_attr_str.end(); ++iStr)
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
	int err = 1;
	string err_str;


	rdt_ticket = request["rdt_ticket"].asUInt();



//++++



	try {
			TAllObjectMap::iterator p;
			list<CMyObject*>::iterator j;
			int nLocationCnt = 0;


			for(p = __allObjects.m_mapAllLocations.begin(); p!=__allObjects.m_mapAllLocations.end(); ++p)
			{
				CLocation *pLocation;
				int nAccessoryCnt = 0;

				
				pLocation = (CLocation*) p->second;


				locations[nLocationCnt]["id"] =  pLocation->m_id,
				locations[nLocationCnt]["name"] =  pLocation->m_attr_str["name"].c_str();

				
				accessories.clear();

				for(j = pLocation->m_listObject.begin(); j!=pLocation->m_listObject.end(); ++j)
				{
					CMyObject *pObject;
					map<string,int>::iterator iNum;
					map<string,string>::iterator iStr;					

					pObject = *j;

					accessories[nAccessoryCnt]["id"] = pObject->m_id;


					for(iNum = pObject->m_attr_num.begin(); iNum!=pObject->m_attr_num.end(); ++iNum)
					{
						//printf("eddy test attr:%s value:%d \n",iNum->first.c_str(),iNum->second);

						accessories[nAccessoryCnt][iNum->first.c_str()] = iNum->second;
					}

					for(iStr = pObject->m_attr_str.begin(); iStr!=pObject->m_attr_str.end(); ++iStr)
					{
						//printf("eddy test attr:%s value:%s \n",iStr->first.c_str(),iStr->second.c_str());

						accessories[nAccessoryCnt][iStr->first.c_str()] = iStr->second.c_str();
					}


					nAccessoryCnt++;
				}

				locations[nLocationCnt]["accessories"] = accessories;	

				nLocationCnt++;

			}

			err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = "get_gateway";
	response["name"] = "Getway 01";
	response["locations"] = locations;


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

