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

struct CommandHardwardNotifyData
{
    
};

struct CommandHardwardRecvProductName
{
    char* pProductName;
};

class CommandHardwardEvent
{
public:
    virtual void onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData) = 0;
    
//    virtual void onCommandHardwardRecvProductName(CommandHardwardRecvProductName* pCommandHardwardRecvProductName) = 0;
};

#endif /* CommandHardwardEvent_hpp */
