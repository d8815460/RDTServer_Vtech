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

Device* Device::m_pInstance = NULL;

Device::Device()
{
    LOGD("Device");
    
    if (m_pInstance != NULL) {
        throw Exception(__PRETTY_FUNCTION__, __LINE__, -1, "Device two constrator error");
    }
    else {
        m_pInstance = this;
    }
    
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
    
    m_pHardward = createHardward();
    Connect* pConnect = createConnect(&binraryConnectData);
    m_pCommand = createCommand(pConnect, m_pHardward);
    
    constructorFinish();
    m_pCommand->getConnect()->run();
}

#pragma mark - Device

Hardward* Device::createHardward()
{
    return new Hardward();
}

Connect* Device::createConnect(ConnectData* pConnectData)
{
    return new BinraryRDTServerConnect(pConnectData);
}

Command* Device::createCommand(Connect* pConnect, CommandHardwardEvent* pCommandHardwardEvent)
{
    return new BinraryRDTServerCommand(this, pCommandHardwardEvent, pConnect);
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

#pragma mark - Normal Method

//void SampoDevice::registerListener(Callback callback)
//{
//    m_callback = callback;
//}
