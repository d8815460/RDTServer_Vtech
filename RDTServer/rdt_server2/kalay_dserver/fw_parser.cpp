
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

#include "dtable.h"


#include "fw_api.h"



int CVtechIPHub::parser(Json::Value& root)
{
	std::string recv_json;
	Json::Value objects;
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

	objects = root["objects"];

	printf("test received : error:%d isLast:%d seq_no:%d  objects:%d \n",error,isLast,seqNo,objects.size());

			// Change Value +++
			{
				Json::ValueIterator itrObj;

				for(itrObj=objects.begin();itrObj != objects.end(); itrObj++)
				{
					Json::ValueIterator itrAttr;
					Json::Value aObj = (*itrObj);
					string id;

					if ( aObj["id"].isString() )
					{

						id = aObj["id"].asString();


						printf("ID:%s\n",id.c_str());

						if ( id == "0" ) // __GATEWAY__
						{
							CMyObject *pGateway = __allObjects.m_mapAllObjects[__allObjects.m_idGateway];



							if ( pGateway == NULL )
							{
								pGateway = new CAccessory(__allObjects.getID(IDTYPE_GATEWAY),"V-Tech IP-Hub",0xff00); //GateWay

	
								pGateway->m_about_num["on"] = 1;
								pGateway->m_about_str["mac_address"] = "00:0c:29:36:3f:b1",
								pGateway->m_about_str["udid"] = "udid-00001";	
								pGateway->m_about_str["firmware_version"] = "1.0.0";
								pGateway->m_about_str["hardware_version"] = "1.0.1";
								pGateway->m_about_str["ip_address"] = "192.168.1.12";
								pGateway->m_about_str["subnet_mask"] = "255.255.255.0";
								pGateway->m_about_str["gateway_name"] = "V-Tech IP-Hub";	

								__allObjects.m_mapAllObjects[pGateway->m_id] = pGateway;
								__allObjects.m_idGateway = pGateway->m_id;								
							}


							for(itrAttr=aObj.begin();itrAttr != aObj.end(); itrAttr++)
							{
								Json::Value key = itrAttr.key();
								Json::Value value = (*itrAttr);

								if ( key != "id" )
								{
									printf("Gateway Set key : %s  = %s \n",key.asString().c_str(),value.asString().c_str());	

									if ( value.isString() )
										pGateway->m_attr_str[key.asString().c_str()] = value.asString();
									else if ( value.isDouble() )
										pGateway->m_attr_num[key.asString().c_str()] = value.asDouble();
									else
										pGateway->m_attr_num[key.asString().c_str()] = value.asUInt();
								}
								
							}
						}
						else
						{
							CMyObject *pObject = NULL;

							TAllObjectMap::iterator p;
							string udid;

							for(p = __allObjects.m_mapAllObjects.begin(); p!=__allObjects.m_mapAllObjects.end(); ++p)
							{
								if ( p->second->m_about_str["udid"] == id.c_str()  )
								{ // Found it 
									pObject = p->second;
									printf(" found object %s ",pObject->m_attr_str["name"].c_str());
									break;
								}
							}

							if ( pObject == NULL )
							{
								//CLocation *pLocation = (CLocation*)__allObjects.m_mapAllObjects[0x13000001]; // Find location
								printf("New device \n");

								pObject = new CAccessory(__allObjects.getID(IDTYPE_ACCESSORY),"IP-Hub Light",0x0109);

								pObject->m_attr_num["on"] = 1;
								pObject->m_attr_num["icon"] = 0;
								pObject->m_attr_num["trigger"] = 0;


							    pObject->m_attr_num["color_hue"] = 23;
							    pObject->m_attr_num["color_saturation"] = 50;
							    pObject->m_attr_num["color_brightness"] = 50;
							    pObject->m_attr_num["white_brightness"] = 50;
							    pObject->m_attr_num["white_temperature"] = 5000;


								pObject->m_about_str["udid"] = id;	
								pObject->m_about_str["firmware_version"] = "1.0.0";

								if ( __allObjects.getLocationOther() != NULL )		
									__allObjects.getLocationOther()->add(pObject);

								__allObjects.m_mapAllObjects[pObject->m_id] = pObject;								
							}

							

							for(itrAttr=aObj.begin();itrAttr != aObj.end(); itrAttr++)
							{
								Json::Value key = itrAttr.key();
								Json::Value value = (*itrAttr);

								if ( key != "id" )
								{
									if ( value.isString() )
									{
										printf("Obj Set key : %s  = %s (str) \n",key.asString().c_str(),value.asString().c_str());	
										pObject->m_attr_str[key.asString().c_str()] = value.asString();
										
									}
									//else if ( value.isDouble() )
									//{
									//	printf("type-double\n");
									//	pObject->m_attr_num[key.asString().c_str()] = value.asDouble();
									//}
									else
									{
										printf("Obj Set key : %s  = %s (num) \n",key.asString().c_str(),value.asString().c_str());	
										pObject->m_attr_num[key.asString().c_str()] = value.asUInt();
									}
										
								}
								
							}
						}
					}
				}
			}

/*					
					




					if ( 	key.asString() != "api"
						 && key.asString() != "id"
						 && key.asString() != "rdt_ticket"
						 && key.asString() != "uid"			)
					{

						

						if ( value.isString() )
							pObject->m_attr_str[key.asString().c_str()] = value.asString();
						else if ( value.isDouble() )
							pObject->m_attr_num[key.asString().c_str()] = value.asDouble();
						else
							pObject->m_attr_num[key.asString().c_str()] = value.asUInt();
					}
					*/
		



	return 1;
}