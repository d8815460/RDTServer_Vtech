//
//  ServiceDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "ServiceDao.hpp"
#include "DatabaseManager.hpp"

void ServiceDao::readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList)
{
    shared_ptr<ServicePojo> pServicePojo(new ServicePojo());
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
//        LOGD("data:%s", data);
        
        if (i == 0) {
            pServicePojo->serviceSerial = stoi(data);
        }
        else if (i == 1) {
            pServicePojo->fkAccessorySerial = stoi(data);
        }
        else if (i == 2) {
            pServicePojo->name = data;
//            LOGD("data:%s", data);
//            LOGD("pServicePojo->name:%s", pServicePojo->name);
        }
        else if (i == 3) {
            pServicePojo->value = data;
        }
        else {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Column_Over_The_Range);
        }
    }
    
    outPtrPojoList->push_back(pServicePojo);
}

shared_ptr<vector<shared_ptr<Pojo>>> ServiceDao::read(int fkAccessorySerial)
{
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "SELECT * FROM Service WHERE fkAccessorySerial = %d;", fkAccessorySerial);
    
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    return databaseManager.read(buffer, ServiceDao::readCallback);
}

void ServiceDao::create(shared_ptr<ServicePojo> pServicePojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "INSERT INTO Service VALUES(NULL, %d, '%s', '%s');", pServicePojo->fkAccessorySerial, pServicePojo->name.c_str(), pServicePojo->value.c_str());
    LOGD("buffer:%s", buffer);
    
    databaseManager.exec(buffer);
}

void ServiceDao::update(shared_ptr<ServicePojo> pServicePojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "UPDATE Service SET name = '%s', value = '%s';", pServicePojo->name.c_str(), pServicePojo->value.c_str());
    LOGD("buffer:%s", buffer);
    databaseManager.exec(buffer);
}

int ServiceDao::deleteAll()
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    return databaseManager.exec("DELETE FROM Service;");
}

int ServiceDao::deleteWithSerial(int serviceSerial)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "DELETE FROM Service WHERE serviceSerial = %d;", serviceSerial);
    LOGD("buffer:%s", buffer);
    
    return databaseManager.exec(buffer);
}

int ServiceDao::deleteWithFKAccessorySerial(int fkAccessorySerial)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "DELETE FROM Service WHERE fkAccessorySerial = %d;", fkAccessorySerial);
    LOGD("buffer:%s", buffer);
    
    return databaseManager.exec(buffer);
}
