//
//  AccessoryPojo.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/4/26.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef AccessoryPojo_hpp
#define AccessoryPojo_hpp

#include <stdio.h>
#include <vector>
#include "Pojo.hpp"
#include "RoomDao.hpp"

/******************************************* 修改處 *****************************************************/
static const char* createAccessory =    "CREATE TABLE Accessory ("
                                        "accessorySerial    INTEGER PRIMARY KEY,"
                                        "fkRoomSerial       INTEGER REFERENCES Room(RoomSerial),"
                                        "AID                INTEGER,"
                                        "Name               TEXT,"
                                        "AccSeq             INTEGER,"
                                        "AccIconType        INTEGER,"
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
    std::string AccName;
    int         AccSeq;
    int         AccIconType;
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
                std::string, AccName,
                int,         AccSeq,
                int,         AccIconType,
                int,         Connection,
                bool,        IsGateway)
    /******************************************* 修改處 *****************************************************/
    
    void genValueObject()
    {
        /******************************************* 修改處 *****************************************************/
        valueObjectList = {
            createValueObject(fkRoomSerial),
            createValueObject(AID),
            createValueObject(AccName),
            createValueObject(AccSeq),
            createValueObject(AccIconType),
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
        
        addJson(subJsonList, AccName);
        addJson(subJsonList, AccSeq);
        addJson(subJsonList, AccIconType);
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
        LOGD("IconType:%d", AccIconType);
        
        if (pSubPojoList != NULL) {
            for (shared_ptr<Pojo> pPojo : *pSubPojoList) {
                pPojo->print();
            }
        }
        LOGD("================================================================================");
        LOGD();
    }
};

#endif /* AccessoryPojo_hpp */
