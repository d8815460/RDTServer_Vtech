//
//  Metadata.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/4/27.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef Metadata_hpp
#define Metadata_hpp

#include <stdio.h>
#include "Pojo.hpp"

struct MetadataPojo : public Pojo
{
    vector<ValueObject> valueObjectList;
    
    std::string MinValue;
    std::string MaxValue;
    std::string StepValue;
    std::string Format;
    std::string Units;
    
    MetadataPojo() {}
    
    /******************************************* 修改處 *****************************************************/
    Contractor3(MetadataPojo, NotingSubPojoList(),
                int,            Metadata,
                std::string,    Value)
    /******************************************* 修改處 *****************************************************/
    
    void genValueObject()
    {
        /******************************************* 修改處 *****************************************************/
        valueObjectList = {
            createValueObject(MinValue),
            createValueObject(MaxValue),
            createValueObject(StepValue),
            createValueObject(Format),
            createValueObject(Units),
        };
        /******************************************* 修改處 *****************************************************/
    }
    
    virtual void toJson(Json::Value& json)
    {
        /******************************************* 修改處 *****************************************************/
        addJson(json, MinValue);
        addJson(json, MaxValue);
        addJson(StepValue);
        addJson(Format);
        addJson(Units);
        
        // Metadata
        // 在下面加
        /******************************************* 修改處 *****************************************************/
        
        json["Metadata"] = Value;
    }
    
    virtual void print()
    {
        LOGD("Metadata MinValue:%d", MinValue);
        LOGD("Metadata MaxValue:%d", MaxValue);
    }
};

#endif /* Metadata_hpp */
