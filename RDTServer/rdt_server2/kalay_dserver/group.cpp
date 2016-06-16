#include "../headers/exception.hpp"
#include <unistd.h>
#include <json/json.h>

#include <algorithm>
#include <string>
#include <iostream>



#include "dserver.h"
#include "myobject.h"
#include "group.h"
#include "dtable.h"




CGroup::CGroup(const char *name,CLocation *pLocation) : CMyObject("group",__allObjects.getID(IDTYPE_GROUP),name,0xff11)
{
	if ( pLocation != NULL )
		pLocation->add(this);	

	m_attr_num["on"] = 0;
	m_attr_num["icon"] = 0;
	m_attr_num["trigger"] = 0;

	m_attr_num["groupNo"] = 1;
	m_attr_num["brightness"] = 60;
	m_attr_num["hue"] = 75;
	m_attr_num["saturation"] = 3;
	m_attr_num["colorMode"] = 1;
	m_attr_num["temperature"] = 7000;
	m_attr_num["whiteIntensity"] = 95;
	m_attr_num["brightnessLoop1"] = 30;
	m_attr_num["hueLoop1"] = 70;
	m_attr_num["saturationLoop1"] = 80;
	m_attr_num["transientLoop1"] = 0x000D2F00;

	m_attr_num["fadePower"] = 0;
    m_attr_num["fadeTime"] = 1000;

	__allObjects.m_mapAllGroups[m_id] = this;
	
}

CGroup::~CGroup()
{
	std::map<unsigned int, CMyObject *>::iterator iterGroup;
	list<CMyObject*>::iterator iterX;

	iterGroup = __allObjects.m_mapAllGroups.find(m_id);
	if ( iterGroup != __allObjects.m_mapAllGroups.end() ) // Found it
	{
		__allObjects.m_mapAllGroups.erase(iterGroup);
	}

	for(iterX = m_listObject.begin(); iterX!=m_listObject.end(); ++iterX)
	{
		CMyObject *pSubObject;

		pSubObject = *iterX;

		pSubObject->m_pGroup = NULL;
	}	

}

int CGroup::add (CMyObject *pObject)
{
	pObject->m_pGroup = this;

	addToList(pObject);

	return 1;
}

int CGroup::remove (CMyObject *pObject)
{
	removeFromList(pObject);

	pObject->m_pGroup = NULL;

	return 1;
}

