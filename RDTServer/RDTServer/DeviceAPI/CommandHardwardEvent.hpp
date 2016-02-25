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

struct CommandHardwardRecv_ProductCode : CommandBase
{
    int productCode;
};

struct CommandHardwardRecv_ProductName : CommandBase
{
    string productName;
};

struct CommandHardwardRecv_CreateAccessoryItems : CommandBase
{
    AccessoryData* pAccessoryData;
};

struct CommandHardwardRecv_DeleteAccessoryItems : CommandBase
{
    int accessoryId;
};

struct CommandHardwardRecv_ReadAccessoryByType : CommandBase
{
    set<int> typeSet;
};

struct CommandHardwardRecv_UpdateAccessoryFunctionCode : CommandBase
{
    vector<AccessoryData*>  m_accessoryList;
};

class CommandHardwardEvent
{
public:
    virtual void onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData) = 0;
    virtual void onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData) = 0;
    
    virtual void onCommandHardwardRecv_ProductCode(CommandHardwardRecv_ProductCode* pCommandHardwardRecv_ProductCode) = 0;
    virtual void onCommandHardwardRecv_ProductName(CommandHardwardRecv_ProductName* pCommandHardwardRecv_ProductCode) = 0;
    
    /**
     * \brief 硬體收到新增Accessory項目
     *
     * \details 當收到新增Accessory項目時，系統將會建立Accessory，並發送一個struct，包含資料項目AccessoryData,必須填入相關資料
     *
     * \param CommandHardwardRecv_CreateAccessoryItems.pAccessoryData 包含新增Accessory相關的資料
     * \param psRDT_Status [out] The status of specified RDT channel
     *
     * \return #RDT_ER_NoERROR if getting the RDT status successfully
     * \return Error code if return value < 0
     *			- #RDT_ER_NOT_INITIALIZED RDT module is not initialized yet
     *			- #RDT_ER_INVALID_RDT_ID The specified RDT channel ID is not valid
     */
    virtual void onCommandHardwardRecv_CreateAccessoryItems(CommandHardwardRecv_CreateAccessoryItems* pCommandHardwardRecv_CreateAccessoryItems) = 0;
    virtual void onCommandHardwardRecv_DeleteAccessoryItems(CommandHardwardRecv_DeleteAccessoryItems* pCommandHardwardRecv_DeleteAccessoryItems) = 0;
    virtual void onCommandHardwardRecv_ReadAccessoryByType(CommandHardwardRecv_ReadAccessoryByType* pCommandHardwardRecv_ReadAccessoryByType) = 0;
    virtual void onCommandHardwardRecv_UpdateAccessoryFunctionCode(CommandHardwardRecv_UpdateAccessoryFunctionCode* pCommandHardwardRecv_UpdateAccessoryFunctionCode) = 0;
    
//    virtual void onCommandHardwardRecv_GetAccessoryByType(CommandHardwardRecv_GetAccessoryByType* pCommandHardwardRecv_GetAccessoryByType) = 0;
};

#endif /* CommandHardwardEvent_hpp */
