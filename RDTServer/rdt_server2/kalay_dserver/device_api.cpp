#include "../headers/exception.hpp"

#include <string.h>
#include <unistd.h>

#include <json/json.h>

#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>


#include "dserver.h"
#include "dtable.h"
#include "device_api.h"

#include "rdtcnnt.h"

#include "fw_api.h"


using namespace std;

int sendto_all_client (Json::Value& responseRoot)
{
	unsigned char szBuff[1024*32];
	int send_length;
	int option_len = 0;
	int rc;
	int data_length;

	Json::FastWriter fastWriter;
	std::string strSendOut;





	strSendOut = fastWriter.write(responseRoot);


	data_length  = strSendOut.length();



	szBuff[0]= 0xfe;
	szBuff[1]= 0xef;


	{ // rdt_ticket = 0
		option_len = 0;

		szBuff[2]= 0x00;
		szBuff[3]= 0x00;
	}

	szBuff[4+option_len]= (data_length&0xff00)>>8;
	szBuff[5+option_len]= (data_length&0x00ff);
	memcpy(&szBuff[6+option_len],strSendOut.c_str(),data_length);
	send_length = 6+option_len+data_length;
		

	rc = rdtcnnt_send_data_to_all_client((char*)szBuff,send_length);


	if ( rc < 0 )
	{
		
	}

	return rc;

}

int sendto_other_client (int session,Json::Value& responseRoot)
{
	unsigned char szBuff[1024*32];
	int send_length;
	int option_len = 0;
	int rc;
	int data_length;

	Json::FastWriter fastWriter;
	std::string strSendOut;




	strSendOut = fastWriter.write(responseRoot);


	data_length  = strSendOut.length();


	szBuff[0]= 0xfe;
	szBuff[1]= 0xef;

	{ // rdt_ticket = 0
		option_len = 0;

		szBuff[2]= 0x00;
		szBuff[3]= 0x00;
	}



	szBuff[4+option_len]= (data_length&0xff00)>>8;
	szBuff[5+option_len]= (data_length&0x00ff);
	memcpy(&szBuff[6+option_len],strSendOut.c_str(),data_length);
	send_length = 6+option_len+data_length;
		

	rc = rdtcnnt_send_data_to_other_client(session,(char*)szBuff,send_length);


	if ( rc < 0 )
	{
		
	}

	return rc;

}


