//
//  AccessoryDao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef AccessoryDao_hpp
#define AccessoryDao_hpp

#include <stdio.h>
#include "Dao.hpp"

struct AccessoryDao : public Dao
{
    int accessoryNumber;
    int accessoryId;
    int accessoryType;
};

#endif /* AccessoryDao_hpp */
