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
                                        "value              TEXT);";
/******************************************* 修改處 *****************************************************/

struct ElementNOPojo : public Pojo
{
    vector<ValueObject> valueObjectList;
    
    int elementNOSerial;
    
    int fkElementSerial;
    int ElementNO;
    std::string Value;
    
    ElementNOPojo() {}
    
    void genValueObject()
    {
        //        if (valueObjectList.size() == 0) {
        /******************************************* 修改處 *****************************************************/
        valueObjectList = {
            createValueObject(DatabaseType_INTEGER, fkElementSerial)
            createValueObject(DatabaseType_INTEGER, ElementNO)
            createValueObject(DatabaseType_TEXT,    Value)
        };
        /******************************************* 修改處 *****************************************************/
        //        }
    }
    
    virtual void toJson(Json::Value& json)
    {
        json[to_string(ElementNO)] = Value;
    }
    
//    virtual std::string toJson()
//    {
//        std::string json;
//        
//        json.append(QUOTES).append("ElementNO").append(QUOTES_COLON).append(to_string(elementNO)).append(COMMA).append(NEW_LINE);
//        json.append(QUOTES).append("value").append(QUOTES_COLON).append(QUOTES).append(value).append(QUOTES).append(NEW_LINE);
//        
//        return json;
//    }
    
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
    static int deleteWithFKAccessorySerial(int fkAccessorySerial);
    
    static shared_ptr<vector<shared_ptr<Pojo>>> read(int fkAccessorySerial);
    
private:
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList);
};

#endif /* ElementNODao_hpp */
