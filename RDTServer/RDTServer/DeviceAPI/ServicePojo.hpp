//
//  ServicePojo.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/4/26.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef ServicePojo_hpp
#define ServicePojo_hpp

#include <stdio.h>
#include <vector>
#include "Pojo.hpp"

struct ServicePojo : public Pojo
{
    vector<ValueObject> valueObjectList;
    
    std::string Service;
    
    shared_ptr<vector<shared_ptr<Pojo>>> pSubPojoList;
    
    ServicePojo()
    {
        pSubPojoList = shared_ptr<vector<shared_ptr<Pojo>>>(new vector<shared_ptr<Pojo>>());
    }
    
    /******************************************* 修改處 *****************************************************/
    Contractor1(ServicePojo, SubPojoList(),
                std::string, Service)
    /******************************************* 修改處 *****************************************************/
    
    void genValueObject()
    {
        /******************************************* 修改處 *****************************************************/
        valueObjectList = {
            createValueObject(Service),
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
        
        jsonList[Service] = subJsonList;
        json["ListService"] = jsonList;
        
        //        LOGD("產生json = \n%s", json.toStyledString().c_str());
    }
    
    virtual void print()
    {
        LOGD("Service:%s", Service.c_str());
        
        if (pSubPojoList != NULL) {
            for (shared_ptr<Pojo> pPojo : *pSubPojoList) {
                pPojo->print();
            }
        }
    }
};

#endif /* ServicePojo_hpp */