int sendto_rdt_client (int session,unsigned int rdt_ticket,Json::Value& responseRoot)
{
	unsigned char szBuff[1024*32];
	int send_length;
	int option_len = 0;
	int rc;
	int data_length;

	Json::FastWriter fastWriter;
	std::string strSendOut;



	strSendOut = fastWriter.write(responseRoot);
				//responseRoot.toStyledString().c_str();


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
		


	//printf("Dump RDT json: \n%s\n",szBuff.c_str());
	
	rc =  RDT_Write(__rdt_cnnt[session].rdt_id,(char*)szBuff,send_length); 
	if ( rc < 0 )
	{
		
	}

	return rc;

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

	//response["uid"] = (char*) __myUID;;
	response["api"] = request["api"].asString();

	if(!request["ticket"].isNull()){
		response["ticket"] = request["ticket"].asUInt();
	}

	id = request["id"].asUInt();

	printf("get_about id :%d \n",id);


	try {
		if ( id == 0 ) // Get gateway about
		{
			CMyObject *pGateway;

			pGateway  = __allObjects.getGateway();
			
			if ( pGateway != NULL )
			{
				pGateway->getAbout(response);
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
				response["type"] = pAccessory->m_type;
 
				pAccessory->getAbout(response);


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

	response["uid"] = (char*) __myUID;;
	response["api"] = request["api"].asString();

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

	if(!request["ticket"].isNull()){
		response["ticket"] = request["ticket"].asUInt();
	}

	try {
			std::map<unsigned int, CMyObject *>::iterator p;
			list<CMyObject*>::iterator j;
			int nAccessoryCnt = 0;


			for(p = __allObjects.m_mapAllObjects.begin(); p!=__allObjects.m_mapAllObjects.end(); ++p)
			{
				CMyObject *pObject;

				
				pObject = (CMyObject*) p->second;

				if ( pObject->m_pGroup == NULL && pObject->m_attr_num["type"] == 0x0109 ) // FixMe if light type is 0
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
	response["api"] = request["api"].asString();
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
	Json::Value responseRoot;
	Json::Value responseObjects;
	Json::Value response;
	Json::Value objects;
	Json::Value location;

	unsigned int rdt_ticket;
	int rc;
	unsigned int id;
	int err = 1;
	int setting = 0;
	string err_str;		
	int clearTrigger = 0;

	int sendResponse = 0;
	

printf("set_detail request:\n%s\n-------------------\n",(char*)request.toStyledString().c_str());
	


	response["uid"] = (char*) __myUID;;
	response["api"] = request["api"].asString();

	if(!request["ticket"].isNull()){
		response["ticket"] = request["ticket"].asUInt();
	}

	rdt_ticket = request["rdt_ticket"].asUInt();
	clearTrigger = request["clear_trigger"].asUInt();

	



	try {
		CMyObject *pObject = NULL;
		Json::Value fwObjects;		
		int nfwObjectCnt = 0;
		

		Json::Value requestObjects;
		unsigned int i;


		requestObjects = request["objects"];

		if ( requestObjects.isArray() )
		{
			//int ntype;
			for(i=0;i<requestObjects.size();i++)
			{
				
					if(requestObjects[i]["id"].isNull())
					{
						int ntype;
						string newname;
				
						ntype = requestObjects[i]["type"].asInt();
						newname = requestObjects[i]["name"].asString();

						if(ntype == 0xff10) //location 
						{
							pObject = new CLocation(newname.c_str());
							requestObjects[i]["id"] =  pObject->m_id;
							pObject->m_attr_num["editable"]=1;

						}
						else if(ntype == 0xff11)//group
						{
							std::map<unsigned int, CMyObject *>::iterator p;
							int groupNO=1;

							for(p = __allObjects.m_mapAllGroups.begin(); p!=__allObjects.m_mapAllGroups.end(); ++p)
							{
								CGroup *pGroup;
								pGroup = (CGroup*) p->second;

								if(pGroup->m_attr_num["groupNo"] == groupNO )
									groupNO++;
								else
									break;


							}	
							pObject = new CGroup(newname.c_str(),__allObjects.getLocationOther());
							pObject->m_attr_num["groupNo"] = groupNO;
							requestObjects[i]["id"] =  pObject->m_id;
													
						}
						/*
						else if(ntype == 0xff40)//schedule
						{
							pObject = new CSchedule(newname.c_str());
							requestObjects[i]["id"] =  pObject->m_id;
							
						}*/

					}
					else if(!requestObjects[i]["req_type"].isNull()){


						response["uid"] = (char*) __myUID;
						response["api"] = request["api"].asString();

						CGateway *pGateway = __allObjects.getGateway();	

						if(!requestObjects[i]["name"].isNull()){
								pGateway->m_name = requestObjects[i]["name"].asString();
								pGateway->m_attr_str["name"] = pGateway->m_name;


						}

						if(!requestObjects[i]["led"].isNull()){
								pGateway->m_attr_num["led"]= requestObjects[i]["led"].asUInt();
						}

						responseObjects[i]["name"] =  pGateway->m_name;
						responseObjects[i]["led"] =  pGateway->m_attr_num["led"];
						responseObjects[i]["type"] = pGateway->m_type;
						responseObjects[i]["id"] = pGateway->m_id;
						responseObjects[i]["req_type"] = requestObjects[i]["req_type"].asUInt();

						response["objects"] = responseObjects;



						
						//response["objects"] = objects;


			

					 
						responseRoot["error"] = 0;
						responseRoot["response"] = response;

						rc = sendto_rdt_client(session,rdt_ticket,responseRoot);
						printf("deviceapi_setting_detail response \n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());

						setting = 1;
					}
					else
					{
						id = requestObjects[i]["id"].asUInt();

						pObject = __allObjects.getObjectByID(id);

					}	

					if ( pObject != NULL )
					{
						map<string,int>::iterator iNum;
						map<string,string>::iterator iStr;
						//int accessoryType;

						if ( clearTrigger )
						{
							
						}

						// Change Value +++
						{
							Json::ValueIterator itr;

							int valueChanged = 0;
							int fwChanged = 0;


							for(itr=requestObjects[i].begin();itr != requestObjects[i].end(); itr++)
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
										printf("Set key location : %s  ",key.asString().c_str());

										if ( value.isNumeric() )
											printf("value:%d \n",value.asInt());
										else  if ( value.isString() )
											printf("value:%s \n",value.asString().c_str());							
										else  if ( value.isString() )
											printf("value:%s \n",value.toStyledString().c_str());							


										idLocation = value["id"].asUInt();

										printf("value: \n id:%d  name:%s \n",value["id"].asUInt(),value["name"].asString().c_str());

										if (    pObject->m_pLocation == NULL 
											 || pObject->m_pLocation->m_id != idLocation)
										{
											CLocation *newLocation;

											newLocation = __allObjects.getLocationByID(idLocation);
											if ( newLocation != NULL )
											{
												newLocation->add(pObject);

												valueChanged = 1;
											}

										}

									}

									else if ( key.asString() == "order" )
									{
										int newOrder = value.asInt();

										if ( pObject->m_pLocation != NULL )							
										{
											pObject->m_pLocation->UpdateOrder(pObject,newOrder);

											valueChanged = 1;
										}

									}
									else if ( key.asString() == "name"	 )
									{
										printf("Set key name : %s   value:%s \n ",key.asString().c_str(),value.asString().c_str());

										
										if ( pObject->m_attr_str[key.asString().c_str()] != value.asString() )
										{
											pObject->m_attr_str[key.asString().c_str()] = value.asString();
											pObject->m_name = value.asString();
											valueChanged = 1;
										}
									}
									else if(key.asString() == "add"	 ){
										int i;

										

										if(value.isArray()){
											printf("value_size: %d",value.size());

											for(i=0;i< (int)value.size();i++){
												CMyObject *subobject;

												id = value[i].asUInt();


												subobject = __allObjects.getObjectByID(id);

												if(pObject->m_type==0xff10){//location
													((CLocation*)pObject)->add(subobject);
												}
												else if(pObject->m_type==0xff11){//group
													((CGroup*)pObject)->add(subobject);


													fwObjects[0]["id"][i]= subobject->m_fwid;
													fwObjects[0]["groupNo"] = pObject->m_attr_num["groupNo"];
												}

												//else{
												//	  pObject->addToList(subobject);
												//}

											}
											
										}


										int seq = 0;

										CTXRecord *txRecord = new CTXRecord();
								
						    			txRecord->seq = 0;
						    			txRecord->session = session;
										txRecord->request = request;
										txRecord->sendTime = time(NULL);

										
						    		
						    			seq = __ipHub.fwapi_addDev(fwObjects,txRecord);

						    		

						    			if( seq <= 0){
						    				delete	txRecord;
						    			} 


										valueChanged = 1;

									}
									else if(key.asString() == "remove"	 ){
											int i;


										if(value.isArray()){
											printf("value_size: %d",value.size());

											for(i=0;i< (int)value.size() ; i++){
												CMyObject *subobject;

												id = value[i].asUInt();
												subobject = __allObjects.getObjectByID(id);

												if(pObject->m_type==0xff10){
													((CLocation*)pObject)->remove(subobject);
												}
												else if(pObject->m_type==0xff11){
													((CGroup*)pObject)->remove(subobject);
												}
											//	else{
											//		pObject->removeFromList(subobject);
											//	}

											}
										}
										valueChanged = 1;

									}

									else
									{
										printf("Set key others : %s  ",key.asString().c_str());

										if ( value.isNumeric() )
											printf("value(num):%d \n",value.asInt());
										else if ( value.isString() )
											printf("value(str):%s \n",value.asString().c_str());
										else
											printf("value(obj):\n");

										if ( value.isNumeric() )
										{
											printf("value %d\n",value.asInt());
							
											if ( pObject->m_attr_num[key.asString().c_str()] !=  value.asInt() )
											{
												if ( pObject->m_fwid.length() ==  0 ) // Dummy Test Device
												{
													pObject->m_attr_num[key.asString().c_str()] = value.asInt();
												}

												if(pObject->m_type == 65297 && key.asString() == "status")// group
												{
													std::map<unsigned int, CMyObject *>::iterator iterGroup;
															list<CMyObject*>::iterator iterX;

															for(iterX = pObject->m_listObject.begin(); iterX!=pObject->m_listObject.end(); ++iterX)
															{
																CMyObject *pSubObject;

																pSubObject = *iterX;

																pSubObject->m_attr_num[key.asString().c_str()] = value.asInt();
															}

												}
												valueChanged = 1;
											}								
										}
										else  if ( value.isString() )
										{
											printf("value %s\n",value.asString().c_str());

											if ( pObject->m_attr_str[key.asString().c_str()] != value.asString() )
											{
												 if ( pObject->m_fwid.length() ==  0 ) // Dummy Test Device
												 {
													pObject->m_attr_str[key.asString().c_str()] = value.asString();
												 }

												valueChanged = 1;
											}
										}
										else if( value.isObject() )
										{	
											unsigned int idObject;
											CMyObject *pObject_target = NULL;

											//need to fix
											if(key.asString() == "power_off")
											{
												//printf("%d %d %d",value["on"].asInt(),value["time"].asInt(),value["duration"].asInt());
												pObject->m_attr_num["pow_off_on"] = value["on"].asInt();
												pObject->m_attr_num["pow_off_duration"] = value["duration"].asInt();
												pObject->m_attr_num["pow_off_time"] = value["time"].asInt();

											}
											else if(key.asString() == "power_on")
											{
												//printf("%d %d %d",value["on"].asInt(),value["time"].asInt(),value["duration"].asInt());
												pObject->m_attr_num["pow_on_on"] = value["on"].asInt();
												pObject->m_attr_num["pow_on_duration"] = value["duration"].asInt();
												pObject->m_attr_num["pow_on_time"] = value["time"].asInt();
											}
											else if(key.asString() == "if")
											{
												printf("%d %d %d",value["id"].asInt(),value["status"].asInt(),value["notify"].asInt());
												if(!value["id"].isNull())
												{
													
													idObject = value["id"].asUInt();
													pObject_target = __allObjects.getObjectByID(idObject);

													pObject->m_attr_num["if_id"] = value["id"].asUInt();
													pObject->m_attr_str["if_name"] = pObject_target->m_name;
													//printf("name: %s\n ",pObject->m_attr_str["if_name"].c_str());
												}
												if(!value["status"].isNull())
													pObject->m_attr_num["if_status"] = value["status"].asInt();
												if(!value["time"].isNull())
													pObject->m_attr_num["if_time"] = value["time"].asInt();
											}
											else if(key.asString() == "then")
											{
												printf("%d %d %d",value["id"].asInt(),value["status"].asInt(),value["notify"].asInt());
												if(!value["id"].isNull())
												{
													idObject = value["id"].asUInt();
													pObject_target = __allObjects.getObjectByID(idObject);
													pObject->m_attr_num["then_id"] = value["id"].asUInt();
													pObject->m_attr_str["then_name"] = pObject_target->m_name;
												}
												if(!value["status"].isNull())
													pObject->m_attr_num["then_status"] = value["status"].asInt();
												if(!value["notify"].isNull())
													pObject->m_attr_num["then_notify"] = value["notify"].asInt();
											}
											valueChanged = 1;
										

										}
							
									}



									if ( 	 valueChanged != 0
									     &&  key.asString() != "name"	
									     &&  key.asString() != "location"
									     &&  key.asString() != "order"	
									     &&  key.asString() != "add"	
									     &&  key.asString() != "remove"	)
									{

										if ( key.asString() == "status"	)
										{
											fwChanged++;

											fwObjects[nfwObjectCnt]["on"] = value.asInt();// #TBD : if we only send change items
											//printf("fw test\n");
										}
										else
										{   
											//printf("fw test2\n");
											fwChanged++;
											if ( value.isNumeric() )
												fwObjects[nfwObjectCnt][key.asString().c_str()] = value.asInt();// #TBD : if we only send change items
											else  if ( value.isString() )
												fwObjects[nfwObjectCnt][key.asString().c_str()] = value.asString();// #TBD : if we only send change items

										}

									}
								}

							}


				    		if ( pObject->m_fwid.length() > 0 && fwChanged > 0 )
				    		{
					    		fwObjects[nfwObjectCnt]["id"] = pObject->m_fwid; 

					    		nfwObjectCnt++;			
					    	}
					    	else if (pObject->m_type ==0xff11  && fwChanged > 0)
					    	{
					    		fwObjects[nfwObjectCnt]["groupNo"] = pObject->m_attr_num["groupNo"];
					    		nfwObjectCnt++;		
					    	}	
						}

						// Change Value ---	
						//accessoryType = pAccessory->m_attr_num["type"];	

						err = 0;
					}
					else
					{
						err = -1;
						err_str = "not found";
					}
			
								


			}
		}








// Set to FW
			

		if ( nfwObjectCnt > 0 )
		{
			int seq = 0;

				CTXRecord *txRecord = new CTXRecord();
		
    			txRecord->seq = 0;
    			txRecord->session = session;
				txRecord->request = request;
				txRecord->sendTime = time(NULL);

				
    		
    		seq = __ipHub.fwapi_set(fwObjects,txRecord);

    		

    		if( seq <= 0){
    			delete	txRecord;
    		} 

    		
		}
		else //if ( valueChanged != 0 )
		{
			if ( requestObjects.isArray() && setting==0)
			{
				//int ntype;
				for(i=0;i<requestObjects.size();i++)
				{
					id = requestObjects[i]["id"].asUInt();
					//printf("id");

					pObject = __allObjects.getObjectByID(id);


					if ( pObject != NULL )
					{			
						if ( pObject->m_pLocation != NULL ) 
						{
							location["id"] = pObject->m_pLocation->m_id;
							location["name"] = pObject->m_pLocation->m_attr_str["name"];

							objects[i]["location"] = location;
						}
						

						pObject->getDetail(objects[i]);
					}
				}

				response["objects"] = objects;
			}

			sendResponse = 1;		    			
		}

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }


    if ( sendResponse  && setting == 0)
    {
		responseRoot["error"] = err;
		if ( err_str.length() != 0 )
			responseRoot["error_str"] = err_str;

		responseRoot["response"] = response;


		printf("set_detail response:\n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());

		rc = sendto_rdt_client(session,rdt_ticket,responseRoot);

		
		response["api"] = "update";
		responseRoot["response"] = response;
		
		//rc = sendto_other_client(session,responseRoot);  disable for temp need to fix
		
		if ( rc < 0 )
		{

		}
    }
    



	return;
}


void deviceapi_remove (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;
	Json::Value objects;
	Json::Value responseObjects;

	unsigned int rdt_ticket;
	int rc;
	int err = 1;
	string err_str;		



	rdt_ticket = request["rdt_ticket"].asUInt();

	printf("remove request:\n%s\n-------------------\n",(char*)request.toStyledString().c_str());

	if(!request["ticket"].isNull()){
		response["ticket"] = request["ticket"].asUInt();
	}



	try {
		Json::Value removeObject;

		removeObject = request["objects"];

		if ( removeObject.isArray() )
		{
			unsigned int i;
			int removeCnt = 0;



				for(i=0;i<removeObject.size();i++)
				{   unsigned int start_time=0;
					unsigned int end_time=0;
					std::map<unsigned int, CMyObject *>::iterator p;

					if(removeObject[i]["req_type"]!=0x0003)
					{	
						err = __allObjects.removeByID(removeObject[i]["id"].asUInt());
						responseObjects[removeCnt]["id"] = removeObject[i]["id"].asUInt();
						if ( err != 0 )
						{
							printf("err %d\n",err);
						}

						removeCnt++;
					}
					else
					{
						responseObjects[i]["req_type"] = removeObject[i]["req_type"];
						responseObjects[i]["id"] = removeObject[i]["id"].asUInt();
						start_time = removeObject[i]["start_time"].asUInt();
						end_time = removeObject[i]["end_time"].asUInt();

						for(p = __allObjects.m_mapAllActivities.begin(); p!=__allObjects.m_mapAllActivities.end(); ++p)
						{
							CActivity *pActivity;
							CMyObject *pMyObject;	
							pActivity = (CActivity*) p->second;
							unsigned int timestamp;

							timestamp = pActivity->m_attr_num["time"];

							if(end_time == 0)
							{
								pMyObject = pActivity->m_pAccessory;
								pMyObject->remove(pActivity);
								err = __allObjects.removeByID(pActivity->m_id);
								
							}
							else if(timestamp > start_time && timestamp < end_time)
							{
								err = __allObjects.removeByID(pActivity->m_id);
							}

					
						}
						removeCnt++;
					}	
				}


		}
		else 
		{
			err = __allObjects.removeByID(removeObject["id"].asUInt());
			responseObjects["id"] = removeObject["id"].asUInt();

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
	response["api"] = request["api"].asString();
	response["objects"] = responseObjects;


	responseRoot["error"] = err;
	if ( err_str.length() != 0 )
		responseRoot["error_str"] = err_str;
	responseRoot["response"] = response;



printf("remove response:\n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}


	return;
}

void deviceapi_get_activities (int session,Json::Value &request)
{
	Json::Value responseRoot;
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


	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}


	return;
}

void deviceapi_get_light_effects (int session,Json::Value &request)
{
	Json::Value responseRoot;
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
 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}


	return;
}

void deviceapi_set_light_effects (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();


	objects[0]["id"] = "e01";


	response["api"] = request["api"].asString();
	response["id"] = "a01";
	response["objects"] = objects;
 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_get_list (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;
	Json::Value objects;

	int rc;					
	unsigned int rdt_ticket;	
	int err = 1;
	string err_str;
	unsigned int  idObject;

	idObject = request["id"].asUInt();


	rdt_ticket = request["rdt_ticket"].asUInt();
	printf("set_detail request:\n%s\n-------------------\n",(char*)request.toStyledString().c_str());
	

	if(!request["ticket"].isNull()){
		response["ticket"] = request["ticket"].asUInt();
	}

    try{
		std::map<unsigned int, CMyObject *>::iterator p;
		list<CMyObject*>::iterator j;
		int nAccessoryCnt = 0;
		//Json::Value accessories;

		if ( request["req_type"].asUInt() == 0xff11 ) //for group
		{	
			if(idObject ==0)
			{
				for(p = __allObjects.m_mapAllGroups.begin(); p!=__allObjects.m_mapAllGroups.end(); ++p)
				{
					CGroup *pGroup;	
					pGroup = (CGroup*) p->second;
					Json::Value subObjects;

					objects[nAccessoryCnt]["id"] =  pGroup->m_id,
					objects[nAccessoryCnt]["type"] =  pGroup->m_type,
					objects[nAccessoryCnt]["name"] =  pGroup->m_attr_str["name"].c_str();

					if (pGroup->m_listObject.size() > 0 )
					{
						pGroup->getSubObjects(subObjects);
						objects[nAccessoryCnt]["objects"] = subObjects;
					}
						nAccessoryCnt++;
				}
			}	
		}

		else if( request["req_type"].asUInt() == 0x0109)// for light
		{

			if(idObject ==0 )
			{
				for(p = __allObjects.m_mapAllObjects.begin(); p!=__allObjects.m_mapAllObjects.end(); ++p)
				{
					CMyObject *pObject;	
					pObject = (CMyObject*) p->second;

					if ( pObject->m_pGroup == NULL && pObject->m_attr_num["type"] == 0x0109)
					{
						objects[nAccessoryCnt]["id"] =  pObject->m_id,
						objects[nAccessoryCnt]["name"] =  pObject->m_attr_str["name"].c_str();
						objects[nAccessoryCnt]["type"] = pObject->m_attr_num["type"];
						nAccessoryCnt++;
					}
					

				}
			}	

		}
		else if(request["req_type"].asUInt()==0x0003)//activity
		{
				unsigned int start_time;
				unsigned int end_time;
				int nAccessoryCnt =0;
				printf("test get activity");
				std::map<unsigned int, CMyObject *>::iterator p;
				start_time = request["start_time"].asUInt();
				end_time = request["end_time"].asUInt();

#if 0
				ifstream inFile;
    			inFile.open("autodisk.json");// Open the input file
    			stringstream strStream;
    			strStream << inFile.rdbuf();// Read the file
    			string string = strStream.str();

    			Json::Reader reader;
				Json::Value activitylog;

				if(reader.parse(string, activitylog)){
					Json::Value notify;

					notify = activitylog["messages"][0];
					printf("time[%d]\n",notify["timestamp"].asInt());


				}
#endif

				if(request["id"].asUInt()==0)
				{
								for(p = __allObjects.m_mapAllActivities.begin(); p!=__allObjects.m_mapAllActivities.end(); ++p)
								{

									CActivity *pActiviry;	
									pActiviry = (CActivity*) p->second;
									Json::Value subObjects;
									unsigned int timestamp;

									timestamp = pActiviry->m_attr_num["time"];

									//pActiviry->getBaseAttr(objects[nAccessoryCnt]);
									if(end_time ==0)
									{
										objects[nAccessoryCnt]["name"] = pActiviry->m_name;
										objects[nAccessoryCnt]["time"] = timestamp;
										objects[nAccessoryCnt]["status"] = pActiviry->m_attr_num["status"];
										objects[nAccessoryCnt]["req_type"] = request["req_type"];
										objects[nAccessoryCnt]["index"] = nAccessoryCnt;
										nAccessoryCnt++;

									}
									else if(timestamp > start_time && timestamp <end_time)
									{	
										objects[nAccessoryCnt]["name"] = pActiviry->m_attr_num["name"];
										objects[nAccessoryCnt]["time"] = timestamp;
										objects[nAccessoryCnt]["status"] = pActiviry->m_attr_num["status"];
										objects[nAccessoryCnt]["req_type"] = request["req_type"];
										objects[nAccessoryCnt]["index"] = nAccessoryCnt;
										
										nAccessoryCnt++;

									}

									
								}

								response["more"] = 0;
				}
				else
				{
					
					CMyObject *pObject;
					pObject = __allObjects.getObjectByID(idObject);


					if(pObject != NULL)
					{
						if(pObject->m_listObject_activity.size()>0)
						{
							
							for(j = pObject->m_listObject_activity.begin(); j!=pObject->m_listObject_activity.end(); ++j)
							{
							
								CMyObject *pActiviry;	
								//pActiviry = (CActivity*) p->second;
								Json::Value subObjects;
								unsigned int timestamp;

								pActiviry = *j;

								timestamp = pActiviry->m_attr_num["time"];

									//pActiviry->getBaseAttr(objects[nAccessoryCnt]);
									if(end_time ==0)
									{
										objects[nAccessoryCnt]["name"] = pActiviry->m_name;
										objects[nAccessoryCnt]["time"] = timestamp;
										objects[nAccessoryCnt]["status"] = pActiviry->m_attr_num["status"];
										objects[nAccessoryCnt]["req_type"] = request["req_type"];
										objects[nAccessoryCnt]["index"] = nAccessoryCnt;
										nAccessoryCnt++;

									}
									else if(timestamp > start_time && timestamp <end_time)
									{	
										objects[nAccessoryCnt]["name"] = pActiviry->m_attr_num["name"];
										objects[nAccessoryCnt]["time"] = timestamp;
										objects[nAccessoryCnt]["status"] = pActiviry->m_attr_num["status"];
										objects[nAccessoryCnt]["req_type"] = request["req_type"];
										objects[nAccessoryCnt]["index"] = nAccessoryCnt;
										
										nAccessoryCnt++;

									}

							}
							
						}

					}	


								response["more"] = 0;
				}				

		}	
		else if(request["req_type"].asUInt() == 0xff30)//task
		{

			
			Json::Value subObjects;
			Json::Value requestObjects;
			list<CMyObject*>::iterator j;
			
#if 0
			CMyObject *pObject;
			pObject = __allObjects.getObjectByID(request["id"].asUInt());

			if(pObject->m_listObject_task.size()>0)
			{
				
				for(j = pObject->m_listObject_task.begin(); j!=pObject->m_listObject_task.end(); ++j)
				{
					CMyObject *taskpObject;
					map<string,int>::iterator iNum;
					map<string,string>::iterator iStr;					

					taskpObject = *j;

					taskpObject->getBaseAttr(objects[nAccessoryCnt]);
					nAccessoryCnt++;

				}
				


			}	
#endif
				for(p = __allObjects.m_mapAllTasks.begin(); p!=__allObjects.m_mapAllTasks.end(); ++p)
				{
					CTask *pTask;	
					pTask = (CTask*) p->second;
					Json::Value subObjects;

					pTask->getBaseAttr(objects[nAccessoryCnt]);
					subObjects["type"] = pTask->m_attr_num["then_type"];
					subObjects["status"] = pTask->m_attr_num["then_status"];
					subObjects["id"] = pTask->m_attr_num["then_id"];
					objects[nAccessoryCnt]["then"] = subObjects;
					nAccessoryCnt++;
				}



		}
		err = 0;	 



		}catch (const libsocket::socket_exception& exc)
    	{
			std::cerr << exc.mesg;
			err_str = exc.mesg;
    	}	

		response["uid"] = (char*) __myUID;
		response["api"] = request["api"].asString();
		response["objects"] = objects;

		responseRoot["error"] = err;

		if ( err_str.length() != 0 )
			responseRoot["error_str"] = err_str;
			responseRoot["response"] = response;


		printf("deviceapi get_all accessories response:\n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());
		rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


		if ( rc < 0 )
		{

		}

	return;




}



void __get_gateway_detail (Json::Value &locations)
{
	std::map<unsigned int, CMyObject *>::iterator p;
	list<CMyObject*>::iterator j;
	int nLocationCnt = 0;
	Json::Value accessories;


	for(p = __allObjects.m_mapAllLocations.begin(); p!=__allObjects.m_mapAllLocations.end(); ++p)
	{
		CLocation *pLocation;
		int nAccessoryCnt = 0;

		
		pLocation = (CLocation*) p->second;


		locations[nLocationCnt]["id"] =  pLocation->m_id,
		locations[nLocationCnt]["type"] =  pLocation->m_type,
		locations[nLocationCnt]["name"] =  pLocation->m_attr_str["name"].c_str();

		
		accessories.clear();

		for(j = pLocation->m_listObject.begin(); j!=pLocation->m_listObject.end(); ++j)
		{
			CMyObject *pObject;
			map<string,int>::iterator iNum;
			map<string,string>::iterator iStr;					

			pObject = *j;

			if(pObject->m_pGroup == NULL){
			pObject->getBaseAttr(accessories[nAccessoryCnt]);
		
			nAccessoryCnt++;
			}
		}

		locations[nLocationCnt]["objects"] = accessories;	

		nLocationCnt++;

	}


	return;
}

void deviceapi_add_accessories (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();


	objects[0]["id"] = "a01";
	objects[1]["id"] = "a02";


	response["api"] = request["api"].asString();
	response["objects"] = objects;
 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_merge_accessories (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();


	objects[0]["id"] = "a01";
	objects[1]["id"] = "a02";


	response["api"] = request["api"].asString();
	response["objects"] = objects;
 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_backup_gateway (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();



	response["api"] = request["api"].asString();
 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_restore_gateway (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();



	response["api"] = request["api"].asString();
 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_reset_gateway (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();



	response["api"] = request["api"].asString();
 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_update_gateway (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();



	response["api"] = request["api"].asString();
 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}



void deviceapi_get_detail (int session,Json::Value &request)
{
//+++
	Json::Value responseRoot;
	Json::Value response;
	Json::Value responseObjects;

	int rc;					
	unsigned int rdt_ticket = 0;	
	int err = 1;

	unsigned int idObject;
	
	string err_str;


printf("deviceapi_get_detail request \n%s\n-------------------\n",(char*)request.toStyledString().c_str());

	if(!request["ticket"].isNull()){
		response["ticket"] = request["ticket"].asUInt();
	}

	try {

		Json::Value requestObjects;
		

		rdt_ticket = request["rdt_ticket"].asUInt();
		requestObjects = request["objects"];



			if ( requestObjects.isArray() )
			{
				unsigned int i;
				CMyObject *pObject;
				//int ntype;

				for(i=0;i<requestObjects.size();i++)
				{
					idObject = requestObjects[i]["id"].asUInt();

					//ntype = idObject & 0xff000000;


					if ( idObject == 0 ) // GetGateway
					{
						CGateway *pGateway = __allObjects.getGateway();

						Json::Value locations;


						if ( pGateway != NULL )
						{
							if(requestObjects[i]["req_type"].asUInt()==0xff50)
							{
								//printf("test get gateway");
								response["uid"] = (char*) __myUID;
								response["api"] = request["api"].asString();
								responseObjects[i]["name"] =  pGateway->m_name;
								responseObjects[i]["led"] =  pGateway->m_attr_num["led"];
								responseObjects[i]["id"] = pGateway->m_id;
								responseObjects[i]["type"] = pGateway->m_type;
								responseObjects[i]["req_type"] = requestObjects[i]["req_type"];
								response["objects"] = responseObjects;
							}
							else if(requestObjects[i]["req_type"].asUInt()==0x0003)//activity
							{
								unsigned int start_time;
								unsigned int end_time;
								int nAccessoryCnt =0;
								printf("test get activity");
								std::map<unsigned int, CMyObject *>::iterator p;
								start_time = requestObjects[i]["start_time"].asUInt();
								end_time = requestObjects[i]["end_time"].asUInt();



								for(p = __allObjects.m_mapAllActivities.begin(); p!=__allObjects.m_mapAllActivities.end(); ++p)
								{

									CActivity *pActiviry;	
									pActiviry = (CActivity*) p->second;
									Json::Value subObjects;
									unsigned int timestamp;

									timestamp = pActiviry->m_attr_num["time"];

									//pActiviry->getBaseAttr(objects[nAccessoryCnt]);
									if(end_time ==0)
									{
										responseObjects[nAccessoryCnt]["name"] = pActiviry->m_name;
										responseObjects[nAccessoryCnt]["time"] = timestamp;
										responseObjects[nAccessoryCnt]["status"] = pActiviry->m_attr_num["status"];
										responseObjects[nAccessoryCnt]["req_type"] = requestObjects[i]["req_type"];
										responseObjects[nAccessoryCnt]["index"] = nAccessoryCnt;
										nAccessoryCnt++;

									}
									else if(timestamp > start_time && timestamp <end_time)
									{	
										responseObjects["name"] = pActiviry->m_attr_num["name"];
										responseObjects["time"] = timestamp;
										responseObjects["status"] = pActiviry->m_attr_num["status"];
										responseObjects["req_type"] = requestObjects[i]["req_type"];
										responseObjects["index"] = nAccessoryCnt;
										
										nAccessoryCnt++;

									}

									
								}

								response["more"] = 0;

							}	
							else
							{
								__get_gateway_detail(locations);
								

								pGateway->getBaseAttr(responseObjects[i]);
								responseObjects[i]["objects"] = locations;
							}
						}
					}
					else
					{
						pObject = (CMyObject*) __allObjects.getObjectByID(idObject);


						if(pObject != NULL){
							if(requestObjects[i]["req_type"].asUInt()==0xff50) // for setting
							{
								Json::Value subObjects;

								responseObjects[i]["req_type"] = requestObjects[i]["req_type"].asUInt();
								responseObjects[i]["id"] = pObject->m_id;
								responseObjects[i]["name"] = pObject->m_name;
								responseObjects[i]["type"] = pObject->m_type;
								responseObjects[i]["fadePower"] = pObject->m_attr_num["fadePower"];

								if(pObject->m_listObject.size() > 0 ){

									pObject->getSubObjects(subObjects);
									responseObjects[i]["objects"] = subObjects;


								}else{
								}


							}	
							else
							{	

								if ( pObject != NULL )
								{

									pObject->getDetail(responseObjects[i]);

									//if ( ntype == IDTYPE_GROUP )
									//else if ( ntype == IDTYPE_ACCESSORY )
									//else if ( ntype == IDTYPE_LOCATION )
									//else if ( ntype == IDTYPE_GATEWAY )
									//else if ( ntype == IDTYPE_SWITCH )
								}
							}	
						}	
							


					}
				}
			}


		err = 0;


    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }


	response["uid"] = (char*) __myUID;
	response["api"] = request["api"].asString();


	response["objects"] = responseObjects;




	responseRoot["error"] = err;
	if ( err_str.length() != 0 )
		responseRoot["error_str"] = err_str;
	responseRoot["response"] = response;


printf("deviceapi_get_detail response \n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());


	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{
		
	}	    




	return;
}

void deviceapi_get_other_groups (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;
	Json::Value groups;

	int rc;					
	unsigned int rdt_ticket;	
	int err = 1;
	string err_str;
	unsigned int idGroup;


	rdt_ticket = request["rdt_ticket"].asUInt();

	idGroup = request["id"].asUInt();

	if(!request["ticket"].isNull()){
		response["ticket"] = request["ticket"].asUInt();
	}
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
				//pGroup->getBaseAttr(groups[nGroupCnt]);
				groups[nGroupCnt]["id"] =  pGroup->m_id;
				groups[nGroupCnt]["type"] =  pGroup->m_type;
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
	response["api"] = request["api"].asString();
	response["objects"] = groups;


	responseRoot["error"] = err;
	if ( err_str.length() != 0 )
		responseRoot["error_str"] = err_str;
	responseRoot["response"] = response;


	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{
		
	}

	return;
}

//void deviceapi_set_detail (int session,Json::Value &request)


void deviceapi_add_an_accessory_to_group (int session,Json::Value &request)
{
	Json::Value responseRoot;
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
	response["api"] = request["api"].asString();
	response["id"] = idGroup;


	responseRoot["error"] = err;
	if ( err_str.length() != 0 )
		responseRoot["error_str"] = err_str;
	responseRoot["response"] = response;


	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{
		
	}

	return;
}

void deviceapi_remove_accessories_from_group (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["api"] = request["api"].asString();

 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_get_locations (int session,Json::Value &request)
{

// ++++
	Json::Value responseRoot;
	Json::Value response;
	Json::Value locations;

	int rc;					
	unsigned int rdt_ticket;	
	int err = 1;
	string err_str;


	rdt_ticket = request["rdt_ticket"].asUInt();

	if(!request["ticket"].isNull()){
		response["ticket"] = request["ticket"].asUInt();
	}



	try {
			std::map<unsigned int, CMyObject *>::iterator p;
			list<CMyObject*>::iterator j;
			int nLocationCnt = 0;


			for(p = __allObjects.m_mapAllLocations.begin(); p!=__allObjects.m_mapAllLocations.end(); ++p)
			{
				CLocation *pLocation;

				
				pLocation = (CLocation*) p->second;

				pLocation->getAttr(locations[nLocationCnt]);

				nLocationCnt++;

			}

			err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = request["api"].asString();
	response["objects"] = locations;


	responseRoot["error"] = err;
	if ( err_str.length() != 0 )
		responseRoot["error_str"] = err_str;
	responseRoot["response"] = response;

// ----

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_add_accessories_to_location (int session,Json::Value &request)
{
// +++
	Json::Value responseRoot;
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

	if(!request["ticket"].isNull()){
		response["ticket"] = request["ticket"].asUInt();
	}

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
	response["api"] = request["api"].asString();

	response["id"] = idLocation;
	response["objects"] = responseObjects;

 
	responseRoot["error"] = err;
	if ( err_str.length() != 0 )
		responseRoot["error_str"] = err_str;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

// ---

	return;
}

void deviceapi_set_a_location (int session,Json::Value &request)
{
	Json::Value responseRoot;
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

	if(!request["ticket"].isNull()){
		response["ticket"] = request["ticket"].asUInt();
	}


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
	response["api"] = request["api"].asString();

	response["id"] = pLocation->m_id;
	response["name"] = strLocationName;


 
	responseRoot["error"] = err;
	if ( err_str.length() != 0 )
		responseRoot["error_str"] = err_str;
	responseRoot["response"] = response;

	printf("deviceapi_get_detail response \n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}


void deviceapi_add (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value responseObjects;
	Json::Value response;




	unsigned int rdt_ticket;
	int err = 1;
	string err_str;
	string object_name;
	int rc;
	unsigned int idObject;


	rdt_ticket = request["rdt_ticket"].asUInt();
	Json::Value requestObjects;
	Json::Value subObjects;

	if(!request["ticket"].isNull()){
		response["ticket"] = request["ticket"].asUInt();
	}

	requestObjects = request["objects"];



	printf("deviceapi_put request \n%s\n-------------------\n",(char*)request.toStyledString().c_str());

	// location
	try {

		if ( requestObjects.isArray() )
			{
				unsigned int i;
				CLightBulb *pObject;
				//int ntype;
				for(i=0;i<requestObjects.size();i++){
				

						idObject = requestObjects[i]["id"].asUInt();
						pObject = (CLightBulb *)__allObjects.getObjectByID(idObject);
					

						if( pObject != NULL)
						{
							printf("test2\n");

							if(requestObjects[i]["req_type"].asUInt()==0xff40) // for schedule
							{
								CSchedule *pSchedule  = NULL;

								object_name = requestObjects[i]["name"].asString();
								pSchedule = new CSchedule(object_name.c_str());
								pSchedule->m_attr_num["effect"] = requestObjects[i]["effect"].asInt();

								subObjects = requestObjects[i]["power_on"];
								pSchedule->m_attr_num["pow_on_on"] = subObjects["on"].asInt();
								pSchedule->m_attr_num["pow_on_time"] = subObjects["time"].asInt();
								pSchedule->m_attr_num["pow_on_duration"] = subObjects["duration"].asInt();

								subObjects = requestObjects[i]["power_off"];
								pSchedule->m_attr_num["pow_off_on"] = subObjects["on"].asInt();
								pSchedule->m_attr_num["pow_off_time"] = subObjects["time"].asInt();
								pSchedule->m_attr_num["pow_off_duration"] = subObjects["duration"].asInt();

								responseObjects["id"] = pSchedule->m_id;
								responseObjects["name"] = pSchedule->m_name;
								responseObjects["type"] = pSchedule->m_type;

								pObject->add(pSchedule);

							}
							else if(requestObjects[i]["req_type"].asUInt()==0xff30) // for task
							{
								printf("test1\n");
							
								CTask *pTask  = NULL;
								CMyObject *pObject;
								Json::Value tasklist;
								Json::Value tasks;
								Json::Value fwObjects;
								int idObject_if;
								int idObject_then;

								object_name = requestObjects[i]["name"].asString();

								subObjects = requestObjects[i]["if"];
								idObject_if = subObjects["id"].asInt();
								subObjects = requestObjects[i]["then"];
								idObject_then = subObjects["id"].asInt();


								pTask = new CTask(object_name.c_str(),idObject_if,idObject_then);
								pTask->m_attr_num["effect"] = requestObjects[i]["effect"].asInt();

								subObjects = requestObjects[i]["if"];
								//accessoryObject = __allObjects.getObjectByID(idObject_if);
								//pTask->m_attr_str["if_name"] = accessoryObject->m_name;
								pTask->m_attr_num["if_id"] = subObjects["id"].asInt();
								pTask->m_attr_num["if_status"] = subObjects["status"].asInt();
								pTask->m_attr_num["if_time"] = subObjects["time"].asInt();

								subObjects = requestObjects[i]["then"];
								//accessoryObject = __allObjects.getObjectByID(idObject_then);
								//pTask->m_attr_str["then_name"] = accessoryObject->m_name;
								pTask->m_attr_num["then_id"] = subObjects["id"].asInt();
								pTask->m_attr_num["then_status"] = subObjects["status"].asInt();
								pTask->m_attr_num["then_notify"] = subObjects["notify"].asInt();


								responseObjects["id"] = pTask->m_id;
								//responseObjects["name"] = pSchedule->m_name;
								responseObjects["type"] = pTask->m_type;


													//send to fw
								int seq = 0;


								fwObjects[0]["id"] = pTask->m_type;
								fwObjects[0]["action"] = "createTask";

								tasklist["taskID"] = pTask->m_id;

								pObject = __allObjects.getObjectByID(idObject_if);
								tasklist["id"][0] = pObject->m_fwid;

								pObject = __allObjects.getObjectByID(idObject_then);
								tasklist["id"][1] = pObject->m_fwid;

								if(pTask->m_attr_num["if_status"]==0)
									tasklist["if"] = "close";
								else
									tasklist["if"] = "open";


								tasks["on"] = pTask->m_attr_num["then_status"];
								tasklist["then"] = tasks;

								fwObjects[0]["tasklist"] = tasklist;


								CTXRecord *txRecord = new CTXRecord();
						
				    			txRecord->seq = 0;
				    			txRecord->session = session;
								txRecord->request = request;
								txRecord->sendTime = time(NULL);

								
				    		
				    			seq = __ipHub.fwapi_set(fwObjects,txRecord);

				    		

					    		if( seq <= 0){
					    			delete	txRecord;
					    		} 

								


							}
					
						}else
							printf("test3\n");

				}
			}


		err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	response["uid"] = (char*) __myUID;
	response["api"] = request["api"].asString();

 
	responseRoot["error"] = err;
	if ( err_str.length() != 0 )
		responseRoot["error_str"] = err_str;


	response["objects"][0] = responseObjects;

	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);
    printf("deviceput response \n%s\n-------------------\n",(char*)responseRoot.toStyledString().c_str());

	if ( rc < 0 )
	{

	}

	return;
}


//void deviceapi_get_detail (int session,Json::Value &request)
void deviceapi_set_schedule_detail (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["api"] = request["api"].asString();

	

 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}

void deviceapi_add_a_schedule (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["api"] = request["api"].asString();

	

 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}
	
	return;
}

//void deviceapi_remove_a_schedule (int session,Json::Value &request)
void deviceapi_get_accessory_setting (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group


	response["api"] = request["api"].asString();

	

 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}
	
	return;
}

void deviceapi_get_gateway_setting (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	CGateway *pGateway = __allObjects.getGateway();	


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group



	response["uid"] = (char*) __myUID;
	response["api"] = request["api"].asString();
	response["name"] =  pGateway->m_name;
	response["led"] =  pGateway->m_attr_num["led"];

	/*
	response["home"] = "appl";
	response["led"] = 0;
	*/
	response["objects"] = objects;
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}
	
	return;
}

void deviceapi_set_accessory_setting (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group
	response["uid"] = (char*) __myUID;
	response["api"] = request["api"].asString();
	response["id"] = "s01";
	
	//response["objects"] = objects;

 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}


	return;
}

//void deviceapi_set_accessory_setting (int session,Json::Value &request)
void deviceapi_set_gateway_setting (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;
	Json::Value objects;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group
	response["uid"] = (char*) __myUID;
	response["api"] = request["api"].asString();

	CGateway *pGateway = __allObjects.getGateway();	

	if(!request["name"].isNull()){
			pGateway->m_name = request["name"].asString();
	}

	if(!request["led"].isNull()){
			pGateway->m_attr_num["led"]= request["led"].asUInt();
	}

	response["name"] =  pGateway->m_name;
	response["led"] =  pGateway->m_attr_num["led"];

	
	//response["objects"] = objects;

 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}

	return;
}


//void deviceapi_get_detail (int session,Json::Value &request)
//void deviceapi_set_detail (int session,Json::Value &request)
void deviceapi_remove_a_switch_accessory (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group

	response["api"] = request["api"].asString();
	

 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}	
	return;
}

void deviceapi_get_tasks (int session,Json::Value &request)
{
	Json::Value responseRoot;
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

 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}


	return;
}

//void deviceapi_get_detail (int session,Json::Value &request)
//void deviceapi_set_detail(session,value);
void deviceapi_add_a_task (int session,Json::Value &request)
{
	Json::Value responseRoot;
	Json::Value response;

	unsigned int rdt_ticket;
	int rc;


	rdt_ticket = request["rdt_ticket"].asUInt();

	// group

	response["api"] = request["api"].asString();
 
	responseRoot["error"] = 0;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}


	return;
}

//void deviceapi_remove (int session,Json::Value &request)



void deviceapi_api_not_found (int session,Json::Value &request)
{
	Json::Value responseRoot;
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


	responseRoot["error"] = err;
	if ( err_str.length() != 0 )
		responseRoot["error_str"] = err_str;
	responseRoot["response"] = response;

	rc = sendto_rdt_client(session,rdt_ticket,responseRoot);


	if ( rc < 0 )
	{

	}
	
	return;
}
