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
#include <stdio.h>
#include <string.h>
#include "Common.hpp"
#include "Utility.hpp"
#include "IOTCAPIs.h"
#include "RDTAPIs.h"

// Dao
#include "RoomDao.hpp"
#include "AccessoryDao.hpp"
#include "ElementDao.hpp"
#include "ElementNODao.hpp"

JsonRDTCommand::JsonRDTCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData) : Command(pCommandEvent, pCommandHardwardEvent, pConnect, pCommandData)
{
    LOGD("JsonRDTServerCommand");
    
    m_CommandData.version1 = 2;
    m_CommandData.version2 = 1;
    m_CommandData.version3 = 0;
    
    shared_ptr<vector<shared_ptr<AccessoryPojo>>> pp(new vector<shared_ptr<AccessoryPojo>>);
    m_pAccessoryList = pp;
    
    {
        /* 新增一筆Accessory資料 */
        // param1: fkRoomSerial Room流水號
        // param2: AID代表accessory id
        // param3: Name 一個名字,用於標示目標類型的一種可視化手段
        // oaram4: AccSeq The accessory's sequence , the default value is 0.
        // param5: IconType 會面呈現的Icon所代表的型態，如IPHub
        // param6: Connection 連線狀態，
        // param7: IsGateway is gateway or not
        shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo(1, 1, "PC Home", 1, 1, 1, true));

        // param1: Element 一個元件有單個或多個element NO
        shared_ptr<ElementPojo> pElement1(new ElementPojo("switch"));

        // param1: ElementNO 一個元件的編號
        // param2: Value 由一個字串組成，字串的類型可能是數值，字串或整數，也有可能是其他的。它的類型由Metadata決定一個 key 通常會有一個 value
        // param3: NtfyEnable 是否開啟推播
        shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo(0, "轟天1", true));
        shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo(1, "大鑫1", true));

        pAccessoryPojo->pSubPojoList->push_back(pElement1);
        pElement1->pSubPojoList->push_back(pNO1);
        pElement1->pSubPojoList->push_back(pNO2);

        CommandHardwardSend_UpdateItems items;
        items.dataType = DataType_Accessory;
        items.pPojoList->push_back(pAccessoryPojo);
    }
    {
        /* 新增一筆Accessory資料 */
        // param1: fkRoomSerial Room流水號
        // param2: AID代表accessory id
        // param3: Name 一個名字,用於標示目標類型的一種可視化手段
        // oaram4: AccSeq The accessory's sequence , the default value is 0.
        // param5: IconType 會面呈現的Icon所代表的型態，如IPHub
        // param6: Connection 連線狀態，
        // param7: IsGateway is gateway or not
        shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo(2, 2, "Super", 2, 2, 2, false));
        
        // param1: Element 一個元件有單個或多個element NO
        shared_ptr<ElementPojo> pElement1(new ElementPojo("switch"));
        
        // param1: ElementNO 一個元件的編號
        // param2: Value 由一個字串組成，字串的類型可能是數值，字串或整數，也有可能是其他的。它的類型由Metadata決定一個 key 通常會有一個 value
        // param3: NtfyEnable 是否開啟推播
        shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo(0, "轟天2", true));
        shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo(1, "大鑫2", true));
        
        pAccessoryPojo->pSubPojoList->push_back(pElement1);
        pElement1->pSubPojoList->push_back(pNO1);
        pElement1->pSubPojoList->push_back(pNO2);
        
        CommandHardwardSend_UpdateItems items;
        items.dataType = DataType_Accessory;
        items.pPojoList->push_back(pAccessoryPojo);
    }
}

JsonRDTCommand::~JsonRDTCommand()
{
    m_pAccessoryList->clear();
}

#pragma mark - ConnectEvent

void JsonRDTCommand::onConnectCreateClient(ConnectCreateClient* pConnectCreateClient)
{
    JsonRDTCommand_ConnectCreateClient* pJsonConnectCreateClient = (JsonRDTCommand_ConnectCreateClient*) pConnectCreateClient;
    
    m_nChannelIDList.insert(pJsonConnectCreateClient->channelID);
}

#pragma mark - Command

void JsonRDTCommand::parseSendData(ParseSendData* pParseSendData) throw(RDTException)
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
        throw RDTException(__PRETTY_FUNCTION__, __LINE__, ret);
    }
}

