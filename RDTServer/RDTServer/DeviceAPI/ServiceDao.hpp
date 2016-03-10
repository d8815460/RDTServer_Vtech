//
//  FunctionCodeDao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef FunctionCodeDao_hpp
#define FunctionCodeDao_hpp

#include <stdio.h>
#include <string>
#include "Dao.hpp"

struct ServiceDao : public Dao
{
    int ServiceNumber;
    std::string name;
    std::string value;
};

#endif /* FunctionCodeDao_hpp */
