//
//  BinraryRDTClientCommand.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/21.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "BinraryRDTClientCommand.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "Common.hpp"
#include "Utility.hpp"
#include "AccessoryTypeEnum.hpp"
#include "IOTCAPIs.h"
#include "RDTAPIs.h"
#include "BinraryRDTServerConnect.hpp"

BinraryRDTClientCommand::BinraryRDTClientCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData) : BinraryRDTCommand(pCommandEvent, pCommandHardwardEvent, pConnect, pCommandData)
{
    LOGD("BinraryRDTClientCommand");
    
    pthread_t pThreadInput;
    pthread_create(&pThreadInput, NULL, &BinraryRDTClientCommand::threadInput, (void*)this);
}

#pragma mark - ConnectEvent

void BinraryRDTClientCommand::onConnectRecvData(ConnectRecvData* pConnectRecvData)
{
    BinraryRDTServerConnect_ConnectRecvData* pBinraryConnectRecvData = (BinraryRDTServerConnect_ConnectRecvData*) pConnectRecvData;
    BinraryRDTClientCommand_ParseRecvData* pBinraryParseRecvData = (BinraryRDTClientCommand_ParseRecvData*) pBinraryConnectRecvData;
    
    parseRecvData(pBinraryParseRecvData);
}

#pragma mark - Thread

void* BinraryRDTClientCommand::threadInput(void *arg)
{
    BinraryRDTClientCommand* pBinraryRDTClientCommand = (BinraryRDTClientCommand*) arg;
    
    char pInput;
    while(true) {
        LOGD("請輸入一個字元:");
        cin >> pInput;
        LOGD("input:%c", pInput);
        
        LOGD("===================================================================================================================================");
        int count = 0;
        for (set<int>::iterator it = pBinraryRDTClientCommand->m_nChannelIDList.begin() ; it!=pBinraryRDTClientCommand->m_nChannelIDList.end() ; it++) {
            LOGD("m_nChannelIDList[%d]:%d", count++, *it);
        }
        LOGD("===================================================================================================================================");
        
        if (count > 0) {
            set<int>::iterator it = pBinraryRDTClientCommand->m_nChannelIDList.end();
            it--;
            
            BYTE buffer[MAX_BUFFER_SIZE];
            BinraryRDTClientCommand_ParseSendData parseSendData;
            parseSendData.channelID = *it;
            parseSendData.stage = 5;
            parseSendData.operators = 31;
            parseSendData.pData = buffer;
            parseSendData.dataLength = 0;
            pBinraryRDTClientCommand->parseSendData(&parseSendData);
            
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
            //        pBinraryRDTClientCommand->sendReportWithCommand30(0, &functionInfoList);
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

#pragma mark - Command

void BinraryRDTClientCommand::parseSendData(ParseSendData* pParseSendData) throw (RDTException)
{
    BinraryRDTClientCommand_ParseSendData* pBinraryCommandRecvData = (BinraryRDTClientCommand_ParseSendData*) pParseSendData;
    
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
        throw RDTException(__PRETTY_FUNCTION__, __LINE__, ret);
    }
}

void BinraryRDTClientCommand::recvData(int channelID, BYTE* buffer, int totalLength)
{
    LOGD("recvData");
    
    Utility::printData(__PRETTY_FUNCTION__, __LINE__, buffer, totalLength);
}

void BinraryRDTClientCommand::parseRecvData(ParseRecvData* pParseRecvData)
{
    BinraryRDTClientCommand_ParseRecvData* pBinraryParseRecvData = (BinraryRDTClientCommand_ParseRecvData*) pParseRecvData;
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
