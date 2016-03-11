//
//  ServiceDao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef ServiceDao_hpp
#define ServiceDao_hpp

#include <stdio.h>
#include <string>
#include "Pojo.hpp"
#include "PojoArray.hpp"

struct ServicePojo : public Pojo
{
    int serviceSerial;
    int fkAccessorySerial;
    std::string name;
    std::string value;
    
    virtual void print()
    {
        LOGD("serviceSerial:%d", serviceSerial);
        LOGD("fkAccessorySerial:%d", fkAccessorySerial);
        LOGD("name:%s", name.c_str());
        LOGD("value:%s", value.c_str());
        LOGD();
    }
};

class ServiceDao
{
public:
    static void read(char* sql, PojoArray& outPojoArray);
    static void create(ServicePojo& servicePojo);
    
private:
    static void readCallback(PojoArray& outPojoArray, int row, vector<char*>& colList);
};

#endif /* ServiceDao_hpp */
