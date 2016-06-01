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

	

	CLocation  *pLocationBedroom;
	CLocation  *pLocationBathroom;
	CLocation  *pLocationKitchen;
	CGroup     *pGroup;
	CAccessory *pAccessory;
	CWallSwitch *pWallSwitch01;
	CWallSwitch *pWallSwitch02;
	CWallSwitch *pWallSwitch03;

	pthread_mutex_init(&mutex_global_id, NULL);


	global_id = 0;



	//m_mapAllObjects.insert(TAllObjectPair(0x01000001,new CAccessory(0x01000001)));
	//m_mapAllObjects[0x01000002] = new CAccessory(0x01000002);


	// insert Gateway
	pGateway = new CAccessory(getID(IDTYPE_GATEWAY),"V-Tech IP-Hub",0xff00); //GateWay

	
	pGateway->m_about_num["on"] = 1;
	pGateway->m_about_str["mac_address"] = "00:0c:29:36:3f:b1",
	pGateway->m_about_str["udid"] = "udid-00001";	
	pGateway->m_about_str["firmware_version"] = "1.0.0";
	pGateway->m_about_str["hardware_version"] = "1.0.1";
	pGateway->m_about_str["ip_address"] = "192.168.1.12";
	pGateway->m_about_str["subnet_mask"] = "255.255.255.0";
	pGateway->m_about_str["gateway_name"] = "V-Tech IP-Hub";	

	m_mapAllObjects[pGateway->m_id] = pGateway;

	m_idGateway = pGateway->m_id;


	//----------------------------------------------------------
	locationOther = new CLocation(getID(IDTYPE_LOCATION),"Other");


	m_mapAllObjects[locationOther->m_id] = locationOther;
	m_mapAllLocations[locationOther->m_id] = locationOther;	


	//----------------------------------------------------------------

	pLocationBedroom = new CLocation(getID(IDTYPE_LOCATION),"Bedroom"); 
	


	m_mapAllObjects[pLocationBedroom->m_id] = pLocationBedroom;
	m_mapAllLocations[pLocationBedroom->m_id] = pLocationBedroom;


	//----------------------------------------------------------------
	pWallSwitch01 = new CWallSwitch(getID(IDTYPE_ACCESSORY),"Wall Switch 01",0x0101);

	pWallSwitch01->m_attr_num["on"] = 0;
	pWallSwitch01->m_attr_num["icon"] = 0; // 0 is use default icon
	pWallSwitch01->m_attr_num["trigger"] = 0;
	pWallSwitch01->m_attr_num["batLow"] = 1;


	pWallSwitch01->m_about_str["udid"] = "0035482900";	
	pWallSwitch01->m_about_str["firmware_version"] = "1.0.0";	

	pLocationBedroom->add(pWallSwitch01);

	m_mapAllObjects[pWallSwitch01->m_id] = pWallSwitch01;


	//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Light 71",0x0109);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;


    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;




	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocationBedroom->add(pAccessory);
	pWallSwitch01->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;


	//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Light 72",0x0109);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;


    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;


	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocationBedroom->add(pAccessory);
	pWallSwitch01->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;


	//----------------------------------------------------------------
	pWallSwitch02 = new CWallSwitch(getID(IDTYPE_ACCESSORY),"Wall Switch 02",0x0101);

	pWallSwitch02->m_attr_num["on"] = 1;
	pWallSwitch02->m_attr_num["icon"] = 0; // 0 is use default icon
	pWallSwitch02->m_attr_num["trigger"] = 0;
	pWallSwitch02->m_attr_num["batLow"] = 0;


	pWallSwitch02->m_about_str["udid"] = "0035482900";	
	pWallSwitch02->m_about_str["firmware_version"] = "1.0.0";	

	pLocationBedroom->add(pWallSwitch02);

	m_mapAllObjects[pWallSwitch02->m_id] = pWallSwitch02;


	//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Light 81",0x0109);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;


    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;




	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocationBedroom->add(pAccessory);
	pWallSwitch02->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;	


	//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Light 01",0x0109);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;


    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;




	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocationBedroom->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;



//----------------------------------------------------------------
	pLocationBathroom = new CLocation(getID(IDTYPE_LOCATION),"Bathroom"); 
	


	m_mapAllObjects[pLocationBathroom->m_id] = pLocationBathroom;
	m_mapAllLocations[pLocationBathroom->m_id] = pLocationBathroom;


//----------------------------------------------------------------
	pWallSwitch03 = new CWallSwitch(getID(IDTYPE_ACCESSORY),"Wall Switch 03",0x0101);


	pWallSwitch03->m_attr_num["on"] = 0;
	pWallSwitch03->m_attr_num["icon"] = 0;
	pWallSwitch03->m_attr_num["trigger"] = 0;
	pWallSwitch03->m_attr_num["batLow"] = 1;

	pWallSwitch03->m_about_str["udid"] = "0035482900";	
	pWallSwitch03->m_about_str["firmware_version"] = "1.0.0";		

	pLocationBathroom->add(pWallSwitch03);
	m_mapAllObjects[pWallSwitch03->m_id] = pWallSwitch03;

//----------------------------------------------------------------
	pGroup = new CGroup(getID(IDTYPE_GROUP),"Group 01");	

	pGroup->m_attr_num["on"] = 0;
	pGroup->m_attr_num["icon"] = 0;
	pGroup->m_attr_num["trigger"] = 0;


	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocationBathroom->add(pGroup);

	m_mapAllObjects[pGroup->m_id] = pGroup;
	m_mapAllGroups[pGroup->m_id] = pGroup;


	//---------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Light 11",0x0109);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;


    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;




	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocationBathroom->add(pAccessory);
	pGroup->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;

	//---------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Light 12",0x0109);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;


    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;




	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocationBathroom->add(pAccessory);
	pGroup->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;



//----------------------------------------------------------------
	pLocationKitchen = new CLocation(getID(IDTYPE_LOCATION),"Kitchen"); 
	


	m_mapAllObjects[pLocationKitchen->m_id] = pLocationKitchen;
	m_mapAllLocations[pLocationKitchen->m_id] = pLocationKitchen;


//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Garage Door Sensor 01",0x0202);

	pAccessory->m_attr_num["on"] = 2;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 1;

	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocationKitchen->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;

//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Light 02",0x0109);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;


    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;


	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocationKitchen->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;

//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Light 03",0x0109);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;

    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;


	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocationKitchen->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;

//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Light 04",0x0109);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;

    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;


	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	pLocationKitchen->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;




	//---------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Light 91",0x0109);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;


    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;




	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	locationOther->add(pAccessory);
	pGroup->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;

	//---------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Light 92",0x0109);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;


    pAccessory->m_attr_num["color_hue"] = 23;
    pAccessory->m_attr_num["color_saturation"] = 50;
    pAccessory->m_attr_num["color_brightness"] = 50;
    pAccessory->m_attr_num["white_brightness"] = 50;
    pAccessory->m_attr_num["white_temperature"] = 5000;




	pAccessory->m_about_str["udid"] = "0035482900";	
	pAccessory->m_about_str["firmware_version"] = "1.0.0";		

	locationOther->add(pAccessory);
	pGroup->add(pAccessory);
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




unsigned int CAllObjects::getID(unsigned int idtype)
{
	unsigned int ret = -1;

	pthread_mutex_lock(&mutex_global_id);

	global_id++;
	global_id &= 0x00ffffff;
	ret = (global_id | idtype);

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


CWallSwitch::~CWallSwitch()
{

}



