//
//  ElementNODao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef ElementNODao_hpp
#define ElementNODao_hpp

#include <stdio.h>
#include <string>
#include <memory>
#include "Pojo.hpp"
#include "Common.hpp"

/******************************************* 修改處 *****************************************************/
static const char* createElementNO =    "CREATE TABLE ElementNO ("
                                        "elementNOSerial    INTEGER PRIMARY KEY,"
                                        "fkElementSerial    INTEGER REFERENCES Element(elementSerial),"
                                        "elementNO          INTEGER,"
                                        "value              TEXT,"
                                        "NtfyEnable         BOOLEAN"
                                        ");";
/******************************************* 修改處 *****************************************************/

struct ElementNOPojo : public Pojo
{
    vector<ValueObject> valueObjectList;
    
    int         elementNOSerial;
    int         fkElementSerial;
    
    int         ElementNO;
    std::string Value;
    bool        NtfyEnable;
    
    ElementNOPojo() {}
    
    /******************************************* 修改處 *****************************************************/
    Contractor3(ElementNOPojo, SubPojoListNO(),
                int,            ElementNO,
                std::string,    Value,
                bool,           NtfyEnable)
    /******************************************* 修改處 *****************************************************/
    
    void genValueObject()
    {
        //        if (valueObjectList.size() == 0) {
        /******************************************* 修改處 *****************************************************/
        valueObjectList = {
            createValueObject(DatabaseType_INTEGER, fkElementSerial)
            createValueObject(DatabaseType_INTEGER, ElementNO)
            createValueObject(DatabaseType_TEXT,    Value)
            createValueObject(DatabaseType_INTEGER, NtfyEnable)
        };
        /******************************************* 修改處 *****************************************************/
        //        }
    }
    
    virtual void toJson(Json::Value& json)
    {
        /******************************************* 修改處 *****************************************************/
        addJson(json, NtfyEnable);
        
        // ElementNO
        // Value
        // 在下面加
        /******************************************* 修改處 *****************************************************/
        
        json[to_string(ElementNO)] = Value;
    }
        
    virtual void print()
    {
        LOGD("elementNOSerial:%d", elementNOSerial);
        LOGD("fkElementSerial:%d", fkElementSerial);
        LOGD("ElementNO:%d", ElementNO);
        LOGD("Value:%s", Value.c_str());
    }
};

class ElementNODao
{
public:
    static void create(shared_ptr<ElementNOPojo> pElementNOPojo);
    static void update(shared_ptr<ElementNOPojo> pElementNOPojo);
    
    static int deleteAll();
    static int deleteWithSerial(int elementNOSerial);
    static int deleteWithFKElementSerialList(vector<int>& elementSerialList);
    
    static shared_ptr<vector<shared_ptr<Pojo>>> read(vector<int>& elementSerialList);
    
private:
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList);
};

#endif /* ElementNODao_hpp */
