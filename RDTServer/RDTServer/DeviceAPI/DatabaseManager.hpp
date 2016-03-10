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
#include <vector>
#include "sqlite3.h"
#include "DatabaseException.hpp"
#include "PojoManager.hpp"
#include "AccessoryDao.hpp"

using namespace std;

static const char* createAccessory = "CREATE TABLE Accessory ("
                                     "accessorySerial INTEGER PRIMARY KEY,"
                                     "accessoryId     INTEGER,"
                                     "accessoryType   INTEGER);";

static const char* createService =  "CREATE TABLE Service ("
                                    "serviceSerial INTEGER PRIMARY KEY,"
                                    "fkAccessorySerial INTEGER,"
                                    "name      TEXT,"
                                    "value     TEXT,"
                                    "FOREIGN KEY(fkAccessorySerial) REFERENCES Accessory(accessorySerial));";

static const char* insertAccessory1 = "INSERT INTO Accessory VALUES(NULL, 888, 999);";
static const char* insertAccessory2 = "INSERT INTO Accessory VALUES(NULL, 111, 222);";

static const char* insertService1 = "INSERT INTO Service VALUES(NULL, 1, 'ColorService', 'RGB');";
static const char* insertService2 = "INSERT INTO Service VALUES(NULL, 2, 'SwitchService', 'ON_OFF');";

static const char* queryAccessorySql = "SELECT * FROM Accessory;";
static const char* queryServiceSql   = "SELECT * FROM Service;";

typedef void (*DatabaseManager_ReadCallback) (PojoManager& outPojoManager, int row, vector<char*>& rowList);

class DatabaseManager
{
public:
    static DatabaseManager& getInstance() { return m_Instance; }
    
    void open();
    void close();
    int exec(const char* sql);
    void read(const char* sql, PojoManager& outPojoManager, DatabaseManager_ReadCallback callback);
    
#pragma mark - Private Method
    
private:
    DatabaseManager();
    
    static DatabaseManager m_Instance;
    sqlite3* m_pDatabase;
};

#endif /* DatabaseManager_hpp */
