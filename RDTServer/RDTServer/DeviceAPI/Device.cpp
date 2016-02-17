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

void Device::onCommandHardwardRecvProductCode(CommandHardwardRecvProductCode* pCommandHardwardRecvProductCode)
{
    LOGD("onCommandHardwardRecvProductCode");
}

void Device::onCommandHardwardRecvProductName(CommandHardwardRecvProductName* pCommandHardwardRecvProductName)
{
    LOGD("onCommandHardwardRecvProductName");
}

#pragma mark - Normal Method

//void SampoDevice::registerListener(Callback callback)
//{
//    m_callback = callback;
//}
