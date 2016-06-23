#ifndef __MYOBJECT_SCHEDULE_H__
#define __MYOBJECT_SCHEDULE_H__



	#include "myobject.h"



	class CSchedule : public CMyObject
	{
	public:
		CSchedule(const char *name);
		~CSchedule();

	public:
		int add (CMyObject *pObject);
		int remove (CMyObject *pObject);
	    int getDetail(Json::Value &jsonDetail);

	};	

	class action
	{
		public:
			string name;
			map<string,int> m_attr_num;
			map<string,string> m_attr_str;
			
			action(int on,int time,int duration);


	};




#endif