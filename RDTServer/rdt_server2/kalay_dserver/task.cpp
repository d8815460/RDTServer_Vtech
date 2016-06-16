#include "../headers/exception.hpp"
#include <unistd.h>
#include <json/json.h>

#include <algorithm>
#include <string>
#include <iostream>



#include "dserver.h"
#include "myobject.h"
#include "task.h"


CTask::CTask(int id,const char *name): CMyObject("task",id,name,0xff30)
{

}

CTask::~CTask()
{

}
