#include "../headers/exception.hpp"
#include <unistd.h>
#include <json/json.h>

#include <algorithm>
#include <string>
#include <iostream>



#include "dserver.h"
#include "myobject.h"

#include "dtable.h"



CMyObject::CMyObject(const char *myClassType,int id,const char *name,int type,int icon)
{
	m_id = id;
	m_type = type;
	m_sClassType = myClassType;
	m_name = name;

	m_pLocation = NULL;
	m_pGroup = NULL;
	m_pSwitch = NULL;

	m_orderInLocation = 0;

	m_attr_str["name"] = m_name;
	m_attr_num["icon"] = icon;

	if (   m_type == 0x0201   // garage sensor (door)
		|| m_type == 0x0202   // Magnetic sensor
	 	|| m_type == 0x0203   // motion sensor
		|| m_type == 0x0206 ) // flood detector 
		m_attr_num["status"] = 2;
	else
		m_attr_num["status"] = 0;

	__allObjects.m_mapAllObjects[m_id] = this;
//	__allObjects.m_mapObjectsByFWID[m_fwid] = this; // ??? should I do that ??


}

CMyObject::~CMyObject()
{
	if ( m_pLocation != NULL )
	{
		list<CMyObject*>::iterator iter2;

		iter2 = std::find(m_pLocation->m_listObject.begin(), m_pLocation->m_listObject.end(), this);

		if ( iter2 != m_pLocation->m_listObject.end() )
		{
			m_pLocation->m_listObject.erase(iter2);
		}
	}

	if ( m_pGroup != NULL )
	{
		list<CMyObject*>::iterator iter2;

		iter2 = std::find(m_pGroup->m_listObject.begin(), m_pGroup->m_listObject.end(), this);
		if ( iter2 != m_pGroup->m_listObject.end() )
		{
			m_pGroup->m_listObject.erase(iter2);
		}
	}

	if ( m_pSwitch != NULL )
	{
		list<CMyObject*>::iterator iter2;

		iter2 = std::find(m_pSwitch->m_listObject.begin(), m_pSwitch->m_listObject.end(), this);
		if ( iter2 != m_pSwitch->m_listObject.end() )
		{
			m_pSwitch->m_listObject.erase(iter2);
		}

	}





	// Remove from all_object
	{
		std::map<unsigned int, CMyObject *>::iterator iter;

		iter = __allObjects.m_mapAllObjects.find(m_id);
		if ( iter != __allObjects.m_mapAllObjects.end() ) // Found it
		{
			__allObjects.m_mapAllObjects.erase(iter);
		}

	}


	// Remove from all_object_by_fwid
	{
		std::map<string, CMyObject *>::iterator iter;

		iter = __allObjects.m_mapObjectsByFWID.find(m_fwid);
		if ( iter != __allObjects.m_mapObjectsByFWID.end() ) // Found it
		{
			__allObjects.m_mapObjectsByFWID.erase(iter);
		}	
	}


}

int CMyObject::addToList (CMyObject *pObject)
{
	m_listObject.push_back(pObject);

	return 1;
}	




int CMyObject::removeFromList (CMyObject *pObject)
{
	int ret = 0;
	list<CMyObject*>::iterator iter2;
	list<CMyObject*>::iterator j;

	iter2 = std::find(m_listObject.begin(), m_listObject.end(), pObject);
	if ( iter2 != m_listObject.end() )
	{
		m_listObject.erase(iter2);
		ret = 1;
	}


	return ret;
}

int CMyObject::addToListtask (CMyObject *pObject)
{
	m_listObject_task.push_back(pObject);
    
	return 1;
}	




int CMyObject::removeFromListtask (CMyObject *pObject)
{
	int ret = 0;
	list<CMyObject*>::iterator iter2;
	list<CMyObject*>::iterator j;

	iter2 = std::find(m_listObject_task.begin(), m_listObject_task.end(), pObject);
	if ( iter2 != m_listObject_task.end() )
	{
		m_listObject_task.erase(iter2);
		ret = 1;
	}


	return ret;
}
int CMyObject::addToListactivity (CMyObject *pObject)
{
	m_listObject_task.push_back(pObject);
    pObject->m_pAccessory = this;

	return 1;
}	


int CMyObject::removeFromListactivity (CMyObject *pObject)
{
	int ret = 0;
	list<CMyObject*>::iterator iter2;
	list<CMyObject*>::iterator j;

	iter2 = std::find(m_listObject_activity.begin(), m_listObject_activity.end(), pObject);
	if ( iter2 != m_listObject_activity.end() )
	{
		m_listObject_activity.erase(iter2);
		ret = 1;
	}
	


	return ret;
}		

