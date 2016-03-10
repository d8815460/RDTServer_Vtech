//
//  ServiceDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "ServiceDao.hpp"
#include "DatabaseManager.hpp"

void ServiceDao::readCallback(PojoManager& outPojoManager, int row, vector<char*>& colList)
{
    ServicePojo* pServicePojo = new ServicePojo();
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
        LOGD("data:%s", data);
        
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
    
    outPojoManager.push_back(pServicePojo);
}

void ServiceDao::read(std::string& sql, PojoManager& outPojoManager)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    databaseManager.read(sql, outPojoManager, ServiceDao::readCallback);
    
}
