//
//  RoomDao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/4/8.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef RoomDao_hpp
#define RoomDao_hpp

#include <stdio.h>
#include <string>
#include <memory>
#include "Pojo.hpp"
#include "Common.hpp"

/******************************************* 修改處 *****************************************************/
static const char* createRoom =         "CREATE TABLE Room ("
                                        "RoomSerial         INTEGER PRIMARY KEY,"
                                        "RoomName           TEXT,"
                                        "RoomSeq            INTEGER"
                                        ");";
/******************************************* 修改處 *****************************************************/

struct RoomPojo : public Pojo
{
    vector<ValueObject> valueObjectList;
    
    int         RoomSerial;
    
    std::string RoomName;
    int         RoomSeq;
    
    RoomPojo() {}
    
    /******************************************* 修改處 *****************************************************/
    Contractor2(RoomPojo, SubPojoListNO(),
                std::string,    RoomName,
                int,            RoomSeq)
    /******************************************* 修改處 *****************************************************/
    
    void genValueObject()
    {
        /******************************************* 修改處 *****************************************************/
        valueObjectList = {
            createValueObject(RoomName),
            createValueObject(RoomSeq),
        };
        /******************************************* 修改處 *****************************************************/
    }
    
    virtual void toJson(Json::Value& json)
    {
        /******************************************* 修改處 *****************************************************/
        addJson(json, RoomName);
        addJson(json, RoomSeq);
        /******************************************* 修改處 *****************************************************/
    }
    
    virtual void print()
    {
        LOGD("RoomName:%s", RoomName.c_str());
        LOGD("RoomSeq:%d", RoomSeq);
    }
};

class RoomDao
{
public:
    static void create(shared_ptr<RoomPojo> pRoomPojo);
    static void update(shared_ptr<RoomPojo> pRoomPojo);
    
    static int deleteAll();
    static int deleteWithSerial(int roomSerial);
    static int deleteWithFKElementSerialList(vector<int>& elementSerialList);
    
    static shared_ptr<vector<shared_ptr<Pojo>>> read(vector<int>& elementSerialList);
    static shared_ptr<vector<shared_ptr<Pojo>>> readWithSQL(string& SQL);
    
private:
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList, bool isNest);
};

#endif /* RoomDao_hpp */
