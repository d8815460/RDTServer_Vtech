//
//  AccessoryDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "AccessoryDao.hpp"
#include <string>
#include "ServiceDao.hpp"

void AccessoryDao::readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList)
{
    shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo());
//    LOGD("use_count:%ld", pAccessoryPojo.use_count());
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
//        LOGD("data:%s", data);
        
        if (i == 0) {
            pAccessoryPojo->accessorySerial = stoi(data);
            
            /* 取得 database 裡所有的資料 */
            pAccessoryPojo->pServicePojoList = ServiceDao::read(pAccessoryPojo->accessorySerial);
//            for (shared_ptr<Pojo> pPojo : *pAccessoryPojo->pServicePojoList) {
//                pPojo->print();
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
    
    outPtrPojoList->push_back(pAccessoryPojo);
}

void AccessoryDao::create(AccessoryPojo& accessoryPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "INSERT INTO Accessory VALUES(NULL, %d, %d);", accessoryPojo.accessoryId, accessoryPojo.accessoryType);
    LOGD("buffer:%s", buffer);
    databaseManager.exec(buffer);
    
    for (shared_ptr<Pojo> pPojo : *accessoryPojo.pServicePojoList) {
        shared_ptr<ServicePojo>& pServicePojo = (shared_ptr<ServicePojo>&) pPojo;
//        LOGD("pServicePojo->name:%s", pServicePojo->name.c_str());
        
        ServiceDao::create(pServicePojo);
    }
}

void AccessoryDao::update(AccessoryPojo& accessoryPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "UPDATE Accessory SET accessoryId = %d, accessoryType = %d;", accessoryPojo.accessoryId, accessoryPojo.accessoryType);
    databaseManager.exec(buffer);
    
    if (accessoryPojo.pServicePojoList != NULL) {
        for (shared_ptr<Pojo> pPojo : *accessoryPojo.pServicePojoList) {
            shared_ptr<ServicePojo>& pServicePojo = (shared_ptr<ServicePojo>&) pPojo;
            ServiceDao::update(pServicePojo);
        }
    }
}

int AccessoryDao::deleteAll()
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    ServiceDao::deleteAll();
    
    return databaseManager.exec("DELETE FROM Accessory;");
}

int AccessoryDao::deleteWithSerial(int accessorySerial)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "DELETE FROM Accessory WHERE accessorySerial = %d;", accessorySerial);
    
    ServiceDao::deleteWithFKAccessorySerial(accessorySerial);
    
    return databaseManager.exec(buffer);
}

shared_ptr<vector<shared_ptr<Pojo>>> AccessoryDao::read()
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    return databaseManager.read("SELECT * FROM Accessory;", AccessoryDao::readCallback);
}
