//
//  Hardward.cpp
//  HardwardAPI
//
//  Created by jakey on 2016/3/4.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "Hardward.hpp"
#include "AccessoryDao.hpp"

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
        }   break;
            
        default: {
            LOGE("對應不到dataType");
        }   break;
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
        }   break;
            
        default: {
            LOGE("對應不到dataType");
        }   break;
    }
    
}

void Hardward::onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems)
{
    LOGD("onCommandHardwardRecv_ReadItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_ReadItems->dataType) {
        case DataType_Accessory: {
            // 針對收到的資料做為參考
            shared_ptr<vector<shared_ptr<Pojo>>> pAccessoryList = (shared_ptr<vector<shared_ptr<Pojo>>>) pCommandHardwardRecv_ReadItems->pojoList;
            for (shared_ptr<Pojo> pPojo : *pAccessoryList) {
                shared_ptr<AccessoryPojo>& accessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
                
                LOGD("AID:%d", accessoryPojo->AID);
                LOGD("iconType:%d", accessoryPojo->IconType);
            }
        }   break;
            
        default: {
            LOGE("對應不到dataType");
        }   break;
    }
}

void Hardward::onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems)
{
    LOGD("onCommandHardwardRecv_UpdateItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_UpdateItems->dataType) {
        case DataType_Accessory: {
            // 針對收到的資料做為更新硬體參考
            vector<AccessoryData*> accessoryList = (vector<AccessoryData*>&) pCommandHardwardRecv_UpdateItems->baseDataList;
            
            for (int i=0 ; i<accessoryList.size() ; i++) {
                LOGD("accessoryId:%d", accessoryList[i]->accessoryId);
                
                for (int j=0 ; j<accessoryList[i]->functionCodeDataList.size() ; j++) {
                    LOGD("functionCode:%s", accessoryList[i]->functionCodeDataList[j]->functonCode.c_str());
                    
                    for (int k=0 ; k<accessoryList[i]->functionCodeDataList[j]->functionCodeValueDataList.size() ; k++) {
                        LOGD("value:%d", accessoryList[i]->functionCodeDataList[j]->functionCodeValueDataList[k]->value);
                    }
                }
            }
        }   break;
            
        default: {
            LOGE("對應不到dataType");
        }   break;
    }
}
