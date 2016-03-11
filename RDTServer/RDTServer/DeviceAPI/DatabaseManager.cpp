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

static const char* createAccessory =    "CREATE TABLE Accessory ("
                                        "accessorySerial INTEGER PRIMARY KEY,"
                                        "accessoryId     INTEGER,"
                                        "accessoryType   INTEGER);";

static const char* createService =  "CREATE TABLE Service ("
                                    "serviceSerial INTEGER PRIMARY KEY,"
                                    "fkAccessorySerial INTEGER,"
                                    "name      TEXT,"
                                    "value     TEXT,"
                                    "FOREIGN KEY(fkAccessorySerial) REFERENCES Accessory(accessorySerial));";

#pragma mark - Private Method

DatabaseManager::DatabaseManager()
{
    LOGD("DatabaseManager");
    
    open();
    
    /* 建立 Table */
    exec(createAccessory);
    exec(createService);
    
    /* 新增一筆資料 */
    ServicePojo servicePojo1;
    servicePojo1.fkAccessorySerial = 1;
    servicePojo1.name = "ColorService";
    servicePojo1.value = "RGB";
    ServicePojo servicePojo2;
    servicePojo2.fkAccessorySerial = 1;
    servicePojo2.name = "SwitchService";
    servicePojo2.value = "ON_OFF";
    AccessoryPojo accessoryPojo;
    accessoryPojo.accessoryId = 1;
    accessoryPojo.accessoryType = 1;
    accessoryPojo.servicePojoList.push_back(&servicePojo1);
    accessoryPojo.servicePojoList.push_back(&servicePojo2);
    AccessoryDao::create(accessoryPojo);
    
    /* 取得該筆資料的 ID */
//    LOGD("ID:%lld\n", sqlite3_last_insert_rowid(m_pDatabase));
    
    /* 取得 database 裡所有的資料 */
    vector<shared_ptr<Pojo>> pojoList;
    AccessoryDao::read(pojoList);
    for (shared_ptr<Pojo> pPojo : pojoList) {
        LOGD("use_count:%ld", pPojo.use_count());
        pPojo->print();
    }
    
    close();
}

void DatabaseManager::open()
{
    /* 開啟 database 檔 */
    if (sqlite3_open_v2(Database_File_Name, &m_pDatabase, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)) {
        throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Open_Database_Failed);
    }
}

void DatabaseManager::close()
{
    /* 關閉 database */
    sqlite3_close(m_pDatabase);
}

int DatabaseManager::exec(const char* sql)
{
//    LOGD("execSQL:%s", sql.c_str());
    
    char *errMsg = NULL;
    
    /* 新增一筆資料 */
    int count = sqlite3_exec(m_pDatabase, sql, 0, 0, &errMsg);
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

void DatabaseManager::read(const char* sql, vector<shared_ptr<Pojo>>& outPojoList, DatabaseManager_ReadCallback callback)
{
    char* errMsg = NULL;
    int rows;
    int cols;
    char** result;
    
    sqlite3_get_table(m_pDatabase, sql, &result, &rows, &cols, &errMsg);
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
            callback(outPojoList, i, colList);
            colList.clear();
        }
        
//        LOG("\n");
    }
    
    /* 釋放 */
    sqlite3_free_table(result);
}
