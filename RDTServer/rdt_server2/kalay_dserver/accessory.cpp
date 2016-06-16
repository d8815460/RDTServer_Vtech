#include "../headers/exception.hpp"
#include <unistd.h>
#include <json/json.h>

#include <algorithm>
#include <string>
#include <iostream>



#include "dserver.h"
#include "myobject.h"
#include "accessory.h"
#include "dtable.h"





CAccessory::CAccessory(const char *name,int type,CLocation *pLocation) : CMyObject("accessory",__allObjects.getID(IDTYPE_ACCESSORY),name,type)
{
	if ( pLocation != NULL )
		pLocation->add(this);	
}

CAccessory::~CAccessory()
{

}




CLightBulb::CLightBulb(const char *name,CLocation *pLocation,CGroup *pGroup) : CAccessory(name,0x0109,pLocation)
{
	if ( pGroup != NULL)
		pGroup->add(this);

	m_attr_num["on"] = 1;
	m_attr_num["icon"] = 0;
	m_attr_num["trigger"] = 0;

    m_attr_num["brightness"] = 60;
    m_attr_num["hue"] = 23;
    m_attr_num["saturation"] = 40;
    m_attr_num["colorMode"] = 1;
    m_attr_num["temperature"] = 4500;
    m_attr_num["whiteIntensity"] = 65;
    m_attr_num["fadePower"] = 0;
    m_attr_num["fadeTime"] = 1000;

	m_about_str["ver"] = "1.0.0";	

}

CLightBulb::~CLightBulb()
{
}


CSensor::CSensor(const char *name,int type,CLocation *pLocation): CAccessory(name,type,pLocation)
{
	m_attr_num["on"] = 2;
	m_attr_num["icon"] = 0;
	m_attr_num["trigger"] = 1;

	m_attr_num["alert"] = 0;
	m_attr_num["testMode"] = 0;
	m_attr_num["arm"] = 1;
	m_attr_num["batLow"] = 0;
	m_attr_num["outLink"] = 0;

	m_about_str["ver"] = "1.0.0";	
}

CSensor::~CSensor()
{

}



CWallSwitch::CWallSwitch(const char *name,CLocation *pLocation) : CMyObject("wallswitch",__allObjects.getID(IDTYPE_WALLSWITCH),name,0x0101)
{
	if ( pLocation != NULL )
		pLocation->add(this);


	m_attr_num["icon"] = 0; // 0 is use default icon
	m_attr_num["trigger"] = 0;
	m_attr_num["batLow"] = 1;

	m_attr_num["alert"] = 1;
	m_attr_num["testMode"] = 1;

	m_about_str["ver"] = "1.0.0";	
}

CWallSwitch::~CWallSwitch()
{
	list<CMyObject*>::iterator iterX;

	for(iterX = m_listObject.begin(); iterX!=m_listObject.end(); ++iterX)
	{
		CSwitch *pSwitch;

		pSwitch = (CSwitch *)(*iterX);

		pSwitch->m_pWallSwitch = NULL;
	}	

}

int CWallSwitch::add (CSwitch *pSwitch)
{
	pSwitch->m_pWallSwitch = this;

	addToList(pSwitch);

	return 1;
}

int CWallSwitch::remove (CSwitch *pSwitch)
{
	removeFromList(pSwitch);

	pSwitch->m_pWallSwitch = NULL;

	return 1;
}


CSwitch::CSwitch(const char *name,CWallSwitch *pWallSwitch,CAccessory *pAccessory) : CMyObject("switch",__allObjects.getID(IDTYPE_SWITCH),name,0xff20)
{
	m_pWallSwitch = pWallSwitch;

	if ( pAccessory != NULL )
	{
		pAccessory->m_pSwitch = this;
		addToList(pAccessory);
	}


	m_attr_num["on"] = 0;
	m_attr_num["icon"] = 0; // 0 is use default icon

	m_pWallSwitch->add(this);


}

CSwitch::~CSwitch()
{
	if ( m_pAccessory != NULL )
		m_pAccessory->m_pSwitch = NULL;

	//m_pWallSwitch 

	if ( m_pWallSwitch != NULL )
	{
		list<CMyObject*>::iterator iter2;

		iter2 = std::find(m_pWallSwitch->m_listObject.begin(), m_pWallSwitch->m_listObject.end(), this);
		if ( iter2 != m_pWallSwitch->m_listObject.end() )
		{
			m_pWallSwitch->m_listObject.erase(iter2);
		}
	}

}
