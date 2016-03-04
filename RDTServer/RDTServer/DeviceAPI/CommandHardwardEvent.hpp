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
#include "BaseData.hpp"
#include "CommandHardwardNormalEvent.hpp"
#include "CommandHardwardCURDEvent.hpp"

struct CommandHardwardRecvJsonData
{
    Json::Value* pJsonObject;
};

struct CommandHardwardNotifyData : CommandBase
{
    vector<BaseData*> baseDataList;
};

struct CommandHardwardRecv_ProductCode : CommandBase
{
    int productCode;
};

struct CommandHardwardRecv_ProductName : CommandBase
{
    string productName;
};

class CommandHardwardNormalEvent
{
public:
    virtual void onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData) = 0;
    virtual void onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData) = 0;
    
    virtual void onCommandHardwardRecv_ProductCode(CommandHardwardRecv_ProductCode* pCommandHardwardRecv_ProductCode) = 0;
    virtual void onCommandHardwardRecv_ProductName(CommandHardwardRecv_ProductName* pCommandHardwardRecv_ProductCode) = 0;
};

class CommandHardwardEvent : public CommandHardwardCURDEvent, public CommandHardwardNormalEvent
{
};

#endif /* CommandHardwardEvent_hpp */