void JsonRDTCommand::parseRecvData(ParseRecvData* pParseRecvData) throw (CommandException)
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
            fragmentLength = pBuffer[offset + 2] + 2 + 2 + 2; // header first 2 bytes, header end 2 bytes, Length size 2 bytes
            
            if (isBasicVerificationPass(pBuffer + offset, fragmentLength) == true) {
                recvData(channelID, pBuffer + offset, fragmentLength);
            }
            else {
                LOGE("封包未符合!");
                throw CommandException(__PRETTY_FUNCTION__, __LINE__, CommandException_ErrorCode_Packet_Not_Match);
            }
            
            offset += fragmentLength;
        } while (length - offset > 0);
        
    }
}

void JsonRDTCommand::commandHardwardSend_CreateItem(CommandHardwardSend_CreateItems* pCommandHardwardRecv_CreateItems)
{
    LOGD("commandHardwardSend_CreateItem");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_CreateItems->dataType) {
        case DataType_Accessory: {
            // 將新增資料填入
        }   break;
            
        default:
            LOGE("對應不到dataType");
            break;
    }
}

void JsonRDTCommand::commandHardwardSend_DeleteItems(CommandHardwardSend_DeleteItems* pCommandHardwardRecv_DeleteItems)
{
    LOGD("commandHardwardSend_DeleteItems");
    
    // 針對特定的硬體刪除關聯
    // 如移除燈的關聯
    switch (pCommandHardwardRecv_DeleteItems->dataType) {
        case DataType_Accessory: {
            // remove pCommandHardwardRecv_DeleteItems->id;
        }
            
        default:
            LOGE("對應不到dataType");
            break;
    }
}

void JsonRDTCommand::commandHardwardSend_ReadItems(CommandHardwardSend_ReadItems* pCommandHardwardRecv_ReadItems)
{
    LOGD("commandHardwardSend_ReadItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_ReadItems->dataType) {
        case DataType_Accessory: {
            // 針對收到的資料做為參考
            shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = (shared_ptr<vector<shared_ptr<Pojo>>>) pCommandHardwardRecv_ReadItems->pPojoList;
            for (shared_ptr<Pojo> pPojo : *pPojoList) {
                shared_ptr<AccessoryPojo>& pAccessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
                
                LOGD("AID:%d", pAccessoryPojo->AID);
                LOGD("iconType:%d", pAccessoryPojo->AccIconType);
            }
        }   break;
            
        default:
            LOGE("對應不到dataType");
            break;
    }
}

void JsonRDTCommand::commandHardwardSend_UpdateItems(CommandHardwardSend_UpdateItems* pCommandHardwardSend_UpdateItems) throw (CommandException)
{
    LOGD("commandHardwardSend_UpdateItems");
    
    switch (pCommandHardwardSend_UpdateItems->dataType) {
        case DataType_Accessory: {
            // 針對收到的資料做為參考
            shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = (shared_ptr<vector<shared_ptr<Pojo>>>) pCommandHardwardSend_UpdateItems->pPojoList;
            for (shared_ptr<Pojo> pPojo : *pPojoList) {
                shared_ptr<AccessoryPojo>& pAccessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
                
                LOGD("AID:%d", pAccessoryPojo->AID);
                LOGD("iconType:%d", pAccessoryPojo->AccIconType);
                
                Json::Value json;
                pAccessoryPojo->toJson(json);
                LOGD("json:%s", json.toStyledString().c_str());
            }
        }   break;
            
        default:
            throw CommandException(__PRETTY_FUNCTION__, __LINE__, CommandException_ErrorCode_DataType_Not_Found);
            break;
    }
}

#pragma mark - JsonRDTCommand

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

#pragma mark - Method

void JsonRDTCommand::sendJsonData(int channelID, Json::Value& jsonObject)
{
    std::string jsonString = jsonObject.toStyledString();
    LOGD("JSON傳送資料:%s", jsonString.c_str());
    
    JsonRDTCommand_ParseSendData jsonParseSendData;
    jsonParseSendData.channelID = channelID;
    jsonParseSendData.serno = jsonObject["serno"].asUInt();
    jsonParseSendData.totalCount = 1;
    jsonParseSendData.count = 1;
    jsonParseSendData.pData = (BYTE*) jsonString.c_str();
    jsonParseSendData.dataLength = (int) jsonString.length();
    parseSendData(&jsonParseSendData);
}
