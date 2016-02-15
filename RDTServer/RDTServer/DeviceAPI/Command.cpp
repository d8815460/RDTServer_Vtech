//
//  Command.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/12.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "Command.hpp"
#include <cstring>
#include <unistd.h>
#include "Utility.hpp"

Command::Command(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData) : m_pCommandEvent(pCommandEvent), m_pCommandHardwardEvent(pCommandHardwardEvent), m_pConnect(pConnect)
{
    LOGD("Command");
        
    if (pCommandData != NULL) {
        memcpy(&m_CommandData, pCommandData, sizeof(CommandData));
    }
    else {
        m_CommandData.productName = "Device";
        
        // 必須設定ConnectEvent
        m_pConnect->setConnectEvent(this);
        
        m_CommandData.nMaxAID = 0;
        strcpy(m_CommandData.pPassword, "1");
        
        WifiInfo* pWifiInfo = new WifiInfo;
        
        // App Test Mode會以這個為傳送標的
        strcpy(pWifiInfo->ssid, "SimSSID1");
        strcpy(pWifiInfo->security, "password");
        // 信號強度(百分比)
        pWifiInfo->signal = 50;
        m_CommandData.WifinInfo.push_back(pWifiInfo);
        
        // 設定目前的ssid, security
        strcpy(m_CommandData.pSSID, pWifiInfo->ssid);
        strcpy(m_CommandData.pSSIDPassword, pWifiInfo->security);
        
        pWifiInfo = new WifiInfo;
        strcpy(pWifiInfo->ssid, "SimSSID2");
        strcpy(pWifiInfo->security, "password");
        // 信號強度(百分比)
        pWifiInfo->signal = 25;
        m_CommandData.WifinInfo.push_back(pWifiInfo);
        
        pWifiInfo = new WifiInfo;
        strcpy(pWifiInfo->ssid, "jakey's Mac mini");
        strcpy(pWifiInfo->security, "1");
        pWifiInfo->signal = 75;
        m_CommandData.WifinInfo.push_back(pWifiInfo);
        
        m_CommandData.version1 = 1;
        m_CommandData.version2 = 1;
        m_CommandData.version3 = 0;
    }
    
    init();
}

Command::~Command()
{
    for (int i=0 ; i<m_CommandData.WifinInfo.size() ; i++) {
        delete m_CommandData.WifinInfo[i];
    }
    
    for (vector<FunctionInfo*>::iterator it = m_CommandData.DataInfoList.end() ; it != m_CommandData.DataInfoList.begin() ; it--) {
        removeFunctionInfo(it);
    }
    
    delete m_pConnect;
}

Connect* Command::getConnect()
{
    return m_pConnect;
}

void Command::init()
{
    LOGD("init");
}

#pragma maek - Command

void Command::reset()
{
    m_CommandData.nMaxAID = 0;
    m_CommandData.DataInfoList.clear();
    m_CommandData.TypeSet.clear();
}

#pragma mark - Function Info

FunctionInfo* Command::createFunctionInfo(unsigned int type)
{
    m_CommandData.TypeSet.insert(type);
    
    FunctionInfo* pFunctionInfo = new FunctionInfo();
    pFunctionInfo->aid = m_CommandData.nMaxAID++;
    pFunctionInfo->type = type;
    m_CommandData.DataInfoList.push_back(pFunctionInfo);
    
    return pFunctionInfo;
}

void Command::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void Command::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode1);
    addFunctionCode(pFunctionStatus, transferCode2);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void Command::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode1);
    addFunctionCode(pFunctionStatus, transferCode2);
    addFunctionCode(pFunctionStatus, transferCode3);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void Command::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3, unsigned short transferCode4)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode1);
    addFunctionCode(pFunctionStatus, transferCode2);
    addFunctionCode(pFunctionStatus, transferCode3);
    addFunctionCode(pFunctionStatus, transferCode4);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void Command::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3, unsigned short transferCode4, unsigned short transferCode5)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode1);
    addFunctionCode(pFunctionStatus, transferCode2);
    addFunctionCode(pFunctionStatus, transferCode3);
    addFunctionCode(pFunctionStatus, transferCode4);
    addFunctionCode(pFunctionStatus, transferCode5);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void Command::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3, unsigned short transferCode4, unsigned short transferCode5, unsigned short transferCode6)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode1);
    addFunctionCode(pFunctionStatus, transferCode2);
    addFunctionCode(pFunctionStatus, transferCode3);
    addFunctionCode(pFunctionStatus, transferCode4);
    addFunctionCode(pFunctionStatus, transferCode5);
    addFunctionCode(pFunctionStatus, transferCode6);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void Command::addFunctionStatusWithArray(FunctionInfo* pFunctionInfo, UBYTE functionCode, vector<unsigned short>* pTransferCodeArray)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    
    for (int i=0 ; i<pTransferCodeArray->size(); i++) {
        addFunctionCode(pFunctionStatus, (*pTransferCodeArray)[i]);
    }
    
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void Command::addFunctionCode(FunctionStatus* pFunctionStatus, unsigned short transferCode)
{
    FunctionCode* pFunctionCode = new FunctionCode();
    pFunctionCode->transferCode = transferCode;
    pFunctionStatus->functionCodeList.push_back(pFunctionCode);
}

void Command::removeFunctionInfo(vector<FunctionInfo*>::iterator it)
{
    delete (*it);
    m_CommandData.DataInfoList.erase(it);
}
