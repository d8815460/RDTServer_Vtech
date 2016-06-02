
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
			string id;

			if ( aObj["id"].isString() )
			{

				id = aObj["id"].asString();


				printf("ID:%s\n",id.c_str());

				if ( id == "0" ) // __GATEWAY__
				{
					CGateway *pGateway = (CGateway *)__allObjects.m_mapAllObjects[__allObjects.m_idGateway];

					if ( pGateway == NULL )
					{
						pGateway = new CGateway(__allObjects.getID(IDTYPE_GATEWAY),"V-Tech IP-Hub"); //GateWay

						__allObjects.m_mapAllObjects[pGateway->m_id] = pGateway;
						__allObjects.m_idGateway = pGateway->m_id;								
					}


					for(itrAttr=aObj.begin();itrAttr != aObj.end(); itrAttr++)
					{
						Json::Value key = itrAttr.key();
						Json::Value value = (*itrAttr);

						if ( 	key != "id" 
							 && key != "led" ) // FixMe
						{
							printf("Gateway Set key : %s  = %s \n",key.asString().c_str(),value.asString().c_str());	

							if ( value.isString() )
								pGateway->m_attr_str[key.asString().c_str()] = value.asString();
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



						pObject = new CLightBulb(__allObjects.getID(IDTYPE_ACCESSORY),"IP-Hub Light",__allObjects.getLocationOther(),NULL);

						pObject->m_about_str["udid"] = id;	


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
							else
							{
								printf("Obj Set key : %s  = %d (num) \n",key.asString().c_str(),value.asUInt());	
								pObject->m_attr_num[key.asString().c_str()] = value.asUInt();
							}
								
						}
						
					}
				}
			}
		}
	}





	return 1;
}