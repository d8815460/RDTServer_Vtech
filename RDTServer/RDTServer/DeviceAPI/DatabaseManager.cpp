//
//  DatabaseManager.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/8.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "DatabaseManager.hpp"
#include "AccessoryDao.hpp"
#include "ElementDao.hpp"
#include "ElementNODao.hpp"
#include <json/reader.h>
#include "Utility.hpp"

DatabaseManager DatabaseManager::m_Instance = DatabaseManager();

static const char* createAccessory =    "CREATE TABLE Accessory ("
                                        "accessorySerial INTEGER PRIMARY KEY,"
                                        "AID     INTEGER,"
                                        "IconType   INTEGER);";

static const char* createElement =      "CREATE TABLE Element ("
                                        "elementSerial INTEGER PRIMARY KEY,"
                                        "fkAccessorySerial INTEGER REFERENCES Accessory(accessorySerial),"
                                        "element    TEXT);";

static const char* createElementNO =    "CREATE TABLE ElementNO ("
                                        "elementNOSerial INTEGER PRIMARY KEY,"
                                        "fkElementSerial INTEGER REFERENCES Element(elementSerial),"
                                        "elementNO INTEGER,"
                                        "value  TEXT);";

#pragma mark - Private Method

DatabaseManager::DatabaseManager()
{
    LOGD("DatabaseManager");
    
    // 移除Database file
    if(remove(Database_File_Name) != 0 ) {
        LOGE("Error deleting file");
//        throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Error_Deleting_Database);
    }
    else {
        LOGD("File successfully deleted");
    }
    
    open();
    
    /* 建立 Table */
    exec(createAccessory);
    exec(createElement);
    exec(createElementNO);
    
    {
        /* 新增一筆資料 */
        AccessoryPojo accessoryPojo;
        accessoryPojo.AID = 0;
        accessoryPojo.iconType = 0;
        
        shared_ptr<ElementPojo> pElement1(new ElementPojo);
        pElement1->element = "switch";
        
        shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo);
        pNO1->elementNO = 0;
        pNO1->value = "1";
        
        shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo);
        pNO2->elementNO = 1;
        pNO2->value = "大鑫";
        
        accessoryPojo.pElementPojoList->push_back(pElement1);
        pElement1->pElementNOPojoList->push_back(pNO1);
        pElement1->pElementNOPojoList->push_back(pNO2);
        
        AccessoryDao::create(accessoryPojo);
    }
    
    {
        /* 新增一筆資料 */
        AccessoryPojo accessoryPojo;
        accessoryPojo.AID = 1;
        accessoryPojo.iconType = 1;
        
        shared_ptr<ElementPojo> pElement1(new ElementPojo);
        pElement1->element = "switch";
        
        shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo);
        pNO1->elementNO = 0;
        pNO1->value = "1";
        
        shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo);
        pNO2->elementNO = 1;
        pNO2->value = "100";
        
        accessoryPojo.pElementPojoList->push_back(pElement1);
        pElement1->pElementNOPojoList->push_back(pNO1);
        pElement1->pElementNOPojoList->push_back(pNO2);
        
        AccessoryDao::create(accessoryPojo);
    }
    
    /* 取得該筆資料的 ID */
//    LOGD("ID:%lld\n", sqlite3_last_insert_rowid(m_pDatabase));
    
    shared_ptr<vector<shared_ptr<Pojo>>> pojoList = NULL;
//    pojoList = AccessoryDao::read();
    
//    // 更新資料
//    for (shared_ptr<Pojo> pPojo : *pojoList) {
//        shared_ptr<AccessoryPojo>& pAccessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
//        pAccessoryPojo->accessoryId = 111;
//        
//        for (shared_ptr<Pojo> pPojo : *pAccessoryPojo->pElementPojoList) {
//            shared_ptr<ElementPojo>& pElementPojo = (shared_ptr<ElementPojo>&) pPojo;
//            pElementPojo->name = "GGYY";
//            LOGD("pElementPojo->name:%s", pElementPojo->name.c_str());
//        }
//        
//        AccessoryDao::update(*pAccessoryPojo);
//    }
    
    // 刪除資料
//    AccessoryDao::deleteWithSerial(1);
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
//            LOGD("errMsg:%s", errMsg);
        }
        else {
            LOGE("errMsg:%s", errMsg);
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, errMsg);
        }
    }
    
    return count;
}

shared_ptr<vector<shared_ptr<Pojo>>> DatabaseManager::read(const char* sql, DatabaseManager_ReadCallback callback)
{
    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList(new vector<shared_ptr<Pojo>>);
    
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
            callback(pPojoList, i, colList);
            colList.clear();
        }
        
//        LOG("\n");
    }
    
    /* 釋放 */
    sqlite3_free_table(result);
    
    return pPojoList;
}
