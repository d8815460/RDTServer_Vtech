#include "../headers/exception.hpp"
#include <iostream>
#include <string.h>
#include <unistd.h>

#include <json/json.h>

#include <algorithm>
#include <string>
#include <iomanip> 


#include "dserver.h"
#include "dtable.h"
#include "device_api.h"

#include "fw_api.h"


using namespace std;

int sendto_rdt_client (int session,unsigned int rdt_ticket,Json::Value& root)
{
	unsigned char szBuff[1024*32];
	int send_length;
	int option_len = 0;
	int rc;
	int data_length;

	Json::FastWriter fastWriter;
	std::string strSendOut;



	strSendOut = fastWriter.write(root);


	data_length  = strSendOut.length();



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
	memcpy(&szBuff[6+option_len],strSendOut.c_str(),data_length);
	send_length = 6+option_len+data_length;
		


	//printf("Dump RDT json: \n%s\n",payload.c_str());

	rc =  RDT_Write(__rdt_cnnt[session].rdt_id,(char*)szBuff,send_length); 

	if ( rc < 0 )
	{
		
	}

	return rc;

}


int __getBaseAttr(CMyObject *pObject,Json::Value& jsonAttr)
{
	int count = 0;

	map<string,int>::iterator iNum;
	map<string,string>::iterator iStr;

	jsonAttr["id"] = pObject->m_id;
	jsonAttr["type"] = pObject->m_type;

	jsonAttr["name"] 	= pObject->m_attr_str["name"];
	jsonAttr["icon"] 	= pObject->m_attr_num["icon"];
	jsonAttr["trigger"] = pObject->m_attr_num["trigger"];
	jsonAttr["alert"] = pObject->m_attr_num["alert"];
	jsonAttr["on"] 		= pObject->m_attr_num["on"];


	return count;
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

	jsonAbout["type"] = pObject->m_type;

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
void deviceapi_get_about (int session,Json::Value &request)
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
	response["api"] = "get_about";

	id = request["id"].asUInt();

	printf("get_about id :%d \n",id);


	try {
		if ( id == 0 ) // Get gateway about
		{
			CMyObject *pGateway;

			pGateway  = __allObjects.getGateway();
			
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
		}
		else
		{
			CMyObject *pAccessory = __allObjects.getObjectByID(id);
			
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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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
			std::map<unsigned int, CMyObject *>::iterator p;
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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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
	
printf("set_detail request:\n%s\n-------------------\n",(char*)request.toStyledString().c_str());
	


	response["uid"] = (char*) __myUID;;
	response["api"] = "set_detail";

	rdt_ticket = request["rdt_ticket"].asUInt();
	id = request["id"].asUInt();


	try {
		CMyObject *pObject = NULL;

		pObject = __allObjects.getObjectByID(id);


		if ( pObject != NULL )
		{
			map<string,int>::iterator iNum;
			map<string,string>::iterator iStr;
			//int accessoryType;


			// Change Value +++
			{
				Json::ValueIterator itr;
				Json::Value fwObjects;
				int nfwObjectCnt = 0;
				int valueChanged = 0;

				for(itr=request.begin();itr != request.end(); itr++)
				{
					Json::Value key = itr.key();
					Json::Value value = (*itr);

					valueChanged = 0;

					if ( 	key.asString() != "api"
						 && key.asString() != "id"
						 && key.asString() != "type"
						 && key.asString() != "rdt_ticket"
						 && key.asString() != "uid"			)
					{
						valueChanged = 0;

						if ( key.asString() == "location" )
						{ //#Fix Me
							int idLocation;
							

							printf("Set key : %s  ",key.asString().c_str());


							idLocation = value["id"].asUInt();
							printf("eddy test location ID : %d \n",idLocation);


							if (    pObject->m_pLocation == NULL 
								 || pObject->m_pLocation->m_id != idLocation)
							{
								CLocation *newLocation;

								newLocation = __allObjects.getLocationByID(idLocation);
								if ( newLocation != NULL )
								{
									newLocation->add(pObject);
								}

							}

						}
						else
						{
							printf("Set key : %s  ",key.asString().c_str());

							
							if ( value.isNumeric() )
								printf("value:%d \n",value.asInt());
							else  // if ( value.isString() )
								printf("value:%s \n",value.asString().c_str());


							if ( value.isNumeric() )
							{
								if ( pObject->m_attr_num[key.asString().c_str()] !=  value.asInt() )
								{
									pObject->m_attr_num[key.asString().c_str()] = value.asInt();
									valueChanged = 1;
								}								
							}
							else // if ( value.isString() )
							{
								if ( pObject->m_attr_str[key.asString().c_str()] != value.asString() )
								{
									pObject->m_attr_str[key.asString().c_str()] = value.asString();
									valueChanged = 1;
								}
							}
						}



						if ( 	 valueChanged != 0
						     &&  key.asString() != "name"	
						     &&  key.asString() != "location"	)
						{
							if ( value.isNumeric() )
								fwObjects[nfwObjectCnt][key.asString().c_str()] = value.asInt();// #TBD : if we only send change items
							else // if ( value.isString() )
								fwObjects[nfwObjectCnt][key.asString().c_str()] = value.asString();// #TBD : if we only send change items
						}
					}
				}


				// Set to FW
				{
		    		

		    		if ( pObject->m_fwid.length() > 0 )
		    		{
		    			int seq = 0;

			    		fwObjects[nfwObjectCnt]["id"] = pObject->m_fwid; 


			    		seq = __ipHub.fwapi_set(fwObjects);

			    		if ( seq > 0 )
			    		{
			    			CTXRecord *txRecord = new CTXRecord();

			    			txRecord->seq = seq;
			    			txRecord->session = session;
							txRecord->request = request;
							//txRecord->response
							txRecord->sendTime = time(NULL);

							__ipHub.m_txQueue[seq] = txRecord;
			    		}
		    		}
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

	rc = sendto_rdt_client(session,rdt_ticket,root);

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
	Json::Value responseID;

	unsigned int rdt_ticket;
	int rc;
	int err = 1;
	string err_str;		



	rdt_ticket = request["rdt_ticket"].asUInt();


	try {
		Json::Value removeObject;

		removeObject = request["id"];

		if ( removeObject.isArray() )
		{
			unsigned int i;
			int removeCnt = 0;


			for(i=0;i<removeObject.size();i++)
			{
				err = __allObjects.removeByID(removeObject[i].asUInt());

				responseID[removeCnt] = removeObject[i].asUInt();

				removeCnt++;
			}
		}
		else 
		{
			err = __allObjects.removeByID(removeObject.asUInt());
			responseID = removeObject.asUInt();
		}

		if ( err != 0 )
		{

		}

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = "remove";
	response["id"] = responseID;


	root["error"] = err;
	if ( err_str.length() != 0 )
		root["error_str"] = err_str;
	root["response"] = response;


	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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
			std::map<unsigned int, CMyObject *>::iterator p;
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

					__getBaseAttr(pObject,accessories[nAccessoryCnt]);

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


	rc = sendto_rdt_client(session,rdt_ticket,root);

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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


	if ( rc < 0 )
	{

	}

	return;
}


void __get_detail_of_group(int session,Json::Value &request,int idGroup)
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

			pGroup = (CGroup*) __allObjects.m_mapAllGroups[idGroup];

			if ( pGroup != NULL )
			{
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
	response["id"] = idGroup;

	response["objects"] = responseObjects;




	root["error"] = err;
	if ( err_str.length() != 0 )
		root["error_str"] = err_str;
	root["response"] = response;



printf("deviceapi_get_detail_of_group\n%s\n-------------------\n",(char*)root.toStyledString().c_str());


	rc = sendto_rdt_client(session,rdt_ticket,root);


	if ( rc < 0 )
	{
		
	}	


	return;
}



void __get_detail_of_object(int session,Json::Value &request,int idObject)
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


			pObject = (CMyObject*) __allObjects.getObjectByID(idObject);

			if ( pObject != NULL )
			{
				map<string,int>::iterator iNum;
				map<string,string>::iterator iStr;	

				
				response["id"] = pObject->m_id;

				__getAttr(pObject,response);


				if ( pObject->m_pLocation != NULL ) 
				{
					Json::Value location;

					location["id"] = pObject->m_pLocation->m_id;
					location["name"] = pObject->m_pLocation->m_attr_str["name"];

					response["location"] = location;
				}	
				

				if ( pObject->m_pGroup != NULL ) 
				{
					Json::Value group;

					group["id"] = pObject->m_pGroup->m_id;
					group["name"] = pObject->m_pGroup->m_attr_str["name"];

					response["group"] = group;
				}	


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
	response["id"] = idObject;

	response["objects"] = responseObjects;




	root["error"] = err;
	if ( err_str.length() != 0 )
		root["error_str"] = err_str;
	root["response"] = response;


printf("deviceapi_get_detail_of_object\n%s\n-------------------\n",(char*)root.toStyledString().c_str());


	rc = sendto_rdt_client(session,rdt_ticket,root);


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
	string err_str;


	try {
		id = request["id"].asUInt();

		ntype = id & 0xff000000;

		if ( ntype == IDTYPE_GROUP )
		{
			__get_detail_of_group(session,request,id);
		}
		else if ( ntype == IDTYPE_ACCESSORY )
		{
			__get_detail_of_object(session,request,id);
		}
		else if ( ntype == IDTYPE_LOCATION )
		{
			__get_detail_of_object(session,request,id);
		}
		else if ( ntype == IDTYPE_GATEWAY )
		{
			__get_detail_of_object(session,request,id);;
		}
		//else if ( ntype == IDTYPE_SWITCH )
		//{
		//	deviceapi_get_detail_of_switch(session,request,id);;
		//}	
		else
		{
			__get_detail_of_object(session,request,id);;	
		}

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
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
		std::map<unsigned int, CMyObject *>::iterator p;
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


	rc = sendto_rdt_client(session,rdt_ticket,root);


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

			pObject = __allObjects.getObjectByID(idAccessory);

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


	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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
			std::map<unsigned int, CMyObject *>::iterator p;
			list<CMyObject*>::iterator j;
			int nLocationCnt = 0;


printf("eddy test count:%d \n",__allObjects.m_mapAllLocations.size());
			for(p = __allObjects.m_mapAllLocations.begin(); p!=__allObjects.m_mapAllLocations.end(); ++p)
			{
				CLocation *pLocation;

				
				pLocation = (CLocation*) p->second;
printf("eddy test *************** id:%x  %p\n",p->first ,pLocation);

				__getAttr(pLocation,locations[nLocationCnt]);

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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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
		std::map<unsigned int, CMyObject *>::iterator iterFind;


		iterFind = __allObjects.m_mapAllLocations.find(id);



		if ( iterFind == __allObjects.m_mapAllLocations.end() )
		{
			pLocation = new CLocation(strLocationName.c_str()); 

			pLocation->m_attr_num["editable"] = 1;



		}
		else
		{
			pLocation = (CLocation*) iterFind->second;

			if ( pLocation->m_attr_num["editable"] != 0 )
			{
				pLocation->m_name = strLocationName;
				pLocation->m_attr_str["name"] = strLocationName;
			}

		}

		err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }

	response["uid"] = (char*) __myUID;
	response["api"] = "set_a_location";

	response["id"] = pLocation->m_id;
	response["name"] = strLocationName;


 
	root["error"] = err;
	if ( err_str.length() != 0 )
		root["error_str"] = err_str;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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
	response["api"] = "get_gateway_setting";
	response["home"] = "appl";
	response["led"] = 0;
	
	response["objects"] = objects;

 
	root["error"] = 0;
	root["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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
		CMyObject *pAccessory = __allObjects.getObjectByID(id);
		
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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


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

	rc = sendto_rdt_client(session,rdt_ticket,root);


	if ( rc < 0 )
	{

	}
	
	return;
}
