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
#include <memory>
#include <map>
#include "sqlite3.h"
#include "DatabaseException.hpp"
#include "Pojo.hpp"

#define Database_File_Name "database.db3"

using namespace std;

typedef void (*DatabaseManager_ReadCallback) (shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& rowList, bool isNest);

class DatabaseManager
{
public:
    static DatabaseManager& getInstance() { return m_Instance; }
    ~DatabaseManager() { close(); }
    
    sqlite3* getSqliteDatabase() { return m_pDatabase; }
    
    void open();
    void close();
    int exec(const char* sql);
    shared_ptr<vector<shared_ptr<Pojo>>> read(const char* sql, bool isNest, DatabaseManager_ReadCallback callback);
    
#pragma mark - Private Method
    
private:
    DatabaseManager();
    
    static DatabaseManager m_Instance;
    sqlite3* m_pDatabase;
};

#endif /* DatabaseManager_hpp */
