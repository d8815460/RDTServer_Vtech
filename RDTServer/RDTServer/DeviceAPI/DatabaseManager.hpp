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
#include "AccessoryDao.hpp"

using namespace std;

static std::string createsql = "CREATE TABLE Contact ("
                            "ID INTEGER PRIMARY KEY,"
                            "Name VARCHAR(10),"
                            "PhoneNumber VARCHAR(10));";

static std::string createAccessory = "CREATE TABLE Accessory ("
                                     "accessoryNumber INTEGER PRIMARY KEY,"
                                     "accessoryId     INTEGER,"
                                     "accessoryType   INTEGER);";

static std::string insertsql = "INSERT INTO Contact VALUES(NULL, 'Fred', '09990123456');";
static std::string insertAccessory =  "INSERT INTO Accessory VALUES(NULL, 1, 1);";
static std::string insertAccessory2 = "INSERT INTO Accessory VALUES(NULL, 2, 2);";

static std::string querysql = "SELECT * FROM Contact;";
static std::string queryAccessorySql = "SELECT * FROM Accessory;";

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
        char *errMsg = NULL;
        
        /* 新增一筆資料 */
        int count = sqlite3_exec(m_pDatabase, sql.c_str(), 0, 0, &errMsg);
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
    
    void query(std::string& sql)
    {
//        map<std::string, std::string> resultMap;
        
        char *errMsg = NULL;
        int rows, cols;
        char **result;
        
        sqlite3_get_table(m_pDatabase, sql.c_str(), &result, &rows, &cols, &errMsg);
        if (errMsg != NULL) {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, errMsg);
        }
        
//        vector<std::string> headerList;
        for (int i=1 ; i<rows ; i++) {
            for (int j=0 ; j<cols ; j++) {
                LOG("%s\t", result[i * cols + j]);
                
//                resultMap.insert(pair<std::string, std::string>("a", "b"));
            }
            
            LOG("\n");
        }
        
        /* 釋放 */
        sqlite3_free_table(result);
    }
    
    void queryAccessory(std::string& sql, vector<AccessoryDao*>& outAccessoryDaoList)
    {
        char *errMsg = NULL;
        int rows, cols;
        char **result;
        
        sqlite3_get_table(m_pDatabase, sql.c_str(), &result, &rows, &cols, &errMsg);
        if (errMsg != NULL) {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, errMsg);
        }
        
        for (int i=1 ; i<rows ; i++) {
            AccessoryDao* pAccessoryDao = new AccessoryDao();
            
            for (int j=0 ; j<cols ; j++) {
//                LOG("%s\t", result[i * cols + j]);
                
                if (j == 0) {
                    pAccessoryDao->accessoryNumber = stoi(result[i * cols + j]);
                }
                else if (j == 1) {
                    pAccessoryDao->accessoryId = stoi(result[i * cols + j]);
                }
                else if (j == 2) {
                    pAccessoryDao->accessoryType = stoi(result[i * cols + j]);
                }
            }
            
//            LOG("\n");
            outAccessoryDaoList.push_back(pAccessoryDao);
        }
        
        /* 釋放 */
        sqlite3_free_table(result);
    }
    
private:
    DatabaseManager()
    {
        LOGD("DatabaseManager");
        
//        int rows, cols;
//        char **result;
        
        open();
        
        /* 建立 Table */
        exec(createAccessory);
        
        /* 新增一筆資料 */
        exec(insertAccessory);
        exec(insertAccessory2);
        
        /* 取得該筆資料的 ID */
        LOGD("ID:%lld\n", sqlite3_last_insert_rowid(m_pDatabase));
        
        /* 取得 database 裡所有的資料 */
        vector<AccessoryDao*> accessoryDaoList;
        queryAccessory(queryAccessorySql, accessoryDaoList);
        
        for (AccessoryDao* dao : accessoryDaoList) {
            LOGD("id:%d", dao->accessoryNumber);
            LOGD("accessoryId:%d", dao->accessoryId);
            LOGD("accessoryType:%d", dao->accessoryType);
        }
        
        close();
    }
    
    static DatabaseManager m_Instance;
    sqlite3* m_pDatabase;
};

#endif /* DatabaseManager_hpp */
