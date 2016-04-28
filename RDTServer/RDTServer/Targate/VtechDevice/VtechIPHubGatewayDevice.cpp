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
#include "ServicePojo.hpp"
#include "ElementDao.hpp"
#include "ElementNODao.hpp"

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
    
    shared_ptr<vector<shared_ptr<AccessoryPojo>>>& pAccessoryList = pRDTServerCommand->getAccessoryList();
    
    {
        /* 新增一筆Accessory資料 */
        // param1: AID代表accessory id
        // param2: Name 一個名字,用於標示目標類型的一種可視化手段
        // param3: AccSeq The accessory's sequence , the default value is 0.
        // param4: IconType 會面呈現的Icon所代表的型態，如IPHub
        // param5: Connection 連線狀態，
        // param6: IsGateway is gateway or not
        shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo(pRDTServerCommand->getMaxAID(), "PC Home", 1, 1, 1, true));

        // param1: Service 一個元件有單個或多個Element
        shared_ptr<ServicePojo> pService1(new ServicePojo("switchService"));

        // param1: Element 一個元件有單個或多個ElementNO
        shared_ptr<ElementPojo> pElement1(new ElementPojo("switch"));

        // param1: ElementNO 一個元件的編號
        // param2: Value 由一個字串組成，字串的類型可能是數值，字串或整數，也有可能是其他的。它的類型由Metadata決定一個 key 通常會有一個 value
        // param3: NtfyEnable 是否開啟推播
        shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo(0, "轟天1", true));
        shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo(1, "大鑫1", true));

        pAccessoryPojo->pSubPojoList->push_back(pService1);
        pService1->pSubPojoList->push_back(pElement1);
        pElement1->pSubPojoList->push_back(pNO1);
        pElement1->pSubPojoList->push_back(pNO2);

        pAccessoryList->push_back(pAccessoryPojo);
    }
    {
        /* 新增一筆Accessory資料 */
        // param1: AID代表accessory id
        // param2: Name 一個名字,用於標示目標類型的一種可視化手段
        // param3: AccSeq The accessory's sequence , the default value is 0.
        // param4: IconType 會面呈現的Icon所代表的型態，如IPHub
        // param5: Connection 連線狀態，
        // param6: IsGateway is gateway or not
        shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo(pRDTServerCommand->getMaxAID(), "Super", 2, 2, 2, false));

        // param1: Service 一個元件有單個或多個Element
        shared_ptr<ServicePojo> pService1(new ServicePojo("switchService"));

        // param1: Element 一個元件有單個或多個element NO
        shared_ptr<ElementPojo> pElement1(new ElementPojo("switch"));

        // param1: ElementNO 一個元件的編號
        // param2: Value 由一個字串組成，字串的類型可能是數值，字串或整數，也有可能是其他的。它的類型由Metadata決定一個 key 通常會有一個 value
        // param3: NtfyEnable 是否開啟推播
        shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo(0, "轟天2", true));
        shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo(1, "大鑫2", true));

        pAccessoryPojo->pSubPojoList->push_back(pService1);
        pService1->pSubPojoList->push_back(pElement1);
        pElement1->pSubPojoList->push_back(pNO1);
        pElement1->pSubPojoList->push_back(pNO2);
        
        pAccessoryList->push_back(pAccessoryPojo);
    }
    
//    vector<GroupData*>* pGroupList = pRDTServerCommand->getGeoupList();
//    GroupData* pGroupData = new GroupData();
//    pGroupList->push_back(pGroupData);
    
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
            Device* pDevice = Device::getInstance();
            JsonRDTCommand* pJsonRDTCommand = (JsonRDTCommand*) pDevice->getCommand();
            
            /* 新增一筆Accessory資料 */
            // param1: AID代表accessory id
            // param2: Name 一個名字,用於標示目標類型的一種可視化手段
            // param3: AccSeq The accessory's sequence , the default value is 0.
            // param4: IconType 會面呈現的Icon所代表的型態，如IPHub
            // param5: Connection 連線狀態，
            // param6: IsGateway is gateway or not
            shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo(pJsonRDTCommand->getMaxAID(), "PC Home", 1, 1, 1, true));
            
            // param1: Service 一個元件有單個或多個Element
            shared_ptr<ServicePojo> pService1(new ServicePojo("switchService"));
            
            // param1: Element 一個元件有單個或多個ElementNO
            shared_ptr<ElementPojo> pElement1(new ElementPojo("switch"));
            
            // param1: ElementNO 一個元件的編號
            // param2: Value 由一個字串組成，字串的類型可能是數值，字串或整數，也有可能是其他的。它的類型由Metadata決定一個 key 通常會有一個 value
            // param3: NtfyEnable 是否開啟推播
            shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo(0, "轟天1", true));
            shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo(1, "大鑫1", true));
            
            pAccessoryPojo->pSubPojoList->push_back(pService1);
            pService1->pSubPojoList->push_back(pElement1);
            pElement1->pSubPojoList->push_back(pNO1);
            pElement1->pSubPojoList->push_back(pNO2);
            
            pCommandHardwardRecv_CreateItems->pPojoList->push_back(pAccessoryPojo);
            
            // 模擬器儲存
            pJsonRDTCommand->getAccessoryList()->push_back(pAccessoryPojo);
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
            shared_ptr<vector<shared_ptr<Pojo>>> pAccessoryList = (shared_ptr<vector<shared_ptr<Pojo>>>) pCommandHardwardRecv_ReadItems->pPojoList;
            for (shared_ptr<Pojo> pPojo : *pAccessoryList) {
                shared_ptr<AccessoryPojo>& accessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
                
                LOGD("AID:%d", accessoryPojo->AID);
                LOGD("AccIconType:%d", accessoryPojo->AccIconType);
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
            // 針對收到的資料做為參考
            shared_ptr<vector<shared_ptr<Pojo>>> pAccessoryList = (shared_ptr<vector<shared_ptr<Pojo>>>) pCommandHardwardRecv_UpdateItems->pPojoList;
            for (shared_ptr<Pojo> pPojo : *pAccessoryList) {
                shared_ptr<AccessoryPojo>& accessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
                
                LOGD("AID:%d", accessoryPojo->AID);
                LOGD("AccIconType:%d", accessoryPojo->AccIconType);
                // Update資料
            }
        }   break;
        
        default: {
            LOGE("對應不到dataType");
        }   break;
    }
}
