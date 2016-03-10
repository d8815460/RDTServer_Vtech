//
//  DatabaseManager.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/8.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "DatabaseManager.hpp"
#include "AccessoryDao.hpp"

DatabaseManager DatabaseManager::m_Instance = DatabaseManager();

#pragma mark - Private Method

DatabaseManager::DatabaseManager()
{
    LOGD("DatabaseManager");
    
    open();
    
    /* 建立 Table */
    exec(createAccessory);
    
//    exec(createService);
    
    /* 新增一筆資料 */
    exec(insertAccessory1);
    exec(insertAccessory2);
//    exec(insertService1);
//    exec(insertService2);
    
    /* 取得該筆資料的 ID */
//    LOGD("ID:%lld\n", sqlite3_last_insert_rowid(m_pDatabase));
    
    /* 取得 database 裡所有的資料 */
    PojoManager pojoManager;
    AccessoryDao::read(queryAccessorySql, pojoManager);
    
    for (Pojo* pPojo : pojoManager.pojoList) {
        AccessoryPojo* pAccessoryPojo = (AccessoryPojo*) pPojo;
        
        LOGD("accessorySerial:%d", pAccessoryPojo->accessorySerial);
        LOGD("accessoryId:%d", pAccessoryPojo->accessoryId);
        LOGD("accessoryType:%d", pAccessoryPojo->accessoryType);
    }
    
    close();
}