#include "../headers/exception.hpp"
#include <string>
#include <iostream>
#include <unistd.h>

#include <iomanip> 
#include <json/json.h>


#include "dtable.h"



CAllObjects __allObjects;


CAllObjects::CAllObjects()
{
	CMyObject  *pGateway;
	CLocation  *pLocation;
	CGroup     *pGroup;
	CAccessory *pAccessory;

	pthread_mutex_init(&mutex_global_id, NULL);


	global_id = 0;


	m_mapAllObjects.insert(TAllObjectPair(0x01000001,new CAccessory(0x01000001)));
	m_mapAllObjects[0x01000002] = new CAccessory(0x01000002);


	// insert Gateway
	pGateway = new CAccessory(0x70000001); //GateWay

	
	pGateway->m_about_num["status"] = 1;
	pGateway->m_about_str["mac_address"] = "00:0c:29:36:3f:b1",
	pGateway->m_about_str["udid"] = "udid-00001";	
	pGateway->m_about_str["firmware_version"] = "1.0.0";
	pGateway->m_about_str["hardware_version"] = "1.0.1";
	pGateway->m_about_str["ip_address"] = "192.168.1.12";
	pGateway->m_about_str["subnet_mask"] = "255.255.255.0";
	pGateway->m_about_str["gateway_name"] = "V-Tech IP-Hub";	

	m_mapAllObjects[pGateway->m_id] = pGateway;


	//----------------------------------------------------------------
	pLocation = new CLocation(0x13000001); 
	

	pLocation->m_attr_str["name"] = "Bedroom";

	m_mapAllObjects[pLocation->m_id] = pLocation;
	m_mapAllLocations[pLocation->m_id] = pLocation;


	//----------------------------------------------------------------
	pAccessory = new CAccessory(0x01000001);

	pAccessory->m_attr_str["name"] = "Switch 01";
	pAccessory->m_attr_num["status"] = 0;
	pAccessory->m_attr_num["type"] =  4;
	pAccessory->m_attr_num["icon"] = 0; // 0 is use default icon
	pAccessory->m_attr_num["trigger"] = 0;


	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";	

	pLocation->add(pAccessory);

	m_mapAllObjects[pAccessory->m_id] = pAccessory;


	//----------------------------------------------------------------
	pAccessory = new CAccessory(0x01000102);

	pAccessory->m_attr_str["name"] = "Wall Switch";
	pAccessory->m_attr_num["status"] = 1;
	pAccessory->m_attr_num["type"] =  4;
	pAccessory->m_attr_num["icon"] = 0; // 0 is use default icon
	pAccessory->m_attr_num["trigger"] = 0;
	pAccessory->m_attr_num["low_battery"] = 1;


	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";	

	pLocation->add(pAccessory);

	m_mapAllObjects[pAccessory->m_id] = pAccessory;


	//----------------------------------------------------------------
	pAccessory = new CAccessory(0x01000002);

	pAccessory->m_attr_str["name"] = "Light 01";
	pAccessory->m_attr_num["status"] = 1;
	pAccessory->m_attr_num["type"] = 0;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;


    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;




	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocation->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;



//----------------------------------------------------------------
	pLocation = new CLocation(0x13000002); 
	

	pLocation->m_attr_str["name"] = "Bathroom";

	m_mapAllObjects[pLocation->m_id] = pLocation;
	m_mapAllLocations[pLocation->m_id] = pLocation;


//----------------------------------------------------------------
	pAccessory = new CAccessory(0x01000003);


	pAccessory->m_attr_str["name"] = "Switch 02";
	pAccessory->m_attr_num["status"] = 0;
	pAccessory->m_attr_num["type"] = 4;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;

	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocation->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;

//----------------------------------------------------------------
	pGroup = new CGroup(0x12000001);	

	pGroup->m_attr_str["name"] = "Group 01";
	pGroup->m_attr_num["status"] = 0;
	pGroup->m_attr_num["type"] = 5;
	pGroup->m_attr_num["icon"] = 0;
	pGroup->m_attr_num["trigger"] = 0;


	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocation->add(pGroup);


	m_mapAllObjects[pGroup->m_id] = pGroup;
	m_mapAllGroups[pGroup->m_id] = pGroup;


//----------------------------------------------------------------
	pLocation = new CLocation(0x13000003); 
	

	pLocation->m_attr_str["name"] = "Kitchen";

	m_mapAllObjects[pLocation->m_id] = pLocation;
	m_mapAllLocations[pLocation->m_id] = pLocation;


//----------------------------------------------------------------
	pAccessory = new CAccessory(0x01000004);

	pAccessory->m_attr_str["name"] = "Garage Door Sensor 01";
	pAccessory->m_attr_num["status"] = 2;
	pAccessory->m_attr_num["type"] = 2;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 1;

	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocation->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;

//----------------------------------------------------------------
	pAccessory = new CAccessory(0x01000005);

	pAccessory->m_attr_str["name"] = "Light 02";
	pAccessory->m_attr_num["status"] = 1;
	pAccessory->m_attr_num["type"] = 0;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;


    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;


	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocation->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;

//----------------------------------------------------------------
	pAccessory = new CAccessory(0x01000006);

	pAccessory->m_attr_str["name"] = "Light 03";
	pAccessory->m_attr_num["status"] = 1;
	pAccessory->m_attr_num["type"] = 0;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;

    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;


	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocation->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;

//----------------------------------------------------------------
	pAccessory = new CAccessory(0x01000007);

	pAccessory->m_attr_str["name"] = "Light 04";
	pAccessory->m_attr_num["status"] = 1;
	pAccessory->m_attr_num["type"] = 0;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;

    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;


	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocation->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;

	

	return;
}

