#include "../headers/exception.hpp"
#include <unistd.h>
#include <json/json.h>

#include <algorithm>
#include <string>
#include <iostream>



#include "dserver.h"
#include "myobject.h"
#include "location.h"
#include "dtable.h"


CLocation::CLocation(const char *name) : CMyObject("location",__allObjects.getID(IDTYPE_LOCATION),name,0xff10)
{
	__allObjects.m_mapAllLocations[m_id] = this;
}

CLocation::~CLocation()
{
	std::map<unsigned int, CMyObject *>::iterator iterLocation;
	list<CMyObject*>::iterator iterX;

	iterLocation = __allObjects.m_mapAllLocations.find(m_id);
	if ( iterLocation != __allObjects.m_mapAllLocations.end() ) // Found it
	{
		__allObjects.m_mapAllLocations.erase(iterLocation);
	}

	for(iterX = m_listObject.begin(); iterX!=m_listObject.end(); ++iterX)
	{
		CMyObject *pSubObject;
		CLocation *otherLocation = __allObjects.getLocationOther();

		pSubObject = *iterX;


		if ( this != otherLocation )
			pSubObject->m_pLocation = otherLocation;
		else
			pSubObject->m_pLocation = NULL;
	}	

}


int CLocation::add (CMyObject *pObject)
{
	if ( pObject->m_pLocation != NULL )
	{
		pObject->m_pLocation->remove(pObject);
	}

	pObject->m_pLocation = this;
	pObject->m_orderInLocation = m_listObject.size()+1;

	addToList(pObject);

	return 1;
}

int CLocation::remove (CMyObject *pObject)
{
	removeFromList(pObject);

	pObject->m_pLocation = NULL;


	// re-sorting
	{
		list<CMyObject*>::iterator iterX;
		int order = 0;


		for(iterX = m_listObject.begin(); iterX!=m_listObject.end(); ++iterX)
		{
			CMyObject *pSubObject;

			pSubObject = *iterX;

			pSubObject->m_orderInLocation = ++order;
		}	
	}


	return 1;
}


int CLocation::UpdateOrder (CMyObject *pObject,int newOrder)
{
	int ret = 0;

	removeFromList(pObject);

	pObject->m_pLocation = this;

	// re-sorting
	{
		list<CMyObject*>::iterator iterX;
		int order = 0;

		int i,size;

		size = m_listObject.size();
		iterX = m_listObject.begin();

		for(i=0;i<size;i++)
		{
			if ( (i+1) == newOrder )
			{
				m_listObject.insert(iterX,pObject);
				ret = newOrder;
				break;
			}

			++iterX;	
		}

		if ( ret == 0 )
		{
			addToList(pObject);
		}


		// re-sorting
		for(iterX = m_listObject.begin(); iterX!=m_listObject.end(); ++iterX)
		{
			CMyObject *pSubObject;

			pSubObject = *iterX;

			pSubObject->m_orderInLocation = ++order;
		}	
	}

	return ret;
}
