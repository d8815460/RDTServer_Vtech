//
//  IOTCException.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/1.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "IOTCException.hpp"

map<int, const char*> IOTCException::errorMessageMap = IOTCException::createMap();