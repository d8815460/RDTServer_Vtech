//
//  ElementNODao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef ElementNODao_hpp
#define ElementNODao_hpp

#include <stdio.h>
#include <string>
#include "Pojo.hpp"

struct ElementNOPojo : public Pojo
{
    int ElementNOSerial;
    std::string name;
    std::string value;
};

#endif /* ElementNODao_hpp */
