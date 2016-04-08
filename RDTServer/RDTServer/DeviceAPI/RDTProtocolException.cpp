//
//  RDTProtocolException.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/4/6.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "RDTProtocolException.hpp"

map<int, const char*> RDTProtocolException::errorMessageMap = RDTProtocolException::createMap();