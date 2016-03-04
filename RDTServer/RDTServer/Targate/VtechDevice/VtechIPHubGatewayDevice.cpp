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
