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

static std::string insertService1 = "INSERT INTO Service VALUES(NULL, 1, 'ColorService', 'RGB');";
static std::string insertService2 = "INSERT INTO Service VALUES(NULL, 1, 'SwitchService', 'ON_OFF');";

static std::string queryAccessorySql = "SELECT * FROM Accessory;";
static std::string queryServiceSql   = "SELECT * FROM Service;";

typedef void (*DatabaseManager_ReadCallback) (PojoManager& outPojoManager, int row, vector<char*>& rowList);

class DatabaseManager
{
public:
    static DatabaseManager& getInstance() { return m_Instance; }
    
    void open();
    void close();
    int exec(std::string& sql);
    void read(std::string& sql, PojoManager& outPojoManager, DatabaseManager_ReadCallback callback);
    
#pragma mark - Private Method
    
private:
    DatabaseManager();
    
    static DatabaseManager m_Instance;
    sqlite3* m_pDatabase;
};

#endif /* DatabaseManager_hpp */
