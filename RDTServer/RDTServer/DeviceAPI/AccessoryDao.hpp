//
//  AccessoryDao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef AccessoryDao_hpp
#define AccessoryDao_hpp

#include <stdio.h>
#include <string>
#include <memory>
#include <json/reader.h>
#include "DatabaseManager.hpp"
#include "Common.hpp"
#include "AccessoryPojo.hpp"

using namespace std;

class AccessoryDao
{
public:
    static void create(shared_ptr<AccessoryPojo>& pAccessoryPojo);
    static void createList(shared_ptr<vector<shared_ptr<AccessoryPojo>>>& pAccessoryPojoList);
    
    static void update(AccessoryPojo& pojo);
    
    void deleteCallback(Json::Value& root, int AID, vector<ValueObject>& propertyList);
    static int deleteIt(shared_ptr<vector<shared_ptr<AccessoryPojo>>>& pPojoList, vector<int> aidList);
    
    // 更新
//    static void updateElementNOWithWhereSQL(string& selectWhereSQL, vector<ValueObject>& objList);
//    static void updateAccessoryWithWhereSQL(string& selectWhereSQL, vector<ValueObject>& objList);
    
    // 刪除
//    static int deleteAll();
//    static int deleteWithSerialList(vector<int>& accessorySerialList);
//    static int deleteWithAIDList(vector<int>& AIDList);
    
    // 查詢
    static shared_ptr<vector<shared_ptr<Pojo>>> readAll();
    static shared_ptr<vector<shared_ptr<Pojo>>> read(vector<int>& AIDList);
    static shared_ptr<vector<shared_ptr<Pojo>>> readNestWithWhereSQL(string& whereSQL);
    
    static shared_ptr<vector<shared_ptr<Pojo>>> readWithSQL(string& SQL);
    
private:
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList, bool isNest);
};

#endif /* AccessoryDao_hpp */
