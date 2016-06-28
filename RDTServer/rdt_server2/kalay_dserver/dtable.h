#ifndef __DTABLE_H__
#define __DTABLE_H__


	#include <map>
	#include <list>
	#include <string>

	#include <json/json.h>


	#include "myobject.h"
	#include "gateway.h"
	#include "group.h"
	#include "location.h"
	#include "accessory.h"
	#include "schedule.h"
	#include "task.h"

	using namespace std;


	class CAllObjects
	{
	public:
		CAllObjects();
		~CAllObjects();

	private:
		pthread_mutex_t mutex_global_id;
		unsigned int global_id;
		CLocation  *locationOther;


	public: 
		unsigned int m_idGateway;

	public:		
		unsigned int getID(unsigned int idtype);
		CLocation *getLocationOther()
		{
			return locationOther;
		}

		CGateway *getGateway()
		{
			std::map<unsigned int, CMyObject *>::iterator iterFind;

			iterFind = m_mapAllObjects.find(m_idGateway);

			if ( iterFind != m_mapAllObjects.end() )
				return (CGateway*) iterFind->second;

			return NULL;
		}

		CMyObject *getObjectByID(unsigned int id)
		{
			std::map<unsigned int, CMyObject *>::iterator iterFind;

			iterFind = m_mapAllObjects.find(id);

			if ( iterFind != m_mapAllObjects.end() )
				return  iterFind->second;


			return  NULL;
		}

		CLocation *getLocationByID(unsigned int id)
		{
			std::map<unsigned int, CMyObject *>::iterator iterFind;

			iterFind = m_mapAllLocations.find(id);

			if ( iterFind != m_mapAllLocations.end() )
				return  (CLocation *)iterFind->second;


			return  NULL;
		}




	public:
		std::map<unsigned int, CMyObject *>  m_mapAllObjects;
		std::map<unsigned int, CMyObject *>  m_mapAllLocations;
		std::map<unsigned int, CMyObject *>  m_mapAllGroups;
		std::map<unsigned int, CMyObject *>  m_mapAllSchedules;
		std::map<unsigned int, CMyObject *>  m_mapAllTasks;
		std::map<unsigned int, CMyObject *>  m_mapAllActivities;
		std::map<std::string, CMyObject *>   m_mapObjectsByFWID;

	friend class CMyObject;
	friend class CGateway;
	friend class CAccessory;
	friend class CLocation;
	friend class CGroup;	
	friend class CWallSwitch;
	friend class CSwitch;
	friend class CSensor;
	friend class CSchedule;
	friend class CTask;


	public:
		int dump();
		int dumpByLocation();


		int removeByID(int idRemove);


	};

	extern CAllObjects __allObjects;


#endif
