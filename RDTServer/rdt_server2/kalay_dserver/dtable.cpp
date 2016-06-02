#include "../headers/exception.hpp"
#include <string>
#include <iostream>
#include <unistd.h>

#include <iomanip> 
#include <json/json.h>


#include "dserver.h"
#include "dtable.h"



CAllObjects __allObjects;





CAllObjects::CAllObjects()
{
	CGateway  *pGateway;

	CLocation  *pBedroom;
	CLocation  *pBathroom;
	CLocation  *pKitchen;
	CLocation  *pLivingroom;

	CGroup     *pGroup01;
	CGroup     *pGroup02;
	CGroup     *pGroup03;

	CAccessory *pAccessory;

	CWallSwitch *pWallSwitch01;
	CWallSwitch *pWallSwitch02;
	CWallSwitch *pWallSwitch03;

	CLightBulb *pLightBulb;

	Json::Value jsonArray;

	pthread_mutex_init(&mutex_global_id, NULL);


	global_id = 0;



	//m_mapAllObjects.insert(TAllObjectPair(0x01000001,new CAccessory(0x01000001)));
	//m_mapAllObjects[0x01000002] = new CAccessory(0x01000002);


	// insert Gateway
	pGateway = new CGateway(getID(IDTYPE_GATEWAY),"V-Tech IP-Hub"); //Gateway

	

	m_mapAllObjects[pGateway->m_id] = pGateway;

	m_idGateway = pGateway->m_id;


	//----------------------------------------------------------
	locationOther = new CLocation(getID(IDTYPE_LOCATION),"Other");


	locationOther->m_attr_num["editable"] = 0;


	m_mapAllObjects[locationOther->m_id] = locationOther;
	m_mapAllLocations[locationOther->m_id] = locationOther;	


	//----------------------------------------------------------------

	pBedroom = new CLocation(getID(IDTYPE_LOCATION),"Bedroom"); 
	
	pBedroom->m_attr_num["editable"] = 1;

	m_mapAllObjects[pBedroom->m_id] = pBedroom;
	m_mapAllLocations[pBedroom->m_id] = pBedroom;


	//----------------------------------------------------------------
	pWallSwitch01 = new CWallSwitch(getID(IDTYPE_WALLSWITCH),"Wall Switch 01",pBedroom);


	m_mapAllObjects[pWallSwitch01->m_id] = pWallSwitch01;


	//----------------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 71",pBedroom,NULL);


	pWallSwitch01->add(pLightBulb);
	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;


	//----------------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 72",pBedroom,NULL);


	pWallSwitch01->add(pLightBulb);
	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;


	//----------------------------------------------------------------
	pWallSwitch02 = new CWallSwitch(getID(IDTYPE_WALLSWITCH),"Wall Switch 02",pBedroom);

	m_mapAllObjects[pWallSwitch02->m_id] = pWallSwitch02;


	//----------------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 81",pBedroom,NULL);


	pWallSwitch02->add(pLightBulb);
	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;	


	//----------------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 01",pBedroom,NULL);


	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;



//----------------------------------------------------------------
	pBathroom = new CLocation(getID(IDTYPE_LOCATION),"Bathroom"); 
	
	pBathroom->m_attr_num["editable"] = 1;

	m_mapAllObjects[pBathroom->m_id] = pBathroom;
	m_mapAllLocations[pBathroom->m_id] = pBathroom;


//----------------------------------------------------------------
	pWallSwitch03 = new CWallSwitch(getID(IDTYPE_WALLSWITCH),"Wall Switch 03",pBathroom);


	m_mapAllObjects[pWallSwitch03->m_id] = pWallSwitch03;

//----------------------------------------------------------------
	pGroup01 = new CGroup(getID(IDTYPE_GROUP),"Group 01",pBathroom);	

	pGroup01->m_attr_num["groupNo"] = 1;

	m_mapAllObjects[pGroup01->m_id] = pGroup01;
	m_mapAllGroups[pGroup01->m_id] = pGroup01;


	//---------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 11",pBathroom,pGroup01);


	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;

	//---------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 12",pBathroom,pGroup01);
	




	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;



//----------------------------------------------------------------
	pKitchen = new CLocation(getID(IDTYPE_LOCATION),"Kitchen"); 
	
	pKitchen->m_attr_num["editable"] = 1;

	m_mapAllObjects[pKitchen->m_id] = pKitchen;
	m_mapAllLocations[pKitchen->m_id] = pKitchen;


//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Garage Door Sensor 01",0x0201);

	pAccessory->m_attr_num["on"] = 2;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 1;

	pAccessory->m_attr_num["alert"] = 0;
	pAccessory->m_attr_num["testMode"] = 0;
	pAccessory->m_attr_num["arm"] = 1;
	pAccessory->m_attr_num["batLow"] = 0;
	pAccessory->m_attr_num["outLink"] = 0;

	pAccessory->m_about_str["udid"] = std::to_string(pAccessory->m_id);	
	pAccessory->m_about_str["ver"] = "1.0.0";		

	pKitchen->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;


//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"Magnetic sensor",0x0202);

	pAccessory->m_attr_num["on"] = 2;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 1;

	pAccessory->m_attr_num["alert"] = 0;
	pAccessory->m_attr_num["testMode"] = 0;
	pAccessory->m_attr_num["arm"] = 1;
	pAccessory->m_attr_num["batLow"] = 0;
	pAccessory->m_attr_num["outLink"] = 0;

	pAccessory->m_about_str["udid"] = std::to_string(pAccessory->m_id);	
	pAccessory->m_about_str["ver"] = "1.0.0";		

	pKitchen->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;


//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"motion sensor",0x0203);

	pAccessory->m_attr_num["on"] = 2;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 1;

	pAccessory->m_attr_num["alert"] = 0;
	pAccessory->m_attr_num["testMode"] = 0;
	pAccessory->m_attr_num["arm"] = 1;
	pAccessory->m_attr_num["batLow"] = 0;
	pAccessory->m_attr_num["outLink"] = 0;

	pAccessory->m_about_str["udid"] = std::to_string(pAccessory->m_id);	
	pAccessory->m_about_str["ver"] = "1.0.0";		

	pKitchen->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;	

//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"flood detector",0x0206);

	pAccessory->m_attr_num["on"] = 2;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 1;

	pAccessory->m_attr_num["alert"] = 0;
	pAccessory->m_attr_num["testMode"] = 0;
	pAccessory->m_attr_num["arm"] = 1;
	pAccessory->m_attr_num["batLow"] = 0;
	pAccessory->m_attr_num["outLink"] = 0;

	pAccessory->m_about_str["udid"] = std::to_string(pAccessory->m_id);	
	pAccessory->m_about_str["ver"] = "1.0.0";		

	pKitchen->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;		


//----------------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Kitchen Light 02",pKitchen,NULL);

	


	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;


//----------------------------------------------------------------
	pAccessory = new CAccessory(getID(IDTYPE_ACCESSORY),"AC power outlet",0x0106);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;

	pAccessory->m_about_str["udid"] = std::to_string(pAccessory->m_id);	
	pAccessory->m_about_str["ver"] = "1.0.0";		

	pKitchen->add(pAccessory);
	m_mapAllObjects[pAccessory->m_id] = pAccessory;


//----------------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 03",pKitchen,NULL);

	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;

//----------------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 04",pKitchen,NULL);

	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;


//----------------------------------------------------------------
	pGroup02 = new CGroup(getID(IDTYPE_GROUP),"Group 02",pBathroom);	

	pGroup01->m_attr_num["groupNo"] = 2;

	m_mapAllObjects[pGroup02->m_id] = pGroup02;
	m_mapAllGroups[pGroup02->m_id] = pGroup02;	

//----------------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 05",pKitchen,pGroup02);
			

	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;


//----------------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 06",pKitchen,pGroup02);

	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;


	//---------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 91",locationOther,pGroup02);

	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;

	//---------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 92",locationOther,pGroup02);

	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;



	//---------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 93",locationOther,NULL);

	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;


	//---------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 94",locationOther,NULL);

	m_mapAllObjects[pAccessory->m_id] = pAccessory;	

//----------------------------------------------------------------

	pLivingroom = new CLocation(getID(IDTYPE_LOCATION),"Living Room"); 
	
	pLivingroom->m_attr_num["editable"] = 1;

	m_mapAllObjects[pLivingroom->m_id] = pLivingroom;
	m_mapAllLocations[pLivingroom->m_id] = pLivingroom;	



//----------------------------------------------------------------
	pGroup03 = new CGroup(getID(IDTYPE_GROUP),"Group 03",pLivingroom);	

	pGroup01->m_attr_num["groupNo"] = 3;

	m_mapAllObjects[pGroup03->m_id] = pGroup03;
	m_mapAllGroups[pGroup03->m_id] = pGroup03;	


//----------------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 31",pLivingroom,NULL);
			

	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;


	//----------------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 32",pLivingroom,NULL);
	

	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;


	//---------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 95",pLivingroom,NULL);
		
	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;


	//---------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 96",pLivingroom,NULL);

	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;	


	//---------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 97",pLivingroom,pGroup03);

	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;	

	//---------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 98",pLivingroom,pGroup03);
		


	m_mapAllObjects[pLightBulb->m_id] = pLightBulb;	

	//---------------------------------------------------------
	pLightBulb = new CLightBulb(getID(IDTYPE_ACCESSORY),"Light 99",pLivingroom,pGroup03);
	
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


CLocation::CLocation(int id,const char *name) : CMyObject("location",id,name,0xff10)
{
}

CLocation::~CLocation()
{

}

CGroup::CGroup(int id,const char *name,CLocation *pLocation) : CMyObject("group",id,name,0xff11)
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

	m_about_str["udid"] = std::to_string(m_id);
}