int CMyObject::add (CMyObject *pObject)
{
	if(pObject->m_type==65328){
		addToListtask(pObject);
	}
	else if(pObject->m_type==0) //fix if activity type not equal 0
	{
		addToListactivity(pObject);
	}	
	else{	
		addToList(pObject);
	}
	return 1;
}

int CMyObject::remove (CMyObject *pObject)
{
	if(pObject->m_type==65328)
		removeFromListtask(pObject);
	else if(pObject->m_type==0)
		removeFromListactivity(pObject);
	else
		removeFromList(pObject);

	return 1;
}

int CMyObject::getIDTYPE()
{
	return (m_id&0xff000000);
}



int CMyObject::getBaseAttr(Json::Value& jsonAttr)
{
	int count = 0;

	map<string,int>::iterator iNum;
	map<string,string>::iterator iStr;


	jsonAttr["id"] = m_id;
	jsonAttr["type"] = m_type;
	jsonAttr["name"] = m_attr_str["name"];


	if(m_type == 65328 ){
		jsonAttr["enabled"] = m_attr_num["enabled"];

	}
	else
	{
		if(m_type ==265 || m_type ==65344  || m_type ==65297)
		{
			jsonAttr["effect"] 	= m_attr_num["effect"];

		}	
		jsonAttr["icon"] 	= m_attr_num["icon"];
		jsonAttr["trigger"] = m_attr_num["trigger"];
		//jsonAttr["alert"] 	= m_attr_num["alert"];
		//jsonAttr["on"] 		= m_attr_num["on"];
		jsonAttr["status"] 		= m_attr_num["status"];

		if ( m_pLocation != NULL )
			jsonAttr["order"] = m_orderInLocation;		
	}

	return count;
}



int CMyObject::getAttr(Json::Value& jsonAttr)
{
	int count = 0;

	map<string,int>::iterator iNum;
	map<string,string>::iterator iStr;
	

	jsonAttr["id"] = m_id;
	jsonAttr["type"] = m_type;

	

	for(iNum = m_attr_num.begin(); iNum!=m_attr_num.end(); ++iNum)
	{
		string key;

		key = iNum->first.c_str();
		

		if ( 	key != "on"
			 && key != "alert" 
			 && key != "name"
			 && key != "type"
			 && key != "id"		
			 && key != "pow_off_duration"
			 && key != "pow_off_on"
			 && key != "pow_off_time"
			 && key != "pow_on_duration"
			 && key != "pow_on_on"
			 && key != "pow_on_time")
		{
			jsonAttr[key.c_str()] = iNum->second;
			count++;
		}

	}

	for(iStr = m_attr_str.begin(); iStr!=m_attr_str.end(); ++iStr)
	{
		jsonAttr[iStr->first.c_str()] = iStr->second.c_str();
		count++;
	}


	if ( m_pLocation != NULL )
		jsonAttr["order"] = m_orderInLocation;		

	return count;
}

int CMyObject::getAbout(Json::Value& jsonAbout)
{
	int count = 0;

	map<string,int>::iterator iNum;
	map<string,string>::iterator iStr;

	jsonAbout["type"] = m_type;
	string key;

	for(iNum = m_about_num.begin(); iNum!=m_about_num.end(); ++iNum)
	{

		jsonAbout[iNum->first.c_str()] = iNum->second;
	}

	for(iStr = m_about_str.begin(); iStr!=m_about_str.end(); ++iStr)
	{
			

			jsonAbout[iStr->first.c_str()] = iStr->second.c_str();
	}
	

	return count;
}

int CMyObject::gettasks(Json::Value& subObjects)
{
	list<CMyObject*>::iterator iter;
	map<string,int>::iterator iNum;
	map<string,string>::iterator iStr;	
	int cntSubObject = 0;

	for(iter = m_listObject_task.begin(); iter!=m_listObject_task.end(); ++iter)
	{
		CMyObject *pSubObject;

		pSubObject = *iter;


		//pSubObject->getAttr(subObjects[cntSubObject]);
		pSubObject->getBaseAttr(subObjects[cntSubObject]);


		cntSubObject++;
	}


	return cntSubObject;
}


