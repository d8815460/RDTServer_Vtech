//
//  AccessoryDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "AccessoryDao.hpp"
#include <string>

void AccessoryDao::readCallback(vector<shared_ptr<Pojo>>& outPojoList, int row, vector<char*>& colList)
{
    shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo());
//    LOGD("use_count:%ld", pAccessoryPojo.use_count());
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
//        LOGD("data:%s", data);
        
        if (i == 0) {
            pAccessoryPojo->accessorySerial = stoi(data);
            
//            /* 取得 database 裡所有的資料 */
//            outPojoArray.pPojoArray = new PojoArray();
//            PojoArray& pojoArray = *outPojoArray.pPojoArray;
//            
//            ServiceDao::read(pojoArray, pAccessoryPojo->accessorySerial);
//            for (Pojo* pPojo : pojoArray.subPojoList) {
//                ServicePojo* pServicePojo = (ServicePojo*) pPojo;
////                pServicePojo->print();
//                pAccessoryPojo->servicePojoList.push_back(pServicePojo);
//            }
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
    
    outPojoList.push_back(pAccessoryPojo);
}

void AccessoryDao::read(vector<shared_ptr<Pojo>>& outPojoList)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    databaseManager.read("SELECT * FROM Accessory;", outPojoList, AccessoryDao::readCallback);
}

void AccessoryDao::create(AccessoryPojo& accessoryPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "INSERT INTO Accessory VALUES(NULL, %d, %d);", accessoryPojo.accessoryId, accessoryPojo.accessoryType);
    databaseManager.exec(buffer);
    
    for (ServicePojo* pServicePojo : accessoryPojo.servicePojoList) {
        ServiceDao::create(*pServicePojo);
    }
}
