//
//  Device.cpp
//  RDTServer
//
//  Created by jakey on 2015/4/7.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "Device.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <cstring>
#include <time.h>
#include <unistd.h>
#include <algorithm>
#include "Utility.hpp"
#include <wchar.h>
#include "AccessoryTypeEnum.hpp"
#include "BinraryRDTServerConnect.hpp"
#include "BinraryRDTServerCommand.hpp"

using namespace std;

Device::Device()
{
    LOGD("Device");
    
    // Device 註冊推播
//    http://push.iotcplatform.com/tpns?cmd=device&uid=C3KAB97WKTF4AG6GUHC1
    
}

Device::~Device()
{
    delete m_pCommand;
}

void Device::run(const char* parameter)
{
    BinraryRDTServerConnect_ConnectData binraryConnectData;
    binraryConnectData.uid = parameter;
    
    Connect* pConnect = createConnect(&binraryConnectData);
    m_pCommand = createCommand(pConnect);
//    m_pHardward = createHardward();
    
    constructorFinish();
    
    m_pCommand->getConnect()->run();
}

#pragma mark - Device

Connect* Device::createConnect(ConnectData* pConnectData)
{
    return new BinraryRDTServerConnect(pConnectData);
}

Command* Device::createCommand(Connect* pConnect)
{
    return new BinraryRDTServerCommand(this, this, pConnect);
}

#pragma mark - CommandEvent

void Device::onCommandRecvData(CommandRecvData* pCommandRecvData)
{
    LOGD("onCommandRecvData");
}

void Device::onCommandRecvCommand28(FunctionStatus* pFunctionStatus)
{
    LOGD("onCommandRecvCommand28(FunctionStatus* pFunctionStatus)");
}

void Device::onCommandRecvFullCommand28(int channelID, vector<FunctionInfo*>* pDataInfoList)
{
    LOGD("onCommandRecvCommand28(vector<FunctionInfo*>* pDataInfoList)");
    
}

#pragma mark - CommandHardwardEvent

void Device::onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData)
{
    LOGD("onCommandHardwardNotify");
}

void Device::onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData)
{
    LOGD("onCommandHardwardRecvJson");
}

void Device::onCommandHardwardRecv_ProductCode(CommandHardwardRecv_ProductCode* pCommandHardwardRecv_ProductCode)
{
    LOGD("onCommandHardwardRecv_ProductCode");
    
    pCommandHardwardRecv_ProductCode->productCode = -1;
}

void Device::onCommandHardwardRecv_ProductName(CommandHardwardRecv_ProductName* pCommandHardwardRecv_ProductName)
{
    LOGD("onCommandHardwardRecv_ProductName");
    
    pCommandHardwardRecv_ProductName->productName = "Device";
}

void Device::onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems)
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

void Device::onCommandHardwardRecv_DeleteItems(CommandHardwardRecv_DeleteItems* pCommandHardwardRecv_DeleteItems)
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

void Device::onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems)
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

void Device::onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems)
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

#pragma mark - Normal Method

//void SampoDevice::registerListener(Callback callback)
//{
//    m_callback = callback;
//}
