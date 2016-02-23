//
//  BinraryRDTServerCommand.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/12.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "BinraryRDTServerCommand.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "Common.hpp"
#include "Utility.hpp"
#include "IOTCAPIs.h"
#include "RDTAPIs.h"
#include "BinraryRDTServerConnect.hpp"
#include "AccessoryTypeEnum.hpp"

BinraryRDTServerCommand::BinraryRDTServerCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData) : BinraryRDTCommand(pCommandEvent, pCommandHardwardEvent, pConnect, pCommandData)
{
    LOGD("BinraryRDTServerCommand");
    
    pthread_t pThreadInput;
    pthread_create(&pThreadInput, NULL, &BinraryRDTServerCommand::threadInput, (void*)this);
}

BinraryRDTServerCommand::~BinraryRDTServerCommand()
{
    LOGD("~BinraryRDTServerCommand");
}

#pragma mark - ConnectEvent

void BinraryRDTServerCommand::onConnectRecvData(ConnectRecvData* pConnectRecvData)
{
    BinraryRDTServerConnect_ConnectRecvData* pBinraryConnectRecvData = (BinraryRDTServerConnect_ConnectRecvData*) pConnectRecvData;
    BinraryRDTServerCommand_ParseRecvData* pBinraryParseRecvData = (BinraryRDTServerCommand_ParseRecvData*) pBinraryConnectRecvData;
    
    parseRecvData(pBinraryParseRecvData);
}

#pragma mark - Thread

void* BinraryRDTServerCommand::threadInput(void *arg)
{
    BinraryRDTServerCommand* pBinraryRDTServerCommand = (BinraryRDTServerCommand*) arg;
    
    char pInput;
    while(true) {
        LOGD("請輸入一個字元:");
        cin >> pInput;
        LOGD("input:%c", pInput);
        
        LOGD("===================================================================================================================================");
        //        for (map<int, int>::iterator it=g_sidChannelIDMap.begin() ; it != g_sidChannelIDMap.end() ; it++) {
        //            sid = it->first;
        //            channelID = it->second;
        //
        //            LOGD("sid:%d", sid);
        //            LOGD("channelID:%d", channelID);
        //        }
        
        int count = 0;
        for (set<int>::iterator it = pBinraryRDTServerCommand->m_nChannelIDList.begin() ; it!=pBinraryRDTServerCommand->m_nChannelIDList.end() ; it++) {
            LOGD("m_nChannelIDList[%d]:%d", count++, *it);
        }
        LOGD("===================================================================================================================================");
        
        FunctionInfo functionInfo;
        functionInfo.isRuningStack = true;
        functionInfo.aid = 8;
        functionInfo.type = Accessory_Type_VtechGarageDoor;
        
        FunctionStatus functionStatus;
        functionStatus.isRuningStack = true;
        functionStatus.functionCode = 1;
        functionInfo.functionStatusList.push_back(&functionStatus);
        
        static bool switchOn = true;
        switchOn = !switchOn;
        
        FunctionCode functionCode;
        functionCode.transferCode = switchOn;
        functionStatus.functionCodeList.push_back(&functionCode);
        
        vector<FunctionInfo*> functionInfoList;
        functionInfoList.push_back(&functionInfo);
        pBinraryRDTServerCommand->sendReportWithCommand30(0, &functionInfoList);
        
        //        int count = 0;
        //        for (set<int>::iterator it = pBinraryRDTServerConnect->m_nChannelIDList.begin() ; it!=pBinraryRDTServerConnect->m_nChannelIDList.end() ; it++) {
        //            LOGD("m_nChannelIDList[%d]:%d", count++, *it);
        //
        //            struct st_SInfo sInfo;
        //            IOTC_Session_Check(*it, &sInfo);
        //
        //            LOGD("sInfo:%d", sInfo.);
        //        }
        //
        //        sleep(5);
    }
    
    return NULL;
}

#pragma mark - Command

void BinraryRDTServerCommand::parseSendData(ParseSendData* pParseSendData)
{
    BinraryRDTServerCommand_ParseSendData* pBinraryCommandRecvData = (BinraryRDTServerCommand_ParseSendData*) pParseSendData;
    
    int channelID = pBinraryCommandRecvData->channelID;
    BYTE stage = pBinraryCommandRecvData->stage;
    unsigned short operators = pBinraryCommandRecvData->operators;
    BYTE* data = pBinraryCommandRecvData->pData;
    int dataLength = pBinraryCommandRecvData->dataLength;
    
    /* prepare send data */
    int index = 0;
    BYTE buffer[MAX_BUFFER_SIZE];
    memset(buffer, 0, MAX_BUFFER_SIZE);
    buffer[index++] = 'I';
    buffer[index++] = 'O';
    buffer[index++] = 'T';
    buffer[index++] = 'C';
    
    // Skip Length
    if (operators == 29 ||
       (m_CommandData.version1 == 1 && m_CommandData.version2 == 0 && m_CommandData.version3 == 0))
    {
        // 版本 1.0.0
        index++;
    }
    else {
        // 版本 1.1.0 以上
        index += 2;
    }
    
    // Stage
    buffer[index++] = stage;
    
    /* Operator */
    unsigned short* pOperator = (unsigned short*)&buffer[index];
    *pOperator = operators;
    index += 2;
    
    // payload data
    memcpy(buffer + index, data, dataLength);
    index += dataLength;
    
    buffer[index++] = 'G';
    buffer[index++] = 'C';
    
    // Length
    if (operators == 29 ||
       (m_CommandData.version1 == 1 && m_CommandData.version2 == 0 && m_CommandData.version3 == 0))
    {
        buffer[5 - 1] = index - 4 - 2 - 1;
        LOGD("length:%d", buffer[5 - 1]);
    }
    else {
        unsigned short* pLength = (unsigned short*)&buffer[5 - 1];
        *pLength = index - 4 - 2 - 2;
        LOGD("length:%d", *pLength);
    }
    
    LOGD("index:%d", index);
    
    LOGD("Send data");
    Utility::printData(__PRETTY_FUNCTION__, __LINE__, buffer, index);
    int ret = RDT_Write(channelID, (const char*)buffer, index);
    if (ret < 0) {
        LOGE("RDT_Write failed");
    }
}

