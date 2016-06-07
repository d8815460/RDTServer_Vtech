
#include "../headers/exception.hpp"
#include <string.h>
#include <unistd.h>

#include <json/json.h>

#include <string>

#include "dserver.h"
#include "device_api.h"

#include "dserver.h"
#include "dtable.h"


#include "fw_api.h"



int CVtechIPHub::parser(Json::Value& root)
{
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


	printf("test received : error:%d isLast:%d seq_no:%d  objects:%d \n",error,isLast,seqNo,objects.size());




{
	CTXRecord *txRecord;

	txRecord = m_txQueue[seqNo];

	if ( txRecord != NULL )
	{

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

						printf(" found object %s ",pObject->m_attr_str["name"].c_str());
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
							pObject = new CAccessory(__allObjects.getID(IDTYPE_ACCESSORY),"IP-Hub power outlet",unitType,__allObjects.getLocationOther());
						}
						else  if ( unitType == 0x0109 ) // Light bulb
						{
							pObject = new CLightBulb("IP-Hub Light",__allObjects.getLocationOther(),NULL);	
						}
						else if ( unitType == 0x0201 )  // garage sensor (door)
						{
							pObject = new CMyObject("sensor",__allObjects.getID(IDTYPE_ACCESSORY),"IP-Hub Garage sensor",unitType);
						}
						else if ( unitType == 0x0202 ) // Magnetic sensor
						{
							pObject = new CMyObject("sensor",__allObjects.getID(IDTYPE_ACCESSORY),"IP-Hub Magnetic sensor",unitType);
						}
						else if ( unitType == 0x0203 ) // motion sensor
						{
							pObject = new CMyObject("sensor",__allObjects.getID(IDTYPE_ACCESSORY),"IP-Hub Motion sensor",unitType);
						}
						else if ( unitType == 0x0206 ) // flood detector 
						{
							pObject = new CMyObject("sensor",__allObjects.getID(IDTYPE_ACCESSORY),"IP-Hub Flood detector",unitType);
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





	return 1;
}