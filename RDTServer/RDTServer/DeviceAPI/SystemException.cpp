//
//  SystemException.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/30.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "SystemException.hpp"

map<int, const char*> SystemException::errorMessageMap = SystemException::createMap();