void BinraryRDTServerCommand::recvData(int channelID, BYTE* buffer, int totalLength)
{
    LOGD("recvData");
    
    Utility::printData(__PRETTY_FUNCTION__, __LINE__, buffer, totalLength);
    
    // 基本驗證
    if (isBasicVerificationPass(buffer, totalLength)) {
        /* Verification recv data */
        unsigned short operators;
        UBYTE stage;
        
        if (isLength2Byte(buffer, totalLength) == true) {
            stage = buffer[7 - 1];
            operators = buffer[8 - 1];
        }
        else {
            stage = buffer[6 - 1];
            operators = buffer[7 - 1];
        }
        
        LOGD("srage:%d", stage);
        LOGD("operator:%d", operators);
        
        switch (stage) {
            case 3: {
                // 詢問device類別(classCode)
                if (operators == 2) {
                    unsigned short classCode = m_pCommandEvent->onCommandGetProductCode();
                    LOGD("classCode:%d", classCode);
                    
                    BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                    binraryParseSendData.channelID = channelID;
                    binraryParseSendData.stage = stage;
                    binraryParseSendData.operators = operators;
                    binraryParseSendData.pData = (BYTE*) &classCode;
                    binraryParseSendData.dataLength = sizeof(unsigned short);
                    parseSendData(&binraryParseSendData);
                    return;
                }
            }
                
            case 5: {
                switch (operators) {
                    // 3 Report Device Product Name
                    case 3: {
                        const char* productName = m_pCommandEvent->onCommandGetProductName();
                        LOGD("productName:%s", productName);
                        
                        int index = 0;
                        BYTE buffer[MAX_BUFFER_SIZE];
                        memset(buffer, 0, MAX_BUFFER_SIZE);
                        buffer[index++] = strlen(productName);
                        
                        strcpy((char*)buffer, productName);
                        index += strlen(productName) + 1;
                        
                        //    wstring str4 = L"你好么？";
                        //    wstring str44(str4.rbegin(), str4.rend());
                        //    LOGD("str4:%S", str4);
                        
                        //                        wchar_t a[] = L"杯";
                        //                        LOGD("a = %ls", a);
                        //                        LOGD("sizeof:%lu", sizeof(wchar_t));
                        //                        LOGD("wstrlen:%lu", wcslen(a));
                        //
                        //                        char szTime[100];
                        //                        wchar_t szValidDate[] = L"Hello World.";
                        //                        wcstombs(szTime, szValidDate, wcslen(szValidDate));
                        //                        send(channelID, basicData.stage, basicData.operators, (unsigned char*) szTime, (int) (wcslen(a) * 4));
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = buffer;
                        binraryParseSendData.dataLength = index;
                        parseSendData(&binraryParseSendData);
                        return;
                    }
                        
                    // 7 Client Authentication
                    case 7: {
                        char pPassword[32];
                        if (isLength2Byte(buffer, totalLength) == true) {
                            memcpy(pPassword, &buffer[10 - 1], sizeof(pPassword));
                        }
                        else {
                            memcpy(pPassword, &buffer[9 - 1], sizeof(pPassword));
                        }
                        LOGD("Authentication Password:%s", pPassword);
                        
                        bool isAuthentication = false;
                        if (strcmp(m_CommandData.pPassword, pPassword) == 0) {
                            isAuthentication = true;
                        }
                        
                        char sendBuffer[1];
                        sendBuffer[0] = isAuthentication;
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = (BYTE*) sendBuffer;
                        binraryParseSendData.dataLength = sizeof(sendBuffer);
                        parseSendData(&binraryParseSendData);
                        return;
                    }
                        
                    // 8 Change password
                    case 8: {
                        int index = 0;
                        if (isLength2Byte(buffer, totalLength) == true) {
                            index = 10 - 1;
                        }
                        else {
                            index = 9 - 1;
                        }
                        
                        char pOldPassword[32];
                        memcpy(pOldPassword, &buffer[index], sizeof(pOldPassword));
                        index += 32;
                        LOGD("pOldPassword:%s", pOldPassword);
                        
                        char pNewPassword[32];
                        memcpy(pNewPassword, &buffer[index], sizeof(pNewPassword));
                        index += 32;
                        LOGD("pNewPassword:%s", pNewPassword);
                        
                        bool isResponse = false;
                        if (strcmp(m_CommandData.pPassword, pOldPassword) == 0) {
                            memcpy(m_CommandData.pPassword, pNewPassword, sizeof(pOldPassword));
                            isResponse = true;
                        }
                        
                        // 上報
                        sendReportAllWithCommand33(channelID, operators, isResponse);
                        
                        char sendBuffer[1];
                        sendBuffer[0] = isResponse;
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = (BYTE*) sendBuffer;
                        binraryParseSendData.dataLength = sizeof(sendBuffer);
                        parseSendData(&binraryParseSendData);
                        return;
                    }
                        
                    // 11 Get Wifi List
                    case 11: {
                        // 收到sessionId
                        unsigned short sessionId = 0;
                        if (isLength2Byte(buffer, totalLength) == true) {
                            sessionId = buffer[10 - 1];
                        }
                        else {
                            sessionId = buffer[9 - 1];
                        }
                        
                        int count = (int) m_CommandData.WifinInfo.size();
                        int respTotal = count;
                        int respIndex = 0;
                        do {
                            // 傳送資料
                            UBYTE amount = 0;
                            int index = 0;
                            BYTE data[MAX_BUFFER_SIZE];
                            memset(data, 0, MAX_BUFFER_SIZE);
                            
                            data[index] = sessionId;
                            index += 2;
                            
                            data[index++] = respIndex;
                            data[index++] = respTotal;
                            
                            // 一次可以傳送的數量amount
                            int total = 0;
                            while ((total + sizeof(WifiInfo)) <= 255) {
                                amount++;
                                total += sizeof(WifiInfo);
                            }
                            data[index++] = amount;
                            
                            for (int i=0 ; i<amount ; i++) {
                                memcpy(&data[index], (const char*) &m_CommandData.WifinInfo[respIndex], sizeof(WifiInfo));
                                LOGD("WifiInfo:%ld", sizeof(WifiInfo));
                                index += sizeof(WifiInfo);
                                
                                //                                strcpy(data + index, (const char*) m_pWifinInfo[respIndex].ssid);
                            }
                            
                            Utility::printData(__PRETTY_FUNCTION__, __LINE__,data, index);
                            //                        LOGD("index:%d", index);
                            BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                            binraryParseSendData.channelID = channelID;
                            binraryParseSendData.stage = stage;
                            binraryParseSendData.operators = operators;
                            binraryParseSendData.pData = data;
                            binraryParseSendData.dataLength = index;
                            parseSendData(&binraryParseSendData);
                            
                            respIndex++;
                            count--;
                            
                            sleep(1);
                        } while (count > 0);
                        
                        return;
                    }
                        
                    // 15 New Set Wifi Parameter
                    case 15: {
                        char pSSID[128];
                        char pPassword[32];
                        
                        if (isLength2Byte(buffer, totalLength) == true) {
                            memcpy(pSSID, &buffer[10 - 1], sizeof(pSSID));
                            memcpy(pPassword, &buffer[138 - 1], sizeof(pPassword));
                        }
                        else {
                            memcpy(pSSID, &buffer[9 - 1], sizeof(pSSID));
                            memcpy(pPassword, &buffer[137 - 1], sizeof(pPassword));
                        }
                        
                        LOGD("SSID:%s", pSSID);
                        LOGD("Password:%s", pPassword);
                        
                        strcpy(m_CommandData.pSSID, pSSID);
                        strcpy(m_CommandData.pSSIDPassword, pPassword);
                        
                        char sendBuffer[1];
                        sendBuffer[0] = true;
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = (BYTE*) sendBuffer;
                        binraryParseSendData.dataLength = sizeof(sendBuffer);
                        parseSendData(&binraryParseSendData);
                        return;
                    }
                        
                    // 16 Get Wifi Parameter
                    case 16: {
                        int index = 0;
                        BYTE data[MAX_BUFFER_SIZE];
                        memset(data, 0, MAX_BUFFER_SIZE);
                        
                        // ssid
                        memcpy(&data[index], m_CommandData.pSSID, sizeof(m_CommandData.pSSID));
                        index += 128;
                        
                        // mac addr
                        index += 18;
                        
                        // Security Mode
                        data[index++] = 3;  // WPA2PSK
                        
                        // Encryption Type
                        data[index++] = 2;  // AES
                        
                        // Pass Phrase
                        memcpy(&data[index], m_CommandData.pSSIDPassword, sizeof(m_CommandData.pSSIDPassword));
                        index += 32;
                        
                        LOGD("m_pSSID:%s", m_CommandData.pSSID);
                        LOGD("m_pSSIDPassword:%s", m_CommandData.pSSIDPassword);
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = data;
                        binraryParseSendData.dataLength = index;
                        parseSendData(&binraryParseSendData);
                        return;
                    }
                        
                    // 17 Get All Type
                    case 17: {
                        int index = 0;
                        BYTE data[MAX_BUFFER_SIZE];
                        
                        // Amount
                        data[index++] = m_CommandData.TypeSet.size();
                        for (set<unsigned int>::iterator it = m_CommandData.TypeSet.begin() ; it != m_CommandData.TypeSet.end() ; it++) {
                            unsigned int type = *(it);
                            setValue(data, &index, type);
                        }
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = data;
                        binraryParseSendData.dataLength = index;
                        parseSendData(&binraryParseSendData);
                    }   return;
                        
                    // 24 Get Accessory Items
                    case 24: {
                        int index = 0;
                        if (isLength2Byte(buffer, totalLength) == true) {
                            index = 10 - 1;
                        }
                        else {
                            index = 9 - 1;
                        }
                        
                        unsigned int type = (unsigned int) Utility::bytes2UnsignedLongWithBeginData(buffer, &index, 4);
                        LOGD("type:%d", type);
                        
                        int sendIndex = 0;
                        BYTE data[MAX_BUFFER_SIZE];
                        
                        UBYTE totalCount = 1;
                        data[sendIndex++] = totalCount;
                        
                        UBYTE countIndex = 0;
                        data[sendIndex++] = countIndex;
                        
                        UBYTE amount = 0; // m_dataInfoList.size();
                        data[3 - 1] = amount;
                        
                        sendIndex++;
                        
                        for (int i=0 ; i<m_dataInfoList.size() ; i++) {
                            if (type == m_dataInfoList[i]->type) {
                                setValue(data, &sendIndex, m_dataInfoList[i]->aid);
                                setValue(data, &sendIndex, m_dataInfoList[i]->type);
                                UBYTE functionAmount = m_dataInfoList[i]->functionStatusList.size();
                                setValue(data, &sendIndex, functionAmount);
                                
                                for (int j=0 ; j<m_dataInfoList[i]->functionStatusList.size() ; j++) {
                                    LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCode:%d", i, j, m_dataInfoList[i]->functionStatusList[j]->functionCode);
                                    LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCodeAmount:%lu", i, j, m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size());
                                    setValue(data, &sendIndex, m_dataInfoList[i]->functionStatusList[j]->functionCode);
                                    UBYTE functionCodeAmount = m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size();
                                    setValue(data, &sendIndex, functionCodeAmount);
                                    
                                    for (int k=0 ; k<m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
                                        LOGD("m_pDataInfo[%d].pFunctionStatus[%d].pFunctionCode[%d]:%d", i, j, k, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                                        setValue(data, &sendIndex, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                                    }
                                }
                                
                                data[3 - 1] = ++amount;
                            }
                        }
                        
                        //                            if (m_callback) {
                        //                                m_callback(m_pDataInfo);
                        //                            }
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = data;
                        binraryParseSendData.dataLength = sendIndex;
                        parseSendData(&binraryParseSendData);
                        return;
                    } // end 24 Get Accessory Items
                        
                    // 27 Air Condition Query Function
                    case 27: {
                        int recvIndex = 0;
                        if (isLength2Byte(buffer, totalLength) == true) {
                            recvIndex = 10 - 1;
                        }
                        else {
                            recvIndex = 9 - 1;
                        }
                        
                        UBYTE totalCount = buffer[recvIndex++];
                        UBYTE countIndex = buffer[recvIndex++];
                        UBYTE recvAmount = buffer[recvIndex++];
                        LOGD("totalCount:%d", totalCount);
                        LOGD("countIndex:%d", countIndex);
                        LOGD("recvAmount:%d", recvAmount);
                        
                        // 傳送的資料Buffer
                        int sendIndex = 0;
                        BYTE sendDataBuffer[MAX_BUFFER_SIZE];
                        
                        UBYTE sendTotalCount = 1;
                        sendDataBuffer[sendIndex++] = sendTotalCount;
                        
                        UBYTE sendCountIndex = 0;
                        sendDataBuffer[sendIndex++] = sendCountIndex;
                        
                        UBYTE sendAmount = 0;
                        sendDataBuffer[sendIndex++] = sendAmount;
                        
                        for (int x=0 ; x<recvAmount ; x++) {
                            UBYTE aid = buffer[recvIndex++];
                            unsigned int type = (unsigned int) Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 4);
                            UBYTE functionCode = buffer[recvIndex++];
                            
                            LOGD("aid:%d", aid);
                            LOGD("type:%d", type);
                            LOGD("functionCode:%d", functionCode);
                            
                            LOGD("m_dataInfoList.size():%lu", m_dataInfoList.size());
                            for (int i=0 ; i<m_dataInfoList.size() ; i++) {
                                LOGD("m_pDataInfo[%d].functionStatusAmount:%lu", i, m_dataInfoList[i]->functionStatusList.size());
                                
                                for (int j=0 ; j<m_dataInfoList[i]->functionStatusList.size() ; j++) {
                                    LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCode:%d", i, j, m_dataInfoList[i]->functionStatusList[j]->functionCode);
                                    LOGD("m_dataInfoList[i]->aid:%d", m_dataInfoList[i]->aid);
                                    
                                    if (aid == m_dataInfoList[i]->aid)
                                    {
                                        // 查詢所有的 Function Code
                                        if (functionCode == 0 ||
                                            functionCode == m_dataInfoList[i]->functionStatusList[j]->functionCode)
                                        {
                                            // amount
                                            sendDataBuffer[3 - 1] = ++sendAmount;
                                            
                                            sendDataBuffer[sendIndex++] = m_dataInfoList[i]->aid;
                                            setValue(sendDataBuffer, &sendIndex, m_dataInfoList[i]->type);
                                            sendDataBuffer[sendIndex++] = m_dataInfoList[i]->functionStatusList[j]->functionCode;
                                            sendDataBuffer[sendIndex++] = m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size();
                                            
                                            LOGD("aid:%d", m_dataInfoList[i]->aid);
                                            LOGD("type:%d", m_dataInfoList[i]->type);
                                            LOGD("functionCode:%d", m_dataInfoList[i]->functionStatusList[j]->functionCode);
                                            LOGD("functionAmount:%lu", m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size());
                                            
                                            for (int k=0 ; k<m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
                                                LOGD("m_pDataInfo[%d].pFunctionStatus[%d].pFunctionCode[%d].transferCode:%d", i, j, k, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                                                
                                                setValue(sendDataBuffer, &sendIndex, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                                            }
                                        }
                                    }
                                    
                                }
                            }
                            
                        }
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = sendDataBuffer;
                        binraryParseSendData.dataLength = sendIndex;
                        parseSendData(&binraryParseSendData);
                        return;
                    } // 27 Air Condition Query Function
                        
                    // 28 Edit Query Function
                    case 28: {
                        int recvIndex = 0;
                        if (isLength2Byte(buffer, totalLength) == true) {
                            recvIndex = 10 - 1;
                        }
                        else {
                            recvIndex = 9 - 1;
                        }
                        
                        UBYTE totalCount = buffer[recvIndex++];
                        UBYTE countIndex = buffer[recvIndex++];
                        UBYTE amount = buffer[recvIndex++];
                        LOGD("totalCount:%d", totalCount);
                        LOGD("countIndex:%d", countIndex);
                        LOGD("amount:%d", amount);
                        
                        // 傳送的資料Buffer
                        int sendIndex = 0;
                        BYTE sendDataBuffer[MAX_BUFFER_SIZE];
                        
                        UBYTE sendTotalCount = 1;
                        sendDataBuffer[sendIndex++] = sendTotalCount;
                        
                        UBYTE sendCountIndex = 0;
                        sendDataBuffer[sendIndex++] = sendCountIndex;
                        
                        UBYTE sendAmount = 0;
                        sendDataBuffer[sendIndex++] = sendAmount;
                        
                        vector<FunctionInfo*> dataInfoList;
                        
                        // 取得接收的資料
                        for (int x=0 ; x<amount ; x++) {
                            UBYTE aid = buffer[recvIndex++];
                            unsigned int type = (unsigned int) Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 4);
                            UBYTE functionCode = buffer[recvIndex++];
                            UBYTE functionCodeAmount = buffer[recvIndex++];
                            
                            LOGD("aid:%d", aid);
                            LOGD("type:%d", type);
                            LOGD("functionCode:%d", functionCode);
                            LOGD("functionCodeAmount:%d", functionCodeAmount);
                            
                            //                            // 是否要重設
                            //                            if (functionCode == 200) {
                            //                                break;
                            //                            }
                            
                            LOGD("m_dataInfoList.size():%lu", m_dataInfoList.size());
                            for (int i=0 ; i<m_dataInfoList.size() ; i++) {
                                LOGD("m_pDataInfo[%d].functionStatusAmount:%lu", i, m_dataInfoList[i]->functionStatusList.size());
                                
                                for (int j=0 ; j<m_dataInfoList[i]->functionStatusList.size() ; j++) {
                                    LOGD("aid:%d", m_dataInfoList[i]->aid);
                                    LOGD("type:%d", m_dataInfoList[i]->type);
                                    LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCode:%d", i, j, m_dataInfoList[i]->functionStatusList[j]->functionCode);
                                    LOGD("aid:%d", aid);
                                    LOGD("type:%d", type);
                                    LOGD("functionCode:%d", functionCode);
                                    
                                    if (aid == m_dataInfoList[i]->aid &&
                                        // functionCode 詢問狀態 = 修改狀態 - 1
                                        //              修改狀態 = 詢問狀態 + 1
                                        functionCode - 1 == m_dataInfoList[i]->functionStatusList[j]->functionCode)
                                    {
                                        LOGD("functionCodeAmount:%d", functionCodeAmount);
                                        LOGD("m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size() = %lu", m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size());
                                        
                                        FunctionInfo* pFunctionInfo = new FunctionInfo();
                                        pFunctionInfo->aid = m_dataInfoList[i]->aid;
                                        pFunctionInfo->type = m_dataInfoList[i]->type;
                                        FunctionStatus* pFunctionStatus = new FunctionStatus();
                                        
                                        // 設定數量較少
                                        if (functionCodeAmount < m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size())
                                        {
                                            for (int y=0 ; y<m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; y++) {
                                                // 清空
                                                m_dataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = NULL;
                                            }
                                            
                                            // 設定
                                            for (int y=0 ; y<functionCodeAmount ; y++) {
                                                unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
                                                LOGD("y:%d transferCode:%d", y, transferCode);
                                                
                                                m_dataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
                                            }
                                        }
                                        // 設定數量較多
                                        else if (functionCodeAmount > m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
                                            // 設定
                                            for (int y=0 ; y<functionCodeAmount ; y++) {
                                                unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
                                                LOGD("y:%d transferCode:%d", y, transferCode);
                                                
                                                if (y + 1 > m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
                                                    addFunctionCode(m_dataInfoList[i]->functionStatusList[j], transferCode);
                                                }
                                                else {
                                                    m_dataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
                                                }
                                            }
                                        }
                                        // 設定值數量一樣
                                        else if (functionCodeAmount == m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
                                            // 設定
                                            for (int y=0 ; y<functionCodeAmount ; y++) {
                                                unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
                                                LOGD("y:%d transferCode:%d", y, transferCode);
                                                
                                                m_dataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
                                            }
                                        }
                                        else {
                                            LOGE("對應不到");
                                        }
                                        
                                        // amount
                                        sendDataBuffer[3 - 1] = ++sendAmount;
                                        
                                        sendDataBuffer[sendIndex++] = m_dataInfoList[i]->aid;
                                        setValue(sendDataBuffer, &sendIndex, m_dataInfoList[i]->type);
                                        sendDataBuffer[sendIndex++] = functionCode;
                                        sendDataBuffer[sendIndex++] = m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size();
                                        
                                        pFunctionStatus->functionCode = m_dataInfoList[i]->functionStatusList[j]->functionCode;
                                        
                                        for (int k=0 ; k<m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
                                            LOGD("m_pDataInfo[%d].pFunctionStatus[%d].pFunctionCode[%d].transferCode:%d", i, j, k, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                                            
                                            setValue(sendDataBuffer, &sendIndex, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                                            
                                            FunctionCode *pFunctionCode = new FunctionCode();
                                            pFunctionCode->transferCode = m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode;
                                            pFunctionStatus->functionCodeList.push_back(pFunctionCode);
                                        }
                                        
                                        m_pCommandEvent->onCommandRecvCommand28(m_dataInfoList[i]->functionStatusList[j]);
                                        
                                        pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
                                        dataInfoList.push_back(pFunctionInfo); // 回應對應的一組
                                        //                                        dataInfoList.push_back(m_dataInfoList[i]);/ / 回應所有
                                    }
                                }
                            }
                        }
                        
                        m_pCommandEvent->onCommandRecvFullCommand28(channelID, &dataInfoList);
                        
                        // 上報 cmd30
                        sendReportAllWithCommand30(channelID, &dataInfoList);
                        for (int i=0 ; i<dataInfoList.size() ; i++) {
                            delete dataInfoList[i];
                        }
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = sendDataBuffer;
                        binraryParseSendData.dataLength = sendIndex;
                        parseSendData(&binraryParseSendData);
                        break;
                    } // 28 Edit Query Function
                        
                    // 29 Query Device Version Function
                    case 29: {
                        int sendIndex = 0;
                        BYTE sendDataBuffer[MAX_BUFFER_SIZE];
                        
                        setValue(sendDataBuffer, &sendIndex, m_CommandData.version1);
                        setValue(sendDataBuffer, &sendIndex, m_CommandData.version2);
                        setValue(sendDataBuffer, &sendIndex, m_CommandData.version3);
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = sendDataBuffer;
                        binraryParseSendData.dataLength = sendIndex;
                        parseSendData(&binraryParseSendData);
                    }   return;
                        
                    // 30 Device Report To Client Function
                    case 30: {
                        int recvIndex = 0;
                        if (isLength2Byte(buffer, totalLength) == true) {
                            recvIndex = 10 - 1;
                        }
                        else {
                            recvIndex = 9 - 1;
                        }
                        
                        UBYTE SID = buffer[recvIndex++];
                        UBYTE totalCount = buffer[recvIndex++];
                        UBYTE countIndex = buffer[recvIndex++];
                        UBYTE amount = buffer[recvIndex++];
                        
                        LOGD("SID:%d", SID);
                        LOGD("totalCount:%d", totalCount);
                        LOGD("countIndex:%d", countIndex);
                        LOGD("amount:%d", amount);
                        
                        // 傳送的資料Buffer
                        int sendIndex = 0;
                        BYTE sendDataBuffer[MAX_BUFFER_SIZE];
                        
                        UBYTE sendTotalCount = 1;
                        sendDataBuffer[sendIndex++] = sendTotalCount;
                        
                        UBYTE sendCountIndex = 0;
                        sendDataBuffer[sendIndex++] = sendCountIndex;
                        
                        UBYTE sendAmount = 0;
                        sendDataBuffer[sendIndex++] = sendAmount;
                        
                        for (int x=0 ; x<amount ; x++) {
                            UBYTE aid = buffer[recvIndex++];
                            unsigned int type = (unsigned int) Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 4);
                            UBYTE functionCode = buffer[recvIndex++];
                            UBYTE functionCodeAmount = buffer[recvIndex++];
                            
                            LOGD("aid:%d", aid);
                            LOGD("type:%d", type);
                            LOGD("functionCode:%d", functionCode);
                            LOGD("functionCodeAmount:%d", functionCodeAmount);
                            
                            LOGD("m_dataInfoList.size():%lu", m_dataInfoList.size());
                            for (int i=0 ; i<m_dataInfoList.size() ; i++) {
                                LOGD("m_pDataInfo[%d].functionStatusAmount:%lu", i, m_dataInfoList[i]->functionStatusList.size());
                                
                                for (int j=0 ; j<m_dataInfoList[i]->functionStatusList.size() ; j++) {
                                    LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCode:%d", i, j, m_dataInfoList[i]->functionStatusList[j]->functionCode);
                                    LOGD("type:%d", type);
                                    LOGD("aid:%d", aid);
                                    LOGD("functionCode:%d", functionCode);
                                    
                                    //                                    if (// TODO type == Accessory_Type_Air_Conditioner &&
                                    //                                        aid == m_dataInfoList[i]->aid &&
                                    //                                        // functionCode 詢問狀態 = 修改狀態 - 1
                                    //                                        //              修改狀態 = 詢問狀態 + 1
                                    //                                        functionCode - 1 == m_dataInfoList[i]->functionStatusList[j]->functionCode)
                                    //                                    {
                                    //
                                    //                                        LOGD("functionCodeAmount:%d", functionCodeAmount);
                                    //                                        LOGD("m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size() = %lu", m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size());
                                    //
                                    //                                        // 設定數量較少
                                    //                                        if (functionCodeAmount < m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size())
                                    //                                        {
                                    //                                            for (int y=0 ; y<m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; y++) {
                                    //                                                // 清空
                                    //                                                m_dataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = NULL;
                                    //                                            }
                                    //
                                    //                                            // 設定
                                    //                                            for (int y=0 ; y<functionCodeAmount ; y++) {
                                    //                                                unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
                                    //                                                LOGD("y:%d transferCode:%d", y, transferCode);
                                    //
                                    //                                                m_dataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
                                    //                                            }
                                    //                                        }
                                    //                                        // 設定數量較多
                                    //                                        else if (functionCodeAmount > m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
                                    //                                            // 設定
                                    //                                            for (int y=0 ; y<functionCodeAmount ; y++) {
                                    //                                                unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
                                    //                                                LOGD("y:%d transferCode:%d", y, transferCode);
                                    //
                                    //                                                if (y + 1 > m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
                                    //                                                    addFunctionCode(m_dataInfoList[i]->functionStatusList[j], transferCode);
                                    //                                                }
                                    //                                                else {
                                    //                                                    m_dataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
                                    //                                                }
                                    //                                            }
                                    //                                        }
                                    //                                        // 設定值數量一樣
                                    //                                        else if (functionCodeAmount == m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
                                    //                                            // 設定
                                    //                                            for (int y=0 ; y<functionCodeAmount ; y++) {
                                    //                                                unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
                                    //                                                LOGD("y:%d transferCode:%d", y, transferCode);
                                    //
                                    //                                                m_dataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
                                    //                                            }
                                    //                                        }
                                    //                                        else {
                                    //                                            LOGE("對應不到");
                                    //                                        }
                                    //
                                    //                                        // amount
                                    //                                        sendDataBuffer[3 - 1] = ++sendAmount;
                                    //
                                    //                                        sendDataBuffer[sendIndex++] = m_dataInfoList[i]->aid;
                                    //                                        setValue(sendDataBuffer, &sendIndex, m_dataInfoList[i]->type);
                                    //                                        sendDataBuffer[sendIndex++] = functionCode;
                                    //                                        sendDataBuffer[sendIndex++] = m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size();
                                    //
                                    //                                        for (int k=0 ; k<m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
                                    //                                            LOGD("m_pDataInfo[%d].pFunctionStatus[%d].pFunctionCode[%d].transferCode:%d", i, j, k, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                                    //
                                    //                                            setValue(sendDataBuffer, &sendIndex, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                                    //                                        }
                                    //
                                    //                                        onCommandRecvCommand28(m_dataInfoList[i]->functionStatusList[j]);
                                    //                                    }
                                }
                            }
                        }
                        
                        //                        send(channelID, basicData.stage, basicData.operators, sendDataBuffer, sendIndex);
                        return;
                    } // 30 Device Report To Client Function
                        
                    // Add Accessory Items
                    case 19: {
                        int sendIndex = 0;
                        BYTE data[MAX_BUFFER_SIZE];
                        
                        UBYTE paringStatus = 1;
                        data[sendIndex++] = paringStatus;
                        
                        UBYTE totalCount = 1;
                        data[sendIndex++] = totalCount;
                        
                        UBYTE countIndex = 0;
                        data[sendIndex++] = countIndex;
                        
                        UBYTE amount = 0;
                        data[sendIndex++] = ++amount;
                        
                        // 加入Sensor
                        //                    TUTKPIRDevice::generatorDataInfoList(m_nMaxAID++, &m_dataInfoList, &m_TypeSet);
                        //                    TUTKSmokeDevice::generatorDataInfoList(m_nMaxAID++, &m_dataInfoList, &m_TypeSet);
//                        VtechVirtualGroupDevice::generatorDataInfoList(this);
                        
                        // 取最後一個
                        //                    data[4 - 1] = ++amount;
                        
                        int i = (int) m_dataInfoList.size() - 1;
                        setValue(data, &sendIndex, m_dataInfoList[i]->aid);
                        setValue(data, &sendIndex, m_dataInfoList[i]->type);
                        
                        UBYTE functionAmount = m_dataInfoList[i]->functionStatusList.size();
                        setValue(data, &sendIndex, functionAmount);
                        
                        for (int j=0 ; j<m_dataInfoList[i]->functionStatusList.size() ; j++) {
                            LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCode:%d", i, j, m_dataInfoList[i]->functionStatusList[j]->functionCode);
                            LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCodeAmount:%lu", i, j, m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size());
                            setValue(data, &sendIndex, m_dataInfoList[i]->functionStatusList[j]->functionCode);
                            UBYTE functionCodeAmount = m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size();
                            setValue(data, &sendIndex, functionCodeAmount);
                            
                            for (int k=0 ; k<m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
                                LOGD("m_pDataInfo[%d].pFunctionStatus[%d].pFunctionCode[%d]:%d", i, j, k, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                                setValue(data, &sendIndex, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                            }
                        }
                        
                        sendReportAllWithCommand32(channelID, operators, m_dataInfoList[i]->aid, m_dataInfoList[i]->type, 1);
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = data;
                        binraryParseSendData.dataLength = sendIndex;
                        parseSendData(&binraryParseSendData);
                    }   break;
                        
                    // Remove Accessory Items
                    case 20: {
                        int recvIndex = 0;
                        if (isLength2Byte(buffer, totalLength) == true) {
                            recvIndex = 10 - 1;
                        }
                        else {
                            recvIndex = 9 - 1;
                        }
                        
                        UBYTE totalCount = buffer[recvIndex++];
                        LOGD("totalCount:%d", totalCount);
                        
                        UBYTE countIndex = buffer[recvIndex++];
                        LOGD("countIndex:%d", countIndex);
                        
                        UBYTE amount = buffer[recvIndex++];
                        LOGD("amount:%d", amount);
                        
                        set<UBYTE> aidSet;
                        for (int i=0 ; i<amount ; i++) {
                            UBYTE aid = buffer[recvIndex++];
                            LOGD("aid:%d", aid);
                            aidSet.insert(aid);
                        }
                        //                    sort(aidSet.begin(), aidSet.end());
                        
                        vector<int> resultAidList;
                        vector<unsigned int> resultTypeList;
                        vector<int> resultResponseList;
                        map<int, bool> resultTypeMap;
                        
                        for (set<UBYTE>::iterator it = aidSet.begin() ; it != aidSet.end() ; it++) {
                            for (int i=(int)m_dataInfoList.size()-1 ; i>=0 ; i--) {
                                LOGD("(*it):%d", (*it));
                                LOGD("m_dataInfoList[%d]->aid:%d", i, m_dataInfoList[i]->aid);
                                
                                if (m_dataInfoList[i]->aid == (*it)) {
                                    LOGD("m_dataInfoList[i]->type:%d", m_dataInfoList[i]->type);
                                    resultTypeMap.insert( std::pair<int, bool>(m_dataInfoList[i]->type, true) );
                                    
                                    resultAidList.push_back((*it));
                                    resultTypeList.push_back(m_dataInfoList[i]->type);
                                    resultResponseList.push_back(1);
                                    
                                    m_dataInfoList.erase(m_dataInfoList.begin() + i);
                                    break;
                                }
                            }
                        }
                        
                        // 檢查型態是否還存在
                        for (map<int, bool>::iterator it = resultTypeMap.begin() ; it != resultTypeMap.end() ; it++) {
                            LOGD("it->first:%d", it->first);
                            
                            for (int i=(int)m_dataInfoList.size()-1 ; i>=0 ; i--) {
                                LOGD("type:%d", m_dataInfoList[i]->type);
                                
                                // 已存在
                                if (m_dataInfoList[i]->type == it->first) {
                                    LOGD("it->first:%d", it->first);
                                    
                                    it->second = false;
                                }
                            }
                        }
                        
                        // 設定型態不存在的刪除
                        for (map<int, bool>::iterator it = resultTypeMap.begin() ; it != resultTypeMap.end() ; it++) {
                            if (it->second == true) {
                                m_CommandData.TypeSet.erase(it->first);
                            }
                        }
                        
                        int sendIndex = 0;
                        UBYTE sendDataBuffer[MAX_BUFFER_SIZE];
                        
                        UBYTE sendTotalCount = 1;
                        sendDataBuffer[sendIndex++] = sendTotalCount;
                        
                        UBYTE sendCountIndex = 0;
                        sendDataBuffer[sendIndex++] = sendCountIndex;
                        
                        UBYTE sendAmount = resultAidList.size();
                        sendDataBuffer[sendIndex++] = sendAmount;
                        
                        for (int i=0 ; i<resultAidList.size() ; i++) {
                            sendDataBuffer[sendIndex++] = resultAidList[i];
                        }
                        
                        // 上報機制
                        sendReportAllWithCommand32(channelID, operators, (int)resultAidList.size(), &resultAidList[0], &resultTypeList[0], &resultResponseList[0]);
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = sendDataBuffer;
                        binraryParseSendData.dataLength = sendIndex;
                        parseSendData(&binraryParseSendData);
                    }   break;
                        
                    // Get All Type And Accessory Items
                    case 31: {
                        int sendIndex = 0;
                        BYTE data[MAX_BUFFER_SIZE];
                        
                        UBYTE totalCount = 1;
                        data[sendIndex++] = totalCount;
                        
                        UBYTE countIndex = 0;
                        data[sendIndex++] = countIndex;
                        
                        UBYTE amount = 0; // m_dataInfoList.size();
                        data[3 - 1] = amount;
                        sendIndex++;
                        
                        int type = Accessory_Type_Gateway;
                        for (int i=0 ; i<m_dataInfoList.size() ; i++) {
                            if (type != m_dataInfoList[i]->type) {
                                setValue(data, &sendIndex, m_dataInfoList[i]->aid);
                                setValue(data, &sendIndex, m_dataInfoList[i]->type);
                                UBYTE functionAmount = m_dataInfoList[i]->functionStatusList.size();
                                setValue(data, &sendIndex, functionAmount);
                                
                                for (int j=0 ; j<m_dataInfoList[i]->functionStatusList.size() ; j++) {
                                    LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCode:%d", i, j, m_dataInfoList[i]->functionStatusList[j]->functionCode);
                                    LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCodeAmount:%lu", i, j, m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size());
                                    setValue(data, &sendIndex, m_dataInfoList[i]->functionStatusList[j]->functionCode);
                                    UBYTE functionCodeAmount = m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size();
                                    setValue(data, &sendIndex, functionCodeAmount);
                                    
                                    for (int k=0 ; k<m_dataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
                                        LOGD("m_pDataInfo[%d].pFunctionStatus[%d].pFunctionCode[%d]:%d", i, j, k, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                                        setValue(data, &sendIndex, m_dataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                                    }
                                }
                                
                                data[3 - 1] = ++amount;
                            }
                        }
                        
                        BinraryRDTServerCommand_ParseSendData binraryParseSendData;
                        binraryParseSendData.channelID = channelID;
                        binraryParseSendData.stage = stage;
                        binraryParseSendData.operators = operators;
                        binraryParseSendData.pData = data;
                        binraryParseSendData.dataLength = sendIndex;
                        parseSendData(&binraryParseSendData);
                        break;
                    }
                        
                }
            }
        }
        
        // 呼叫子類別
        BinraryRDTServerCommand_RecvData BinraryCommandRecvData;
        BinraryCommandRecvData.channelID = channelID;
        BinraryCommandRecvData.pBuffer = buffer;
        BinraryCommandRecvData.totalLength = totalLength;
        BinraryCommandRecvData.operators = operators;
        BinraryCommandRecvData.stage = stage;
        m_pCommandEvent->onCommandRecvData(&BinraryCommandRecvData);
    }
    else {
        LOGE("Error not match RDT command");
    }
}

void BinraryRDTServerCommand::parseRecvData(ParseRecvData* pParseRecvData)
{
    BinraryRDTServerCommand_ParseRecvData* pBinraryParseRecvData = (BinraryRDTServerCommand_ParseRecvData*) pParseRecvData;
    int channelID = pBinraryParseRecvData->channelID;
    UBYTE* pBuffer = pBinraryParseRecvData->pBuffer;
    int length = pBinraryParseRecvData->length;
    
    Utility::printData(__PRETTY_FUNCTION__, __LINE__, pBuffer, length);
    
    // 只有一組資料
    if (isBasicVerificationPass(pBuffer, length) == true) {
        LOGD("只有一組資料");
        
        recvData(channelID, pBuffer, length);
    }
    // 兩個以上
    else {
        LOGD("兩個以上");
        
        int offset = 0;
        
        do {
            int fragmentLength = 0;
            if (isLength2Byte(pBuffer, length)) {
                fragmentLength = pBuffer[offset + 4] + 4 + 2 + 2;
            }
            else {
                fragmentLength = pBuffer[offset + 4] + 4 + 2 + 1;
            }
            
            if (isBasicVerificationPass(pBuffer + offset, fragmentLength) == true) {
                recvData(channelID, pBuffer + offset, fragmentLength);
            }
            else {
                LOGE("封包未符合!");
            }
            
            offset += fragmentLength;
        } while (length - offset > 0);
        
    }
}

#pragma mark - Report

void BinraryRDTServerCommand::sendReportAllWithCommand30(int channelID, vector<FunctionInfo*>* pFunctionInfoList)
{
    int count = 0;
    for (set<int>::iterator it = m_nChannelIDList.begin() ; it != m_nChannelIDList.end() ; it++) {
        int myChannelID = *it;
        LOGD("m_nChannelIDList[%d]:%d", count++, myChannelID);
        
        if (channelID == myChannelID) {
            continue;
        }
        else {
            sendReportWithCommand30(myChannelID, pFunctionInfoList);
        }
    }
}

void BinraryRDTServerCommand::sendReportWithCommand30(int channelID, vector<FunctionInfo*>* pFunctionInfoList)
{
    // 傳送的資料Buffer
    int sendIndex = 0;
    BYTE sendDataBuffer[MAX_BUFFER_SIZE];
    
    sendDataBuffer[sendIndex++] = channelID;
    
    UBYTE sendTotalCount = 1;
    sendDataBuffer[sendIndex++] = sendTotalCount;
    
    UBYTE sendCountIndex = 0;
    sendDataBuffer[sendIndex++] = sendCountIndex;
    
    UBYTE sendAmount = 0;
    sendDataBuffer[sendIndex++] = sendAmount;
    
    for (int i=0 ; i<pFunctionInfoList->size() ; i++) {
        for (int j=0 ; j<(*pFunctionInfoList)[i]->functionStatusList.size() ; j++) {
            // amount
            sendDataBuffer[4 - 1] = ++sendAmount;
            
            sendDataBuffer[sendIndex++] = (*pFunctionInfoList)[i]->aid;
            setValue(sendDataBuffer, &sendIndex, (*pFunctionInfoList)[i]->type);
            sendDataBuffer[sendIndex++] = (*pFunctionInfoList)[i]->functionStatusList[j]->functionCode;
            sendDataBuffer[sendIndex++] = (*pFunctionInfoList)[i]->functionStatusList[j]->functionCodeList.size();
            
            LOGD("aid:%d", (*pFunctionInfoList)[i]->aid);
            LOGD("type:%d", (*pFunctionInfoList)[i]->type);
            LOGD("functionCode:%d", (*pFunctionInfoList)[i]->functionStatusList[j]->functionCode);
            LOGD("functionCodeList count:%lu", (*pFunctionInfoList)[i]->functionStatusList[j]->functionCodeList.size());
            
            for (int k=0 ; k<(*pFunctionInfoList)[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
                LOGD("(*pFunctionInfoList)[%d]->functionStatusList[%d]->functionCodeList[%d]->transferCode:%d", i, j, k, (*pFunctionInfoList)[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
                
                setValue(sendDataBuffer, &sendIndex, (*pFunctionInfoList)[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
            }
        }
    }
    
    BinraryRDTServerCommand_ParseSendData binraryParseSendData;
    binraryParseSendData.channelID = channelID;
    binraryParseSendData.stage = 5;
    binraryParseSendData.operators = 30;
    binraryParseSendData.pData = sendDataBuffer;
    binraryParseSendData.dataLength = sendIndex;
    parseSendData(&binraryParseSendData);
}

void BinraryRDTServerCommand::sendReportAllWithCommand32(int channelID, int operations, int aid, unsigned int type, int status)
{
    int count = 0;
    for (set<int>::iterator it = m_nChannelIDList.begin() ; it != m_nChannelIDList.end() ; it++) {
        int myChannelID = *it;
        LOGD("m_nChannelIDList[%d]:%d", count++, myChannelID);
        
        if (channelID == myChannelID) {
            continue;
        }
        else {
            int aids[] = {aid};
            unsigned int types[] = {type};
            int statuses[] = {status};
            sendReportWithCommand32(myChannelID, operations, 1, aids, types, statuses);
        }
    }
}

void BinraryRDTServerCommand::sendReportAllWithCommand32(int channelID, int operations, int amount, int aids[], unsigned int types[], int statuses[])
{
    int count = 0;
    for (set<int>::iterator it = m_nChannelIDList.begin() ; it != m_nChannelIDList.end() ; it++) {
        int myChannelID = *it;
        LOGD("m_nChannelIDList[%d]:%d", count++, myChannelID);
        
        if (channelID == myChannelID) {
            continue;
        }
        else {
            sendReportWithCommand32(myChannelID, operations, amount, aids, types, statuses);
        }
    }
}

void BinraryRDTServerCommand::sendReportWithCommand32(int channelID, int operations, int amount, int aids[], unsigned int types[], int statuses[])
{
    // 傳送的資料Buffer
    int sendIndex = 0;
    BYTE sendDataBuffer[MAX_BUFFER_SIZE];
    
    sendDataBuffer[sendIndex++] = channelID;
    
    UBYTE sendTotalCount = 1;
    sendDataBuffer[sendIndex++] = sendTotalCount;
    
    UBYTE sendCountIndex = 0;
    sendDataBuffer[sendIndex++] = sendCountIndex;
    
    sendDataBuffer[sendIndex++] = amount;
    
    for (int i=0 ; i<amount ; i++) {
        sendDataBuffer[sendIndex++] = aids[i];
        setValue(sendDataBuffer, &sendIndex, types[i]);
        sendDataBuffer[sendIndex++] = statuses[i];
        sendDataBuffer[sendIndex++] = operations;
    }
    
    BinraryRDTServerCommand_ParseSendData binraryParseSendData;
    binraryParseSendData.channelID = channelID;
    binraryParseSendData.stage = 5;
    binraryParseSendData.operators = 32;
    binraryParseSendData.pData = sendDataBuffer;
    binraryParseSendData.dataLength = sendIndex;
    parseSendData(&binraryParseSendData);
}

void BinraryRDTServerCommand::sendReportAllWithCommand33(int channelID, int operations, int status)
{
    int count = 0;
    for (set<int>::iterator it = m_nChannelIDList.begin() ; it != m_nChannelIDList.end() ; it++) {
        int myChannelID = *it;
        LOGD("m_nChannelIDList[%d]:%d", count++, myChannelID);
        
        if (channelID == myChannelID) {
            continue;
        }
        else {
            sendReportWithCommand33(myChannelID, operations, status);
        }
    }
}

void BinraryRDTServerCommand::sendReportWithCommand33(int channelID, int operations, int status)
{
    // 傳送的資料Buffer
    int sendIndex = 0;
    BYTE sendDataBuffer[MAX_BUFFER_SIZE];
    
    sendDataBuffer[sendIndex++] = channelID;
    
    UBYTE sendTotalCount = 1;
    sendDataBuffer[sendIndex++] = sendTotalCount;
    
    UBYTE sendCountIndex = 0;
    sendDataBuffer[sendIndex++] = sendCountIndex;
    
    int amount = 1;
    sendDataBuffer[sendIndex++] = amount;
    
    //    for (int i=0 ; i<amount ; i++) {
    sendDataBuffer[sendIndex++] = status;
    sendDataBuffer[sendIndex++] = operations;
    //    }
    
    BinraryRDTServerCommand_ParseSendData binraryParseSendData;
    binraryParseSendData.channelID = channelID;
    binraryParseSendData.stage = 5;
    binraryParseSendData.operators = 33;
    binraryParseSendData.pData = sendDataBuffer;
    binraryParseSendData.dataLength = sendIndex;
    parseSendData(&binraryParseSendData);
}
