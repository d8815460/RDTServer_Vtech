//
//  ElementDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "ElementDao.hpp"
#include "DatabaseManager.hpp"

void ElementDao::readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList)
{
    shared_ptr<ElementPojo> pElementPojo(new ElementPojo());
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
//        LOGD("data:%s", data);
        
        if (i == 0) {
            pElementPojo->elementSerial = stoi(data);
        }
        else if (i == 1) {
            pElementPojo->fkAccessorySerial = stoi(data);
        }
        else if (i == 2) {
            pElementPojo->name = data;
//            LOGD("data:%s", data);
//            LOGD("pElementPojo->name:%s", pElementPojo->name);
        }
        else if (i == 3) {
            pElementPojo->value = data;
        }
        else {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Column_Over_The_Range);
        }
    }
    
    outPtrPojoList->push_back(pElementPojo);
}

shared_ptr<vector<shared_ptr<Pojo>>> ElementDao::read(int fkAccessorySerial)
{
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "SELECT * FROM Element WHERE fkAccessorySerial = %d;", fkAccessorySerial);
    
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    return databaseManager.read(buffer, ElementDao::readCallback);
}

void ElementDao::create(shared_ptr<ElementPojo> pElementPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "INSERT INTO Element VALUES(NULL, %d, '%s', '%s');", pElementPojo->fkAccessorySerial, pElementPojo->name.c_str(), pElementPojo->value.c_str());
    LOGD("buffer:%s", buffer);
    
    databaseManager.exec(buffer);
}

void ElementDao::update(shared_ptr<ElementPojo> pElementPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "UPDATE Element SET name = '%s', value = '%s';", pElementPojo->name.c_str(), pElementPojo->value.c_str());
    LOGD("buffer:%s", buffer);
    databaseManager.exec(buffer);
}

int ElementDao::deleteAll()
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
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
