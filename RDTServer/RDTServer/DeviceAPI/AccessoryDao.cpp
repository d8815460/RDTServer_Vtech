//
//  AccessoryDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "AccessoryDao.hpp"
#include <string>

void AccessoryDao::readCallback(PojoManager& outPojoManager, int row, vector<char*>& colList)
{
    AccessoryPojo* pAccessoryPojo = new AccessoryPojo();
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
//        LOGD("data:%s", data);
        
        if (i == 0) {
            pAccessoryPojo->accessorySerial = stoi(data);
            
            char buffer[100];
            sprintf(buffer, "SELECT * FROM Service WHERE fkAccessorySerial = %d;", pAccessoryPojo->accessorySerial);
            
            /* 取得 database 裡所有的資料 */
            outPojoManager.pPojoManager = new PojoManager();
            PojoManager& pojoManager = *outPojoManager.pPojoManager;
            
            ServiceDao::read(buffer, pojoManager);
            for (Pojo* pPojo : pojoManager.pojoList) {
                ServicePojo* pServicePojo = (ServicePojo*) pPojo;
//                pServicePojo->print();
                pAccessoryPojo->serviceList.push_back(pServicePojo);
            }
        }
        else if (i == 1) {
            pAccessoryPojo->accessoryId = stoi(data);
        }
        else if (i == 2) {
            pAccessoryPojo->accessoryType = stoi(data);
        }
        else {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Column_Over_The_Range);
        }
    }
    
    outPojoManager.push_back(pAccessoryPojo);
}

void AccessoryDao::read(const char* sql, PojoManager& outPojoManager)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    databaseManager.read(sql, outPojoManager, AccessoryDao::readCallback);
}
