//
//  HardwardEvent.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/28.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef CommandHardwardEvent_hpp
#define CommandHardwardEvent_hpp

#include <stdio.h>
#include <string>
#include <json/reader.h>

struct CommandHardwardNotifyData
{
    Json::Value* pJsonObject;
};

struct CommandHardwardRecvJsonData
{
    Json::Value* pJsonObject;
};

struct CommandBase
{
    int errorCode;
};

struct CommandHardwardRecvProductCode : CommandBase
{
    int productCode;
};

struct CommandHardwardRecvProductName : CommandBase
{
    string productName;
};

class CommandHardwardEvent
{
public:
    virtual void onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData) = 0;
    virtual void onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData) = 0;
    
    virtual void onCommandHardwardRecvProductCode(CommandHardwardRecvProductCode* pCommandHardwardRecvProductCode) = 0;
    virtual void onCommandHardwardRecvProductName(CommandHardwardRecvProductName* pCommandHardwardRecvProductName) = 0;
};

#endif /* CommandHardwardEvent_hpp */
