//
//  Hardward.cpp
//  HardwardAPI
//
//  Created by jakey on 2016/3/4.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "Hardward.hpp"

#pragma mark - CommandHardwardEvent

void Hardward::onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData)
{
    LOGD("onCommandHardwardNotify");
}

void Hardward::onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData)
{
    LOGD("onCommandHardwardRecvJson");
}

void Hardward::onCommandHardwardRecv_ProductCode(CommandHardwardRecv_ProductCode* pCommandHardwardRecv_ProductCode)
{
    LOGD("onCommandHardwardRecv_ProductCode");
    
    pCommandHardwardRecv_ProductCode->productCode = -1;
}

void Hardward::onCommandHardwardRecv_ProductName(CommandHardwardRecv_ProductName* pCommandHardwardRecv_ProductName)
{
    LOGD("onCommandHardwardRecv_ProductName");
    
    pCommandHardwardRecv_ProductName->productName = "Hardward";
}

void Hardward::onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems)
{
    LOGD("onCommandHardwardRecv_CreateItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_CreateItems->dataType) {
        case DataType_Accessory: {
            // 將新增資料填入
            AccessoryData* pAccessoryData = (AccessoryData*) pCommandHardwardRecv_CreateItems->pBaseData;
            pAccessoryData->accessoryId = 1;
            pAccessoryData->accessoryType = 1;
            pAccessoryData->addFunctionCodeData("switch", 1);
            pAccessoryData->addFunctionCodeData("color", 1, 2);
        }   break;
            
        default:
            LOGE("對應不到dataType");
            break;
    }
    
}

void Hardward::onCommandHardwardRecv_DeleteItems(CommandHardwardRecv_DeleteItems* pCommandHardwardRecv_DeleteItems)
{
    LOGD("onCommandHardwardRecv_DeleteItems");
    
    // 針對特定的硬體刪除關聯
    // 如移除燈的關聯
    switch (pCommandHardwardRecv_DeleteItems->dataType) {
        case DataType_Accessory: {
            // remove pCommandHardwardRecv_DeleteItems->id;
        }
            
        default:
            LOGE("對應不到dataType");
            break;
    }
    
}

void Hardward::onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems)
{
    LOGD("onCommandHardwardRecv_ReadItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_ReadItems->dataType) {
        case DataType_Accessory: {
            // 針對收到的資料做為參考
            vector<AccessoryData*>* pAccessoryList = (vector<AccessoryData*>*) &pCommandHardwardRecv_ReadItems->baseDataList;
            for (int i=0 ; i<pAccessoryList->size() ; i++) {
                LOGD("accessoryId:%d", (*pAccessoryList)[i]->accessoryId);
                LOGD("accessoryType:%d", (*pAccessoryList)[i]->accessoryType);
            }
        }
            
        default:
            LOGE("對應不到dataType");
            break;
    }
}

void Hardward::onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems)
{
    LOGD("onCommandHardwardRecv_UpdateItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_UpdateItems->dataType) {
        case DataType_Accessory: {
            // 針對收到的資料做為更新硬體參考
            vector<AccessoryData*>* pAccessoryList = (vector<AccessoryData*>*) &pCommandHardwardRecv_UpdateItems->baseDataList;
            for (int i=0 ; i<pAccessoryList->size() ; i++) {
                LOGD("accessoryId:%d", (*pAccessoryList)[i]->accessoryId);
                LOGD("accessoryType:%d", (*pAccessoryList)[i]->accessoryType);
            }
        }
            
        default:
            LOGE("對應不到dataType");
            break;
    }
}
