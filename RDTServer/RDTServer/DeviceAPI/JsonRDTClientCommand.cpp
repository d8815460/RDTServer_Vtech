//
//  JsonRDTClientCommand.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/26.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "JsonRDTClientCommand.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "Common.hpp"
#include "Utility.hpp"
#include "AccessoryTypeEnum.hpp"
#include "IOTCAPIs.h"
#include "RDTAPIs.h"
#include "BinraryRDTServerConnect.hpp"

JsonRDTClientCommand::JsonRDTClientCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData) : JsonRDTCommand(pCommandEvent, pCommandHardwardEvent, pConnect, pCommandData)
{
    LOGD("JsonRDTClientCommand");
        
    pthread_t pThreadInput;
    pthread_create(&pThreadInput, NULL, &JsonRDTClientCommand::threadInput, (void*)this);
}

#pragma mark - ConnectEvent

void JsonRDTClientCommand::onConnectRecvData(ConnectRecvData* pConnectRecvData)
{
    BinraryRDTServerConnect_ConnectRecvData* pBinraryConnectRecvData = (BinraryRDTServerConnect_ConnectRecvData*) pConnectRecvData;
    JsonRDTClientCommand_ParseRecvData* pBinraryParseRecvData = (JsonRDTClientCommand_ParseRecvData*) pBinraryConnectRecvData;
    
    parseRecvData(pBinraryParseRecvData);
}

#pragma mark - Thread

