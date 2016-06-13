
#include "../headers/exception.hpp"
#include <string.h>
#include <unistd.h>

#include <json/json.h>

#include <iostream>
#include <string>

#include "dserver.h"
#include "device_api.h"

#include "dserver.h"
#include "dtable.h"


#include "fw_api.h"

int __getAttr(CMyObject *pObject,Json::Value& jsonAttr);
int sendto_rdt_client (int session,unsigned int rdt_ticket,Json::Value& responseRoot);
int sendto_all_client (Json::Value& responseRoot);





int CVtechIPHub::parser(Json::Value& root)
{
	CTXRecord *txRecord = NULL;
	std::string recv_json;
	Json::Value objects;
	std::string func;
	int isLast;
	int seqNo;
	int error;

	recv_json = root.toStyledString().c_str();

	printf("unixsocket receive \n%s\n---------------\n"
		,recv_json.c_str() );


	error  = root["error"].asInt();

	if ( root.isMember("last") )
		isLast   = root["last"].asInt();
	else
		isLast = 1;
	seqNo = atoi(root["seq"].asString().c_str());

	func = root["func"].asString();

	objects = root["objects"];

	if ( !objects.isArray() )
	{
		objects = root["object"];
	}


	printf("test received : error:%d isLast:%d seq_no:%d  func:%s\n objects:%d \n",error,isLast,seqNo,func.c_str(),objects.size());


	if ( func == "notify" )
	{




	}
	else
	{

		std::map<unsigned int, CTXRecord *>::iterator iterFind;

		iterFind = m_txQueue.find(seqNo);

		if ( iterFind == m_txQueue.end() )
		{

		}
		else
		{
			txRecord = iterFind->second;
		}
	}


	// Change Value +++
	{
		Json::ValueIterator itrObj;

		for(itrObj=objects.begin();itrObj != objects.end(); itrObj++)
		{
			Json::ValueIterator itrAttr;
			Json::Value aObj = (*itrObj);
			string fwid;
			unsigned int unitType;

			if ( aObj["id"].isString() )
			{

				fwid = aObj["id"].asString();
				unitType = aObj["type"].asUInt();


				printf("ID:%s\n",fwid.c_str());

				if ( fwid == "0" || unitType == 0xff00 ) // __GATEWAY__
				{
					CGateway *pGateway = __allObjects.getGateway();

					if ( pGateway == NULL )
					{
						pGateway = new CGateway(__allObjects.getID(IDTYPE_GATEWAY),"V-Tech IP-Hub"); //GateWay

						
					}


					for(itrAttr=aObj.begin();itrAttr != aObj.end(); itrAttr++)
					{
						Json::Value key = itrAttr.key();
						Json::Value value = (*itrAttr);

						if ( 	key == "ver" )
						{
							printf("Gateway Set about key : %s  = %s \n",key.asString().c_str(),value.asString().c_str());	

							if ( value.isString() )
								pGateway->m_about_str[key.asString().c_str()] = value.asString();
							else
								pGateway->m_about_num[key.asString().c_str()] = value.asInt();

						}
						else if (  	 key != "id" 
							      && key != "led" 
							 	  && key != "type" ) // FixMe
						{
							printf("Gateway Set key : %s  = %s \n",key.asString().c_str(),value.asString().c_str());	

							if ( value.isString() )
								pGateway->m_attr_str[key.asString().c_str()] = value.asString();
							else
								pGateway->m_attr_num[key.asString().c_str()] = value.asInt();
						}
						
					}
				}
				else
				{
					CMyObject *pObject = NULL;

					std::map<unsigned int, CMyObject *>::iterator p;
					std::map<std::string, CMyObject *>::iterator iterFind;

					iterFind = __allObjects.m_mapObjectsByFWID.find(fwid);
					
					if (  iterFind != __allObjects.m_mapObjectsByFWID.end() )
					{
						pObject = iterFind->second;

						printf(" found object %s \n",pObject->m_attr_str["name"].c_str());
					}
					else
					{
						//CLocation *pLocation = (CLocation*)__allObjects.m_mapAllObjects[0x13000001]; // Find location
						printf("New device type:%x \n",unitType);

						if (    unitType == 0x0101   //  wall switch
							 || unitType == 0xff01 ) //  virtual wireless wall switch
						{
							pObject = new CWallSwitch("IP-Hub WallSwitch",__allObjects.getLocationOther());	
						}
						else  if ( unitType == 0x0106 ) // power outlet
						{
							pObject = new CAccessory("IP-Hub power outlet",unitType,__allObjects.getLocationOther());
						}
						else  if ( unitType == 0x0109 ) // Light bulb
						{
							pObject = new CLightBulb("IP-Hub Light",__allObjects.getLocationOther(),NULL);	
						}
						else if ( unitType == 0x0201 )  // garage sensor (door)
						{
							pObject = new CSensor("IP-Hub Garage sensor",unitType,__allObjects.getLocationOther());
						}
						else if ( unitType == 0x0202 ) // Magnetic sensor
						{
							pObject = new CSensor("IP-Hub Magnetic sensor",unitType,__allObjects.getLocationOther());
						}
						else if ( unitType == 0x0203 ) // motion sensor
						{
							pObject = new CSensor("IP-Hub Motion sensor",unitType,__allObjects.getLocationOther());
						}
						else if ( unitType == 0x0206 ) // flood detector 
						{
							pObject = new CSensor("IP-Hub Flood detector",unitType,__allObjects.getLocationOther());
						}
						else // if 
						{
							pObject = new CLightBulb("IP-Hub Light",__allObjects.getLocationOther(),NULL);		
						}


						pObject->m_fwid = fwid;	

						__allObjects.m_mapObjectsByFWID[fwid] = pObject;
					}

					

					for(itrAttr=aObj.begin();itrAttr != aObj.end(); itrAttr++)
					{
						Json::Value key = itrAttr.key();
						Json::Value value = (*itrAttr);

						if ( 	key == "ver" )
						{
							if ( value.isString() )
							{
								printf("Obj Set key : %s  = %s (str) \n",key.asString().c_str(),value.asString().c_str());	
								pObject->m_about_str[key.asString().c_str()] = value.asString();
								
							}
							else
							{
								printf("Obj Set key : %s  = %d (num) \n",key.asString().c_str(),value.asInt());	
								pObject->m_about_num[key.asString().c_str()] = value.asInt();
							}

						}
						else if ( 	key == "alert" )
						{
							printf("Obj Set key : %s  = %d (num) \n",key.asString().c_str(),value.asInt());	
							pObject->m_attr_num["trigger"] = value.asInt();
							pObject->m_attr_num["alert"] = value.asInt();
						}
						else if ( 	key != "id" 
							 && key != "type")
						{
							if ( value.isString() )
							{
								printf("Obj Set key : %s  = %s (str) \n",key.asString().c_str(),value.asString().c_str());	
								pObject->m_attr_str[key.asString().c_str()] = value.asString();
								
							}
							else
							{
								printf("Obj Set key : %s  = %d (num) \n",key.asString().c_str(),value.asInt());	
								pObject->m_attr_num[key.asString().c_str()] = value.asInt();
							}
						}
						
					}
				}
			}
		}
	}

	if ( txRecord != NULL )
	{
		Json::Value responseRoot;
		Json::Value response;
		Json::Value objects;
		Json::Value location;

		unsigned int rdt_ticket;
		int rc;
		unsigned int id;
		int ntype;
		int err = 1;
		string err_str;		

		//int seq;
		//int session;
		//Json::Value response;
		//Json::Value request;
		//time_t sendTime;

printf("Test TXRecord *****************\n seq:%d  session:%d\nrequest\n%s\n*****************\n\n",txRecord->seq,txRecord->session,txRecord->request.toStyledString().c_str());

		response["uid"] = (char*) __myUID;
		response["api"] = txRecord->request["api"].asString();

		rdt_ticket = txRecord->request["rdt_ticket"].asUInt();

		id = txRecord->request["id"].asUInt();

		ntype = id & 0xff000000;

		if ( ntype > 0 )
		{

		}

		try {
			CMyObject *pObject = NULL;

			pObject = __allObjects.getObjectByID(id);

			if ( pObject != NULL )
			{

				if ( pObject->m_pLocation != NULL ) 
				{
					location["id"] = pObject->m_pLocation->m_id;
					location["name"] = pObject->m_pLocation->m_attr_str["name"];

					response["location"] = location;
				}
				
				
				__getAttr(pObject,response);			

				err = 0;
			}


	    } catch (const libsocket::socket_exception& exc)
	    {
			std::cerr << exc.mesg;
			err_str = exc.mesg;
	    }


		responseRoot["error"] = err;
		if ( err_str.length() != 0 )
			responseRoot["error_str"] = err_str;
		responseRoot["response"] = response;


		rc = sendto_rdt_client(txRecord->session,rdt_ticket,responseRoot);


		if ( rc < 0 )
		{

		}

				

	}
	else if ( func == "notify" )
	{
		Json::ValueIterator itrObj;

		for(itrObj=objects.begin();itrObj != objects.end(); itrObj++)
		{
			Json::ValueIterator itrAttr;
			Json::Value aObj = (*itrObj);
			string fwid;
			unsigned int unitType;

			if ( aObj["id"].isString() )
			{

				fwid = aObj["id"].asString();
				unitType = aObj["type"].asUInt();


				printf("ID:%s\n",fwid.c_str());

				if ( fwid == "0" || unitType == 0xff00 ) // __GATEWAY__
				{

				}
				else
				{
					CMyObject *pObject = NULL;

					std::map<unsigned int, CMyObject *>::iterator p;
					std::map<std::string, CMyObject *>::iterator iterFind;

					iterFind = __allObjects.m_mapObjectsByFWID.find(fwid);
					
					if (  iterFind != __allObjects.m_mapObjectsByFWID.end() )
					{
						Json::Value responseRoot;
						Json::Value response;
						Json::Value objects;
						Json::Value location;

						//unsigned int rdt_ticket;
						int rc;
						unsigned int id;
						int ntype;
						int err = 1;
						string err_str;		


						pObject = iterFind->second;

						printf("notify found object %s \n",pObject->m_attr_str["name"].c_str());


						response["uid"] = (char*) __myUID;
						response["api"] = "notify";

						//rdt_ticket = 0;

						id = pObject->m_id;

						ntype = id & 0xff000000;

						if ( ntype > 0 )
						{

						}

						try {
							CMyObject *pObject = NULL;

							pObject = __allObjects.getObjectByID(id);

							if ( pObject != NULL )
							{

								if ( pObject->m_pLocation != NULL ) 
								{
									location["id"] = pObject->m_pLocation->m_id;
									location["name"] = pObject->m_pLocation->m_attr_str["name"];

									response["location"] = location;
								}
								
								
								__getAttr(pObject,response);			

								err = 0;
							}


					    } catch (const libsocket::socket_exception& exc)
					    {
							std::cerr << exc.mesg;
							err_str = exc.mesg;
					    }


						responseRoot["error"] = err;
						if ( err_str.length() != 0 )
							responseRoot["error_str"] = err_str;
						responseRoot["response"] = response;


						printf("notify_detail:\n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());
						rc = sendto_all_client(responseRoot);


						if ( rc < 0 )
						{

						}


					}
				}
			}
		}
	}




	return 1;
}

