//
//  DatabaseException.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/9.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "DatabaseException.hpp"

map<int, const char*> DatabaseException::errorMessageMap = DatabaseException::createMap();