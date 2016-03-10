//
//  CharacteristicDao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef CharacteristicDao_hpp
#define CharacteristicDao_hpp

#include <stdio.h>
#include <string>
#include "Dao.hpp"

struct CharacteristicDao : public Dao
{
    int characteristicNumber;
    std::string name;
    std::string value;
};

#endif /* CharacteristicDao_hpp */
