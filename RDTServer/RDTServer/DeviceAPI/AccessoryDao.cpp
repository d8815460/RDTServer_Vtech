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

//void loopVA_Args(Json::Value& json, int count, const char* value, ...)
//{
//    va_list vl;
//    va_start(vl, value);
//    LOGD("value:%s", value);
//
//    addJson(json, value);
//
////    ch = va_arg(vl, char*);
//    for (int i=1 ; i<count ; i++)
//    {
//        value = va_arg(vl, char*);
//        LOGD("value:%s", value);
//
//        addJson(json, value);
//    }
//
//    va_end(vl);
//}

void AccessoryDao::readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList)
{
    shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo());
//    LOGD("use_count:%ld", pAccessoryPojo.use_count());
//    pAccessoryPojo->genValueObject();   // 值會不正確
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
//        LOGD("data:%s", data);
        
        if (i == 0) {
            pAccessoryPojo->accessorySerial = stoi(data);
//            LOGD("pAccessoryPojo->accessorySerial:%d", pAccessoryPojo->accessorySerial);
            
            /* 取得 pElementPojoList 裡所有的資料 */
            pAccessoryPojo->pSubPojoList = ElementDao::read(pAccessoryPojo->accessorySerial);
//            for (shared_ptr<Pojo> pPojo : *pAccessoryPojo->pElementPojoList) {
//                pPojo->print();
//            }

        }
        /******************************************* 修改處 *****************************************************/
        if_index_int_va(1, pAccessoryPojo->AID, data)
        if_index_str_va(2, pAccessoryPojo->Name, data)
        if_index_int_va(3, pAccessoryPojo->IconType, data)
        if_index_int_va(4, pAccessoryPojo->Connection, data)
        if_index_int_va(5, pAccessoryPojo->IsGateway, data)
        /******************************************* 修改處 *****************************************************/
        else {
//            ValueObject& valObj = pAccessoryPojo->valueObjectList[i-1];
//            if (valObj.type == DatabaseType_INTEGER) {
////                pAccessoryPojo->AID = stoi(data);
//                int iData = stoi(data);
//                addPojo(pAccessoryPojo, valObj.key, iData);
//            }
//            else {
////                pAccessoryPojo->Name = data;
//                addPojo(pAccessoryPojo, valObj.key, data);
//            }
            
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Column_Over_The_Range);
        }
    }
    
//    pAccessoryPojo->genValueObject(); // 值會正確
    outPtrPojoList->push_back(pAccessoryPojo);
}

void AccessoryDao::create(AccessoryPojo& accessoryPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    LOGD("ID:%lld\n", sqlite3_last_insert_rowid(databaseManager.getSqliteDatabase()));
    
    accessoryPojo.genValueObject();
    std::string sql = accessoryPojo.createSQL("INSERT INTO Accessory (accessorySerial, ", accessoryPojo.valueObjectList);
    databaseManager.exec(sql.c_str());
    
    int rowid = (int) sqlite3_last_insert_rowid(databaseManager.getSqliteDatabase());
    
    for (shared_ptr<Pojo> pPojo : *accessoryPojo.pSubPojoList) {
        shared_ptr<ElementPojo>& pElementPojo = (shared_ptr<ElementPojo>&) pPojo;
        
        accessoryPojo.accessorySerial =rowid ;
        pElementPojo->fkAccessorySerial = accessoryPojo.accessorySerial;
        
//        LOGD("accessoryPojo.accessorySerial:%d", accessoryPojo.accessorySerial);
//        LOGD("pElementPojo->name:%s", pElementPojo->name.c_str());
        
        ElementDao::create(pElementPojo);
    }
}

void AccessoryDao::update(AccessoryPojo& accessoryPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    accessoryPojo.genValueObject();
    std::string sql = accessoryPojo.updateSQL("UPDATE Accessory SET ", accessoryPojo.valueObjectList);
    databaseManager.exec(sql.c_str());
    
    if (accessoryPojo.pSubPojoList != NULL) {
        for (shared_ptr<Pojo> pPojo : *accessoryPojo.pSubPojoList) {
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

int AccessoryDao::deleteWithAID(int AID)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    shared_ptr<Pojo> pPojo = AccessoryDao::read(AID);
    if (pPojo != NULL) {
       shared_ptr<AccessoryPojo>& pAccessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
        ElementDao::deleteWithFKAccessorySerial(pAccessoryPojo->accessorySerial);
        
        char buffer[Pojo_Buffer_Size];
        sprintf(buffer, "DELETE FROM Accessory WHERE AID = %d;", AID);
        
        return databaseManager.exec(buffer);
    }
    else {
        return 0;
    }
}

shared_ptr<vector<shared_ptr<Pojo>>> AccessoryDao::readAll()
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    return databaseManager.read("SELECT * FROM Accessory;", AccessoryDao::readCallback);
}

shared_ptr<Pojo> AccessoryDao::read(int AID)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "SELECT * FROM Accessory WHERE AID = %d;", AID);
    
    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = databaseManager.read(buffer, AccessoryDao::readCallback);
    
    // 只能有一筆
    if (pPojoList->size() == 1) {
        return (*pPojoList)[0];
    }
    else {
        return NULL;
    }
}