int CMyObject::getSubObjects(Json::Value& subObjects)
{
	list<CMyObject*>::iterator iter;
	map<string,int>::iterator iNum;
	map<string,string>::iterator iStr;
	Json::Value Objects;
	int cntSubObject = 0;

	for(iter = m_listObject.begin(); iter!=m_listObject.end(); ++iter)
	{
		CMyObject *pSubObject;

		pSubObject = *iter;


		//pSubObject->getAttr(subObjects[cntSubObject]);
		pSubObject->getBaseAttr(subObjects[cntSubObject]);
		if(pSubObject->m_type ==0xff40){
			subObjects[cntSubObject]["on"] = pSubObject->m_attr_num["on"];
			/*
			subObjects[cntSubObject]["repeat"] = pSubObject->m_attr_num["repeat"];
			Objects["on"] = pSubObject->m_attr_num["pow_on_on"];
			Objects["duration"] = pSubObject->m_attr_num["pow_on_duration"];
			Objects["time"] = pSubObject->m_attr_num["pow_on_time"];
			subObjects[cntSubObject]["power_on"] = Objects;

			Objects["on"] = pSubObject->m_attr_num["pow_off_on"];
			Objects["duration"] = pSubObject->m_attr_num["pow_off_duration"];
			Objects["time"] = pSubObject->m_attr_num["pow_off_time"];
			subObjects[cntSubObject]["power_off"] = Objects;
			*/
		}


		cntSubObject++;
	}


	return cntSubObject;
}



int  CMyObject::getDetail(Json::Value &jsonDetail)
{
	Json::Value subObjects;
	int err = 1;
	string err_str;	

	try {
			list<CMyObject*>::iterator iter;

	
			map<string,int>::iterator iNum;
			map<string,string>::iterator iStr;	
			map<string,action *>::iterator iact;	
			
			//jsonDetail["id"] = m_id;

			if(this->m_type==0xff40)//schedule
			{ 
				Json::Value subObjects;
				Json::Value action;

				jsonDetail["id"] = 		m_id;
				jsonDetail["name"] = 	m_name;
				jsonDetail["type"] = 	m_type;
				jsonDetail["on"] = 		m_attr_num["on"];
				jsonDetail["effect"] = 	m_attr_num["effect"];
				jsonDetail["activated"] = m_attr_num["activated"];
				jsonDetail["repeat"] = 		m_attr_num["repeat"];
				//need to be ideal
/*
				for(iact = (CSchedule*)m_attr_action.begin(); iact!=(CSchedule*)m_attr_action.end(); ++iact)
				{

					action["on"] = iact->second->m_attr_num["on"];
					action["time"] = iact->second->m_attr_num["time"];
					action["duration"] = iact->second->m_attr_num["duration"];
					subObjects[iact->first.c_str()] = action;
				}
*/
				subObjects["on"] = m_attr_num["pow_on_on"];
				subObjects["duration"] = m_attr_num["pow_on_duration"];
				subObjects["time"] = m_attr_num["pow_on_time"];
				jsonDetail["power_on"] = subObjects;

				subObjects["on"] = m_attr_num["pow_off_on"];
				subObjects["duration"] = m_attr_num["pow_off_duration"];
				subObjects["time"] = m_attr_num["pow_off_time"];
				jsonDetail["power_off"] = subObjects;


				


			}
			else if(this->m_type==0xff30)//task
			{
				Json::Value subObjects;
				Json::Value action;

				getBaseAttr(jsonDetail);


				subObjects["id"] = m_attr_num["if_id"];
				subObjects["name"] = m_attr_str["if_name"];
				subObjects["time"] = m_attr_num["if_time"];
				subObjects["status"] = m_attr_num["if_status"];
				subObjects["type"] = m_attr_num["if_type"];
				jsonDetail["if"] = subObjects;

				subObjects["id"] = m_attr_num["then_id"];
				subObjects["name"] = m_attr_str["then_name"];
				subObjects["notify"] = m_attr_num["then_notify"];
				subObjects["status"] = m_attr_num["then_status"];
				subObjects["type"] = m_attr_num["then_type"];
				jsonDetail["then"] = subObjects;

			}

			else{
				getAttr(jsonDetail);
			}

			if ( m_pLocation != NULL ) 
			{
				Json::Value location;				

				location["id"] = m_pLocation->m_id;
				location["name"] = m_pLocation->m_attr_str["name"];

				jsonDetail["location"] = location;
			}	
			

			if ( m_pGroup != NULL ) 
			{
				Json::Value group;

				group["id"] = m_pGroup->m_id;
				group["name"] = m_pGroup->m_attr_str["name"];

				jsonDetail["group"] = group;
			}	


			if ( m_listObject.size() > 0 )
			{
				getSubObjects(subObjects);
				jsonDetail["objects"] = subObjects;
			}


		err = 0;

    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }

	


	return err;
}

