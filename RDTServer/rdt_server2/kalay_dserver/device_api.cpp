#include "../headers/unixclientstream.hpp"
#include "../headers/exception.hpp"
#include <string>
#include <iostream>
#include <string.h>
#include <unistd.h>
#include <algorithm>

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

int __getAttr(CMyObject *pObject,Json::Value& jsonAttr)
{
	int count = 0;

	map<string,int>::iterator iNum;
	map<string,string>::iterator iStr;

	jsonAttr["id"] = pObject->m_id;
	jsonAttr["type"] = pObject->m_type;

	for(iNum = pObject->m_attr_num.begin(); iNum!=pObject->m_attr_num.end(); ++iNum)
	{
		jsonAttr[iNum->first.c_str()] = iNum->second;
		count++;
	}

	for(iStr = pObject->m_attr_str.begin(); iStr!=pObject->m_attr_str.end(); ++iStr)
	{
		jsonAttr[iStr->first.c_str()] = iStr->second.c_str();
		count++;
	}

	return count;
}

int __getAbout(CMyObject *pObject,Json::Value& jsonAbout)
{
	int count = 0;

	map<string,int>::iterator iNum;
	map<string,string>::iterator iStr;

	for(iNum = pObject->m_about_num.begin(); iNum!=pObject->m_about_num.end(); ++iNum)
	{
		jsonAbout[iNum->first.c_str()] = iNum->second;
	}

	for(iStr = pObject->m_about_str.begin(); iStr!=pObject->m_about_str.end(); ++iStr)
	{
		jsonAbout[iStr->first.c_str()] = iStr->second.c_str();
	}
	

	return count;
}

int __getSubObjects(CMyObject *pObject,Json::Value& subObjects)
{
	list<CMyObject*>::iterator iter;
	map<string,int>::iterator iNum;
	map<string,string>::iterator iStr;	
	int cntSubObject = 0;

	for(iter = pObject->m_listObject.begin(); iter!=pObject->m_listObject.end(); ++iter)
	{
		CMyObject *pSubObject;

		pSubObject = *iter;


		__getAttr(pSubObject,subObjects[cntSubObject]);


		cntSubObject++;
	}


	return cntSubObject;
}


// Implemente API functions -----------------------------

