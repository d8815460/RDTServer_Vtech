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
#include <string>
#include "DatabaseManager.hpp"
#include "ServiceDao.hpp"

using namespace std;

struct AccessoryPojo : public Pojo
{
    int accessorySerial;
    int accessoryId;
    int accessoryType;
    
    vector<ServicePojo*> serviceList;
    
    void print()
    {
        LOGD("accessorySerial:%d", accessorySerial);
        LOGD("accessoryId:%d", accessoryId);
        LOGD("accessoryType:%d", accessoryType);
        
        for (ServicePojo* pServicePojo : serviceList) {
            pServicePojo->print();
        }
        
        LOGD();
    }
};

class AccessoryDao
{
public:
    static void read(const char* sql, PojoManager& outPojoManager);

private:
    static void readCallback(PojoManager& outPojoManager, int row, vector<char*>& colList);
};

#endif /* AccessoryDao_hpp */
