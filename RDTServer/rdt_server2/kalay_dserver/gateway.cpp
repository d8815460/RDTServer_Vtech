#include "../headers/exception.hpp"
#include <unistd.h>
#include <json/json.h>

#include <algorithm>
#include <string>
#include <iostream>



#include "dserver.h"
#include "myobject.h"
#include "gateway.h"

#include "dtable.h"




CGateway::CGateway(int id,const char *name) : CMyObject("gateway",id,name,0xff00)
{
	m_attr_num["on"] = 1;
	m_attr_num["led"] = 0x05;
	m_attr_num["NumOfDev"] = 0x15;
	m_attr_str["ip"] = "192.168.1.12";
	m_attr_str["mask"] = "255.255.255.0";


	m_about_str["mac"] = "00:0c:29:36:3f:b1",
	m_about_str["uid"] = (char*) __myUID,

	m_about_str["ver"] = "1.0.0";
	m_about_str["verH"] = "";

	__allObjects.m_idGateway = m_id;
}

CGateway::~CGateway()
{
}