CAllObjects::~CAllObjects()
{
	TAllObjectMap::iterator p;

	for(p = m_mapAllObjects.begin(); p!=m_mapAllObjects.end(); ++p)
	{
		CMyObject *pObject;
		
		pObject = p->second;

		delete pObject;
	}

	m_mapAllObjects.clear();

	return;
}

int CAllObjects::dump()
{
	TAllObjectMap::iterator p;

	for(p = m_mapAllObjects.begin(); p!=m_mapAllObjects.end(); ++p)
	{
		CMyObject *pObject;

		
		pObject = p->second;


		printf("Dump All Objects: id:0x%0x obj:%p class:%s \n"
			,(int)p->first
			,p->second
			, pObject->m_sClassType.c_str());

	}


	return 0;

}

int CAllObjects::dumpByLocation()
{
	TAllObjectMap::iterator p;
	list<CMyObject*>::iterator j;

	printf("Dump All Objects by Location:\n");

	for(p = m_mapAllLocations.begin(); p!=m_mapAllLocations.end(); ++p)
	{
		CLocation *pLocation;

		
		pLocation = (CLocation*) p->second;


		printf("Location id:0x%0x  name:%s \n"
			, pLocation->m_id
			, pLocation->m_attr_str["name"].c_str());

		
		for(j = pLocation->m_listObject.begin(); j!=pLocation->m_listObject.end(); ++j)
		{
			CMyObject *pObject;

			pObject = *j;

			printf("\t object id:0x%0x  name:%s \n"
					,pObject->m_id
					, pObject->m_attr_str["name"].c_str());



		}	

	}


	return 0;
}


unsigned int CAllObjects::getID(unsigned int type)
{
	unsigned int ret = -1;

	pthread_mutex_lock(&mutex_global_id);

	global_id++;
	global_id &= 0x00ffffff;
	ret = (global_id | type);

	pthread_mutex_unlock(&mutex_global_id);

	return ret;
}


CLocation::~CLocation()
{

}

CGroup::~CGroup()
{

}

CAccessory::~CAccessory()
{

}



