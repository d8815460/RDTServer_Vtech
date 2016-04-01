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

#define ContractorAssign(key) \
    this->key = key

#define Declare(type, value) \
    type value

#define SubPojoListYES() \
    pSubPojoList = shared_ptr<vector<shared_ptr<Pojo>>>(new vector<shared_ptr<Pojo>>());

#define SubPojoListNO()

#define Contractor1(method, subPojoList, k, v)   \
    method(Declare(k, v))  \
    {                        \
        ContractorAssign(v); \
        subPojoList \
    }

#define Contractor2(method, subPojoList, k1, v1, k2, v2)   \
    method(Declare(k1, v1), Declare(k2, v2))  \
    {                        \
        ContractorAssign(v1); \
        ContractorAssign(v2); \
        subPojoList \
    }

#define Contractor3(method, subPojoList, k1, v1, k2, v2, k3, v3)   \
    method(Declare(k1, v1), Declare(k2, v2), Declare(k3, v3))  \
    {                        \
        ContractorAssign(v1); \
        ContractorAssign(v2); \
        ContractorAssign(v3); \
        subPojoList \
    }

#define Contractor4(method, subPojoList, k1, v1, k2, v2, k3, v3, k4, v4)   \
    method(Declare(k1, v1), Declare(k2, v2), Declare(k3, v3), Declare(k4, v4))  \
    {                        \
        ContractorAssign(v1); \
        ContractorAssign(v2); \
        ContractorAssign(v3); \
        ContractorAssign(v4); \
        subPojoList \
    }

#define Contractor5(method, subPojoList, k1, v1, k2, v2, k3, v3, k4, v4, k5, v5)   \
    method(Declare(k1, v1), Declare(k2, v2), Declare(k3, v3), Declare(k4, v4), Declare(k5, v5))  \
    {                        \
        ContractorAssign(v1); \
        ContractorAssign(v2); \
        ContractorAssign(v3); \
        ContractorAssign(v4); \
        ContractorAssign(v5); \
        subPojoList \
    }

#define Contractor6(method, subPojoList, k1, v1, k2, v2, k3, v3, k4, v4, k5, v5, k6, v6)   \
    method(Declare(k1, v1), Declare(k2, v2), Declare(k3, v3), Declare(k4, v4), Declare(k5, v5), Declare(k6, v6))  \
    {                        \
        ContractorAssign(v1); \
        ContractorAssign(v2); \
        ContractorAssign(v3); \
        ContractorAssign(v4); \
        ContractorAssign(v5); \
        ContractorAssign(v6); \
        subPojoList \
    }

enum DatabaseType
{
    DatabaseType_INTEGER,
    DatabaseType_TEXT,
};

using namespace std;

struct ValueObject
{
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
    
    static std::string createSQL(std::string prefixSQL, vector<ValueObject>& objList)
    {
        std::string sql = prefixSQL;
        sql.append(" ");
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
    
    static std::string updateSQL(std::string prefixSQL, vector<ValueObject>& objList)
    {
        std::string sql = prefixSQL;
        sql.append(" ");
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
    
    static std::string genInSQL(std::string prefixSQL, vector<ValueObject>& objList)
    {
        std::string SQL = prefixSQL;
        SQL.append(" in (");
        
        for (ValueObject obj : objList) {
            if (obj.type == DatabaseType_INTEGER) {
                SQL.append(to_string(obj.nValue)).append(", ");
            }
            else {
                SQL.append("'").append(obj.strValue).append("'").append(", ");
            }
        }
        
        SQL.erase(SQL.size() - 2);
//        LOGD("SQL2:%s", SQL.c_str());
        SQL.append(")");
        
        LOGD("SQL: %s", SQL.c_str());
        return SQL;
    }
};

#endif /* Pojo_hpp */
