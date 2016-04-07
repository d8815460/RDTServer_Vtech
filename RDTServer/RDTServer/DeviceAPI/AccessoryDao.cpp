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
#include "ElementNODao.hpp"

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

void AccessoryDao::readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList, bool isNest)
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
            
            if (isNest == true) {
                /* 取得 pElementPojoList 裡所有的資料 */
                vector<int> accessorySerialList;
                accessorySerialList.push_back(pAccessoryPojo->accessorySerial);
                
                pAccessoryPojo->pSubPojoList = ElementDao::read(accessorySerialList);
                //            for (shared_ptr<Pojo> pPojo : *pAccessoryPojo->pElementPojoList) {
                //                pPojo->print();
                //            }
            }
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
    std::string sql = Pojo::createSQL("INSERT INTO Accessory (accessorySerial,", accessoryPojo.valueObjectList);
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
    std::string sql = Pojo::updateSQL("UPDATE Accessory SET", accessoryPojo.valueObjectList);
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

int AccessoryDao::deleteWithSerialList(vector<int>& accessorySerialList)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    vector<ValueObject> objList;
    for (int accessorySerial : accessorySerialList) {
        ValueObject obj("accessorySerial", accessorySerial);
        objList.push_back(obj);
    }
    
    string SQL = "DELETE FROM Accessory WHERE accessorySerial";
    SQL.append(Pojo::genInSQL(objList, false));
    
    return databaseManager.exec(SQL.c_str());
}

int AccessoryDao::deleteWithAIDList(vector<int>& AIDList)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = AccessoryDao::read(AIDList);
    if (pPojoList != NULL) {
        shared_ptr<vector<shared_ptr<AccessoryPojo>>>& pAccessoryPojoList = (shared_ptr<vector<shared_ptr<AccessoryPojo>>>&) pPojoList;
        
        if (pAccessoryPojoList->size() > 0) {
            // 呼叫下一層Delete
            vector<int> accessorySerialList;
            for (shared_ptr<AccessoryPojo> pAccessory : *pAccessoryPojoList) {
                accessorySerialList.push_back(pAccessory->accessorySerial);
            }
            ElementDao::deleteWithFKAccessorySerialList(accessorySerialList);
            
            // 這一層的刪除
            vector<ValueObject> objList;
            for (int AID : AIDList) {
                ValueObject obj("AID", AID);
                objList.push_back(obj);
            }
            
            string SQL = "DELETE FROM Accessory WHERE AID";
            SQL.append(Pojo::genInSQL(objList, false));
            
            return databaseManager.exec(SQL.c_str());
        }
    }
    
    return DatabaseException_ErrorCode_Error_Deleting_Database;
}

shared_ptr<vector<shared_ptr<Pojo>>> AccessoryDao::readAll()
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    return databaseManager.read("SELECT * FROM Accessory;", true, AccessoryDao::readCallback);
}

shared_ptr<vector<shared_ptr<Pojo>>> AccessoryDao::read(vector<int>& AIDList)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    vector<ValueObject> objList;
    for (int AID : AIDList) {
        ValueObject obj("AID", AID);
        objList.push_back(obj);
    }
    
    string SQL = "SELECT * FROM Accessory WHERE AID";
    SQL.append(Pojo::genInSQL(objList, false));
    
    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = databaseManager.read(SQL.c_str(), true, AccessoryDao::readCallback);
    return pPojoList;
}

shared_ptr<vector<shared_ptr<Pojo>>> AccessoryDao::readNestWithSQL(string& whereSQL)
{
    string selectSQL = "SELECT DISTINCT ";
    string fromSQL = " FROM Accessory INNER JOIN Element INNER JOIN ElementNO ON ";
    
    string accessorySQL = Pojo::genAccessoryNestReadSQL("Accessory.*", whereSQL);
    shared_ptr<vector<shared_ptr<Pojo>>> accessoryPojoList = AccessoryDao::readWithSQL(accessorySQL);
    
    string elementSQL = Pojo::genAccessoryNestReadSQL("Element.*", whereSQL);
    shared_ptr<vector<shared_ptr<Pojo>>> elementPojoList = ElementDao::readWithSQL(elementSQL);
    
    string elementNOSQL = Pojo::genAccessoryNestReadSQL("ElementNO.*", whereSQL);
    shared_ptr<vector<shared_ptr<Pojo>>> elementNOPojoList = ElementNODao::readWithSQL(elementNOSQL);
    
    for (shared_ptr<Pojo> pPojo : *accessoryPojoList) {
        shared_ptr<AccessoryPojo>& pAccessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
        
        for (shared_ptr<Pojo> pPojo : *elementPojoList) {
            shared_ptr<ElementPojo>& pElementPojo = (shared_ptr<ElementPojo>&) pPojo;
            
            if (pAccessoryPojo->accessorySerial == pElementPojo->fkAccessorySerial) {
                pAccessoryPojo->pSubPojoList->push_back(pElementPojo);
//                break;
            }
        }
    }
    
    for (shared_ptr<Pojo> pPojo : *elementPojoList) {
        shared_ptr<ElementPojo>& pElementPojo = (shared_ptr<ElementPojo>&) pPojo;
        
        for (shared_ptr<Pojo> pPojo : *elementNOPojoList) {
            shared_ptr<ElementNOPojo>& pElementNOPojo = (shared_ptr<ElementNOPojo>&) pPojo;
            
            if (pElementPojo->elementSerial == pElementNOPojo->fkElementSerial) {
                pElementPojo->pSubPojoList->push_back(pElementNOPojo);
//                break;
            }
        }
    }
    
    return accessoryPojoList;
}

shared_ptr<vector<shared_ptr<Pojo>>> AccessoryDao::readWithSQL(string& SQL)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = databaseManager.read(SQL.c_str(), false, AccessoryDao::readCallback);
    return pPojoList;
}
