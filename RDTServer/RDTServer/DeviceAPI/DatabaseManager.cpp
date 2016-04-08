//
//  DatabaseManager.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/8.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "DatabaseManager.hpp"
#include <json/reader.h>
#include "Utility.hpp"

// Dao
#include "RoomDao.hpp"
#include "AccessoryDao.hpp"
#include "ElementDao.hpp"
#include "ElementNODao.hpp"

DatabaseManager DatabaseManager::m_Instance = DatabaseManager();

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
    exec(createRoom);
    exec(createAccessory);
    exec(createElement);
    exec(createElementNO);
    
    /******************************************* 修改處 *****************************************************/
    {
        shared_ptr<RoomPojo> pRoomPojo(new RoomPojo("MyRoom", 0));
        RoomDao::create(pRoomPojo);
    }
    
    {
        shared_ptr<RoomPojo> pRoomPojo(new RoomPojo("Has Room", 0));
        RoomDao::create(pRoomPojo);
    }
    
    {
        /* 新增一筆資料 */
        // AID, Name, IconType, Connection, IsGateway;
        AccessoryPojo accessoryPojo(0, "IPHub", 0, 1, false);
        
        // Element
        shared_ptr<ElementPojo> pElement1(new ElementPojo("switch"));
        
        // ElementNO, Value, NtfyEnable
        shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo(0, "轟天", true));
        shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo(1, "大鑫", true));
        
        accessoryPojo.pSubPojoList->push_back(pElement1);
        pElement1->pSubPojoList->push_back(pNO1);
        pElement1->pSubPojoList->push_back(pNO2);
        
        AccessoryDao::create(accessoryPojo);
    }
    
    {
        /* 新增一筆資料 */
        // AID, Name, IconType, Connection, IsGateway;
        AccessoryPojo accessoryPojo(1, "PC Home", 1, 1, false);
        
        // Element
        shared_ptr<ElementPojo> pElement1(new ElementPojo("switch"));
        
        // ElementNO, Value, NtfyEnable
        shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo(0, "轟天2", true));
        shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo(1, "大鑫2", true));
        
        accessoryPojo.pSubPojoList->push_back(pElement1);
        pElement1->pSubPojoList->push_back(pNO1);
        pElement1->pSubPojoList->push_back(pNO2);
        
        AccessoryDao::create(accessoryPojo);
    }
    /******************************************* 修改處 *****************************************************/
    
    /* 取得該筆資料的 ID */
//    LOGD("ID:%lld\n", sqlite3_last_insert_rowid(m_pDatabase));
    
    shared_ptr<vector<shared_ptr<Pojo>>> pojoList = NULL;
//    pojoList = AccessoryDao::readAll();
    
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
    
//    // 依照查詢條件生成Accessory
//    vector<ValueObject> vo;
//    vo.push_back(ValueObject("AID", 0));
//    vo.push_back(ValueObject("AID", 1));
//    string SQL = Pojo::genInSQL(vo, false);
//    
//    vo.clear();
//    vo.push_back(ValueObject("Element", "switch"));
//    SQL.append(Pojo::genInSQL(vo, true));
//    
//    vo.clear();
//    vo.push_back(ValueObject("ElementNo", 1));
//    SQL.append(Pojo::genInSQL(vo, true));
//    
//    Json::Value json;
//    pojoList = AccessoryDao::readNestWithSQL(SQL);
//    for (shared_ptr<Pojo> pPojo : *pojoList) {
//        pPojo->toJson(json);
//    }
//    LOGD("json:\n%s", json.toStyledString().c_str());
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

shared_ptr<vector<shared_ptr<Pojo>>> DatabaseManager::read(const char* sql, bool isNest, DatabaseManager_ReadCallback callback)
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
            callback(pPojoList, i, colList, isNest);
            colList.clear();
        }
        
//        LOG("\n");
    }
    
    /* 釋放 */
    sqlite3_free_table(result);
    
    return pPojoList;
}
