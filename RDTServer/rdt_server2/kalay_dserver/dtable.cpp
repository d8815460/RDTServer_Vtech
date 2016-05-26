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
	CMyObject *pGateway;
	CLocation *pLocationBedroom;;
	CAccessory *pAccessory;


	m_mapAllObjects.insert(TAllObjectPair(0x01000001,new CAccessory(0x01000001)));
	m_mapAllObjects[0x01000002] = new CAccessory(0x01000002);


	// insert Gateway
	pGateway = new CAccessory(0x70000001); //GateWay

	
	pGateway->m_attr_num["status"] = 1;
	pGateway->m_attr_str["mac_address"] = "00:0c:29:36:3f:b1",
	pGateway->m_attr_str["udid"] = "udid-00001";	
	pGateway->m_attr_str["firmware_version"] = "1.0.0";
	pGateway->m_attr_str["hardware_version"] = "1.0.1";
	pGateway->m_attr_str["ip_address"] = "192.168.1.12";
	pGateway->m_attr_str["subnet_mask"] = "255.255.255.0";
	pGateway->m_attr_str["gateway_name"] = "V-Tech IP-Hub";	

	m_mapAllObjects[pGateway->m_id] = pGateway;


	//----------------------------------------------------------------
	pLocationBedroom = new CLocation(0x13000001); 
	

	pLocationBedroom->m_attr_str["name"] = "Bedroom";

	m_mapAllObjects[pLocationBedroom->m_id] = pLocationBedroom;


	//----------------------------------------------------------------
	pAccessory = new CAccessory(0x01000001);

	pAccessory->m_attr_str["name"] = "Switch 01";
	pAccessory->m_attr_num["status"] = 0;
	pAccessory->m_attr_num["type"] =  4;
	pAccessory->m_attr_num["icon"] = 0; // 0 is use default icon
	pAccessory->m_attr_num["trigger"] = 0;

	pLocationBedroom->addAccessory(pAccessory);

	m_mapAllObjects[pAccessory->m_id] = pAccessory;

	//----------------------------------------------------------------
	pAccessory = new CAccessory(0x01000002);

	pAccessory->m_attr_str["name"] = "Light 01";
	pAccessory->m_attr_num["status"] = 1;
	pAccessory->m_attr_num["type"] = 0;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;

	pLocationBedroom->addAccessory(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;

// To Be Finish	
/*
	locations[0]["accessories"] = accessories;

	locations[1]["id"] = 0x13000002;
	locations[1]["name"] = "Bathroom";

	accessories.clear();

	accessories[0]["id"] = 0x01000003;
	accessories[0]["name"] = "Switch 02";
	accessories[0]["status"] = 0;
	accessories[0]["type"] = 4;
	accessories[0]["icon"] = 0;
	accessories[0]["trigger"] = 0;

	accessories[1]["id"] = 0x12000001;
	accessories[1]["name"] = "Group 01";
	accessories[1]["status"] = 0;
	accessories[1]["type"] = 5;
	accessories[1]["icon"] = 0;
	accessories[1]["trigger"] = 0;

	locations[1]["accessories"] = accessories;

	locations[2]["id"] = 0x13000002;
	locations[2]["name"] = "Kitchen";

	accessories.clear();

	accessories[0]["id"] = 0x01000004;
	accessories[0]["name"] = "Garage Door Sensor 01";
	accessories[0]["status"] = 2;
	accessories[0]["type"] = 2;
	accessories[0]["icon"] = 0;
	accessories[0]["trigger"] = 1;

	accessories[1]["id"] = 0x01000005;
	accessories[1]["name"] = "Light 02";
	accessories[1]["status"] = 1;
	accessories[1]["type"] = 0;
	accessories[1]["icon"] = 0;
	accessories[1]["trigger"] = 0;

	accessories[2]["id"] = 0x01000006;
	accessories[2]["name"] = "Light 03";
	accessories[2]["status"] = 1;
	accessories[2]["type"] = 0;
	accessories[2]["icon"] = 0;
	accessories[2]["trigger"] = 0;

	accessories[3]["id"] = 0x01000007;
	accessories[3]["name"] = "Light 04";
	accessories[3]["status"] = 1;
	accessories[3]["type"] = 0;
	accessories[3]["icon"] = 0;
	accessories[3]["trigger"] = 0;

	locations[2]["accessories"] = accessories;

	response["locations"] = locations;
*/

	

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


CLocation::~CLocation()
{

}

CGroup::~CGroup()
{

}

CAccessory::~CAccessory()
{

}



