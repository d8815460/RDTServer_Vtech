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
#include <memory>
#include "DatabaseManager.hpp"
#include "ServiceDao.hpp"

using namespace std;

struct AccessoryPojo : public Pojo
{
    int accessorySerial;
    int accessoryId;
    int accessoryType;
    
    vector<ServicePojo*> servicePojoList;
    
    virtual ~AccessoryPojo()
    {
//        if (servicePojoList.size() > 0) {
//            for (ServicePojo* pServicePojo : servicePojoList) {
//                delete pServicePojo;
//            }
//        }
    }
    
    virtual void print()
    {
        LOGD("accessorySerial:%d", accessorySerial);
        LOGD("accessoryId:%d", accessoryId);
        LOGD("accessoryType:%d", accessoryType);
        
        for (ServicePojo* pServicePojo : servicePojoList) {
            pServicePojo->print();
        }
        
        LOGD();
    }
};

class AccessoryDao
{
public:
    static void read(vector<shared_ptr<Pojo>>& outPojoList);
    static void create(AccessoryPojo& accessoryPojo);
    
private:
    static void readCallback(vector<shared_ptr<Pojo>>& outPojoList, int row, vector<char*>& colList);
};

#endif /* AccessoryDao_hpp */
