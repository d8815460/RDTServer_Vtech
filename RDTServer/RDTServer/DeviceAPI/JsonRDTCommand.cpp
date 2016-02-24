//
//  JsonRDTcommand.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/28.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "JsonRDTCommand.hpp"
#include <cstring>
#include <unistd.h>
#include "Common.hpp"
#include "Utility.hpp"
#include "IOTCAPIs.h"
#include "RDTAPIs.h"

#include <stdio.h>
#include <string.h>

JsonRDTCommand::JsonRDTCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData) : Command(pCommandEvent, pCommandHardwardEvent, pConnect, pCommandData)
{
    LOGD("JsonRDTServerCommand");
    
    m_CommandData.version1 = 2;
    m_CommandData.version2 = 0;
    m_CommandData.version3 = 0;
}

void JsonRDTCommand::onConnectCreateClient(ConnectCreateClient* pConnectCreateClient)
{
    JsonRDTCommand_ConnectCreateClient* pJsonConnectCreateClient = (JsonRDTCommand_ConnectCreateClient*) pConnectCreateClient;
    
    m_nChannelIDList.insert(pJsonConnectCreateClient->channelID);
}

void JsonRDTCommand::parseSendData(ParseSendData* pParseSendData)
{
    JsonRDTCommand_ParseSendData* pBinraryCommandRecvData = (JsonRDTCommand_ParseSendData*) pParseSendData;
    
    /* prepare send data */
    int index = 0;
    BYTE buffer[MAX_BUFFER_SIZE];
    memset(buffer, 0, MAX_BUFFER_SIZE);
    // header first 0x01 0x02
    buffer[index++] = 0x01;
    buffer[index++] = 0x02;
    
    // Skip Length
    index += 2;
    
    /* serno */
    setValue(buffer, &index, pBinraryCommandRecvData->serno);
    
    /* totalCount */
    buffer[index++] = pBinraryCommandRecvData->totalCount;
    
    /* count */
    buffer[index++] = pBinraryCommandRecvData->count;
    
    // payload data
    memcpy(buffer + index, pBinraryCommandRecvData->pData, pBinraryCommandRecvData->dataLength);
    index += pBinraryCommandRecvData->dataLength;
    
    // header end   0x03 0x04
    buffer[index++] = 0x03;
    buffer[index++] = 0x04;
    
    // Length
    unsigned short* pLength = (unsigned short*)&buffer[3 - 1];
    *pLength = index - 2 - 2 - 2;       // header first 2 bytes, header end 2 bytes, Length size 2 bytes
    LOGD("length:%d", *pLength);
    
    LOGD("index:%d", index);
    
    LOGD("原始傳送資料");
    Utility::printData(__PRETTY_FUNCTION__, __LINE__, buffer, index);
    int ret = RDT_Write(pBinraryCommandRecvData->channelID, (const char*)buffer, index);
    if (ret < 0) {
        LOGE("RDT_Write failed");
    }
}

void JsonRDTCommand::parseRecvData(ParseRecvData* pParseRecvData)
{
    JsonRDTCommand_ParseRecvData* pJsonParseRecvData = (JsonRDTCommand_ParseRecvData*) pParseRecvData;
    int channelID = pJsonParseRecvData->channelID;
    UBYTE* pBuffer = pJsonParseRecvData->pBuffer;
    int length = pJsonParseRecvData->length;
    
    LOGD("原始接收資料");
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
            fragmentLength = pBuffer[offset + 4] + 4 + 2 + 2;
            
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

bool JsonRDTCommand::isBasicVerificationPass(BYTE *buffer, int length)
{
    // 基本驗證
    if (buffer[0] == 0x01 && buffer[1] == 0x02 &&                                               // header first 0x01 0x02
        buffer[length - 2] == 0x03 && buffer[length - 1] == 0x04)                               // header end   0x03 0x04
    {
        unsigned short* pLength = (unsigned short*)&buffer[2]; // 長度驗證
        if (*pLength == length - 2 - 2 - 2) {       // header first 2 bytes, header end 2 bytes, Length size 2 bytes
            return true;
        }
        
        return false;
    }
    else {
        return false;
    }
}
