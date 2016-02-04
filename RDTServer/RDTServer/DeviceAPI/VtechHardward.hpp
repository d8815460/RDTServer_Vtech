//
//  VtechHardward.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/28.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef VtechHardward_hpp
#define VtechHardward_hpp

#include <stdio.h>
#include "Hardward.hpp"
#include <json/reader.h>

struct VtechHardward_HardwardData : HardwardData
{
    
};

struct VtechHardward_SendHardwardData : SendHardwardData
{
    const Json::Value* pInJsonObject;
    Json::Value* pOutJsonObject;
};

struct VtechHardward_HardwardNotifyData : HardwardNotifyData
{
    Json::Value* pOutJsonObject;
};

class VtechHardward : public Hardward
{
public:
    VtechHardward(HardwardEvent* pHardwardEvent, HardwardData* pHardwardData);
    
#pragma mark - Hardward
    void sendHardward(SendHardwardData* pSendHardwardData);
};

#endif /* VtechHardward_hpp */
