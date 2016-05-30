#ifndef __DTABLE_H__
#define __DTABLE_H__


	#include <map>
	#include <list>
	#include <string>

	using namespace std;

	class CLocation;
	class CGroup;	

	class CMyObject
	{
	public:
		CMyObject(int id,string myClassType)
		{
			m_id = id;
			m_sClassType = myClassType;

			m_pLocation = NULL;
			m_pGroup = NULL;
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

		int m_id;


		CLocation 	*m_pLocation;
		CGroup		*m_pGroup;		
	};



	class CAccessory : public CMyObject
	{
	public:
		CAccessory(int id) : CMyObject(id,"accessory")
		{
		}

		~CAccessory();

	public:

	};
	

	class CGroup : public CMyObject
	{
	public:
		CGroup(int id) : CMyObject(id,"group")
		{

		}

		~CGroup();
		
	public:
		string m_name;
		list<CMyObject*>  m_accessory;

	public:
		int add (CMyObject *pObject)
		{
			pObject->m_pGroup = this;

			m_accessory.push_back(pObject);

			return 1;
		}
	};




	class CLocation : public CMyObject
	{
	public:
		CLocation(int id) : CMyObject(id,"location")
		{
		}

		~CLocation();
		
	public:
		string m_name;
		list<CMyObject*> m_listObject;

	public:
		int add (CMyObject *pObject)
		{
			pObject->m_pLocation = this;

			m_listObject.push_back(pObject);

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

	public: 
		unsigned int getID(unsigned int type);

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