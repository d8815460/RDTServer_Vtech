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
#include "AccessoryDao.hpp"

#include "BinraryRDTServerCommand.hpp"
#include "VtechJsonRDTServerCommand.hpp"

// Devices
#include "VtechGarageDoorDevice.hpp"
#include "VtechOpenClosedDevice.hpp"
#include "VtechMotionSensorDevice.hpp"
#include "VtechLightBulbDevice.hpp"
#include "VtechWallSwitchDevice.hpp"
#include "VtechVirtualGroupDevice.hpp"

// Database
#include "AccessoryTypeEnum.hpp"
#include "AccessoryDao.hpp"
#include "ElementDao.hpp"
#include "ElementNoDao.hpp"

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
    return new VtechIPHubGatewayHardward();
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

VtechIPHubGatewayHardward::VtechIPHubGatewayHardward()
{
    LOGD("VtechIPHubGatewayHardward");
}

void VtechIPHubGatewayHardward::onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems)
{
    LOGD("onCommandHardwardRecv_CreateItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_CreateItems->dataType) {
        case DataType_Accessory: {
            /* 新增一筆資料 */
            
            // 建立accessoryPojo
            shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo);
            pAccessoryPojo->AID = 10;
            pAccessoryPojo->Name = "PIR Sensor";
            pAccessoryPojo->IconType = 1;
            pAccessoryPojo->Connection = 1;
            pAccessoryPojo->IsGateway = true;
            
            // 建立ElementPojo
            shared_ptr<ElementPojo> pElement1(new ElementPojo);
            pElement1->Element = "switch";
            
            // 建立ElementNOPojo
            shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo);
            pNO1->ElementNO = 0;
            pNO1->Value = "1";
            pNO1->NtfyEnable = true;
            
            // 建立ElementNOPojo
            shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo);
            pNO2->ElementNO = 1;
            pNO2->Value = "100";
            pNO2->NtfyEnable = true;
            
            // 放入相關階層
            pAccessoryPojo->pSubPojoList->push_back(pElement1);
            pElement1->pSubPojoList->push_back(pNO1);
            pElement1->pSubPojoList->push_back(pNO2);
            
            // 將accessoryPojo放入pojoList
            pCommandHardwardRecv_CreateItems->pojoList->push_back(pAccessoryPojo);
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
    
    // 通知update
    FunctionCodeValueData* pFunctionCodeValueData = new FunctionCodeValueData();
    pFunctionCodeValueData->value = 1;
    
    FunctionCodeData* pFunctionCodeData = new FunctionCodeData();
    pFunctionCodeData->functonCode = 1;
    pFunctionCodeData->functionCodeValueDataList.push_back(pFunctionCodeValueData);

    AccessoryData* pAccessoryData = new AccessoryData();
    pAccessoryData->accessoryId = 1;
    pAccessoryData->functionCodeDataList.push_back(pFunctionCodeData);
    
    CommandHardwardSend_UpdateItems sendUpdateItems;
    sendUpdateItems.baseDataList.push_back(pAccessoryData);
    sendUpdateItems.dataType = DataType_Accessory;
    sendUpdateItems.errorCode = 0;
    
    Device* pDevice = Device::getInstance();
    JsonRDTCommand* jsonRDTCommand = (JsonRDTCommand*) pDevice->getCommand();
    jsonRDTCommand->commandHardwardSend_UpdateItems(&sendUpdateItems);
    
    // 通知update
//    LOGD("通知update");
//    CommandHardwardSend_UpdateItems sendUpdateItems;
//    sendUpdateItems.baseDataList = pUpdateItems->baseDataList;
//    sendUpdateItems.dataType = pUpdateItems->dataType;
//    sendUpdateItems.errorCode = pUpdateItems->errorCode;
//    
//    Device* pDevice = Device::getInstance();
//    JsonRDTCommand* jsonRDTCommand = (JsonRDTCommand*) pDevice->getCommand();
//    jsonRDTCommand->commandHardwardSend_UpdateItems(&sendUpdateItems);
}
