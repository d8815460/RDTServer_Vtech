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

struct AccessoryPojo : public Pojo
{
    int accessorySerial;
    int AID;
    int AType;
    shared_ptr<vector<shared_ptr<Pojo>>> pElementPojoList;
    
    AccessoryPojo()
    {
        pElementPojoList = shared_ptr<vector<shared_ptr<Pojo>>>(new vector<shared_ptr<Pojo>>());
    }
    
    virtual void toJson(Json::Value& json)
    {
        json["AID"] = AID;
        json["AType"] = AType;
        
        Json::Value subJsonList;
        for (vector<shared_ptr<Pojo>>::iterator it=pElementPojoList->begin() ; it!=pElementPojoList->end() ; it++) {
            shared_ptr<Pojo> pPojo = *it;
            
            Json::Value subJson;
            pPojo->toJson(subJson);
//            LOGD("產生json = \n%s", subJson.toStyledString().c_str());
            subJsonList.append(subJson);
        }
        
        json["ListElement"] = subJsonList;
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
        LOGD("AType:%d", AType);
        
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
