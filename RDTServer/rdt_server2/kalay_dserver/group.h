#ifndef __MYOBJECT_GROUP_H__
#define __MYOBJECT_GROUP_H__


	#include "myobject.h"
	#include "location.h"

	class CGroup : public CMyObject
	{
	public:
		CGroup(const char *name,CLocation *pLocation);
		~CGroup();
		

	public:
		int add (CMyObject *pObject);
		int remove (CMyObject *pObject);
	};








#endif