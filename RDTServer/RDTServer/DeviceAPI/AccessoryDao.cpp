//
//  AccessoryDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "AccessoryDao.hpp"

void AccessoryDao::readCallback(PojoManager& outPojoManager, int row, vector<char*>& colList)
{
    AccessoryPojo* pAccessoryPojo = new AccessoryPojo();
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
        
        if (i == 0) {
            pAccessoryPojo->accessorySerial = stoi(data);
        }
        else if (i == 1) {
            pAccessoryPojo->accessoryId = stoi(data);
        }
        else if (i == 2) {
            pAccessoryPojo->accessoryType = stoi(data);
        }
        else {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Column_Over_The_Range);
        }
    }
    
    outPojoManager.push_back(pAccessoryPojo);
}

void AccessoryDao::read(std::string& sql, PojoManager& outPojoManager)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    databaseManager.read(sql, outPojoManager, readCallback);
    
}
