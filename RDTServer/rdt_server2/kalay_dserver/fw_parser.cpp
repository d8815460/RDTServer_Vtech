
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
/***** for TPNS *****/
#include <curl/curl.h>
#include <time.h>

int sendto_rdt_client (int session,unsigned int rdt_ticket,Json::Value& responseRoot);
int sendto_all_client (Json::Value& responseRoot);
int sendto_other_client (int session,Json::Value& responseRoot);


int TPNS_alert_count=100;





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



	if ( func == "notify" )
	{
/*	printf("unixsocket receive \n%s\n---------------\n"
		,recv_json.c_str() );

	printf("test received : error:%d isLast:%d seq_no:%d  func:%s\n objects:%d \n",error,isLast,seqNo,func.c_str(),objects.size());
*/


	}
	else
	{

	printf("unixsocket receive \n%s\n---------------\n"
		,recv_json.c_str() );

	printf("test received : error:%d isLast:%d seq_no:%d  func:%s\n objects:%d \n",error,isLast,seqNo,func.c_str(),objects.size());



		std::map<unsigned int, CTXRecord *>::iterator iterFind;

		iterFind = m_txQueue.find(seqNo);

		if ( iterFind == m_txQueue.end() )
		{

		}
		else
		{
			txRecord = iterFind->second;

			m_txQueue.erase(iterFind);
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


				//printf("ID:%s\n",fwid.c_str());

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
							//printf("Gateway Set about key : %s  = %s \n",key.asString().c_str(),value.asString().c_str());	

							if ( value.isString() )
								pGateway->m_about_str[key.asString().c_str()] = value.asString();
							else
								pGateway->m_about_num[key.asString().c_str()] = value.asInt();

						}
						else if (  	 key != "id" 
							      && key != "led" 
							 	  && key != "type" ) // FixMe
						{
							//printf("Gateway Set key : %s  = %s \n",key.asString().c_str(),value.asString().c_str());	

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
					}
					else
					{
						//CLocation *pLocation = (CLocation*)__allObjects.m_mapAllObjects[0x13000001]; // Find location
						if (    unitType == 0x0101   //  wall switch
							 || unitType == 0xff01 ) //  virtual wireless wall switch
						{
							pObject = new CWallSwitch("IP-Hub WallSwitch",__allObjects.getLocationOther());	
						}
						else  if ( unitType == 0x0106 ) // power outlet
						{
							pObject = new CAccessory("IP-Hub power outlet",unitType,__allObjects.getLocationOther(),0);
						}
						else  if ( unitType == 0x0109 ) // Light bulb
						{
							pObject = new CLightBulb("IP-Hub Light",__allObjects.getLocationOther(),NULL);	
						}
						else if ( unitType == 0x0201 )  // garage sensor (door)
						{
							pObject = new CSensor("IP-Hub Garage sensor",unitType,__allObjects.getLocationOther(),3);
						}
						else if ( unitType == 0x0202 ) // Magnetic sensor
						{
							pObject = new CSensor("IP-Hub Magnetic sensor",unitType,__allObjects.getLocationOther(),4);
						}
						else if ( unitType == 0x0203 ) // motion sensor
						{
							pObject = new CSensor("IP-Hub Motion sensor",unitType,__allObjects.getLocationOther(),2);
						}
						else if ( unitType == 0x0206 ) // flood detector 
						{
							pObject = new CSensor("IP-Hub Flood detector",unitType,__allObjects.getLocationOther(),6);
						}
						else // if 
						{
							pObject = new CLightBulb("IP-Hub Light",__allObjects.getLocationOther(),NULL);		
						}


						pObject->m_fwid = fwid;	

						pObject->m_attr_num["status"] = 0;

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
								//printf("Obj Set key : %s  = %s (str) \n",key.asString().c_str(),value.asString().c_str());	
								pObject->m_about_str[key.asString().c_str()] = value.asString();
							}
							else
							{
								//printf("Obj Set key : %s  = %d (num) \n",key.asString().c_str(),value.asInt());	
								pObject->m_about_num[key.asString().c_str()] = value.asInt();
							}

						}
						else if ( key == "alert" )
						{
							int alert = value.asInt();
							string message;
							CMyObject *pactivity;

							//printf("Obj Set key : %s  = %d (num) \n",key.asString().c_str(),value.asInt());	

							if ( alert ){
								pObject->m_attr_num["trigger"] = 1;
								TPNS_alert_count++;
								//put curl code here to connect TPNS
								if(TPNS_alert_count>0){
										//printf("---------start TPNS------------ \n");
										CURL *curl;
		  								CURLcode res;
		  								char POST[255] = "";
		  								//char *POST=NULL;
		  								curl_global_init(CURL_GLOBAL_DEFAULT);

		 								
										curl = curl_easy_init();
										if(curl) {
										  sprintf(POST,"cmd=event&uid=%s&event_type=100&msg=%s alert",(char*)__myUID,pObject->m_attr_str["name"].c_str());
										  curl_easy_setopt(curl, CURLOPT_URL, "http://push.iotcplatform.com/tpns");
										  curl_easy_setopt(curl, CURLOPT_POSTFIELDS,POST);

										  res = curl_easy_perform(curl);
										  printf("\n");

									    /* Check for errors */
									    if(res != CURLE_OK)
									      fprintf(stderr, "curl_easy_perform() failed: %s\n",
									      		curl_easy_strerror(res));
									 
									    /* always cleanup */ 
									    curl_easy_cleanup(curl);

										}
										curl_global_cleanup();							  

										//printf("\n---------end of TPNS------------ \n");
										TPNS_alert_count=0;
								}		
										//end of connect to TPNS

								printf("unix time [%u]\n",(unsigned) time(NULL));
								string target_name;
								target_name = pObject->m_name;
								pactivity = new CActivity((unsigned) time(NULL),alert,target_name.c_str());
								pObject->add(pactivity);
	


							}
							else
								pObject->m_attr_num["trigger"] = 0; // FixMe , here should be reset by app

							//pObject->m_attr_num["alert"] = value.asInt();

							if ( alert )
								pObject->m_attr_num["status"] = 3;
							else
								pObject->m_attr_num["status"] = 2;
						}
						else if ( key == "on" )
						{
							int on = value.asInt();


							//printf("Obj Set key : %s  = %d (num) \n",key.asString().c_str(),value.asInt());	

							if (   pObject->m_type == 0x0201   // garage sensor (door)
								|| pObject->m_type == 0x0202   // Magnetic sensor
							 	|| pObject->m_type == 0x0203   // motion sensor
								|| pObject->m_type == 0x0206 ) // flood detector 
							{
								int oldStatus = pObject->m_attr_num["status"];
								if ( oldStatus != 3 && oldStatus != 255 )
									pObject->m_attr_num["status"] = 2;
							}
							else
							{
								if ( on )
									pObject->m_attr_num["status"] = 1;
								else
									pObject->m_attr_num["status"] = 0;
							}

						}
						else if ( key == "outLink" )
						{
							int outLink = value.asInt();
							//printf("Obj Set key : %s  = %d (num) \n",key.asString().c_str(),value.asInt());	

							if ( outLink == 1 )
								pObject->m_attr_num["status"] = 255;
						}
						else if ( 	   key != "id" 
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
			Json::Value requestObjects;
			CMyObject *pObject = NULL;
			unsigned int i;


			requestObjects = txRecord->request["objects"];			


			if ( requestObjects.isArray() )
			{
				//int ntype;
				for(i=0;i<requestObjects.size();i++)
				{
					id = requestObjects[i]["id"].asUInt();

					pObject = __allObjects.getObjectByID(id);


					if ( pObject != NULL )
					{			
						if ( pObject->m_pLocation != NULL ) 
						{
							location["id"] = pObject->m_pLocation->m_id;
							location["name"] = pObject->m_pLocation->m_attr_str["name"];

							objects[i]["location"] = location;
						}
						

						pObject->getAttr(objects[i]);
					}
				}

				response["objects"] = objects;
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

		printf("set_detail response(fw):\n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());

		rc = sendto_rdt_client(txRecord->session,rdt_ticket,responseRoot);

		response["api"] = "update";
		responseRoot["response"] = response;

		rc = sendto_other_client(txRecord->session,responseRoot);




		if ( rc < 0 )
		{

		}

		delete txRecord;

				

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


				//printf("ID:%s\n",fwid.c_str());

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

						//printf("notify found object %s \n",pObject->m_attr_str["name"].c_str());


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

									objects[0]["location"] = location;
								}
								

								
								pObject->getAttr(objects[0]);			
								response["objects"] = objects;

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


						//printf("notify_detail:\n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());
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

