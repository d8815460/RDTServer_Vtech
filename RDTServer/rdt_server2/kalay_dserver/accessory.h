#ifndef __MYOBJECT_ACCESSORY_H__
#define __MYOBJECT_ACCESSORY_H__

	#include "myobject.h"

	class CAccessory : public CMyObject
	{
	public:
		CAccessory(const char *name,int type,CLocation *pLocation,int icon);
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
		CSensor(const char *name,int type,CLocation *pLocation,int icon);
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
	



#endif
