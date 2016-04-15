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
#include "RoomDao.hpp"

using namespace std;

/******************************************* 修改處 *****************************************************/
static const char* createAccessory =    "CREATE TABLE Accessory ("
                                        "accessorySerial    INTEGER PRIMARY KEY,"
                                        "fkRoomSerial       INTEGER REFERENCES Room(RoomSerial),"
                                        "AID                INTEGER,"
                                        "Name               TEXT,"
                                        "AccSeq             INTEGER,"
                                        "IconType           INTEGER,"
                                        "Connection         INTEGER,"
                                        "IsGateway          BOOLEAN"
                                        ");";
/******************************************* 修改處 *****************************************************/

struct AccessoryPojo : public Pojo
{
    vector<ValueObject> valueObjectList;
    
    int         accessorySerial;
    
    shared_ptr<RoomPojo>    pRoomPojo;
    int         fkRoomSerial;
    
    int         AID;
    std::string Name;
    int         AccSeq;
    int         IconType;
    int         Connection;
    bool        IsGateway;
    
    shared_ptr<vector<shared_ptr<Pojo>>> pSubPojoList;
    
    AccessoryPojo()
    {
        pSubPojoList = shared_ptr<vector<shared_ptr<Pojo>>>(new vector<shared_ptr<Pojo>>());
    }
    
    /******************************************* 修改處 *****************************************************/
    Contractor7(AccessoryPojo, SubPojoList(),
                int,         fkRoomSerial,
                int,         AID,
                std::string, Name,
                int,         AccSeq,
                int,         IconType,
                int,         Connection,
                bool,        IsGateway)
    /******************************************* 修改處 *****************************************************/
    
    void genValueObject()
    {
        /******************************************* 修改處 *****************************************************/
        valueObjectList = {
            createValueObject(fkRoomSerial),
            createValueObject(AID),
            createValueObject(Name),
            createValueObject(AccSeq),
            createValueObject(IconType),
            createValueObject(Connection),
            createValueObject(IsGateway),
        };
        /******************************************* 修改處 *****************************************************/
    }
    
    virtual void toJson(Json::Value& json)
    {
        Json::Value subJsonList;
        
        /******************************************* 修改處 *****************************************************/
        // AID在下面加
//        addJson(subJsonList, fkRoomSerial);
        
        addJson(subJsonList, Name);
        addJson(subJsonList, AccSeq);
        addJson(subJsonList, IconType);
        addJson(subJsonList, Connection);
        addJson(subJsonList, IsGateway);
        /******************************************* 修改處 *****************************************************/
        
        for (vector<shared_ptr<Pojo>>::iterator it=pSubPojoList->begin() ; it!=pSubPojoList->end() ; it++) {
            shared_ptr<Pojo> pPojo = *it;
            
            pPojo->toJson(subJsonList);
//            LOGD("產生json = \n%s", subJson.toStyledString().c_str());
        }
        
        json[to_string(AID)] = subJsonList;
//        LOGD("產生json = \n%s", json.toStyledString().c_str());
    }
    
    virtual void print()
    {
        LOGD("================================================================================");
        LOGD("accessorySerial:%d", accessorySerial);
        LOGD("AID:%d", AID);
        LOGD("IconType:%d", IconType);
        
        if (pSubPojoList != NULL) {
            for (shared_ptr<Pojo> pPojo : *pSubPojoList) {
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
    
    // 更新
    static void updateElementNOWithWhereSQL(string& selectWhereSQL, vector<ValueObject>& objList);
    static void updateAccessoryWithWhereSQL(string& selectWhereSQL, vector<ValueObject>& objList);
    
    // 刪除
    static int deleteAll();
    static int deleteWithSerialList(vector<int>& accessorySerialList);
    static int deleteWithAIDList(vector<int>& AIDList);
    
    // 查詢
    static shared_ptr<vector<shared_ptr<Pojo>>> readAll();
    static shared_ptr<vector<shared_ptr<Pojo>>> read(vector<int>& AIDList);
    static shared_ptr<vector<shared_ptr<Pojo>>> readNestWithWhereSQL(string& whereSQL);
    
    static shared_ptr<vector<shared_ptr<Pojo>>> readWithSQL(string& SQL);
    
private:
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList, bool isNest);
};

#endif /* AccessoryDao_hpp */
