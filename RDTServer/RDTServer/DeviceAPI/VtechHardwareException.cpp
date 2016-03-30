//
//  VtechHardwareException.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/30.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "VtechHardwareException.hpp"

map<int, const char*> VtechHardwareException::errorMessageMap = VtechHardwareException::createMap();