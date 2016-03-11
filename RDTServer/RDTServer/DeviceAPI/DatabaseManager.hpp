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
#include "sqlite3.h"
#include "DatabaseException.hpp"
#include "PojoArray.hpp"
#include "Pojo.hpp"

#define Database_File_Name "database.db3"

using namespace std;

typedef void (*DatabaseManager_ReadCallback) (vector<shared_ptr<Pojo>>& outPojoList, int row, vector<char*>& rowList);

class DatabaseManager
{
public:
    static DatabaseManager& getInstance() { return m_Instance; }
    
    void open();
    void close();
    int exec(const char* sql);
    void read(const char* sql, vector<shared_ptr<Pojo>>& outPojoList, DatabaseManager_ReadCallback callback);
    
#pragma mark - Private Method
    
private:
    DatabaseManager();
    
    static DatabaseManager m_Instance;
    sqlite3* m_pDatabase;
};

#endif /* DatabaseManager_hpp */
