#include "../headers/exception.hpp"
#include <unistd.h>
#include <json/json.h>

#include <algorithm>
#include <string>
#include <iostream>



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

	CSensor *pSensor;

	CWallSwitch *pWallSwitchBedroom;
	CWallSwitch *pWallSwitchBathroom;
	CWallSwitch *pWallSwitchKitchen;
	CWallSwitch *pWallSwitchLivingroom;

	CSwitch 	*pSwitch;

	CLightBulb *pLightBulb;

	Json::Value jsonArray;

	pthread_mutex_init(&mutex_global_id, NULL);


	global_id = 0;




	// insert Gateway
	pGateway = new CGateway(getID(IDTYPE_GATEWAY),"V-Tech IP-Hub"); //Gateway

	m_idGateway = pGateway->m_id;


	//----------------------------------------------------------
	locationOther = new CLocation("Other");


	locationOther->m_attr_num["editable"] = 0;



	//----------------------------------------------------------------

	pBedroom = new CLocation("Bedroom"); 
	
	pBedroom->m_attr_num["editable"] = 1;

	//----------------------------------------------------------------
	pWallSwitchBedroom = new CWallSwitch("Bedroom WallSwitch",pBedroom);


	//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Bedroom Light-1",pBedroom,NULL);
	pSwitch = new CSwitch("Bedroom Switch 01",pWallSwitchBedroom,pLightBulb);

	 pLightBulb->m_attr_num["colorMode"] = 0;


	//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Bedroom Light-2",pBedroom,NULL);
	pSwitch = new CSwitch("Bedroom Switch 02",pWallSwitchBedroom,pLightBulb);

	pLightBulb->m_attr_num["colorMode"] = 0;



	//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Bedroom Light-3",pBedroom,NULL);
	pSwitch = new CSwitch("Bedroom Switch 03",pWallSwitchBedroom,pLightBulb);

	//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Bedroom Light-4",pBedroom,NULL);
	pSwitch = new CSwitch("Bedroom Switch 04",pWallSwitchBedroom,pLightBulb);


	//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Bedroom Light-5",pBedroom,NULL);

	//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Bedroom Light-6",pBedroom,NULL);


	//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Light 81",pBedroom,NULL);


	//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Light 01",pBedroom,NULL);





//----------------------------------------------------------------
	pBathroom = new CLocation("Bathroom"); 
	
	pBathroom->m_attr_num["editable"] = 1;

//----------------------------------------------------------------
	pWallSwitchBathroom = new CWallSwitch("Bathroom WallSwitch",pBathroom);



//----------------------------------------------------------------
	pGroup01 = new CGroup("Group 01",pBathroom);	

	pGroup01->m_attr_num["groupNo"] = 1;


	//---------------------------------------------------------
	pLightBulb = new CLightBulb("Bathroom Light-1",pBathroom,pGroup01);
	pLightBulb->m_attr_num["colorMode"] = 0;

	//---------------------------------------------------------
	pLightBulb = new CLightBulb("Bathroom Light-2",pBathroom,pGroup01);
	pLightBulb->m_attr_num["colorMode"] = 0;

	//---------------------------------------------------------
	pLightBulb = new CLightBulb("Bathroom Light-3",pBathroom,pGroup01);

	//---------------------------------------------------------
	pLightBulb = new CLightBulb("Bathroom Light-4",pBathroom,pGroup01);	


	//---------------------------------------------------------
	pLightBulb = new CLightBulb("Bathroom Light-5",pBathroom,pGroup01);
	pSwitch = new CSwitch("Bathroom Switch 01",pWallSwitchBathroom,pLightBulb);


	//---------------------------------------------------------
	pLightBulb = new CLightBulb("Bathroom Light-6",pBathroom,pGroup01);	
	pSwitch = new CSwitch("Bathroom Switch 02",pWallSwitchBathroom,pLightBulb);


	//---------------------------------------------------------
	pLightBulb = new CLightBulb("Bathroom Light-7",pBathroom,NULL);
	pSwitch = new CSwitch("Bathroom Switch 03",pWallSwitchBathroom,pLightBulb);

	//---------------------------------------------------------
	pLightBulb = new CLightBulb("Bathroom Light-8",pBathroom,NULL);
	pSwitch = new CSwitch("Bathroom Switch 04",pWallSwitchBathroom,pLightBulb);

	//---------------------------------------------------------
	pLightBulb = new CLightBulb("Bathroom Light-9",pBathroom,NULL);

	

