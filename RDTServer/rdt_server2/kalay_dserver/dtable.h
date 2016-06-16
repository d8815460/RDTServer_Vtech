#ifndef __DTABLE_H__
#define __DTABLE_H__


	#include <map>
	#include <list>
	#include <string>

	#include <json/json.h>

	using namespace std;

	#define IDTYPE_GATEWAY		0x00000000
	#define IDTYPE_LOCATION		0x10000000
	#define IDTYPE_GROUP		0x11000000

	#define IDTYPE_TASK		  	0x21000000
	#define IDTYPE_SCHEDULE  	0x22000000

	#define IDTYPE_WALLSWITCH  	0x51000000
	#define IDTYPE_SWITCH  		0x52000000

	#define IDTYPE_ACCESSORY  	0x70000000




	class CLocation;
	class CGroup;	
	class CWallSwitch;
	class CSwitch;

	class CMyObject
	{
	public:
		CMyObject(const char *myClassType,int id,const char *name,int type );
		virtual ~CMyObject();

	public:		
		string m_sClassType;
		map<string,int> m_attr_num;
		map<string,string> m_attr_str;

		map<string,int> m_about_num;
		map<string,string> m_about_str;

		list<CMyObject*>  m_listObject;

		int m_id;
		int m_type;
		string m_name;

		string m_fwid;

		int m_orderInLocation;

		CLocation 	*m_pLocation;
		CGroup		*m_pGroup;
		CSwitch 	*m_pSwitch;	// for Accessory



	protected:
		int addToList (CMyObject *pObject);
		int removeFromList (CMyObject *pObject);
		int getIDTYPE();


	public:
		int getBaseAttr(Json::Value& jsonAttr);
		int getAttr(Json::Value& jsonAttr);
		int getAbout(Json::Value& jsonAbout);
		int getSubObjects(Json::Value& subObjects);

		int getDetail(Json::Value &jsonDetail);
	};


	class CGateway : public CMyObject
	{
	public:
		CGateway(int id,const char *name);
		~CGateway();

	public:

	};


	class CAccessory : public CMyObject
	{
	public:
		CAccessory(const char *name,int type,CLocation *pLocation);
		~CAccessory();

	public:

	};


	class CLightBulb : public CAccessory
	{
	public:
		CLightBulb(const char *name,CLocation *pLocation,CGroup *pGroup);
		~CLightBulb();

	public:

	};	


	class CSensor : public CAccessory
	{
	public:
		CSensor(const char *name,int type,CLocation *pLocation);
		~CSensor();

	public:

	};	

	class CWallSwitch : public CMyObject
	{
	public:
		CWallSwitch(const char *name,CLocation *pLocation);
		~CWallSwitch();

	public:
		int add (CSwitch *pSwitch);
		int remove (CSwitch *pSwitch);
	};	


	class CSwitch : public CMyObject
	{
	public:
		CSwitch(const char *name,CWallSwitch *pWallSwitch,CAccessory *pAccessory);
		~CSwitch();

	public:
		CWallSwitch	*m_pWallSwitch;
		CAccessory 	*m_pAccessory;
	};		
	

	class CGroup : public CMyObject
	{
	public:
		CGroup(const char *name,CLocation *pLocation);
		~CGroup();
		

	public:
		int add (CMyObject *pObject);
		int remove (CMyObject *pObject);
	};




	class CLocation : public CMyObject
	{
	public:
		CLocation(const char *name);
		~CLocation();
		

	public:
		int add (CMyObject *pObject);
		int remove (CMyObject *pObject);
		int UpdateOrder (CMyObject *pObject,int newOrder);
	};


	class CTask : public CMyObject
	{
	public:
		CTask(int id,const char *name);
		~CTask();

	public:

	};

	class CSchedule : public CMyObject
	{
	public:
		CSchedule(int id,const char *name);
		~CSchedule();

	public:

	};	



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
		std::map<std::string, CMyObject *>   m_mapObjectsByFWID;

	friend class CMyObject;
	friend class CGateway;
	friend class CAccessory;
	friend class CLocation;
	friend class CGroup;	
	friend class CWallSwitch;
	friend class CSwitch;
	friend class CSensor;


	public:
		int dump();
		int dumpByLocation();


		int removeByID(int idRemove);


	};

	extern CAllObjects __allObjects;


#endif