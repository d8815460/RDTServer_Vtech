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
        m_CommandData.productCode = -1;
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
    m_CommandData.TypeSet.clear();
}
