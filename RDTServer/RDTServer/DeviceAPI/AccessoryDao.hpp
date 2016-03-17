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

using namespace std;

struct AccessoryPojo : public Pojo
{
    int accessorySerial;
    int AID;
    int AType;
    shared_ptr<vector<shared_ptr<Pojo>>> pElementPojoList;
    
    AccessoryPojo()
    {
        pElementPojoList = shared_ptr<vector<shared_ptr<Pojo>>>(new vector<shared_ptr<Pojo>>());
    }
    
    virtual void print()
    {
        LOGD("================================================================================");
        LOGD("accessorySerial:%d", accessorySerial);
        LOGD("AID:%d", AID);
        LOGD("AType:%d", AType);
        
        if (pElementPojoList != NULL) {
            for (shared_ptr<Pojo> pPojo : *pElementPojoList) {
                pPojo->print();
            }
        }
        LOGD("================================================================================");
        LOGD();
    }
};

class AccessoryDao
{
public:
    static void create(AccessoryPojo& pojo);
    static void update(AccessoryPojo& pojo);
    
    static int deleteAll();
    static int deleteWithSerial(int accessorySerial);
    
    static shared_ptr<vector<shared_ptr<Pojo>>> read();
    
private:
    AccessoryDao() {};
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList);
};

#endif /* AccessoryDao_hpp */
