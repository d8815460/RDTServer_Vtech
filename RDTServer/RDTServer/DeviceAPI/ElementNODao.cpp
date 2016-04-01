//
//  ElementNODao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/16.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "ElementNODao.hpp"
#include "DatabaseManager.hpp"

void ElementNODao::readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList)
{
    shared_ptr<ElementNOPojo> pElementNOPojo(new ElementNOPojo());
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
//        LOGD("data:%s", data);
        
        if (i == 0) {
            pElementNOPojo->elementNOSerial = stoi(data);
        }
        /******************************************* 修改處 *****************************************************/
        if_index_int_va(1, pElementNOPojo->fkElementSerial, data)
        if_index_int_va(2, pElementNOPojo->ElementNO,       data)
        if_index_str_va(3, pElementNOPojo->Value,           data)
        if_index_str_va(4, pElementNOPojo->NtfyEnable,      data)
        /******************************************* 修改處 *****************************************************/
        else {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Column_Over_The_Range);
        }
    }
    
    outPtrPojoList->push_back(pElementNOPojo);
}

shared_ptr<vector<shared_ptr<Pojo>>> ElementNODao::read(vector<int>& elementSerialList)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    vector<ValueObject> objList;
    for (int elementSerial : elementSerialList) {
        ValueObject obj(DatabaseType_INTEGER, "elementSerial", elementSerial);
        objList.push_back(obj);
    }
    string SQL = Pojo::genInSQL("SELECT * FROM ElementNO WHERE fkElementSerial", objList);
    
    return databaseManager.read(SQL.c_str(), ElementNODao::readCallback);
}

void ElementNODao::create(shared_ptr<ElementNOPojo> pElementNOPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    pElementNOPojo->genValueObject();
    std::string sql = Pojo::createSQL("INSERT INTO ElementNO (elementNOSerial,", pElementNOPojo->valueObjectList);
    databaseManager.exec(sql.c_str());
}

void ElementNODao::update(shared_ptr<ElementNOPojo> pElementNOPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    pElementNOPojo->genValueObject();
    std::string sql = Pojo::updateSQL("UPDATE ElementNO SET", pElementNOPojo->valueObjectList);
    databaseManager.exec(sql.c_str());
}

int ElementNODao::deleteAll()
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    return databaseManager.exec("DELETE FROM ElementNO;");
}

int ElementNODao::deleteWithSerial(int elementNOSerial)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "DELETE FROM ElementNO WHERE elementSerial = %d;", elementNOSerial);
    LOGD("buffer:%s", buffer);
    
    return databaseManager.exec(buffer);
}

int ElementNODao::deleteWithFKElementSerialList(vector<int>& elementSerialList)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    vector<ValueObject> objList;
    for (int fkElementSerial : elementSerialList) {
        ValueObject obj(DatabaseType_INTEGER, "fkElementSerial", fkElementSerial);
        objList.push_back(obj);
    }
    string SQL = Pojo::genInSQL("DELETE FROM ElementNO WHERE fkElementSerial", objList);
    
    return databaseManager.exec(SQL.c_str());
}
