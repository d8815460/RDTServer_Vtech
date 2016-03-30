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

void ElementDao::readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList)
{
    shared_ptr<ElementPojo> pElementPojo(new ElementPojo());
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
//        LOGD("data:%s", data);
        
        if (i == 0) {
            pElementPojo->elementSerial = stoi(data);
//            LOGD("pElementPojo->elementSerial:%d", pElementPojo->elementSerial);
            
            /* 取得 pElementPojoList 裡所有的資料 */
            pElementPojo->pSubPojoList = ElementNODao::read(pElementPojo->elementSerial);
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

shared_ptr<vector<shared_ptr<Pojo>>> ElementDao::read(int fkAccessorySerial)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "SELECT * FROM Element WHERE fkAccessorySerial = %d;", fkAccessorySerial);
    
    return databaseManager.read(buffer, ElementDao::readCallback);
}

void ElementDao::create(shared_ptr<ElementPojo> pElementPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    pElementPojo->genValueObject();
    std::string sql = pElementPojo->createSQL("INSERT INTO Element (elementSerial, ", pElementPojo->valueObjectList);
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
    std::string sql = pElementPojo->updateSQL("UPDATE Element SET ", pElementPojo->valueObjectList);
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

int ElementDao::deleteWithFKAccessorySerial(int fkAccessorySerial)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "DELETE FROM Element WHERE fkAccessorySerial = %d;", fkAccessorySerial);
    LOGD("buffer:%s", buffer);
    
    return databaseManager.exec(buffer);
}
