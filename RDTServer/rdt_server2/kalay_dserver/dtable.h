#ifndef __DTABLE_H__
#define __DTABLE_H__


	#include <map>
	#include <list>
	#include <string>

	using namespace std;

	#define IDTYPE_ACCESSORY  	0x01000000
	#define IDTYPE_WALLSWITCH  	0x02000000
	#define IDTYPE_GROUP		0x12000000
	#define IDTYPE_LOCATION		0x13000000
	#define IDTYPE_GATEWAY		0x70000000

	class CLocation;
	class CGroup;	
	class CWallSwitch;

	class CMyObject
	{
	public:
		CMyObject(const char *myClassType,int id,const char *name,int type )
		{
			m_id = id;
			m_type = type;
			m_sClassType = myClassType;
			m_name = name;

			m_pLocation = NULL;
			m_pGroup = NULL;

			m_attr_str["name"] = m_name;
		}
		
		virtual ~CMyObject()
		{
		}

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



		CLocation 		*m_pLocation;
		CGroup			*m_pGroup;
		CWallSwitch 	*m_pWallSwitch;	

	protected:
		int addToList (CMyObject *pObject)
		{
			m_listObject.push_back(pObject);

			return 1;
		}		

	public:
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
		CAccessory(int id,const char *name,int type);
		~CAccessory();

	public:

	};


	class CLightBulb : public CAccessory
	{
	public:
		CLightBulb(int id,const char *name,CLocation *pLocation,CGroup *pGroup);
		~CLightBulb();

	public:

	};	

	class CWallSwitch : public CMyObject
	{
	public:
		CWallSwitch(int id,const char *name,CLocation *pLocation);
		~CWallSwitch();

	public:
		int add (CMyObject *pObject)
		{
			pObject->m_pWallSwitch = this;

			addToList(pObject);

			return 1;
		}

	};	
	

	class CGroup : public CMyObject
	{
	public:
		CGroup(int id,const char *name,CLocation *pLocation);
		~CGroup();
		

	public:
		int add (CMyObject *pObject)
		{
			pObject->m_pGroup = this;

			addToList(pObject);

			return 1;
		}
	};




	class CLocation : public CMyObject
	{
	public:
		CLocation(int id,const char *name);
		~CLocation();
		

	public:
		int add (CMyObject *pObject)
		{
			pObject->m_pLocation = this;

			addToList(pObject);

			return 1;
		}
	};







	typedef std::map<unsigned int, CMyObject *> TAllObjectMap;
	typedef std::pair<unsigned int, CMyObject *> TAllObjectPair;


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
		unsigned int getID(unsigned int idtype);
		CLocation *getLocationOther()
		{
			return locationOther;
		}
		unsigned int m_idGateway;


	public:
		TAllObjectMap m_mapAllObjects;
		TAllObjectMap m_mapAllLocations;
		TAllObjectMap m_mapAllGroups;



	public:
		int dump();
		int dumpByLocation();
	};

	extern CAllObjects __allObjects;


#endif