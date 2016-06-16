#include "../headers/exception.hpp"
#include <unistd.h>
#include <json/json.h>

#include <algorithm>
#include <string>
#include <iostream>



#include "dserver.h"
#include "myobject.h"
#include "schedule.h"


CSchedule::CSchedule(int id,const char *name): CMyObject("schedule",id,name,0xff40)
{

}

CSchedule::~CSchedule()
{
	
}


