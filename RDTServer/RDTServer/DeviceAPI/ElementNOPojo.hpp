//
//  ElementNOPojo.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/4/26.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef ElementNOPojo_hpp
#define ElementNOPojo_hpp

#include <stdio.h>
#include "Pojo.hpp"

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
    
    int         ElementNO;
    std::string Value;
    bool        NtfyEnable;
    
    ElementNOPojo() {}
    
    /******************************************* 修改處 *****************************************************/
    Contractor3(ElementNOPojo, NotingSubPojoList(),
                int,            ElementNO,
                std::string,    Value,
                bool,           NtfyEnable)
    /******************************************* 修改處 *****************************************************/
    
    void genValueObject()
    {
        /******************************************* 修改處 *****************************************************/
        valueObjectList = {
            createValueObject(ElementNO),
            createValueObject(Value),
            createValueObject(NtfyEnable),
        };
        /******************************************* 修改處 *****************************************************/
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
        LOGD("ElementNO:%d", ElementNO);
        LOGD("Value:%s", Value.c_str());
    }
};

#endif /* ElementNOPojo_hpp */
