#include "../headers/exception.hpp"
#include <unistd.h>
#include <json/json.h>

#include <algorithm>
#include <string>
#include <iostream>





#include "dtable.h"
#include "dserver.h"
#include "myobject.h"
#include "schedule.h"



action::action(int on,int duration,int time){

	 	
	 	m_attr_num["on"] = on ;
	 	m_attr_num["time"] = time;
	 	m_attr_num["duration"] = duration;
	
}


CSchedule::CSchedule(const char *name): CMyObject("schedule",__allObjects.getID(IDTYPE_LOCATION),name,0xff40,0)
{	
	std::map<std::string,action *> m_attr_action;

	action *paction;

	paction = new action(1,5,128);
	m_attr_action["power_on"] = paction;
	paction = new action(0,5,128);
	m_attr_action["power_off"] = paction;

	
	m_attr_num["activated"] = 1;
	//m_attr_num["brightness"] = 60;
	m_attr_num["on"] = 1;
	m_attr_num["effect"] = 1;



	m_attr_num["pow_on_on"] = 1;
	m_attr_num["pow_on_duration"] = 5;
	m_attr_num["pow_on_time"] = 128;

	m_attr_num["pow_off_on"] = 0;
	m_attr_num["pow_off_duration"] = 15;
	m_attr_num["pow_off_time"] = 128;

	m_attr_num["repeat"] = 127;
	

	__allObjects.m_mapAllSchedules[m_id] = this;


}

CSchedule::~CSchedule()
{
	std::map<unsigned int, CMyObject *>::iterator iterSchedule;
	list<CMyObject*>::iterator iterX;

	iterSchedule = __allObjects.m_mapAllSchedules.find(m_id);
	if ( iterSchedule != __allObjects.m_mapAllSchedules.end() ) // Found it
	{
		__allObjects.m_mapAllSchedules.erase(iterSchedule);
	}
/*
	for(iterX = m_listObject.begin(); iterX!=m_listObject.end(); ++iterX)
	{
		CMyObject *pSubObject;

		pSubObject = *iterX;

		pSubObject->m_pSchedule = NULL;
	}	
	*/
}

int CSchedule::add (CMyObject *pObject)
{
	if(pObject->m_pSchedule!=NULL){
		pObject->m_pSchedule->remove(pObject);
	}


	pObject->m_pSchedule = this;

	addToList(pObject);

	return 1;
}

int CSchedule::remove (CMyObject *pObject)
{
	removeFromList(pObject);

	pObject->m_pSchedule = NULL;

	return 1;
}




