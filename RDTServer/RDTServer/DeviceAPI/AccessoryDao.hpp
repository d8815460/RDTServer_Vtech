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
#include "DatabaseManager.hpp"
#include "Common.hpp"
#include <json/reader.h>

using namespace std;

/******************************************* 修改處 *****************************************************/
static const char* createAccessory =    "CREATE TABLE Accessory ("
                                        "accessorySerial    INTEGER PRIMARY KEY,"
                                        "AID                INTEGER,"
                                        "Name               TEXT,"
                                        "IconType           INTEGER,"
                                        "Connection         INTEGER,"
                                        "IsGateway          BOOLEAN"
                                        ");";
/******************************************* 修改處 *****************************************************/

struct AccessoryPojo : public Pojo
{
    vector<ValueObject> valueObjectList;
    
    int         accessorySerial;
    
    int         AID;
    std::string Name;
    int         IconType;
    int         Connection;
    bool        IsGateway;
    
    shared_ptr<vector<shared_ptr<Pojo>>> pElementPojoList;
    
    AccessoryPojo()
    {
        pElementPojoList = shared_ptr<vector<shared_ptr<Pojo>>>(new vector<shared_ptr<Pojo>>());
    }
    
    void genValueObject()
    {
//        if (valueObjectList.size() == 0) {
            /******************************************* 修改處 *****************************************************/
            valueObjectList = {
                ValueObject(DatabaseType_INTEGER,   "AID",          AID),
                ValueObject(DatabaseType_TEXT,      "Name",         Name),
                ValueObject(DatabaseType_INTEGER,   "IconType",     IconType),
                ValueObject(DatabaseType_INTEGER,   "Connection",   Connection),
                ValueObject(DatabaseType_INTEGER,   "IsGateway",    IsGateway),
            };
            /******************************************* 修改處 *****************************************************/
//        }
    }
    
    virtual void toJson(Json::Value& json)
    {
        Json::Value subJsonList;
        
        /******************************************* 修改處 *****************************************************/
        addJson(subJsonList, Name);
        addJson(subJsonList, IconType);
        addJson(subJsonList, Connection);
        addJson(subJsonList, IsGateway);
        /******************************************* 修改處 *****************************************************/
        
//        for (map<std::string, enum DatabaseType>::iterator it=mapping.begin() ; it!=mapping.end() ; it++) {
////            LOGD("first:%s", it->first.c_str());
//            addJson(subJsonList, it->first.c_str());
//        }
        
//        addJson(subJsonList, IconType);
//        addJson(subJsonList, Connection);
        
//        subJsonList["Connection"]
        
        for (vector<shared_ptr<Pojo>>::iterator it=pElementPojoList->begin() ; it!=pElementPojoList->end() ; it++) {
            shared_ptr<Pojo> pPojo = *it;
            
            pPojo->toJson(subJsonList);
//            LOGD("產生json = \n%s", subJson.toStyledString().c_str());
        }
        
        json[to_string(AID)] = subJsonList;
//        LOGD("產生json = \n%s", json.toStyledString().c_str());
    }
    
//    virtual std::string toJson()
//    {
//        std::string json;
//        
//        json.append("{").append(NEW_LINE);
//        
//        json.append(QUOTES).append("AID").append(QUOTES_COLON).append(to_string(AID)).append(COMMA).append(NEW_LINE);
//        json.append(QUOTES).append("AType").append(QUOTES_COLON).append(to_string(AType)).append(COMMA).append(NEW_LINE);
//        
//        json.append(QUOTES).append("ListElement").append(QUOTES_COLON_BRACKETS).append(NEW_LINE);
//        for (vector<shared_ptr<Pojo>>::iterator it=pElementPojoList->begin() ; it!=pElementPojoList->end() ; it++) {
//            shared_ptr<Pojo> pPojo = *it;
//            
//            json.append("{");
//            json.append(pPojo->toJson());
//            json.append("}");
//            
//            // 不是最後一個
//            if (it != pElementPojoList->end() - 1) {
//                json.append(COMMA);
//            }
//        }
//        json.append("]");
//        
//        json.append("}");
//        
//        return json;
//    }
    
    virtual void print()
    {
        LOGD("================================================================================");
        LOGD("accessorySerial:%d", accessorySerial);
        LOGD("AID:%d", AID);
        LOGD("IconType:%d", IconType);
        
        if (pElementPojoList != NULL) {
            for (shared_ptr<Pojo> pPojo : *pElementPojoList) {
                pPojo->print();
            }
        }
        LOGD("================================================================================");
        LOGD();
    }
};

class AccessoryDao
{
public:
    static void create(AccessoryPojo& pojo);
    static void update(AccessoryPojo& pojo);
    
    static int deleteAll();
    static int deleteWithSerial(int accessorySerial);
    
    static shared_ptr<vector<shared_ptr<Pojo>>> read();
    
private:
    AccessoryDao() {};
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList);
};

#endif /* AccessoryDao_hpp */
