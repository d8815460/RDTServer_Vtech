//
//  RDTException.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/1.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "RDTException.hpp"

map<int, const char*> RDTException::errorMessageMap = RDTException::createMap();