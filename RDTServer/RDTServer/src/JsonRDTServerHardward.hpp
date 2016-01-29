//
//  JsonRDTServerHardward.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/29.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef JsonRDTServerHardward_hpp
#define JsonRDTServerHardward_hpp

#include <stdio.h>
#include "Hardward.hpp"
#include <json/reader.h>

struct JsonRDTServerHardward_HardwardData : HardwardData
{
    
};

struct JsonRDTServerHardward_SendHardwardData : SendHardwardData
{
    const Json::Value* pInJsonObject;
    Json::Value* pOutJsonObject;
};

struct JsonRDTServerHardward_HardwardNotifyData : HardwardNotifyData
{
    Json::Value* pOutJsonObject;
};

class JsonRDTServerHardward : public Hardward
{
public:
    JsonRDTServerHardward(HardwardEvent* pHardwardEvent, HardwardData* pHardwardData);
    
#pragma mark - Hardward
    void sendHardward(SendHardwardData* pSendHardwardData);
};

#endif /* JsonRDTServerHardward_hpp */
