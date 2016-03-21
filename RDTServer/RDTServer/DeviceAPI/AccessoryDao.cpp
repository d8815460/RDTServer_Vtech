//
//  AccessoryDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "AccessoryDao.hpp"
#include <string>
#include "ElementDao.hpp"

void AccessoryDao::readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList)
{
    shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo());
//    LOGD("use_count:%ld", pAccessoryPojo.use_count());
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
//        LOGD("data:%s", data);
        
        if (i == 0) {
            pAccessoryPojo->accessorySerial = stoi(data);
//            LOGD("pAccessoryPojo->accessorySerial:%d", pAccessoryPojo->accessorySerial);
            
            /* 取得 pElementPojoList 裡所有的資料 */
            pAccessoryPojo->pElementPojoList = ElementDao::read(pAccessoryPojo->accessorySerial);
//            for (shared_ptr<Pojo> pPojo : *pAccessoryPojo->pElementPojoList) {
//                pPojo->print();
//            }

        }
        else if (i == 1) {
            pAccessoryPojo->AID = stoi(data);
        }
        else if (i == 2) {
            pAccessoryPojo->AType = stoi(data);
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
    
    LOGD("ID:%lld\n", sqlite3_last_insert_rowid(databaseManager.getSqliteDatabase()));
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "INSERT INTO Accessory VALUES(NULL, %d, %d);", accessoryPojo.AID, accessoryPojo.AType);
    LOGD("buffer:%s", buffer);
    databaseManager.exec(buffer);
    
    for (shared_ptr<Pojo> pPojo : *accessoryPojo.pElementPojoList) {
        shared_ptr<ElementPojo>& pElementPojo = (shared_ptr<ElementPojo>&) pPojo;
        
        accessoryPojo.accessorySerial = (int) sqlite3_last_insert_rowid(databaseManager.getSqliteDatabase());
        pElementPojo->fkAccessorySerial = accessoryPojo.accessorySerial;
        
//        LOGD("accessoryPojo.accessorySerial:%d", accessoryPojo.accessorySerial);
//        LOGD("pElementPojo->name:%s", pElementPojo->name.c_str());
        
        ElementDao::create(pElementPojo);
    }
}

void AccessoryDao::update(AccessoryPojo& accessoryPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "UPDATE Accessory SET AID = %d, AType = %d;", accessoryPojo.AID, accessoryPojo.AType);
    databaseManager.exec(buffer);
    
    if (accessoryPojo.pElementPojoList != NULL) {
        for (shared_ptr<Pojo> pPojo : *accessoryPojo.pElementPojoList) {
            shared_ptr<ElementPojo>& pElementPojo = (shared_ptr<ElementPojo>&) pPojo;
            ElementDao::update(pElementPojo);
        }
    }
}

int AccessoryDao::deleteAll()
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    ElementDao::deleteAll();
    
    return databaseManager.exec("DELETE FROM Accessory;");
}

int AccessoryDao::deleteWithSerial(int accessorySerial)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "DELETE FROM Accessory WHERE accessorySerial = %d;", accessorySerial);
    
    ElementDao::deleteWithFKAccessorySerial(accessorySerial);
    
    return databaseManager.exec(buffer);
}

shared_ptr<vector<shared_ptr<Pojo>>> AccessoryDao::read()
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    return databaseManager.read("SELECT * FROM Accessory;", AccessoryDao::readCallback);
}
