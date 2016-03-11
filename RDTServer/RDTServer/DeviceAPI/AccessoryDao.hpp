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
    
    shared_ptr<vector<shared_ptr<Pojo>>> pServicePojoList;
    
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
        
        for (shared_ptr<Pojo> pPojo : *pServicePojoList) {
            pPojo->print();
        }
        
        LOGD();
    }
};

class AccessoryDao
{
public:
    static shared_ptr<vector<shared_ptr<Pojo>>> read();
    static void create(AccessoryPojo& accessoryPojo);
    
private:
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList);
};

#endif /* AccessoryDao_hpp */