//----------------------------------------------------------------
	pKitchen = new CLocation("Kitchen"); 
	
	pKitchen->m_attr_num["editable"] = 1;

//----------------------------------------------------------------
	pWallSwitchKitchen = new CWallSwitch("Kitchen WallSwitch",pKitchen);



//----------------------------------------------------------------
	pSensor = new CSensor("Garage Door Sensor 01",0x0201,pKitchen);

//----------------------------------------------------------------
	pSensor = new CSensor("Magnetic sensor",0x0202,pKitchen);

	pSensor->m_attr_num["batLow"] = 1;
	pSensor->m_attr_num["outLink"] = 1;



//----------------------------------------------------------------
	pSensor = new CSensor("motion sensor",0x0203,pKitchen);

//----------------------------------------------------------------
	pSensor = new CSensor("flood detector",0x0206,pKitchen);


//----------------------------------------------------------------
	pAccessory = new CAccessory("AC power outlet",0x0106,pKitchen);

	pAccessory->m_attr_num["on"] = 1;
	pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;

	//pAccessory->m_fwid = std::to_string(pAccessory->m_id);	
	pAccessory->m_about_str["ver"] = "1.0.0";		


//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Kitchen Light-1",pKitchen,NULL);
	pSwitch = new CSwitch("Kitchen Switch 01",pWallSwitchKitchen,pLightBulb);

//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Kitchen Light-2",pKitchen,NULL);
	pSwitch = new CSwitch("Kitchen Switch 02",pWallSwitchKitchen,pLightBulb);

//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Kitchen Light-3",pKitchen,NULL);
	pSwitch = new CSwitch("Kitchen Switch 03",pWallSwitchKitchen,pLightBulb);

//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Kitchen Light-4",pKitchen,NULL);
	pSwitch = new CSwitch("Kitchen Switch 04",pWallSwitchKitchen,pLightBulb);

//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Kitchen Light-5",pKitchen,NULL);

//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Kitchen Light-6",pKitchen,NULL);



//----------------------------------------------------------------
	pGroup02 = new CGroup("Group 02",pBathroom);	

	pGroup02->m_attr_num["groupNo"] = 2;


//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Kitchen Light-4",pKitchen,pGroup02);

//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Kitchen Light-5",pKitchen,pGroup02);



// locationOther
//---------------------------------------------------------
	pLightBulb = new CLightBulb("Light 91",locationOther,pGroup02);
	pLightBulb->m_attr_num["colorMode"] = 0;

//---------------------------------------------------------
	pLightBulb = new CLightBulb("Light 92",locationOther,pGroup02);
	pLightBulb->m_attr_num["colorMode"] = 0;

//---------------------------------------------------------
	pLightBulb = new CLightBulb("Light 93",locationOther,NULL);

//---------------------------------------------------------
	pLightBulb = new CLightBulb("Light 94",locationOther,NULL);


//----------------------------------------------------------------
	pLivingroom = new CLocation("Living Room"); 
	
	pLivingroom->m_attr_num["editable"] = 1;

	//----------------------------------------------------------------
	pWallSwitchLivingroom = new CWallSwitch("Living room WallSwitch",pLivingroom);	


//----------------------------------------------------------------
	pGroup03 = new CGroup("Group 03",pLivingroom);	

	pGroup03->m_attr_num["groupNo"] = 3;



//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Living room Light-1",pLivingroom,NULL);
			
//----------------------------------------------------------------
	pLightBulb = new CLightBulb("Living room Light-2",pLivingroom,NULL);
	
//---------------------------------------------------------
	pLightBulb = new CLightBulb("Living room Light-3",pLivingroom,NULL);
	pSwitch = new CSwitch("Living room Switch 01",pWallSwitchLivingroom,pLightBulb);

//---------------------------------------------------------
	pLightBulb = new CLightBulb("Living room Light-4",pLivingroom,NULL);
	pSwitch = new CSwitch("Living room Switch 02",pWallSwitchLivingroom,pLightBulb);

