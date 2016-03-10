//
//  DatabaseManager.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/8.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef DatabaseManager_hpp
#define DatabaseManager_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "sqlite3.h"
#include "DatabaseException.hpp"
#include "PojoManager.hpp"
#include "AccessoryDao.hpp"

using namespace std;

static std::string createAccessory = "CREATE TABLE Accessory ("
                                     "accessorySerial INTEGER PRIMARY KEY,"
                                     "accessoryId     INTEGER,"
                                     "accessoryType   INTEGER);";

static std::string createService =  "CREATE TABLE Service ("
                                    "serviceSerial INTEGER PRIMARY KEY,"
                                    "fkAccessorySerial INTEGER,"
                                    "name      TEXT,"
                                    "value     TEXT,"
                                    "FOREIGN KEY(fkAccessorySerial) REFERENCES Accessory(accessorySerial));";

static std::string insertAccessory1 = "INSERT INTO Accessory VALUES(NULL, 888, 999);";
static std::string insertAccessory2 = "INSERT INTO Accessory VALUES(NULL, 111, 222);";

static std::string insertService1 =  "INSERT INTO Service VALUES(NULL, 1, 'ColorService', 'RGB');";
static std::string insertService2 =  "INSERT INTO Service VALUES(NULL, 1, 'SwitchService', 'ON_OFF');";

static std::string queryAccessorySql = "SELECT * FROM Accessory;";

typedef void (*DatabaseManager_ReadCallback) (PojoManager& outPojoManager, int row, vector<char*>& rowList);

class DatabaseManager
{
public:
    static DatabaseManager& getInstance()
    {
        return m_Instance;
    }
    
    void open()
    {
        /* 開啟 database 檔 */
        if (sqlite3_open_v2("database.db3", &m_pDatabase, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL)) {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Open_Database_Failed);
        }
    }
    
    void close()
    {
        /* 關閉 database */
        sqlite3_close(m_pDatabase);
    }
    
    int exec(std::string& sql)
    {
        LOGD("execSQL:%s", sql.c_str());
        
        char *errMsg = NULL;
        
        /* 新增一筆資料 */
        int count = sqlite3_exec(m_pDatabase, sql.c_str(), 0, 0, &errMsg);
        LOGD("count:%d", count);
        
        if (errMsg != NULL) {
            LOGD("errMsg:%s", errMsg);
            
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
    
    void read(std::string& sql, PojoManager& outPojoManager, DatabaseManager_ReadCallback callback)
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
                LOG("%s\t", result[i * cols + j]);
                
                if (i > 0) {
                    colList.push_back(result[i * cols + j]);
                }
                
            }
            
            if (i > 0) {
                callback(outPojoManager, i, colList);
                colList.clear();
            }
            
            LOG("\n");
        }
        
        /* 釋放 */
        sqlite3_free_table(result);
    }
    
#pragma mark - Private Method
    
private:
    DatabaseManager();
    
    static DatabaseManager m_Instance;
    sqlite3* m_pDatabase;
};

#endif /* DatabaseManager_hpp */
