#ifndef __MYOBJECT_H__
#define __MYOBJECT_H__


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
	class CSchedule;

	class CMyObject
	{
	public:
		CMyObject(const char *myClassType,int id,const char *name,int type,int icon);
		virtual ~CMyObject();

	public:		
		string m_sClassType;
		map<string,int> m_attr_num;
		map<string,string> m_attr_str;

		map<string,int> m_about_num;
		map<string,string> m_about_str;
		

		list<CMyObject*>  m_listObject;
		list<CMyObject*>  m_listObject_task;

		int m_id;
		int m_type;
		int m_icon;
		string m_name;

		string m_fwid;

		int m_orderInLocation;

		CLocation 	*m_pLocation;
		CGroup		*m_pGroup;
		CSwitch 	*m_pSwitch;	// for Accessory
		CSchedule   *m_pSchedule;



	protected:
		int addToList (CMyObject *pObject);
		int removeFromList (CMyObject *pObject);
		int addToListtask (CMyObject *pObject);
		int removeFromListtask (CMyObject *pObject);

		int getIDTYPE();


	public:
		int getBaseAttr(Json::Value& jsonAttr);
		int getAttr(Json::Value& jsonAttr);
		int getAbout(Json::Value& jsonAbout);
		int getSubObjects(Json::Value& subObjects);
		int gettasks(Json::Value& subObjects);
		int getDetail(Json::Value &jsonDetail);
		int add (CMyObject *pObject);
		int remove (CMyObject *pObject);
	};




#endif