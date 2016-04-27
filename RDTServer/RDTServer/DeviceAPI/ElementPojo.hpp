//
//  ElementPojo.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/4/26.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef ElementPojo_hpp
#define ElementPojo_hpp

#include <stdio.h>
#include <memory>
#include "Pojo.hpp"

/******************************************* 修改處 *****************************************************/
static const char* createElement =      "CREATE TABLE Element ("
                                        "elementSerial      INTEGER PRIMARY KEY,"
                                        "fkAccessorySerial  INTEGER REFERENCES Accessory(accessorySerial),"
                                        "Element            TEXT);";
/******************************************* 修改處 *****************************************************/

struct ElementPojo : public Pojo
{
    vector<ValueObject> valueObjectList;
    
    std::string Element;
    
    shared_ptr<vector<shared_ptr<Pojo>>> pSubPojoList;
    
    ElementPojo()
    {
        pSubPojoList = shared_ptr<vector<shared_ptr<Pojo>>>(new vector<shared_ptr<Pojo>>());
    }
    
    /******************************************* 修改處 *****************************************************/
    Contractor1(ElementPojo, SubPojoList(),
                std::string, Element)
    /******************************************* 修改處 *****************************************************/
    
    void genValueObject()
    {
        /******************************************* 修改處 *****************************************************/
        valueObjectList = {
            createValueObject(Element),
        };
        /******************************************* 修改處 *****************************************************/
    }
    
    virtual void toJson(Json::Value& json)
    {
        Json::Value jsonList;
        Json::Value subJsonList;
        
        for (vector<shared_ptr<Pojo>>::iterator it=pSubPojoList->begin() ; it!=pSubPojoList->end() ; it++) {
            shared_ptr<Pojo> pPojo = *it;
            
            pPojo->toJson(subJsonList);
            //            LOGD("產生json = \n%s", subJson.toStyledString().c_str());
        }
        
        jsonList[Element] = subJsonList;
        json["ListElement"] = jsonList;
        
        //        LOGD("產生json = \n%s", json.toStyledString().c_str());
    }
    
    virtual void print()
    {
        LOGD("Element:%s", Element.c_str());
        
        if (pSubPojoList != NULL) {
            for (shared_ptr<Pojo> pPojo : *pSubPojoList) {
                pPojo->print();
            }
        }
    }
};

#endif /* ElementPojo_hpp */
