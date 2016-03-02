//
//  CommandException.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/2.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "CommandException.hpp"

map<int, const char*> CommandException::errorMessageMap = CommandException::createMap();