//---------------------------------------------------------
	pLightBulb = new CLightBulb("Living room Light-5",pLivingroom,pGroup03);
	pSwitch = new CSwitch("Living room Switch 03",pWallSwitchLivingroom,pLightBulb);

//---------------------------------------------------------
	pLightBulb = new CLightBulb("Living room Light-6",pLivingroom,pGroup03);
	pSwitch = new CSwitch("Living room Switch 04",pWallSwitchLivingroom,pLightBulb);
		
//---------------------------------------------------------
	pLightBulb = new CLightBulb("Living room Light-7",pLivingroom,pGroup03);
	

	pSwitch = pSwitch;

	return;
}

CAllObjects::~CAllObjects()
{
	std::map<unsigned int, CMyObject *>::iterator p;

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
	std::map<unsigned int, CMyObject *>::iterator p;

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
	std::map<unsigned int, CMyObject *>::iterator p;
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


int CAllObjects::removeByID(int idRemove)
{
	int err = 1;
	string err_str;		

	try {
		CMyObject *pObject = m_mapAllObjects[idRemove];

		if ( pObject != NULL )
			delete pObject;

		err = 0;
    } catch (const libsocket::socket_exception& exc)
    {
		std::cerr << exc.mesg;
		err_str = exc.mesg;
    }



	return err;
}




CMyObject::CMyObject(const char *myClassType,int id,const char *name,int type )
{
	m_id = id;
	m_type = type;
	m_sClassType = myClassType;
	m_name = name;

	m_pLocation = NULL;
	m_pGroup = NULL;
	m_pSwitch = NULL;

	m_attr_str["name"] = m_name;



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

int CMyObject::getIDTYPE()
{
	return (m_id&0xff000000);
}


CAccessory::CAccessory(const char *name,int type,CLocation *pLocation) : CMyObject("accessory",__allObjects.getID(IDTYPE_ACCESSORY),name,type)
{
	if ( pLocation != NULL )
		pLocation->add(this);	
}

CAccessory::~CAccessory()
{

}


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



CLocation::CLocation(const char *name) : CMyObject("location",__allObjects.getID(IDTYPE_LOCATION),name,0xff10)
{
	__allObjects.m_mapAllLocations[m_id] = this;
}

CLocation::~CLocation()
{
	std::map<unsigned int, CMyObject *>::iterator iterLocation;
	list<CMyObject*>::iterator iterX;

	iterLocation = __allObjects.m_mapAllLocations.find(m_id);
	if ( iterLocation != __allObjects.m_mapAllLocations.end() ) // Found it
	{
		__allObjects.m_mapAllLocations.erase(iterLocation);
	}

	for(iterX = m_listObject.begin(); iterX!=m_listObject.end(); ++iterX)
	{
		CMyObject *pSubObject;
		CLocation *otherLocation = __allObjects.getLocationOther();

		pSubObject = *iterX;


		if ( this != otherLocation )
			pSubObject->m_pLocation = otherLocation;
		else
			pSubObject->m_pLocation = NULL;
	}	

}


int CLocation::add (CMyObject *pObject)
{
	if ( pObject->m_pLocation != NULL )
	{
		pObject->m_pLocation->remove(pObject);
	}

	pObject->m_pLocation = this;

	addToList(pObject);

	return 1;
}

int CLocation::remove (CMyObject *pObject)
{
	removeFromList(pObject);

	pObject->m_pLocation = NULL;

	return 1;
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



CGateway::CGateway(int id,const char *name) : CMyObject("gateway",id,name,0xff00)
{
	m_attr_num["on"] = 1;
	m_attr_num["led"] = 0x05;
	m_attr_num["NumOfDev"] = 0x15;
	m_attr_str["ip"] = "192.168.1.12";
	m_attr_str["mask"] = "255.255.255.0";


	m_about_str["mac"] = "00:0c:29:36:3f:b1",
	m_about_str["uid"] = (char*) __myUID,

	m_about_str["ver"] = "1.0.0";
	m_about_str["verH"] = "";

	__allObjects.m_idGateway = m_id;
}

CGateway::~CGateway()
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
