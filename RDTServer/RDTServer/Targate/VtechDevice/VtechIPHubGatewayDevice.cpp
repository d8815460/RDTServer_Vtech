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
    pAccessory->addFunctionCodeData("a", 1);
    pAccessory->addFunctionCodeData("b", 2);
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

Command* VtechIPHubGatewayDevice::createCommand(Connect* pConnect)
{
//    return new BinraryRDTServerCommand(this, pConnect);
    return new VtechJsonRDTServerCommand(this, this, pConnect);
}

#pragma mark - CommandHardwardEvent

void VtechIPHubGatewayDevice::onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData)
{
    LOGD("onCommandHardwardNotify");

//    JsonRDTServerHardward_HardwardNotifyData* jsonRDTServerHardwardHardwardNotifyData = (JsonRDTServerHardward_HardwardNotifyData*) pHardwardRecvData;
//    std::string jsonString = jsonRDTServerHardwardHardwardNotifyData->pOutJsonObject->toStyledString();
//    LOGD("jsonString:%s", jsonString.c_str());
}

void VtechIPHubGatewayDevice::onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData)
{
	LOGD("onCommandHardwardRecvJson");

	 std::string jsonString = pCommandHardwardRecvJsonData->pJsonObject->toStyledString();
	 LOGD("jsonString:%s", jsonString.c_str());
}

void VtechIPHubGatewayDevice::onCommandHardwardRecv_ProductCode(CommandHardwardRecv_ProductCode* pCommandHardwardRecv_ProductCode)
{
    LOGD("onCommandHardwardRecv_ProductCode");
    
    pCommandHardwardRecv_ProductCode->productCode = 0xE1;
}

void VtechIPHubGatewayDevice::onCommandHardwardRecv_ProductName(CommandHardwardRecv_ProductName* pCommandHardwardRecv_ProductName)
{
    LOGD("onCommandHardwardRecv_ProductName");
    
    pCommandHardwardRecv_ProductName->productName = "VtechIPHubGatewayDevice";
}

void VtechIPHubGatewayDevice::onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems)
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

void VtechIPHubGatewayDevice::onCommandHardwardRecv_DeleteItems(CommandHardwardRecv_DeleteItems* pCommandHardwardRecv_DeleteItems)
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

void VtechIPHubGatewayDevice::onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems)
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

void VtechIPHubGatewayDevice::onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems)
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
    
//    switch (pBasicData->stage) {
//        case 5: {
//            switch (pBasicData->operators) {
//                case 28: {
//                    int recvIndex = 10 - 1;
//                    
//                    UBYTE totalCount = buffer[recvIndex++];
//                    UBYTE countIndex = buffer[recvIndex++];
//                    UBYTE amount = buffer[recvIndex++];
//                    LOGD("totalCount:%d", totalCount);
//                    LOGD("countIndex:%d", countIndex);
//                    LOGD("amount:%d", amount);
//                    
//                    // 傳送的資料Buffer
//                    int sendIndex = 0;
//                    BYTE sendDataBuffer[MAX_BUFFER_SIZE];
//                    
//                    UBYTE sendTotalCount = 1;
//                    sendDataBuffer[sendIndex++] = sendTotalCount;
//                    
//                    UBYTE sendCountIndex = 0;
//                    sendDataBuffer[sendIndex++] = sendCountIndex;
//                    
//                    UBYTE sendAmount = 0;
//                    sendDataBuffer[sendIndex++] = sendAmount;
//                    
//                    vector<FunctionInfo*> dataInfoList;
//                    
//                    // 取得接收的資料
//                    for (int x=0 ; x<amount ; x++) {
//                        UBYTE aid = buffer[recvIndex++];
//                        unsigned int type = (unsigned int) Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 4);
//                        UBYTE functionCode = buffer[recvIndex++];
//                        UBYTE functionCodeAmount = buffer[recvIndex++];
//                        
//                        LOGD("aid:%d", aid);
//                        LOGD("type:%d", type);
//                        LOGD("functionCode:%d", functionCode);
//                        LOGD("functionCodeAmount:%d", functionCodeAmount);
//                        
//                        // amount
//                        sendDataBuffer[3 - 1] = ++sendAmount;
//                        
//                        sendDataBuffer[sendIndex++] = 0;
//                        setValue(sendDataBuffer, &sendIndex, Accessory_Type_VtechIPHubGateway);
//                        sendDataBuffer[sendIndex++] = 200;
//                        sendDataBuffer[sendIndex++] = 1;
//                        setValue(sendDataBuffer, &sendIndex, 1);
//                        
//                        // 是否要重設
//                        if (functionCode == 200) {
//                            reset();
//                            
//                            JsonRDTServerCommand_ParseSendData parseSendData;
//                            parseSendData.channelID = channelID;
//                            parseSendData.pData = sendDataBuffer;
//                            parseSendData.dataLength = sendIndex;
//                            ((JsonRDTServerCommand*)m_pCommand)->parseSendData(&parseSendData);
//                        }
//                    }
//                    
//                }   break;
//                    
//            }   break;
//            
//        default: {
//            LOGE("can not find match stage");
//            break;
//        }
//        }
//    }
}
