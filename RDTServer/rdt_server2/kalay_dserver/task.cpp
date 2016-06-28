#include "../headers/exception.hpp"
#include <unistd.h>
#include <json/json.h>

#include <algorithm>
#include <string>
#include <iostream>



#include "dserver.h"
#include "myobject.h"
#include "task.h"
#include "dtable.h"



CTask::CTask(const char *name,int accessory_id_if,int accessory_id_then): CMyObject("task",__allObjects.getID(IDTYPE_TASK),name,0xff30,0)
{

	//m_attr_num["activated"] = 1;
	//m_attr_num["brightness"] = 60;
	CMyObject *pObject;

	m_attr_num["enabled"] = 0;
	m_attr_num["effect"] = 1;


	pObject = __allObjects.getObjectByID(accessory_id_if);
	m_attr_num["if_id"] = accessory_id_if;
	m_attr_num["if_status"] = 0;
	m_attr_num["if_time"] = 128;
	m_attr_num["if_type"] = pObject->m_type;
	m_attr_str["if_name"] = pObject->m_name;


	pObject = __allObjects.getObjectByID(accessory_id_then);
	m_attr_num["then_id"] = accessory_id_then;
	m_attr_num["then_status"] = 1;
	m_attr_num["then_notify"] = 0;
	m_attr_num["then_type"] = pObject->m_type;
    m_attr_str["then_name"] = pObject->m_name;
	
	__allObjects.m_mapAllTasks[m_id] = this;
	

}

CTask::~CTask()
{
	std::map<unsigned int, CMyObject *>::iterator iterSchedule;
	list<CMyObject*>::iterator iterX;

	iterSchedule = __allObjects.m_mapAllTasks.find(m_id);
	if ( iterSchedule != __allObjects.m_mapAllTasks.end() ) // Found it
	{
		__allObjects.m_mapAllTasks.erase(iterSchedule);
	}
	printf("remove schedule\n");
	/*
	for(iterX = m_listObject.begin(); iterX!=m_listObject.end(); ++iterX)
	{
		CMyObject *pSubObject;

		pSubObject = *iterX;

		pSubObject->m_pSchedule = NULL;
		pSubObject->remove(this);
	
	}	
	*/

}
