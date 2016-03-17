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
        else if (i == 1) {
            pElementNOPojo->fkElementSerial = stoi(data);
        }
        else if (i == 2) {
            pElementNOPojo->elementNO = stoi(data);
        }
        else if (i == 3) {
            pElementNOPojo->value = data;
        }
        else {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Column_Over_The_Range);
        }
    }
    
    outPtrPojoList->push_back(pElementNOPojo);
}

shared_ptr<vector<shared_ptr<Pojo>>> ElementNODao::read(int fkAccessorySerial)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "SELECT * FROM ElementNO WHERE fkElementSerial = %d;", fkAccessorySerial);
    
    return databaseManager.read(buffer, ElementNODao::readCallback);
}

void ElementNODao::create(shared_ptr<ElementNOPojo> pElementNOPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "INSERT INTO ElementNO VALUES(NULL, %d, '%d', '%s');", pElementNOPojo->fkElementSerial, pElementNOPojo->elementNO, pElementNOPojo->value.c_str());
    LOGD("buffer:%s", buffer);
    
    databaseManager.exec(buffer);
}

void ElementNODao::update(shared_ptr<ElementNOPojo> pElementNOPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "UPDATE ElementNO SET name = '%d', value = '%s';", pElementNOPojo->elementNO, pElementNOPojo->value.c_str());
    LOGD("buffer:%s", buffer);
    
    databaseManager.exec(buffer);
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

int ElementNODao::deleteWithFKAccessorySerial(int fkAccessorySerial)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "DELETE FROM ElementNO WHERE fkAccessorySerial = %d;", fkAccessorySerial);
    LOGD("buffer:%s", buffer);
    
    return databaseManager.exec(buffer);
}
