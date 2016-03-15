//
//  Hardward.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/4.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef Hardward_hpp
#define Hardward_hpp

#include <stdio.h>
#include "CommandHardwardEvent.hpp"

class Hardward : public CommandHardwardEvent
{
public:
#pragma mark - CommandHardwardEvent
    virtual void onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData);
    virtual void onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData);
    
    virtual void onCommandHardwardRecv_ProductCode(CommandHardwardRecv_ProductCode* pCommandHardwardRecv_ProductCode);
    virtual void onCommandHardwardRecv_ProductName(CommandHardwardRecv_ProductName* pCommandHardwardRecv_ProductName);
    
    virtual void onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems);
    virtual void onCommandHardwardRecv_DeleteItems(CommandHardwardRecv_DeleteItems* pCommandHardwardRecv_DeleteItems);
    virtual void onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems);
    virtual void onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems);
};

#endif /* Hardward_hpp */