void deviceapi_get_gateway_about (int session,Json::Value &request)
{

	Json::Value root;
	Json::Value response;
	unsigned int rdt_ticket = 0;
	int rc;
	int err = 1;
	string err_str;


	response["uid"] = (char*) __myUID;
	response["api"] = "get_gateway_about";


	try {
		CMyObject *pGateway;

		rdt_ticket = request["rdt_ticket"].asUInt();

		pGateway  = __allObjects.m_mapAllObjects[__allObjects.m_idGateway];
		

		if ( pGateway != NULL )
		{
			__getAbout(pGateway,response);
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

			__getAbout(pAccessory,response);


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

			//accessoryType = pAccessory->m_attr_num["type"];	
	
			if ( pObject->m_pLocation != NULL ) 
			{
				location["id"] = pObject->m_pLocation->m_id;
				location["name"] = pObject->m_pLocation->m_attr_str["name"];

				response["location"] = location;
			}

			__getAttr(pObject,response);



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

printf("get_accessory_detail:\n%s\n------------------\n",(char*)root.toStyledString().c_str());

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
	int err = 1;
	string err_str;		


	rdt_ticket = request["rdt_ticket"].asUInt();

	try {
			TAllObjectMap::iterator p;
			list<CMyObject*>::iterator j;
			int nAccessoryCnt = 0;


			for(p = __allObjects.m_mapAllObjects.begin(); p!=__allObjects.m_mapAllObjects.end(); ++p)
			{
				CMyObject *pObject;

				
				pObject = (CMyObject*) p->second;

				if ( pObject->m_pGroup == NULL && pObject->m_attr_num["type"] == 0 ) // FixMe if light type is 0
				{
					objects[nAccessoryCnt]["id"] =  pObject->m_id,
					objects[nAccessoryCnt]["name"] =  pObject->m_attr_str["name"].c_str();
				}


				nAccessoryCnt++;

			}

			err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = "get_group_free_lights";
	response["objects"] = objects;


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
	

	


	response["uid"] = (char*) __myUID;;
	response["api"] = "set_detail";

	rdt_ticket = request["rdt_ticket"].asUInt();
	id = request["id"].asUInt();


	try {
		CMyObject *pObject = NULL;

		pObject = __allObjects.m_mapAllObjects[id];


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
		    		
		    		if ( request["on"].asInt() == 0 )
		    			objects[0]["on"] = 0;
		    		else
		    			objects[0]["on"] = 1;

		    		__ipHub.fwapi_set(objects);
				}


			}

			// Change Value ---


			//accessoryType = pAccessory->m_attr_num["type"];	
						
			if ( pObject->m_pLocation != NULL ) 
			{
				location["id"] = pObject->m_pLocation->m_id;
				location["name"] = pObject->m_pLocation->m_attr_str["name"];

				response["location"] = location;
			}
			
			
			__getAttr(pObject,response);

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


	printf("set_detail:\n%s\n-------------------\n",(char*)root.toStyledString().c_str());

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
	int err = 1;
	string err_str;		
	unsigned int idRemove;



	rdt_ticket = request["rdt_ticket"].asUInt();


	idRemove = request["id"].asUInt();

	try {
		TAllObjectMap::iterator iterRemove;
		CMyObject *pObject = NULL;

		iterRemove = __allObjects.m_mapAllObjects.find(idRemove);
		if ( iterRemove != __allObjects.m_mapAllObjects.end() ) // Found it
		{
			pObject = iterRemove->second;

			__allObjects.m_mapAllObjects.erase(iterRemove);


			if ( pObject->m_pLocation != NULL )
			{
				CLocation *pLocation;
				list<CMyObject*>::iterator iter2;

				pLocation = pObject->m_pLocation ;

				iter2 = std::find(pLocation->m_listObject.begin(), pLocation->m_listObject.end(), pObject);
				if ( iter2 != pLocation->m_listObject.end() )
				{
					pLocation->m_listObject.erase(iter2);
				}
			}

			if ( pObject->m_pGroup != NULL )
			{
				CGroup *pGroup;
				list<CMyObject*>::iterator iter2;

				pGroup = pObject->m_pGroup;
				iter2 = std::find(pGroup->m_listObject.begin(), pGroup->m_listObject.end(), pObject);
				if ( iter2 != pGroup->m_listObject.end() )
				{
					pGroup->m_listObject.erase(iter2);
				}
			}

			if ( pObject->m_pWallSwitch != NULL )
			{
				CWallSwitch *pWallSwitch;
				list<CMyObject*>::iterator iter2;

				pWallSwitch = pObject->m_pWallSwitch;
				iter2 = std::find(pWallSwitch->m_listObject.begin(), pWallSwitch->m_listObject.end(), pObject);
				if ( iter2 != pWallSwitch->m_listObject.end() )
				{
					pWallSwitch->m_listObject.erase(iter2);
				}
			}

			delete pObject;
		}

		err = 0;
    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = "remove";
	response["id"] = idRemove;


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

					__getAttr(pObject,accessories[nAccessoryCnt]);

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

printf("get_gateway:\n%s\n----------\n",(char*)root.toStyledString().c_str());

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


void deviceapi_get_detail_of_group(int session,Json::Value &request,int idGroup)
{
	Json::Value root;
	Json::Value response;
	Json::Value responseObjects;

	int rc;					
	unsigned int rdt_ticket = 0;	
	int err = 1;
	string err_str;	

	try {
			CGroup *pGroup;
			list<CMyObject*>::iterator iter;

			rdt_ticket = request["rdt_ticket"].asUInt();
printf("eddy test GroupID :%d\n",idGroup);

			pGroup = (CGroup*) __allObjects.m_mapAllGroups[idGroup];

			if ( pGroup != NULL )
			{
printf("eddy test GroupID :%d %s\n",idGroup,pGroup->m_name.c_str());				
				
				__getSubObjects(pGroup,responseObjects);
				// Attributes of Group

				__getAttr(pGroup,response);
			}

			err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = "get_detail";

	response["objects"] = responseObjects;




	root["error"] = err;
	if ( err_str.length() != 0 )
		root["error_str"] = err_str;
	root["response"] = response;



printf("deviceapi_get_detail_of_group\n%s\n-------------------\n",(char*)root.toStyledString().c_str());


	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{
		
	}	


	return;
}


void deviceapi_get_detail_of_object(int session,Json::Value &request,int idObject)
{
	Json::Value root;
	Json::Value response;
	Json::Value responseObjects;

	int rc;					
	unsigned int rdt_ticket = 0;	
	int err = 1;
	string err_str;	

	try {
			CMyObject *pObject;
			list<CMyObject*>::iterator iter;

			rdt_ticket = request["rdt_ticket"].asUInt();


			pObject = (CMyObject*) __allObjects.m_mapAllObjects[idObject];

			if ( pObject != NULL )
			{
				map<string,int>::iterator iNum;
				map<string,string>::iterator iStr;	

				
				response["id"] = pObject->m_id;

				__getAttr(pObject,response);


				if ( pObject->m_listObject.size() > 0 )
				{
					__getSubObjects(pObject,responseObjects);
				}
			}

			err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = "get_detail";

	response["objects"] = responseObjects;




	root["error"] = err;
	if ( err_str.length() != 0 )
		root["error_str"] = err_str;
	root["response"] = response;


printf("deviceapi_get_detail_of_object\n%s\n-------------------\n",(char*)root.toStyledString().c_str());


	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{
		
	}	


	return;
}


void deviceapi_get_detail (int session,Json::Value &request)
{
//+++

	unsigned int id;
	int ntype;


	

	id = request["id"].asUInt();

	ntype = id & 0xff000000;

	if ( ntype == IDTYPE_ACCESSORY )
	{
		deviceapi_get_detail_of_object(session,request,id);
	}
	else if ( ntype == IDTYPE_GROUP )
	{
		deviceapi_get_detail_of_group(session,request,id);
	}
	else if ( ntype == IDTYPE_LOCATION )
	{
		deviceapi_get_detail_of_object(session,request,id);
	}
	else if ( ntype == IDTYPE_GATEWAY )
	{
		deviceapi_get_detail_of_object(session,request,id);;
	}



	return;
}

void deviceapi_get_other_groups (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value groups;

	int rc;					
	unsigned int rdt_ticket;	
	int err = 1;
	string err_str;
	unsigned int idGroup;


	rdt_ticket = request["rdt_ticket"].asUInt();

	idGroup = request["id"].asUInt();
//++++

	try {
		TAllObjectMap::iterator p;
		list<CMyObject*>::iterator j;
		int nGroupCnt = 0;


		for(p = __allObjects.m_mapAllGroups.begin(); p!=__allObjects.m_mapAllGroups.end(); ++p)
		{
			CGroup *pGroup;
			
			pGroup = (CGroup*) p->second;

			if ( (unsigned int) pGroup->m_id != idGroup )
			{
				groups[nGroupCnt]["id"] =  pGroup->m_id,
				groups[nGroupCnt]["name"] =  pGroup->m_attr_str["name"].c_str();

				nGroupCnt++;
			}
		}

		err = 0;
    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = "get_other_groups";
	response["objects"] = groups;


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

//void deviceapi_set_detail (int session,Json::Value &request)


void deviceapi_add_an_accessory_to_group (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value object;

	Json::Value response;
	Json::Value responseGroups;

	int rc;					
	unsigned int rdt_ticket;	
	int err = 1;
	string err_str;
	unsigned int idGroup = 0;
	unsigned int idAccessory = 0;		

	rdt_ticket = request["rdt_ticket"].asUInt();

	try {
		CGroup *pGroup;

		idGroup = request["id"].asUInt();

		object = request["object"];
		idAccessory = object["id"].asUInt();

		pGroup = (CGroup*) __allObjects.m_mapAllGroups[idGroup];
		if ( pGroup != NULL )
		{
			CMyObject *pObject;

			pObject = __allObjects.m_mapAllObjects[idAccessory];

			if ( pObject != NULL )
			{
				pGroup->add(pObject);
			}
		}

		err = 0;
    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = "add_an_accessory_to_group";
	response["id"] = idGroup;


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

// ++++
	Json::Value root;
	Json::Value response;
	Json::Value locations;

	int rc;					
	unsigned int rdt_ticket;	
	int err = 1;
	string err_str;


	rdt_ticket = request["rdt_ticket"].asUInt();



	try {
			TAllObjectMap::iterator p;
			list<CMyObject*>::iterator j;
			int nLocationCnt = 0;


			for(p = __allObjects.m_mapAllLocations.begin(); p!=__allObjects.m_mapAllLocations.end(); ++p)
			{
				CLocation *pLocation;

				
				pLocation = (CLocation*) p->second;


				locations[nLocationCnt]["id"] =  pLocation->m_id,
				locations[nLocationCnt]["name"] =  pLocation->m_attr_str["name"].c_str();
				locations[nLocationCnt]["is_editable"] = true;


				nLocationCnt++;

			}

			err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = "get_locations";
	response["objects"] = locations;


	root["error"] = err;
	if ( err_str.length() != 0 )
		root["error_str"] = err_str;
	root["response"] = response;

// ----

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_add_accessories_to_location (int session,Json::Value &request)
{
// +++
	Json::Value root;
	Json::Value response;
	CLocation *pLocation = NULL;
	string strLocationName;
	Json::Value objects;
	Json::Value responseObjects;


	unsigned int rdt_ticket;
	int err = 1;
	string err_str;

	int idLocation;	
	int rc;
	int i;
	int idAccessory;
	


	rdt_ticket = request["rdt_ticket"].asUInt();


	idLocation = request["id"].asUInt();

	objects = request["objects"];


	strLocationName = request["name"].asString();

	// location
	try {

		pLocation =  (CLocation *)__allObjects.m_mapAllLocations[idLocation];  // FixMe: We should check it first

		

		for(i=0;i<(int)objects.size();i++)
		{
			CMyObject *pObject = NULL;

			idAccessory = objects[i]["id"].asUInt();

			pObject = __allObjects.m_mapAllLocations[idAccessory];

			if ( pObject != NULL )
			{
				//pObject->m_pLocation = pLocation;
				pLocation->add(pObject);
			}

			responseObjects[i]["id"] = idAccessory;
		}

		err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = "add_accessories_to_location";

	response["id"] = idLocation;
	response["objects"] = responseObjects;

 
	root["error"] = err;
	if ( err_str.length() != 0 )
		root["error_str"] = err_str;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,(char*)root.toStyledString().c_str());


	if ( rc < 0 )
	{

	}

// ---

	return;
}

void deviceapi_set_a_location (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	CLocation *pLocation = NULL;
	string strLocationName;


	unsigned int rdt_ticket;
	int err = 1;
	string err_str;

	int id;	
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();


	id = request["id"].asUInt();


	strLocationName = request["name"].asString();

	// location
	try {

		pLocation =  (CLocation *)__allObjects.m_mapAllLocations[id];  // FixMe: We should check it first

		if ( pLocation == NULL )
		{
			pLocation = new CLocation(__allObjects.getID(IDTYPE_LOCATION),strLocationName.c_str()); 

			

			__allObjects.m_mapAllObjects[pLocation->m_id] = pLocation;
			__allObjects.m_mapAllLocations[pLocation->m_id] = pLocation;
		}
		else
		{
			pLocation->m_name = strLocationName;
			pLocation->m_attr_str["name"] = strLocationName;
		}

			err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = "set_a_location";

	response["id"] = id;
	response["name"] = strLocationName;


 
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

void deviceapi_remove_locations (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int err = 1;
	string err_str;

	int rc;
	int i;
	int id;


	rdt_ticket = request["rdt_ticket"].asUInt();
	objects = request["objects"];


	// location
	try {

		for(i=0;i<(int)objects.size();i++)
		{
			TAllObjectMap::iterator it;
			CLocation *pLocation = NULL;

			id = objects[i]["id"].asUInt();

			it = __allObjects.m_mapAllObjects.find(id);
			if ( it != __allObjects.m_mapAllObjects.end() ) // Found it
			{
				pLocation = (CLocation *)it->second;
				__allObjects.m_mapAllObjects.erase(it);
			}

			it = __allObjects.m_mapAllLocations.find(id);
			if ( it != __allObjects.m_mapAllLocations.end() ) // Found it
			{
				__allObjects.m_mapAllObjects.erase(it);
			}

			if ( pLocation != NULL )
			delete pLocation;
		}		

		err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }




	response["api"] = "remove_locations";

	
 
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


	response["api"] = "get_accessory_setting";

	

 
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

void deviceapi_get_switches (int session,Json::Value &request)
{
//+++
	Json::Value root;
	Json::Value response;
	Json::Value responseObjects;
	unsigned int rdt_ticket;
	int rc;
	int id;
	int err = 1;
	string err_str;	


	rdt_ticket = request["rdt_ticket"].asUInt();

	id = request["id"].asUInt();

	printf("get_switches id :%d \n",id);


	try {
		CMyObject *pAccessory = __allObjects.m_mapAllObjects[id];
		
		// pAccessory->m_attr_num["type"] == 0x0101 - physical wireless wall switch
		if ( pAccessory != NULL )
		{
			map<string,int>::iterator iNum;
			map<string,string>::iterator iStr;

			//response["type"] = pAccessory->m_attr_num["type"];

			__getAttr(pAccessory,response);

			__getSubObjects(pAccessory,responseObjects);

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


	response["uid"] = (char*) __myUID;;
	response["api"] = "get_switches";
	response["id"] = id;
	response["objects"] = responseObjects;


	root["error"] = err;
	if ( err_str.length() != 0 )
		root["error_str"] = err_str;

	root["response"] = response;


printf("get_switches:\n%s\n----------------\n",(char*)root.toStyledString().c_str());

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



void deviceapi_api_not_found (int session,Json::Value &request)
{
	Json::Value root;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;
	string api;
	string err_str;
	int err = 0;


	rdt_ticket = request["rdt_ticket"].asUInt();
	api = request["api"].asString();

	// group


	response["uid"] = (char*) __myUID;
	response["api"] = api.c_str();
	//response["objects"] = objects;

	err = -2;
	err_str = "api not found";


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
