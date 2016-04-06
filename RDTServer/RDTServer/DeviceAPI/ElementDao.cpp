//
//  ElementDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "ElementDao.hpp"
#include <memory>
#include "DatabaseManager.hpp"
#include "ElementNODao.hpp"

void ElementDao::readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList, bool isNest)
{
    shared_ptr<ElementPojo> pElementPojo(new ElementPojo());
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
//        LOGD("data:%s", data);
        
        if (i == 0) {
            pElementPojo->elementSerial = stoi(data);
//            LOGD("pElementPojo->elementSerial:%d", pElementPojo->elementSerial);
            
            if (isNest == true) {
                /* 取得 pElementPojoList 裡所有的資料 */
                vector<int> elementSerialList;
                elementSerialList.push_back(pElementPojo->elementSerial);
                pElementPojo->pSubPojoList = ElementNODao::read(elementSerialList);
            }
        }
        /******************************************* 修改處 *****************************************************/
        if_index_int_va(1, pElementPojo->fkAccessorySerial, data)
        if_index_str_va(2, pElementPojo->Element, data)
        /******************************************* 修改處 *****************************************************/
        else {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Column_Over_The_Range);
        }
    }
    
    outPtrPojoList->push_back(pElementPojo);
}

shared_ptr<vector<shared_ptr<Pojo>>> ElementDao::read(vector<int>& fkAccessorySerialList)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    vector<ValueObject> objList;
    for (int fkAccessorySerial : fkAccessorySerialList) {
        ValueObject obj(DatabaseType_INTEGER, "fkAccessorySerial", fkAccessorySerial);
        objList.push_back(obj);
    }
    string SQL = Pojo::genInSQL("SELECT * FROM Element WHERE fkAccessorySerial", objList);
    
    return databaseManager.read(SQL.c_str(), true, ElementDao::readCallback);
}

shared_ptr<vector<shared_ptr<Pojo>>> ElementDao::readWithSQL(string& SQL)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
        
    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = databaseManager.read(SQL.c_str(), false, ElementDao::readCallback);
    return pPojoList;
}

void ElementDao::create(shared_ptr<ElementPojo> pElementPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    pElementPojo->genValueObject();
    std::string sql = Pojo::createSQL("INSERT INTO Element (elementSerial,", pElementPojo->valueObjectList);
    databaseManager.exec(sql.c_str());
    
    int rowid = (int) sqlite3_last_insert_rowid(databaseManager.getSqliteDatabase());
                                    
    for (shared_ptr<Pojo> pPojo : *pElementPojo->pSubPojoList) {
        shared_ptr<ElementNOPojo>& pElementNOPojo = (shared_ptr<ElementNOPojo>&) pPojo;
        
        pElementPojo->elementSerial = rowid;
        pElementNOPojo->fkElementSerial = pElementPojo->elementSerial;
        
//        LOGD("pElementPojo->name:%s", pElementPojo->name.c_str());
//        LOGD("pElementPojo->elementSerial:%d", pElementPojo->elementSerial);
        
        ElementNODao::create(pElementNOPojo);
    }
}

void ElementDao::update(shared_ptr<ElementPojo> pElementPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    pElementPojo->genValueObject();
    std::string sql = Pojo::updateSQL("UPDATE Element SET", pElementPojo->valueObjectList);
    databaseManager.exec(sql.c_str());
    
    for (shared_ptr<Pojo> pPojo : *pElementPojo->pSubPojoList) {
        shared_ptr<ElementNOPojo>& pElementNOPojo = (shared_ptr<ElementNOPojo>&) pPojo;
//        LOGD("pElementPojo->name:%s", pElementPojo->name.c_str());
        
        ElementNODao::update(pElementNOPojo);
    }
}

int ElementDao::deleteAll()
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    ElementNODao::deleteAll();
    
    return databaseManager.exec("DELETE FROM Element;");
}

int ElementDao::deleteWithSerial(int elementSerial)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "DELETE FROM Element WHERE elementSerial = %d;", elementSerial);
    LOGD("buffer:%s", buffer);
    
    return databaseManager.exec(buffer);
}

int ElementDao::deleteWithFKAccessorySerialList(vector<int>& accessorySerialList)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    // 呼叫下一層Delete
    vector<int> elementSerialList;
    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = ElementDao::read(accessorySerialList);
    for (shared_ptr<Pojo> pPojo : *pPojoList) {
        shared_ptr<ElementPojo>& pElementPojo = (shared_ptr<ElementPojo>&) pPojo;
        
        elementSerialList.push_back(pElementPojo->fkAccessorySerial);
    }
    ElementNODao::deleteWithFKElementSerialList(elementSerialList);
    
    // 這一層的刪除
    vector<ValueObject> objList;
    for (int elementSerial : elementSerialList) {
        ValueObject obj(DatabaseType_INTEGER, "elementSerial", elementSerial);
        objList.push_back(obj);
    }
    string SQL = Pojo::genInSQL("DELETE FROM Element WHERE fkAccessorySerial", objList);
    
    return databaseManager.exec(SQL.c_str());
}