CGroup::~CGroup()
{

}


CAccessory::CAccessory(int id,const char *name,int type) : CMyObject("accessory",id,name,type)
{
}

CAccessory::~CAccessory()
{

}


CLightBulb::CLightBulb(int id,const char *name,CLocation *pLocation,CGroup *pGroup) : CAccessory(id,name,0x0109)
{
	if ( pLocation != NULL )
		pLocation->add(this);

	if ( pGroup != NULL)
		pGroup->add(this);

	m_attr_num["on"] = 1;
	m_attr_num["icon"] = 0;
	m_attr_num["trigger"] = 0;

    m_attr_num["brightness"] = 60;
    m_attr_num["hue"] = 23;
    m_attr_num["saturation"] = 40;
    m_attr_num["colorMode"] = 0;
    m_attr_num["temperature"] = 4500;
    m_attr_num["whiteIntensity"] = 65;
    m_attr_num["fadePower"] = 0;
    m_attr_num["fadeTime"] = 1000;

	m_about_str["udid"] = std::to_string(m_id);
	m_about_str["ver"] = "1.0.0";	

}

CLightBulb::~CLightBulb()
{
}


CWallSwitch::CWallSwitch(int id,const char *name,CLocation *pLocation) : CMyObject("wallswitch",id,name,0x0101)
{
	if ( pLocation != NULL )
		pLocation->add(this);



	m_attr_num["on"] = 0;

	m_attr_num["icon"] = 0; // 0 is use default icon
	m_attr_num["trigger"] = 0;
	m_attr_num["batLow"] = 1;

	m_attr_num["alert"] = 1;
	m_attr_num["testMode"] = 1;


	m_about_str["udid"] = std::to_string(m_id);	
	m_about_str["ver"] = "1.0.0";	
}

CWallSwitch::~CWallSwitch()
{

}


CGateway::CGateway(int id,const char *name) : CMyObject("gateway",id,name,0xff00)
{
	m_attr_num["on"] = 1;
	m_attr_num["led"] = 0x05;
	m_attr_num["NumOfDev"] = 0x15;
	m_attr_str["ip"] = "192.168.1.12";
	m_attr_str["mask"] = "255.255.255.0";


	m_about_str["mac"] = "00:0c:29:36:3f:b1",
	m_about_str["uid"] = (char*) __myUID,
	m_about_str["udid"] = std::to_string(m_id);
	m_about_str["ver"] = "1.0.0";
	m_about_str["verH"] = "";
}

CGateway::~CGateway()
{
}
