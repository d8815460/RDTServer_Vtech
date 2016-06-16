#ifndef __MYOBJECT_LOCATION_H__
#define __MYOBJECT_LOCATION_H__


	#include "myobject.h"


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





#endif