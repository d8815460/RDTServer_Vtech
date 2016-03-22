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

struct ElementPojo : public Pojo
{
    int elementSerial;
    int fkAccessorySerial;
    std::string element;
    shared_ptr<vector<shared_ptr<Pojo>>> pElementNOPojoList;
    
    ElementPojo()
    {
        pElementNOPojoList = shared_ptr<vector<shared_ptr<Pojo>>>(new vector<shared_ptr<Pojo>>());
    }
    
    virtual void toJson(Json::Value& json)
    {
        Json::Value jsonList;
        
        Json::Value subJsonList;
        for (vector<shared_ptr<Pojo>>::iterator it=pElementNOPojoList->begin() ; it!=pElementNOPojoList->end() ; it++) {
            shared_ptr<Pojo> pPojo = *it;
            
            pPojo->toJson(subJsonList);
//            LOGD("產生json = \n%s", subJson.toStyledString().c_str());
        }
        
        jsonList[element] = subJsonList;
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
        LOGD("element:%s", element.c_str());
        
        if (pElementNOPojoList != NULL) {
            for (shared_ptr<Pojo> pPojo : *pElementNOPojoList) {
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
