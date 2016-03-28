//
//  Dao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef Pojo_hpp
#define Pojo_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <json/reader.h>

#define Pojo_Buffer_Size 128

#define addJson(json, field) \
    json[#field] = field

#define addPojo(pojo, field, data) \
    pojo->##field = data

#define str_va(key, data) \
    key = data

#define int_va(key, data) \
    key = stoi(data)

#define if_index_int_va(index, key, data) \
    else if (i == index) { \
        int_va(key, data); \
    }

#define if_index_str_va(index, key, data) \
    else if (i == index) { \
        str_va(key, data); \
    }

#define createValueObject(type, vo) \
    ValueObject(type, #vo, vo),

enum DatabaseType
{
    DatabaseType_INTEGER,
    DatabaseType_TEXT,
};

using namespace std;

struct ValueObject
{
    ValueObject() {}
    
    ValueObject(DatabaseType type, std::string key, int nValue)
    {
        this->type = type;
        this->key = key;
        this->nValue = nValue;
    }
    
    ValueObject(DatabaseType type, std::string key, std::string strValue)
    {
        this->type = type;
        this->key = key;
        this->strValue = strValue;
    }
    
    DatabaseType type;
    std::string key;
    
//    union {
        int         nValue;
        std::string strValue;
//    };
};

struct Pojo
{
    virtual ~Pojo() {}
    
    virtual void toJson(Json::Value& json) {};
//    virtual std::string toJson() = 0;
    
    virtual void print() = 0;
    
    std::string createSQL(std::string prefixSQL, vector<ValueObject>& objList)
    {
        std::string sql = prefixSQL;
        std::string sql1 = "";
        std::string sql2 = "";
        
        for (ValueObject obj : objList) {
            sql1.append(obj.key).append(", ");
            
            if (obj.type == DatabaseType_INTEGER) {
                sql2.append(to_string(obj.nValue)).append(", ");
            }
            else {
                sql2.append("'").append(obj.strValue).append("'").append(", ");
            }
        }
        
//        LOGD("sql1:%s", sql1.c_str());
//        LOGD("sql2:%s", sql2.c_str());
        sql1.erase(sql1.size() - 2);
        sql2.erase(sql2.size() - 2);
        LOGD("sql1:%s", sql1.c_str());
        LOGD("sql2:%s", sql2.c_str());
        
        sql.append(sql1);
        sql.append(") VALUES (NULL, ");
        sql.append(sql2);
        sql.append(")");
        
        LOGD("sql:%s", sql.c_str());
        return sql;
    }
    
    std::string updateSQL(std::string prefixSQL, vector<ValueObject>& objList)
    {
        std::string sql = prefixSQL;
        std::string sql1 = "";
        std::string sql2 = "";
        
        for (ValueObject obj : objList) {
            sql1.append(obj.key).append(" = ");
            
            if (obj.type == DatabaseType_INTEGER) {
                sql2.append(to_string(obj.nValue)).append(", ");
            }
            else {
                sql2.append("'").append(obj.strValue).append("'").append(", ");
            }
        }
        
        //        LOGD("sql1:%s", sql1.c_str());
        //        LOGD("sql2:%s", sql2.c_str());
        sql1.erase(sql1.size() - 2);
        sql2.erase(sql2.size() - 2);
        LOGD("sql1:%s", sql1.c_str());
        LOGD("sql2:%s", sql2.c_str());
        
        sql.append(sql1);
        sql.append(") VALUES (NULL, ");
        sql.append(sql2);
        sql.append(")");
        
        LOGD("sql:%s", sql.c_str());
        return sql;
    }
};

#endif /* Pojo_hpp */
