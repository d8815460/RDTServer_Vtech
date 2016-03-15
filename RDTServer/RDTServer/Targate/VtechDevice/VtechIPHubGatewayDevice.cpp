//
//  VtechIPHubDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/11/18.
//  Copyright © 2015年 jakey. All rights reserved.
//

#include "VtechIPHubGatewayDevice.hpp"
#include <map>
#include <iostream>
#include <cstring>
//#include <unistd.h>
#include "Common.hpp"
#include "Utility.hpp"
#include "AccessoryTypeEnum.hpp"
#include "VtechIPHubGatewayEnum.hpp"

#include "BinraryRDTServerCommand.hpp"
#include "VtechJsonRDTServerCommand.hpp"

// Devices
#include "VtechGarageDoorDevice.hpp"
#include "VtechOpenClosedDevice.hpp"
#include "VtechMotionSensorDevice.hpp"
#include "VtechLightBulbDevice.hpp"
#include "VtechWallSwitchDevice.hpp"
#include "VtechVirtualGroupDevice.hpp"

VtechIPHubGatewayDevice::VtechIPHubGatewayDevice()
{
    LOGD("VtechIPHubGatewayDevice");
    
//    m_isSimulator = false;
}

VtechIPHubGatewayDevice::~VtechIPHubGatewayDevice()
{
    LOGD("~VtechIPHubGatewayDevice");
}

#pragma mark - Normal Method

void VtechIPHubGatewayDevice::reset()
{
    m_pCommand->reset();
    
    /* Function Status 1 */
    VtechJsonRDTServerCommand* pRDTServerCommand = (VtechJsonRDTServerCommand*) m_pCommand;
    
    vector<AccessoryData*>* pAccessoryList = pRDTServerCommand->getAccessoryList();
    AccessoryData* pAccessory = new AccessoryData();
    pAccessory->accessoryId = 1;
    pAccessory->accessoryType = 1;
    pAccessory->addFunctionCodeData("switch", 0);
//    pAccessory->addFunctionCodeData("color", 255, 255, 255);
    pAccessoryList->push_back(pAccessory);
    
    vector<GroupData*>* pGroupList = pRDTServerCommand->getGeoupList();
    GroupData* pGroupData = new GroupData();
    pGroupList->push_back(pGroupData);
    
//    pAccessories->addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryConnectStatus, 1, 1);
//    pAccessories->addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryPowerStatus, 1, 1);
//    pAccessories->addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryPairStatus, 1, 1);
//    pAccessories->addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryLocationName, u'客', u'廳');
    //    addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryGroupID, 0);
    //    addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryAddGroupID, 0);
    //    addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryLeaveGroupID, 0);
//    pAccessories->addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'I', u'P', u'H', u'u', u'b');
    
    // Sensors
    VtechLightBulbDevice::generatorDataInfoList(m_pCommand);
    VtechLightBulbDevice::generatorDataInfoList(m_pCommand);
    VtechLightBulbDevice::generatorDataInfoList(m_pCommand);
    VtechLightBulbDevice::generatorDataInfoList(m_pCommand);
    
    VtechMotionSensorDevice::generatorDataInfoList(m_pCommand);
    VtechOpenClosedDevice::generatorDataInfoList(m_pCommand);
    VtechWallSwitchDevice::generatorDataInfoList(m_pCommand);
    VtechGarageDoorDevice::generatorDataInfoList(m_pCommand);
    
    //    VtechVirtualGroupDevice::generatorDataInfoList(m_nMaxAID++, &m_DataInfoList, &m_TypeSet);
}

#pragma mark - Device

Hardward* VtechIPHubGatewayDevice::createHardward()
{
    return new VtechIPHubGatewayHardward((JsonRDTCommand*) m_pCommand);
}

Command* VtechIPHubGatewayDevice::createCommand(Connect* pConnect, CommandHardwardEvent* pCommandHardwardEvent)
{
    return new VtechJsonRDTServerCommand(this, pCommandHardwardEvent, pConnect);
}

#pragma mark - CommandEvent

unsigned short VtechIPHubGatewayDevice::onCommandGetProductCode()
{
    return 0xE1;
}

const char* VtechIPHubGatewayDevice::onCommandGetProductName()
{
    return "VtechIPHubGatewayDevice";
}

void VtechIPHubGatewayDevice::onCommandRecvCommand28(FunctionStatus* pFunctionStatus)
{
    LOGD("onCommandRecvCommand28");
}

void VtechIPHubGatewayDevice::onCommandRecvFullCommand28(int channelID, vector<FunctionInfo*>* pDataInfoList)
{
    LOGD("onCommandRecvFullCommand28");
}

void VtechIPHubGatewayDevice::onCommandRecvData(CommandRecvData* pCommandRecvData)
{
    LOGD("onCommandRecvData");
}

#pragma mark - VtechIPHubGatewayHardward::VtechIPHubGatewayHardward

VtechIPHubGatewayHardward::VtechIPHubGatewayHardward(JsonRDTCommand* pJsonRDTCommand)
{
    m_pJsonRDTCommand = pJsonRDTCommand;
}

void VtechIPHubGatewayHardward::onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems)
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
            
        default: {
            LOGE("對應不到dataType");
        }   break;
    }
    
}

void VtechIPHubGatewayHardward::onCommandHardwardRecv_DeleteItems(CommandHardwardRecv_DeleteItems* pCommandHardwardRecv_DeleteItems)
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

void VtechIPHubGatewayHardward::onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems)
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
        }   break;
            
        default: {
            LOGE("對應不到dataType");
        }   break;
    }
}

void VtechIPHubGatewayHardward::onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems)
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
    
//    // 通知update
//    CommandHardwardSend_UpdateItems sendUpdateItems;
//    sendUpdateItems.baseDataList = pCommandHardwardRecv_UpdateItems->baseDataList;
//    sendUpdateItems.dataType = pCommandHardwardRecv_UpdateItems->dataType;
//    sendUpdateItems.errorCode = pCommandHardwardRecv_UpdateItems->errorCode;
//    m_pJsonRDTCommand->commandHardwardSend_UpdateItems(&sendUpdateItems);
}