void* JsonRDTClientCommand::threadInput(void *arg)
{
    JsonRDTClientCommand* pJsonRDTClientCommand = (JsonRDTClientCommand*) arg;
    
    char pInput;
    while(true) {
//        LOGD("請輸入一個字元:");
        cin >> pInput;
        LOGD("input:%c", pInput);
        
        LOGD("===================================================================================================================================");
        int count = 0;
        for (set<int>::iterator it = pJsonRDTClientCommand->m_nChannelIDList.begin() ; it!=pJsonRDTClientCommand->m_nChannelIDList.end() ; it++) {
            LOGD("m_nChannelIDList[%d]:%d", count++, *it);
        }
        LOGD("===================================================================================================================================");
        
        if (count > 0) {
            set<int>::iterator it = pJsonRDTClientCommand->m_nChannelIDList.end();
            it--;
            
            Json::Value root;
//            Json::Value arrayObject;
//            Json::Value arraryItems;
            
            unsigned int serno = 87654321;
            root["serno"] = serno;
            
            root["operation"] = "read";
            root["target"] = "/accessory/0/product_code/";
//            root["target"] = "/accessory/0/product_name/";
            
//            arraryItems["cpp"] = "jsoncpp";
//            arraryItems["java"] = "jsoninjava";
//            arraryItems["php"] = "support";
//            arrayObject.append(arraryItems);
//            root["request"] = arrayObject;
            
            std::string json = root.toStyledString();
            JsonRDTClientCommand_ParseSendData parseSendData;
            parseSendData.channelID = *it;
            parseSendData.serno = serno;
            parseSendData.totalCount = 1;
            parseSendData.count = 1;
            parseSendData.pData = (BYTE*) json.c_str();
            parseSendData.dataLength = (int) json.length();
            pJsonRDTClientCommand->parseSendData(&parseSendData);
            
            /********** 上報 **********/
            //        FunctionInfo functionInfo;
            //        functionInfo.isRuningStack = true;
            //        functionInfo.aid = 8;
            //        functionInfo.type = Accessory_Type_VtechGarageDoor;
            //
            //        FunctionStatus functionStatus;
            //        functionStatus.isRuningStack = true;
            //        functionStatus.functionCode = 1;
            //        functionInfo.functionStatusList.push_back(&functionStatus);
            //
            //        static bool switchOn = true;
            //        switchOn = !switchOn;
            //
            //        FunctionCode functionCode;
            //        functionCode.transferCode = switchOn;
            //        functionStatus.functionCodeList.push_back(&functionCode);
            //
            //        vector<FunctionInfo*> functionInfoList;
            //        functionInfoList.push_back(&functionInfo);
            //        pJsonRDTClientCommand->sendReportWithCommand30(0, &functionInfoList);
            /********** 上報 **********/
            
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

    }
    
    return NULL;
}

#pragma mark - Method

#pragma mark - Command

void JsonRDTClientCommand::recvData(int channelID, BYTE* buffer, int totalLength)
{
//    LOGD("recvData");

    char* json = (char*) (buffer + 11 - 1);
    int jsonLen = (int) strlen(json);
    
    // 清除最後header end 0x03 0x04
    json[jsonLen-1] = NULL;
    json[jsonLen-2] = NULL;
    
    //    LOGD("json binrary 資料");
    //    Utility::printData(__PRETTY_FUNCTION__, __LINE__, (BYTE*)json, jsonLen-2);
    
    LOGD("JSON長度:%d", jsonLen);
    LOGD("JSON資料:%s", json);
    
//    int stage = 0;
//    int operators = 0;
//    
//    switch (stage) {
//        case 3: {
//            // 詢問device類別(classCode)
//            if (operators == 2) {
//                unsigned short classCode = m_pCommandEvent->onCommandGetProductCode();
//                LOGD("classCode:%d", classCode);
//                
//                JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                binraryParseSendData.channelID = channelID;
//                binraryParseSendData.pData = (BYTE*) &classCode;
//                binraryParseSendData.dataLength = sizeof(unsigned short);
//                parseSendData(&binraryParseSendData);
//                return;
//            }
//        }
//            
//        case 5: {
//            switch (operators) {
//                    
//                    // 3 Report Device Product Name
//                case 3: {
//                    const char* productName = m_pCommandEvent->onCommandGetProductName();
//                    LOGD("productName:%s", productName);
//                    
//                    int index = 0;
//                    BYTE buffer[MAX_BUFFER_SIZE];
//                    memset(buffer, 0, MAX_BUFFER_SIZE);
//                    buffer[index++] = strlen(productName);
//                    
//                    strcpy((char*)buffer, productName);
//                    index += strlen(productName) + 1;
//                    
//                    //    wstring str4 = L"你好么？";
//                    //    wstring str44(str4.rbegin(), str4.rend());
//                    //    LOGD("str4:%S", str4);
//                    
//                    //                        wchar_t a[] = L"杯";
//                    //                        LOGD("a = %ls", a);
//                    //                        LOGD("sizeof:%lu", sizeof(wchar_t));
//                    //                        LOGD("wstrlen:%lu", wcslen(a));
//                    //
//                    //                        char szTime[100];
//                    //                        wchar_t szValidDate[] = L"Hello World.";
//                    //                        wcstombs(szTime, szValidDate, wcslen(szValidDate));
//                    //                        send(channelID, basicData.stage, basicData.operators, (unsigned char*) szTime, (int) (wcslen(a) * 4));
//                    
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = buffer;
//                    binraryParseSendData.dataLength = index;
//                    parseSendData(&binraryParseSendData);
//                    return;
//                }
//                    
//                    // 7 Client Authentication
//                case 7: {
//                    char pPassword[32];
//                    memcpy(pPassword, &buffer[10 - 1], sizeof(pPassword));
//                    LOGD("Authentication Password:%s", pPassword);
//                    
//                    bool isAuthentication = false;
//                    if (strcmp(m_CommandData.pPassword, pPassword) == 0) {
//                        isAuthentication = true;
//                    }
//                    
//                    char sendBuffer[1];
//                    sendBuffer[0] = isAuthentication;
//                    
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = (BYTE*) sendBuffer;
//                    binraryParseSendData.dataLength = sizeof(sendBuffer);
//                    parseSendData(&binraryParseSendData);
//                    return;
//                }
//                    
//                    // 8 Change password
//                case 8: {
//                    int index = 0;
//                    index = 10 - 1;
//                    
//                    char pOldPassword[32];
//                    memcpy(pOldPassword, &buffer[index], sizeof(pOldPassword));
//                    index += 32;
//                    LOGD("pOldPassword:%s", pOldPassword);
//                    
//                    char pNewPassword[32];
//                    memcpy(pNewPassword, &buffer[index], sizeof(pNewPassword));
//                    index += 32;
//                    LOGD("pNewPassword:%s", pNewPassword);
//                    
//                    bool isResponse = false;
//                    if (strcmp(m_CommandData.pPassword, pOldPassword) == 0) {
//                        memcpy(m_CommandData.pPassword, pNewPassword, sizeof(pOldPassword));
//                        isResponse = true;
//                    }
//                    
//                    // 上報
//                    sendReportAllWithCommand33(channelID, operators, isResponse);
//                    
//                    char sendBuffer[1];
//                    sendBuffer[0] = isResponse;
//                    
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = (BYTE*) sendBuffer;
//                    binraryParseSendData.dataLength = sizeof(sendBuffer);
//                    parseSendData(&binraryParseSendData);
//                    return;
//                }
//                    
//                    // 11 Get Wifi List
//                case 11: {
//                    // 收到sessionId
//                    unsigned short sessionId = 0;
//                    sessionId = buffer[10 - 1];
//                    
//                    int count = (int) m_CommandData.WifinInfo.size();
//                    int respTotal = count;
//                    int respIndex = 0;
//                    do {
//                        // 傳送資料
//                        UBYTE amount = 0;
//                        int index = 0;
//                        BYTE data[MAX_BUFFER_SIZE];
//                        memset(data, 0, MAX_BUFFER_SIZE);
//                        
//                        data[index] = sessionId;
//                        index += 2;
//                        
//                        data[index++] = respIndex;
//                        data[index++] = respTotal;
//                        
//                        // 一次可以傳送的數量amount
//                        int total = 0;
//                        while ((total + sizeof(WifiInfo)) <= 255) {
//                            amount++;
//                            total += sizeof(WifiInfo);
//                        }
//                        data[index++] = amount;
//                        
//                        for (int i=0 ; i<amount ; i++) {
//                            memcpy(&data[index], (const char*) &m_CommandData.WifinInfo[respIndex], sizeof(WifiInfo));
//                            LOGD("WifiInfo:%ld", sizeof(WifiInfo));
//                            index += sizeof(WifiInfo);
//                            
//                            //                                strcpy(data + index, (const char*) m_pWifinInfo[respIndex].ssid);
//                        }
//                        
//                        //                        LOGD("index:%d", index);
//                        JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                        binraryParseSendData.channelID = channelID;
//                        binraryParseSendData.pData = data;
//                        binraryParseSendData.dataLength = index;
//                        parseSendData(&binraryParseSendData);
//                        
//                        respIndex++;
//                        count--;
//                        
//                        sleep(1);
//                    } while (count > 0);
//                    
//                    return;
//                }
//                    
//                    // 15 New Set Wifi Parameter
//                case 15: {
//                    char pSSID[128];
//                    char pPassword[32];
//                    
//                    memcpy(pSSID, &buffer[10 - 1], sizeof(pSSID));
//                    memcpy(pPassword, &buffer[138 - 1], sizeof(pPassword));
//                    
//                    LOGD("SSID:%s", pSSID);
//                    LOGD("Password:%s", pPassword);
//                    
//                    strcpy(m_CommandData.pSSID, pSSID);
//                    strcpy(m_CommandData.pSSIDPassword, pPassword);
//                    
//                    char sendBuffer[1];
//                    sendBuffer[0] = true;
//                    
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = (BYTE*) sendBuffer;
//                    binraryParseSendData.dataLength = sizeof(sendBuffer);
//                    parseSendData(&binraryParseSendData);
//                    return;
//                }
//                    
//                    // 16 Get Wifi Parameter
//                case 16: {
//                    int index = 0;
//                    BYTE data[MAX_BUFFER_SIZE];
//                    memset(data, 0, MAX_BUFFER_SIZE);
//                    
//                    // ssid
//                    memcpy(&data[index], m_CommandData.pSSID, sizeof(m_CommandData.pSSID));
//                    index += 128;
//                    
//                    // mac addr
//                    index += 18;
//                    
//                    // Security Mode
//                    data[index++] = 3;  // WPA2PSK
//                    
//                    // Encryption Type
//                    data[index++] = 2;  // AES
//                    
//                    // Pass Phrase
//                    memcpy(&data[index], m_CommandData.pSSIDPassword, sizeof(m_CommandData.pSSIDPassword));
//                    index += 32;
//                    
//                    LOGD("m_pSSID:%s", m_CommandData.pSSID);
//                    LOGD("m_pSSIDPassword:%s", m_CommandData.pSSIDPassword);
//                    
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = data;
//                    binraryParseSendData.dataLength = index;
//                    parseSendData(&binraryParseSendData);
//                    return;
//                }
//                    
//                    // 17 Get All Type
//                case 17: {
//                    int index = 0;
//                    BYTE data[MAX_BUFFER_SIZE];
//                    
//                    // Amount
//                    data[index++] = m_CommandData.TypeSet.size();
//                    for (set<unsigned int>::iterator it = m_CommandData.TypeSet.begin() ; it != m_CommandData.TypeSet.end() ; it++) {
//                        unsigned int type = *(it);
//                        setValue(data, &index, type);
//                    }
//                    
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = data;
//                    binraryParseSendData.dataLength = index;
//                    parseSendData(&binraryParseSendData);
//                }   return;
//                    
//                    // 24 Get Accessory Items
//                case 24: {
//                    int index = 0;
//                    index = 10 - 1;
//                    
//                    unsigned int type = (unsigned int) Utility::bytes2UnsignedLongWithBeginData(buffer, &index, 4);
//                    LOGD("type:%d", type);
//                    
//                    int sendIndex = 0;
//                    BYTE data[MAX_BUFFER_SIZE];
//                    
//                    UBYTE totalCount = 1;
//                    data[sendIndex++] = totalCount;
//                    
//                    UBYTE countIndex = 0;
//                    data[sendIndex++] = countIndex;
//                    
//                    UBYTE amount = 0; // m_CommandData.DataInfoList.size();
//                    data[3 - 1] = amount;
//                    
//                    sendIndex++;
//                    
//                    for (int i=0 ; i<m_CommandData.DataInfoList.size() ; i++) {
//                        if (type == m_CommandData.DataInfoList[i]->type) {
//                            setValue(data, &sendIndex, m_CommandData.DataInfoList[i]->aid);
//                            setValue(data, &sendIndex, m_CommandData.DataInfoList[i]->type);
//                            UBYTE functionAmount = m_CommandData.DataInfoList[i]->functionStatusList.size();
//                            setValue(data, &sendIndex, functionAmount);
//                            
//                            for (int j=0 ; j<m_CommandData.DataInfoList[i]->functionStatusList.size() ; j++) {
//                                LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCode:%d", i, j, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode);
//                                LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCodeAmount:%lu", i, j, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size());
//                                setValue(data, &sendIndex, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode);
//                                UBYTE functionCodeAmount = m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size();
//                                setValue(data, &sendIndex, functionCodeAmount);
//                                
//                                for (int k=0 ; k<m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
//                                    LOGD("m_pDataInfo[%d].pFunctionStatus[%d].pFunctionCode[%d]:%d", i, j, k, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
//                                    setValue(data, &sendIndex, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
//                                }
//                            }
//                            
//                            data[3 - 1] = ++amount;
//                        }
//                    }
//                    
//                    //                            if (m_callback) {
//                    //                                m_callback(m_pDataInfo);
//                    //                            }
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = data;
//                    binraryParseSendData.dataLength = sendIndex;
//                    parseSendData(&binraryParseSendData);
//                    return;
//                } // end 24 Get Accessory Items
//                    
//                    // 27 Air Condition Query Function
//                case 27: {
//                    int recvIndex = 0;
//                    recvIndex = 10 - 1;
//                    
//                    UBYTE totalCount = buffer[recvIndex++];
//                    UBYTE countIndex = buffer[recvIndex++];
//                    UBYTE recvAmount = buffer[recvIndex++];
//                    LOGD("totalCount:%d", totalCount);
//                    LOGD("countIndex:%d", countIndex);
//                    LOGD("recvAmount:%d", recvAmount);
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
//                    for (int x=0 ; x<recvAmount ; x++) {
//                        UBYTE aid = buffer[recvIndex++];
//                        unsigned int type = (unsigned int) Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 4);
//                        UBYTE functionCode = buffer[recvIndex++];
//                        
//                        LOGD("aid:%d", aid);
//                        LOGD("type:%d", type);
//                        LOGD("functionCode:%d", functionCode);
//                        
//                        LOGD("m_CommandData.DataInfoList.size():%lu", m_CommandData.DataInfoList.size());
//                        for (int i=0 ; i<m_CommandData.DataInfoList.size() ; i++) {
//                            LOGD("m_pDataInfo[%d].functionStatusAmount:%lu", i, m_CommandData.DataInfoList[i]->functionStatusList.size());
//                            
//                            for (int j=0 ; j<m_CommandData.DataInfoList[i]->functionStatusList.size() ; j++) {
//                                LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCode:%d", i, j, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode);
//                                LOGD("m_CommandData.DataInfoList[i]->aid:%d", m_CommandData.DataInfoList[i]->aid);
//                                
//                                if (aid == m_CommandData.DataInfoList[i]->aid)
//                                {
//                                    // 查詢所有的 Function Code
//                                    if (functionCode == 0 ||
//                                        functionCode == m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode)
//                                    {
//                                        // amount
//                                        sendDataBuffer[3 - 1] = ++sendAmount;
//                                        
//                                        sendDataBuffer[sendIndex++] = m_CommandData.DataInfoList[i]->aid;
//                                        setValue(sendDataBuffer, &sendIndex, m_CommandData.DataInfoList[i]->type);
//                                        sendDataBuffer[sendIndex++] = m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode;
//                                        sendDataBuffer[sendIndex++] = m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size();
//                                        
//                                        LOGD("aid:%d", m_CommandData.DataInfoList[i]->aid);
//                                        LOGD("type:%d", m_CommandData.DataInfoList[i]->type);
//                                        LOGD("functionCode:%d", m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode);
//                                        LOGD("functionAmount:%lu", m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size());
//                                        
//                                        for (int k=0 ; k<m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
//                                            LOGD("m_pDataInfo[%d].pFunctionStatus[%d].pFunctionCode[%d].transferCode:%d", i, j, k, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
//                                            
//                                            setValue(sendDataBuffer, &sendIndex, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
//                                        }
//                                    }
//                                }
//                                
//                            }
//                        }
//                        
//                    }
//                    
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = sendDataBuffer;
//                    binraryParseSendData.dataLength = sendIndex;
//                    parseSendData(&binraryParseSendData);
//                    return;
//                } // 27 Air Condition Query Function
//                    
//                // 28 Edit Query Function
//                case 28: {
//                    int recvIndex = 0;
//                    recvIndex = 10 - 1;
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
//                        //                            // 是否要重設
//                        //                            if (functionCode == 200) {
//                        //                                break;
//                        //                            }
//                        
//                        LOGD("m_CommandData.DataInfoList.size():%lu", m_CommandData.DataInfoList.size());
//                        for (int i=0 ; i<m_CommandData.DataInfoList.size() ; i++) {
//                            LOGD("m_pDataInfo[%d].functionStatusAmount:%lu", i, m_CommandData.DataInfoList[i]->functionStatusList.size());
//                            
//                            for (int j=0 ; j<m_CommandData.DataInfoList[i]->functionStatusList.size() ; j++) {
//                                LOGD("aid:%d", m_CommandData.DataInfoList[i]->aid);
//                                LOGD("type:%d", m_CommandData.DataInfoList[i]->type);
//                                LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCode:%d", i, j, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode);
//                                LOGD("aid:%d", aid);
//                                LOGD("type:%d", type);
//                                LOGD("functionCode:%d", functionCode);
//                                
//                                if (aid == m_CommandData.DataInfoList[i]->aid &&
//                                    // functionCode 詢問狀態 = 修改狀態 - 1
//                                    //              修改狀態 = 詢問狀態 + 1
//                                    functionCode - 1 == m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode)
//                                {
//                                    LOGD("functionCodeAmount:%d", functionCodeAmount);
//                                    LOGD("m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size() = %lu", m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size());
//                                    
//                                    FunctionInfo* pFunctionInfo = new FunctionInfo();
//                                    pFunctionInfo->aid = m_CommandData.DataInfoList[i]->aid;
//                                    pFunctionInfo->type = m_CommandData.DataInfoList[i]->type;
//                                    FunctionStatus* pFunctionStatus = new FunctionStatus();
//                                    
//                                    // 設定數量較少
//                                    if (functionCodeAmount < m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size())
//                                    {
//                                        for (int y=0 ; y<m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; y++) {
//                                            // 清空
//                                            m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = NULL;
//                                        }
//                                        
//                                        // 設定
//                                        for (int y=0 ; y<functionCodeAmount ; y++) {
//                                            unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
//                                            LOGD("y:%d transferCode:%d", y, transferCode);
//                                            
//                                            m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
//                                        }
//                                    }
//                                    // 設定數量較多
//                                    else if (functionCodeAmount > m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
//                                        // 設定
//                                        for (int y=0 ; y<functionCodeAmount ; y++) {
//                                            unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
//                                            LOGD("y:%d transferCode:%d", y, transferCode);
//                                            
//                                            if (y + 1 > m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
//                                                addFunctionCode(m_CommandData.DataInfoList[i]->functionStatusList[j], transferCode);
//                                            }
//                                            else {
//                                                m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
//                                            }
//                                        }
//                                    }
//                                    // 設定值數量一樣
//                                    else if (functionCodeAmount == m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
//                                        // 設定
//                                        for (int y=0 ; y<functionCodeAmount ; y++) {
//                                            unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
//                                            LOGD("y:%d transferCode:%d", y, transferCode);
//                                            
//                                            m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
//                                        }
//                                    }
//                                    else {
//                                        LOGE("對應不到");
//                                    }
//                                    
//                                    // amount
//                                    sendDataBuffer[3 - 1] = ++sendAmount;
//                                    
//                                    sendDataBuffer[sendIndex++] = m_CommandData.DataInfoList[i]->aid;
//                                    setValue(sendDataBuffer, &sendIndex, m_CommandData.DataInfoList[i]->type);
//                                    sendDataBuffer[sendIndex++] = functionCode;
//                                    sendDataBuffer[sendIndex++] = m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size();
//                                    
//                                    pFunctionStatus->functionCode = m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode;
//                                    
//                                    for (int k=0 ; k<m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
//                                        LOGD("m_pDataInfo[%d].pFunctionStatus[%d].pFunctionCode[%d].transferCode:%d", i, j, k, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
//                                        
//                                        setValue(sendDataBuffer, &sendIndex, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
//                                        
//                                        FunctionCode *pFunctionCode = new FunctionCode();
//                                        pFunctionCode->transferCode = m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode;
//                                        pFunctionStatus->functionCodeList.push_back(pFunctionCode);
//                                    }
//                                    
//                                    m_pCommandEvent->onCommandRecvCommand28(m_CommandData.DataInfoList[i]->functionStatusList[j]);
//                                    
//                                    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
//                                    dataInfoList.push_back(pFunctionInfo); // 回應對應的一組
//                                    //                                        dataInfoList.push_back(m_CommandData.DataInfoList[i]);/ / 回應所有
//                                }
//                            }
//                        }
//                    }
//                    
//                    m_pCommandEvent->onCommandRecvFullCommand28(channelID, &dataInfoList);
//                    
//                    // 上報 cmd30
//                    sendReportAllWithCommand30(channelID, &dataInfoList);
//                    for (int i=0 ; i<dataInfoList.size() ; i++) {
//                        delete dataInfoList[i];
//                    }
//                    
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = sendDataBuffer;
//                    binraryParseSendData.dataLength = sendIndex;
//                    parseSendData(&binraryParseSendData);
//                    break;
//                } // 28 Edit Query Function
//                    
//                    // 29 Query Device Version Function
//                case 29: {
//                    int sendIndex = 0;
//                    BYTE sendDataBuffer[MAX_BUFFER_SIZE];
//                    
//                    setValue(sendDataBuffer, &sendIndex, m_CommandData.version1);
//                    setValue(sendDataBuffer, &sendIndex, m_CommandData.version2);
//                    setValue(sendDataBuffer, &sendIndex, m_CommandData.version3);
//                    
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = sendDataBuffer;
//                    binraryParseSendData.dataLength = sendIndex;
//                    parseSendData(&binraryParseSendData);
//                }   return;
//                    
//                    // 30 Device Report To Client Function
//                case 30: {
//                    int recvIndex = 0;
//                    recvIndex = 10 - 1;
//                    
//                    UBYTE SID = buffer[recvIndex++];
//                    UBYTE totalCount = buffer[recvIndex++];
//                    UBYTE countIndex = buffer[recvIndex++];
//                    UBYTE amount = buffer[recvIndex++];
//                    
//                    LOGD("SID:%d", SID);
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
//                        LOGD("m_CommandData.DataInfoList.size():%lu", m_CommandData.DataInfoList.size());
//                        for (int i=0 ; i<m_CommandData.DataInfoList.size() ; i++) {
//                            LOGD("m_pDataInfo[%d].functionStatusAmount:%lu", i, m_CommandData.DataInfoList[i]->functionStatusList.size());
//                            
//                            for (int j=0 ; j<m_CommandData.DataInfoList[i]->functionStatusList.size() ; j++) {
//                                LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCode:%d", i, j, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode);
//                                LOGD("type:%d", type);
//                                LOGD("aid:%d", aid);
//                                LOGD("functionCode:%d", functionCode);
//                                
//                                //                                    if (// TODO type == Accessory_Type_Air_Conditioner &&
//                                //                                        aid == m_CommandData.DataInfoList[i]->aid &&
//                                //                                        // functionCode 詢問狀態 = 修改狀態 - 1
//                                //                                        //              修改狀態 = 詢問狀態 + 1
//                                //                                        functionCode - 1 == m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode)
//                                //                                    {
//                                //
//                                //                                        LOGD("functionCodeAmount:%d", functionCodeAmount);
//                                //                                        LOGD("m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size() = %lu", m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size());
//                                //
//                                //                                        // 設定數量較少
//                                //                                        if (functionCodeAmount < m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size())
//                                //                                        {
//                                //                                            for (int y=0 ; y<m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; y++) {
//                                //                                                // 清空
//                                //                                                m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = NULL;
//                                //                                            }
//                                //
//                                //                                            // 設定
//                                //                                            for (int y=0 ; y<functionCodeAmount ; y++) {
//                                //                                                unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
//                                //                                                LOGD("y:%d transferCode:%d", y, transferCode);
//                                //
//                                //                                                m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
//                                //                                            }
//                                //                                        }
//                                //                                        // 設定數量較多
//                                //                                        else if (functionCodeAmount > m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
//                                //                                            // 設定
//                                //                                            for (int y=0 ; y<functionCodeAmount ; y++) {
//                                //                                                unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
//                                //                                                LOGD("y:%d transferCode:%d", y, transferCode);
//                                //
//                                //                                                if (y + 1 > m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
//                                //                                                    addFunctionCode(m_CommandData.DataInfoList[i]->functionStatusList[j], transferCode);
//                                //                                                }
//                                //                                                else {
//                                //                                                    m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
//                                //                                                }
//                                //                                            }
//                                //                                        }
//                                //                                        // 設定值數量一樣
//                                //                                        else if (functionCodeAmount == m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size()) {
//                                //                                            // 設定
//                                //                                            for (int y=0 ; y<functionCodeAmount ; y++) {
//                                //                                                unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
//                                //                                                LOGD("y:%d transferCode:%d", y, transferCode);
//                                //
//                                //                                                m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[y]->transferCode = transferCode;
//                                //                                            }
//                                //                                        }
//                                //                                        else {
//                                //                                            LOGE("對應不到");
//                                //                                        }
//                                //
//                                //                                        // amount
//                                //                                        sendDataBuffer[3 - 1] = ++sendAmount;
//                                //
//                                //                                        sendDataBuffer[sendIndex++] = m_CommandData.DataInfoList[i]->aid;
//                                //                                        setValue(sendDataBuffer, &sendIndex, m_CommandData.DataInfoList[i]->type);
//                                //                                        sendDataBuffer[sendIndex++] = functionCode;
//                                //                                        sendDataBuffer[sendIndex++] = m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size();
//                                //
//                                //                                        for (int k=0 ; k<m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
//                                //                                            LOGD("m_pDataInfo[%d].pFunctionStatus[%d].pFunctionCode[%d].transferCode:%d", i, j, k, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
//                                //
//                                //                                            setValue(sendDataBuffer, &sendIndex, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
//                                //                                        }
//                                //
//                                //                                        onCommandRecvCommand28(m_CommandData.DataInfoList[i]->functionStatusList[j]);
//                                //                                    }
//                            }
//                        }
//                    }
//                    
//                    //                        send(channelID, basicData.stage, basicData.operators, sendDataBuffer, sendIndex);
//                    return;
//                } // 30 Device Report To Client Function
//                    
//                    // Add Accessory Items
//                case 19: {
//                    int sendIndex = 0;
//                    BYTE data[MAX_BUFFER_SIZE];
//                    
//                    UBYTE paringStatus = 1;
//                    data[sendIndex++] = paringStatus;
//                    
//                    UBYTE totalCount = 1;
//                    data[sendIndex++] = totalCount;
//                    
//                    UBYTE countIndex = 0;
//                    data[sendIndex++] = countIndex;
//                    
//                    UBYTE amount = 0;
//                    data[sendIndex++] = ++amount;
//                    
//                    // 加入Sensor
//                    //                    TUTKPIRDevice::generatorDataInfoList(m_nMaxAID++, &m_CommandData.DataInfoList, &m_TypeSet);
//                    //                    TUTKSmokeDevice::generatorDataInfoList(m_nMaxAID++, &m_CommandData.DataInfoList, &m_TypeSet);
//                    VtechVirtualGroupDevice::generatorDataInfoList(this);
//                    
//                    // 取最後一個
//                    //                    data[4 - 1] = ++amount;
//                    
//                    int i = (int) m_CommandData.DataInfoList.size() - 1;
//                    setValue(data, &sendIndex, m_CommandData.DataInfoList[i]->aid);
//                    setValue(data, &sendIndex, m_CommandData.DataInfoList[i]->type);
//                    
//                    UBYTE functionAmount = m_CommandData.DataInfoList[i]->functionStatusList.size();
//                    setValue(data, &sendIndex, functionAmount);
//                    
//                    for (int j=0 ; j<m_CommandData.DataInfoList[i]->functionStatusList.size() ; j++) {
//                        LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCode:%d", i, j, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode);
//                        LOGD("m_pDataInfo[%d].pFunctionStatus[%d].functionCodeAmount:%lu", i, j, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size());
//                        setValue(data, &sendIndex, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCode);
//                        UBYTE functionCodeAmount = m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size();
//                        setValue(data, &sendIndex, functionCodeAmount);
//                        
//                        for (int k=0 ; k<m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList.size() ; k++) {
//                            LOGD("m_pDataInfo[%d].pFunctionStatus[%d].pFunctionCode[%d]:%d", i, j, k, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
//                            setValue(data, &sendIndex, m_CommandData.DataInfoList[i]->functionStatusList[j]->functionCodeList[k]->transferCode);
//                        }
//                    }
//                    
//                    sendReportAllWithCommand32(channelID, operators, m_CommandData.DataInfoList[i]->aid, m_CommandData.DataInfoList[i]->type, 1);
//                    
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = data;
//                    binraryParseSendData.dataLength = sendIndex;
//                    parseSendData(&binraryParseSendData);
//                }   break;
//                    
//                    // Remove Accessory Items
//                case 20: {
//                    int recvIndex = 0;
//                    recvIndex = 10 - 1;
//                    
//                    UBYTE totalCount = buffer[recvIndex++];
//                    LOGD("totalCount:%d", totalCount);
//                    
//                    UBYTE countIndex = buffer[recvIndex++];
//                    LOGD("countIndex:%d", countIndex);
//                    
//                    UBYTE amount = buffer[recvIndex++];
//                    LOGD("amount:%d", amount);
//                    
//                    set<UBYTE> aidSet;
//                    for (int i=0 ; i<amount ; i++) {
//                        UBYTE aid = buffer[recvIndex++];
//                        LOGD("aid:%d", aid);
//                        aidSet.insert(aid);
//                    }
//                    //                    sort(aidSet.begin(), aidSet.end());
//                    
//                    vector<int> resultAidList;
//                    vector<unsigned int> resultTypeList;
//                    vector<int> resultResponseList;
//                    map<int, bool> resultTypeMap;
//                    
//                    for (set<UBYTE>::iterator it = aidSet.begin() ; it != aidSet.end() ; it++) {
//                        for (int i=(int)m_CommandData.DataInfoList.size()-1 ; i>=0 ; i--) {
//                            LOGD("(*it):%d", (*it));
//                            LOGD("m_CommandData.DataInfoList[%d]->aid:%d", i, m_CommandData.DataInfoList[i]->aid);
//                            
//                            if (m_CommandData.DataInfoList[i]->aid == (*it)) {
//                                LOGD("m_CommandData.DataInfoList[i]->type:%d", m_CommandData.DataInfoList[i]->type);
//                                resultTypeMap.insert( std::pair<int, bool>(m_CommandData.DataInfoList[i]->type, true) );
//                                
//                                resultAidList.push_back((*it));
//                                resultTypeList.push_back(m_CommandData.DataInfoList[i]->type);
//                                resultResponseList.push_back(1);
//                                
//                                m_CommandData.DataInfoList.erase(m_CommandData.DataInfoList.begin() + i);
//                                break;
//                            }
//                        }
//                    }
//                    
//                    // 檢查型態是否還存在
//                    for (map<int, bool>::iterator it = resultTypeMap.begin() ; it != resultTypeMap.end() ; it++) {
//                        LOGD("it->first:%d", it->first);
//                        
//                        for (int i=(int)m_CommandData.DataInfoList.size()-1 ; i>=0 ; i--) {
//                            LOGD("type:%d", m_CommandData.DataInfoList[i]->type);
//                            
//                            // 已存在
//                            if (m_CommandData.DataInfoList[i]->type == it->first) {
//                                LOGD("it->first:%d", it->first);
//                                
//                                it->second = false;
//                            }
//                        }
//                    }
//                    
//                    // 設定型態不存在的刪除
//                    for (map<int, bool>::iterator it = resultTypeMap.begin() ; it != resultTypeMap.end() ; it++) {
//                        if (it->second == true) {
//                            m_CommandData.TypeSet.erase(it->first);
//                        }
//                    }
//                    
//                    int sendIndex = 0;
//                    UBYTE sendDataBuffer[MAX_BUFFER_SIZE];
//                    
//                    UBYTE sendTotalCount = 1;
//                    sendDataBuffer[sendIndex++] = sendTotalCount;
//                    
//                    UBYTE sendCountIndex = 0;
//                    sendDataBuffer[sendIndex++] = sendCountIndex;
//                    
//                    UBYTE sendAmount = resultAidList.size();
//                    sendDataBuffer[sendIndex++] = sendAmount;
//                    
//                    for (int i=0 ; i<resultAidList.size() ; i++) {
//                        sendDataBuffer[sendIndex++] = resultAidList[i];
//                    }
//                    
//                    // 上報機制
//                    sendReportAllWithCommand32(channelID, operators, (int)resultAidList.size(), &resultAidList[0], &resultTypeList[0], &resultResponseList[0]);
//                    
//                    JsonRDTClientCommand_ParseSendData binraryParseSendData;
//                    binraryParseSendData.channelID = channelID;
//                    binraryParseSendData.pData = sendDataBuffer;
//                    binraryParseSendData.dataLength = sendIndex;
//                    parseSendData(&binraryParseSendData);
//                }   break;
//                    
//                    // Get All Type And Accessory Items
//                case 31: {
//                    int recvIndex = 10 - 1;
//                    
//                    UBYTE totalCount = buffer[recvIndex++];
//                    UBYTE countIndex = buffer[recvIndex++];
//                    UBYTE amount = buffer[recvIndex++];
//                    LOGD("totalCount:%d", totalCount);
//                    LOGD("countIndex:%d", countIndex);
//                    LOGD("amount:%d", amount);
//                    
//                    // 取得接收的資料
//                    for (int x=0 ; x<amount ; x++) {
//                        UBYTE aid = buffer[recvIndex++];
//                        unsigned int type = (unsigned int) Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 4);
//                        BYTE functionAmount = buffer[recvIndex++];
//                        
//                        LOGD("aid:%d", aid);
//                        LOGD("type:%d", type);
//                        LOGD("functionAmount:%d", functionAmount);
//                        
//                        for (int y=0 ; y<functionAmount ; y++) {
//                            UBYTE functionCode = buffer[recvIndex++];
//                            UBYTE functionCodeAmount = buffer[recvIndex++];
//                            
//                            LOGD("functionCode:%d", functionCode);
//                            LOGD("functionCodeAmount:%d", functionCodeAmount);
//                            
//                            for (int z=0 ; z<functionCodeAmount ; z++) {
//                                unsigned short transferCode = Utility::bytes2UnsignedLongWithBeginData(buffer, &recvIndex, 2);
//                                LOGD("transferCode:%d", transferCode);
//                            }
//                        }
//                        
//                    }
//                    
//                    break;
//                }
//                    
//            }
//        }
//    }
//    
//    // 呼叫子類別
//    JsonRDTClientCommand_CommandRecvData commandRecvData;
//    commandRecvData.channelID = channelID;
//    commandRecvData.pBuffer = buffer;
//    commandRecvData.totalLength = totalLength;
//    m_pCommandEvent->onCommandRecvData(&commandRecvData);
}
