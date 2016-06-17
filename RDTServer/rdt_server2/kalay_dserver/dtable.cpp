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
	pGroup01->m_attr_num["icon"] = 1;


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
	pSensor = new CSensor("Garage Door Sensor 01",0x0201,pKitchen,3);

//----------------------------------------------------------------
	pSensor = new CSensor("Magnetic sensor",0x0202,pKitchen,4);

	pSensor->m_attr_num["batLow"] = 1;
	pSensor->m_attr_num["outLink"] = 1;
	pSensor->m_attr_num["icon"] = 2;



//----------------------------------------------------------------
	pSensor = new CSensor("motion sensor",0x0203,pKitchen,2);
	pSensor->m_attr_num["icon"] = 2;

//----------------------------------------------------------------
	pSensor = new CSensor("flood detector",0x0206,pKitchen,7);
	pSensor->m_attr_num["icon"] = 2;


//----------------------------------------------------------------
	pAccessory = new CAccessory("AC power outlet",0x0106,pKitchen,0);

	pAccessory->m_attr_num["on"] = 1;
	//pAccessory->m_attr_num["icon"] = 0;
	pAccessory->m_attr_num["trigger"] = 0;

	//pAccessory->m_fwid = std::to_string(pAccessory->m_id);	
	pAccessory->m_about_str["ver"] = "1.0.0";	

	pAccessory->m_attr_num["icon"] = 3;	


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
	pGroup02->m_attr_num["icon"] = 1;


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
	pGroup03->m_attr_num["icon"] = 1;



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







