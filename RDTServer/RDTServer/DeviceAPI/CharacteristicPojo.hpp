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
#include "Pojo.hpp"

struct CharacteristicPojo : public Pojo
{
    int characteristicSerial;
    std::string name;
    std::string value;
};

#endif /* CharacteristicDao_hpp */
