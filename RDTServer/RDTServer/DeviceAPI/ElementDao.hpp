//
//  ElementDao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef ElementDao_hpp
#define ElementDao_hpp

#include <stdio.h>
#include <string>
#include <memory>
#include "Pojo.hpp"
#include "Common.hpp"

/******************************************* 修改處 *****************************************************/
static const char* createElement =      "CREATE TABLE Element ("
                                        "elementSerial      INTEGER PRIMARY KEY,"
                                        "fkAccessorySerial  INTEGER REFERENCES Accessory(accessorySerial),"
                                        "Element            TEXT);";
/******************************************* 修改處 *****************************************************/

struct ElementPojo : public Pojo
{
    vector<ValueObject> valueObjectList;
    
    int elementSerial;
    
    int         fkAccessorySerial;
    std::string Element;
    
    shared_ptr<vector<shared_ptr<Pojo>>> pSubPojoList;
    
    ElementPojo()
    {
        pSubPojoList = shared_ptr<vector<shared_ptr<Pojo>>>(new vector<shared_ptr<Pojo>>());
    }
    
    /******************************************* 修改處 *****************************************************/
    Contractor1(ElementPojo, SubPojoListYES(),
                std::string, Element)
    /******************************************* 修改處 *****************************************************/
    
    void genValueObject()
    {
        //        if (valueObjectList.size() == 0) {
        /******************************************* 修改處 *****************************************************/
        valueObjectList = {
            createValueObject(DatabaseType_INTEGER, fkAccessorySerial)
            createValueObject(DatabaseType_TEXT,    Element)
        };
        /******************************************* 修改處 *****************************************************/
        //        }
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
    
//    virtual std::string toJson()
//    {
//        std::string json;
//        
//        json.append(QUOTES).append("Element").append(QUOTES_COLON).append(QUOTES).append(element).append(QUOTES).append(COMMA).append(NEW_LINE);
//        
//        json.append(QUOTES).append("ListElementNO").append(QUOTES_COLON_BRACKETS).append(NEW_LINE);
//                
//        for (vector<shared_ptr<Pojo>>::iterator it=pElementNOPojoList->begin() ; it!=pElementNOPojoList->end() ; it++) {
//            shared_ptr<Pojo> pPojo = *it;
//            
//            json.append("{");
//            json.append(pPojo->toJson());
//            json.append("}");
//            
//            // 不是最後一個
//            if (it != pElementNOPojoList->end() - 1) {
//                json.append(COMMA);
//            }
//            // 最後一個
////            else {
////                // 移除最後一個逗號
////                json = json.erase(json.size()-1, 1);
////            }
//        }
//        json.append("]");
//        
//        return json;
//    }
    
    virtual void print()
    {
        LOGD("elementSerial:%d", elementSerial);
        LOGD("fkAccessorySerial:%d", fkAccessorySerial);
        LOGD("Element:%s", Element.c_str());
        
        if (pSubPojoList != NULL) {
            for (shared_ptr<Pojo> pPojo : *pSubPojoList) {
                pPojo->print();
            }
        }
    }
};

class ElementDao
{
public:
    static void create(shared_ptr<ElementPojo> pElementPojo);
    static void update(shared_ptr<ElementPojo> pElementPojo);
    
    static int deleteAll();
    static int deleteWithSerial(int elementSerial);
    static int deleteWithFKAccessorySerial(int fkAccessorySerial);
    
    static shared_ptr<vector<shared_ptr<Pojo>>> read(int fkAccessorySerial);
    
private:
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList);
};

#endif /* ElementDao_hpp */
