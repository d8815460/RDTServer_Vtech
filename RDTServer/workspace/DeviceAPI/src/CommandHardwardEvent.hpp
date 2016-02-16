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

struct CommandHardwardNotifyData
{
    
};

struct CommandHardwardRecvProductName
{
    std::string productName;
};

class CommandHardwardEvent
{
public:
    virtual void onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData) = 0;
    virtual void onCommandHardwardRecvProductName(CommandHardwardRecvProductName* pCommandHardwardRecvProductName) = 0;
//    virtual void onCommandHardwardRecvData();
    //    virtual void onCommandHardwardRecvJson(const Json::Value& inJsonObject, Json::Value& outJsonObject);
};

#endif /* CommandHardwardEvent_hpp */
