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
//            Json::Value array;
            Json::Value item;
            
            unsigned int serno = 87654321;
            root["serno"] = serno;
            
//            root["operation"] = "read";
//            root["target"] = "/accessory/0/product_code/";
            
//            root["operation"] = "read";
//            root["target"] = "/accessory/0/product_name/";
            
            // 新增accessory
//            root["operation"] = "create";
//            root["target"] = "/accessory/";
            
            // 刪除accessory
//            root["operation"] = "delete";
//            root["target"] = "/accessory/1/";
            
            // 更新accessory
//            root["operation"] = "update";
//            root["target"] = "/accessory/1/function_code/switch/value/1";
            
//            root["target"] = "[/accessory/1/function_code/switch/value/1, /accessory/2/function_code/switch/value/1]";
//            root["target"] = "function_code/switch/value/1";
//            root["target"] = "/accessory/1/";
            
//            root["target"] = "UPDATE FunctionCode SET value = 1 where accessory_id = 1";
            
//            root["target"] = "[/accessory/1/function_code/switch/1, /accessory/2/function_code/switch/1]";
//            root["target"] = "AID:1/FNC:switch:1";
//            root["target"] = "AID:1&FNC:switch:1;AID:2&FNC:switch:1";
            
            // version 2.1
            root["respID"] = 1;
            root["function"] = "read";
            item["List"] = "ListAccessory";
            root["If"] = item;
            
            // 新增group
//            root["operation"] = "create";
//            root["target"] = "/group/";
            
            // 刪除group
//            root["operation"] = "delete";
//            root["target"] = "/group/1/";
            
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

    LOGD("Binrary 資料");
    Utility::printData(__PRETTY_FUNCTION__, __LINE__, buffer, totalLength);
    
    // json抓取位置
    const int span = 10; // 開頭偏移量
    char* json = (char*) (buffer + span);
    
    // 清除最後header end 0x03 0x04
    json[totalLength-1-span] = NULL;
    json[totalLength-2-span] = NULL;
    
    Utility::printData(__PRETTY_FUNCTION__, __LINE__, (BYTE*) json, totalLength - span - 2); // -2 最後兩個
    
    //    LOGD("json binrary 資料");
    //    Utility::printData(__PRETTY_FUNCTION__, __LINE__, (BYTE*)json, jsonLen-2);
    
    LOGD("JSON長度:%d", totalLength - span - 2); // -2 最後兩個
    LOGD("JSON資料:%s", json);
    
//    LOGD("Binrary 資料");
//    Utility::printData(__PRETTY_FUNCTION__, __LINE__, (BYTE*)json, totalLength-2);
}
