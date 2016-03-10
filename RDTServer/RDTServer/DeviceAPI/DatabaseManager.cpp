//
//  DatabaseManager.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/8.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "DatabaseManager.hpp"
#include "AccessoryDao.hpp"
#include "ServiceDao.hpp"

DatabaseManager DatabaseManager::m_Instance = DatabaseManager();

#pragma mark - Private Method

DatabaseManager::DatabaseManager()
{
    LOGD("DatabaseManager");
    
    open();
    
    /* 建立 Table */
    exec(createAccessory);
    exec(createService);
    
    /* 新增一筆資料 */
    exec(insertAccessory1);
    exec(insertAccessory2);
    exec(insertService1);
    exec(insertService2);
    
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
        LOGD();
    }
    
    /* 取得 database 裡所有的資料 */
    pojoManager.clear();
    ServiceDao::read(queryServiceSql, pojoManager);
    for (Pojo* pPojo : pojoManager.pojoList) {
        ServicePojo* pServicePojo = (ServicePojo*) pPojo;
        
        LOGD("serviceSerial:%d", pServicePojo->serviceSerial);
        LOGD("fkAccessorySerial:%d", pServicePojo->fkAccessorySerial);
        LOGD("name:%s", pServicePojo->name.c_str());
        LOGD("value:%s", pServicePojo->value.c_str());
        LOGD();
    }
    
    close();
}

void DatabaseManager::open()
{
    /* 開啟 database 檔 */
    if (sqlite3_open_v2("database.db3", &m_pDatabase, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)) {
        throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Open_Database_Failed);
    }
}

void DatabaseManager::close()
{
    /* 關閉 database */
    sqlite3_close(m_pDatabase);
}

int DatabaseManager::exec(std::string& sql)
{
//    LOGD("execSQL:%s", sql.c_str());
    
    char *errMsg = NULL;
    
    /* 新增一筆資料 */
    int count = sqlite3_exec(m_pDatabase, sql.c_str(), 0, 0, &errMsg);
//    LOGD("count:%d", count);
    
    if (errMsg != NULL) {
//        LOGD("errMsg:%s", errMsg);
        
        std::string errorMessage = std::string(errMsg);
        if (errorMessage.rfind("already exists") != std::string::npos) {
            // 不處理
        }
        else {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, errMsg);
        }
    }
    
    return count;
}

void DatabaseManager::read(std::string& sql, PojoManager& outPojoManager, DatabaseManager_ReadCallback callback)
{
    char* errMsg = NULL;
    int rows;
    int cols;
    char** result;
    
    sqlite3_get_table(m_pDatabase, sql.c_str(), &result, &rows, &cols, &errMsg);
    if (errMsg != NULL) {
        throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, errMsg);
    }
    
    vector<char*> colList;
    for (int i=0 ; i<rows+1 ; i++) {
        for (int j=0 ; j<cols ; j++) {
//            LOG("%s\t", result[i * cols + j]);
            
            if (i > 0) {
                colList.push_back(result[i * cols + j]);
            }
            
        }
        
        if (i > 0) {
            callback(outPojoManager, i, colList);
            colList.clear();
        }
        
//        LOG("\n");
    }
    
    /* 釋放 */
    sqlite3_free_table(result);
}
