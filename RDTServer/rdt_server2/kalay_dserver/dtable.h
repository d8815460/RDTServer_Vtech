#ifndef __DTABLE_H__
#define __DTABLE_H__


	#include <map>
	#include <list>

	using namespace std;

	class CMyObject
	{
	public:
		CMyObject(int id,string myClassType)
		{
			m_id = id;
			m_sClassType = myClassType;
		}
		
		virtual ~CMyObject()
		{
		}

	public:		
		string m_sClassType;
		map<string,int> m_attr_num;
		map<string,string> m_attr_str;
		int m_id;
	};

	class CLocation;
	class CGroup;

	class CAccessory : public CMyObject
	{
	public:
		CAccessory(int id) : CMyObject(id,"accessory")
		{
			m_pLocation = NULL;
			m_pGroup = NULL;
		}

		~CAccessory();

	public:
		CLocation *m_pLocation;
		CGroup	*m_pGroup;
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
		list<CMyObject*> m_accessory;

	public:
		int addAccessory(CAccessory *pAccessory)
		{
			m_accessory.push_back(pAccessory);
			pAccessory->m_pLocation = this;

			return 1;
		}		
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
		list<CMyObject*> m_accessory;

	public:
		int addAccessory(CAccessory *pAccessory)
		{
			m_accessory.push_back(pAccessory);
			pAccessory->m_pGroup = this;

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

	public:
		TAllObjectMap m_mapAllObjects;

	public:
		int dump();
	};

	extern CAllObjects __allObjects;


#endif