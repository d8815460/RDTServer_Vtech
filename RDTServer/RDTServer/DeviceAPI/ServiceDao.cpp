//
//  ServiceDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "ServiceDao.hpp"
#include "DatabaseManager.hpp"

void ServiceDao::readCallback(PojoArray& outPojoArray, int row, vector<char*>& colList)
{
    ServicePojo* pServicePojo = new ServicePojo();
    
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
        }
        else if (i == 3) {
            pServicePojo->value = data;
        }
        else {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Column_Over_The_Range);
        }
    }
    
    outPojoArray.push_back(pServicePojo);
}

void ServiceDao::read(char* sql, PojoArray& outPojoArray)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    databaseManager.read(sql, outPojoArray, ServiceDao::readCallback);
}

void ServiceDao::create(ServicePojo& servicePojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "INSERT INTO Service VALUES(NULL, %d, '%s', '%s');", servicePojo.fkAccessorySerial, servicePojo.name.c_str(), servicePojo.value.c_str());
    databaseManager.exec(buffer);
}
