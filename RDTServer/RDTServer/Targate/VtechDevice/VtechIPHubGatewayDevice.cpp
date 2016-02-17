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
#include "JsonRDTServerCommand.hpp"

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
}

VtechIPHubGatewayDevice::~VtechIPHubGatewayDevice()
{
    LOGD("~VtechIPHubGatewayDevice");
}

#pragma mark - Normal Method

void VtechIPHubGatewayDevice::reset()
{
    m_pCommand->reset();
    
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    pFunctionInfo = m_pCommand->createFunctionInfo(Accessory_Type_VtechIPHubGateway);
    
    Command::addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QuerySwitch, 1, 1);
    Command::addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryConnectStatus, 1, 1);
    Command::addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryPowerStatus, 1, 1);
    Command::addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryPairStatus, 1, 1);
    Command::addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryLocationName, u'客', u'廳');
    //    addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryGroupID, 0);
    //    addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryAddGroupID, 0);
    //    addFunctionStatus(pFunctionInfo, VtechIPHubGatewayFunctionCode_QueryLeaveGroupID, 0);
    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'I', u'P', u'H', u'u', u'b');
    
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
    
//    pthread_t pThreadsocketInput;
//    pthread_create(&pThreadsocketInput, NULL, &VtechIPHubGatewayDevice::socketInput, (void*)this);
}

#pragma mark - Device

Command* VtechIPHubGatewayDevice::createCommand(Connect* pConnect)
{
//    return new BinraryRDTServerCommand(this, pConnect);
    return new JsonRDTServerCommand(this, this, pConnect);
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

void VtechIPHubGatewayDevice::onCommandHardwardRecvProductCode(CommandHardwardRecvProductCode* pCommandHardwardRecvProductCode)
{
    LOGD("onCommandHardwardRecvProductCode: productCode:%d", pCommandHardwardRecvProductCode->productCode);
    pCommandHardwardRecvProductCode->productCode = 0xE1;
    LOGD("onCommandHardwardRecvProductCode->productCode:%d", pCommandHardwardRecvProductCode->productCode);
}

void VtechIPHubGatewayDevice::onCommandHardwardRecvProductName(CommandHardwardRecvProductName* pCommandHardwardRecvProductName)
{
    LOGD("onCommandHardwardRecvProductName: productName:%s", pCommandHardwardRecvProductName->productName.c_str());
    pCommandHardwardRecvProductName->productName = "VtechIPHubGatewayDevice";
    LOGD("pCommandHardwardRecvProductName->productName:%s", pCommandHardwardRecvProductName->productName.c_str());
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
