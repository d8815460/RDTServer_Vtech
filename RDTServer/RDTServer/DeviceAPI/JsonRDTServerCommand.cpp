//
//  JsonRDTServerCommand.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/21.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "JsonRDTServerCommand.hpp"
#include <iostream>
#include <cstring>
#include <unistd.h>
#include "Common.hpp"
#include "Utility.hpp"
#include "IOTCAPIs.h"
#include "RDTAPIs.h"
#include "BinraryRDTServerConnect.hpp"
#include "AccessoryTypeEnum.hpp"

JsonRDTServerCommand::JsonRDTServerCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData) : JsonRDTCommand(pCommandEvent, pCommandHardwardEvent, pConnect, pCommandData)
{
    LOGD("JsonRDTServerCommand");
    
//    m_isSimulator = true;
    
    pthread_t pThreadInput;
    pthread_create(&pThreadInput, NULL, &JsonRDTServerCommand::threadInput, (void*)this);
}

#pragma mark - ConnectEvent

void JsonRDTServerCommand::onConnectRecvData(ConnectRecvData* pConnectRecvData)
{
    BinraryRDTServerConnect_ConnectRecvData* pBinraryConnectRecvData = (BinraryRDTServerConnect_ConnectRecvData*) pConnectRecvData;
    JsonRDTServerCommand_ParseRecvData* pJsonParseRecvData = (JsonRDTServerCommand_ParseRecvData*) pBinraryConnectRecvData;
    
    parseRecvData(pJsonParseRecvData);
}

#pragma mark - Thread

void* JsonRDTServerCommand::threadInput(void *arg)
{
    JsonRDTServerCommand* pJsonRDTServerCommand = (JsonRDTServerCommand*) arg;
    
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
        for (set<int>::iterator it = pJsonRDTServerCommand->m_nChannelIDList.begin() ; it!=pJsonRDTServerCommand->m_nChannelIDList.end() ; it++) {
            LOGD("m_nChannelIDList[%d]:%d", count++, *it);
        }
        LOGD("===================================================================================================================================");
        
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
//        pJsonRDTServerCommand->sendReportWithCommand30(0, &functionInfoList);
        
        //        int count = 0;
        //        for (set<int>::iterator it = pJsonRDTServerConnect->m_nChannelIDList.begin() ; it!=pJsonRDTServerConnect->m_nChannelIDList.end() ; it++) {
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

#pragma mark - Protected Method

void JsonRDTServerCommand::processCommandTarget(const Json::Value& inJsonObject, Json::Value& outJsonObject) throw (CommandException)
{
    string target = inJsonObject["target"].asString();
    string operation = inJsonObject["operation"].asString();
    
    // vertify
    
    if (target.find("product_code") != std::string::npos) {
        CommandHardwardRecv_ProductCode commandHardwardRecv_ProductCode;
        m_pCommandHardwardEvent->onCommandHardwardRecv_ProductCode(&commandHardwardRecv_ProductCode);
        
        // 上報通知
//        m_pCommandHardwardEvent->onCommandHardwardNotify(<#CommandHardwardNotifyData *pCommandHardwardNotifyData#>);
        
        // 輸出 JSON
        Json::Value arraryItems;
        Json::Value arrayObject;
        arraryItems["index"] = "0";
        arraryItems["value"] = commandHardwardRecv_ProductCode.productCode;
        arrayObject.append(arraryItems);
        outJsonObject["response"] = arrayObject;
    }
    else if (target.find("product_name") != std::string::npos) {
        CommandHardwardRecv_ProductName commandHardwardRecv_ProductName;
        m_pCommandHardwardEvent->onCommandHardwardRecv_ProductName(&commandHardwardRecv_ProductName);
        
        // 上報通知
//        m_pCommandHardwardEvent->onCommandHardwardNotify(<#CommandHardwardNotifyData *pCommandHardwardNotifyData#>);
        
        // 輸出 JSON
        Json::Value arraryItems;
        Json::Value arrayObject;
        arraryItems["index"] = "0";
        arraryItems["value"] = commandHardwardRecv_ProductName.productName;
        arrayObject.append(arraryItems);
        outJsonObject["response"] = arrayObject;
    }
    else if (target.find("accessory") != std::string::npos) {
        // 新增
        if (operation.find("create") != std::string::npos) {
            AccessoryData* pAccessoryData = new AccessoryData();
//            pAccessoryData->print();
            CommandHardwardRecv_CreateItems commandHardwardRecv_CreateItems;
            commandHardwardRecv_CreateItems.dataType = DataType_Accessory;
            commandHardwardRecv_CreateItems.pBaseData = pAccessoryData;
            m_pCommandHardwardEvent->onCommandHardwardRecv_CreateItem(&commandHardwardRecv_CreateItems);
            pAccessoryData->print();
            
            m_accessoryList.push_back(pAccessoryData);
        }
        // 刪除
        else if (operation.find("delete") != std::string::npos) {
            size_t pos2 = target.rfind("/") - 1;
            size_t pos1 = target.rfind("/", pos2);                                                                 
            string number = target.substr(pos1 + 1, pos2 - pos1);
            int accessoryId = atoi(number.c_str());
            CommandHardwardRecv_DeleteItems commandHardwardRecv_DeleteItems;
            commandHardwardRecv_DeleteItems.dataType = DataType_Accessory;
            commandHardwardRecv_DeleteItems.id = accessoryId;
            m_pCommandHardwardEvent->onCommandHardwardRecv_DeleteItems(&commandHardwardRecv_DeleteItems);
//            m_accessoryList.erase();
        }
        // 查詢
        else if (operation.find("read") != std::string::npos) {
            CommandHardwardRecv_ReadItems commandHardwardRecv_ReadItems;
            commandHardwardRecv_ReadItems.dataType = DataType_Accessory;
//            commandHardwardRecv_ReadItems.m_accessoryList
            m_pCommandHardwardEvent->onCommandHardwardRecv_ReadItems(&commandHardwardRecv_ReadItems);
        }
        // 修改
        else if (operation.find("update") != std::string::npos) {
            throw CommandException(__PRETTY_FUNCTION__, __LINE__, CommandException_ErrorCode_No_Match_Command_Operation);
        }
        else {
            throw CommandException(__PRETTY_FUNCTION__, __LINE__, CommandException_ErrorCode_No_Match_Command_Operation);
        }
    }
//    else {
//        LOGE("processCommandTarget Error");
//        throw CommandException(__PRETTY_FUNCTION__, __LINE__, CommandException_ErrorCode_No_Match_Command_Target);
//    }
}

#pragma mark - Command

void JsonRDTServerCommand::recvData(int channelID, BYTE* buffer, int totalLength)
{
//    LOGD("recvData");
    
//    LOGD("Binrary 資料");
//    Utility::printData(__PRETTY_FUNCTION__, __LINE__, buffer, totalLength);
    
    // 取得json的位置
    char* json = (char*) (buffer + 11 - 1);
    int jsonLen = (int) strlen(json);
    
    // 清除最後header end 0x03 0x04
    json[jsonLen-1] = NULL;
    json[jsonLen-2] = NULL;
    
//    LOGD("JSON 接收 Binrary 資料");
//    Utility::printData(__PRETTY_FUNCTION__, __LINE__, (BYTE*)json, jsonLen-2);
//    
//    LOGD("JSON接收長度:%d", jsonLen);
    LOGD("JSON接收資料:%s", json);
    
    Json::Reader reader;
    Json::Value inJsonObject;
    Json::Value outJsonObject;
    if (reader.parse(json, inJsonObject))
    {
        processCommandTarget(inJsonObject, outJsonObject);
        
        // Common
        outJsonObject["serno"] = inJsonObject["serno"];
        outJsonObject["operation"] = "read";
        outJsonObject["target"] = inJsonObject["target"];
        
        // Version
        char version[20];
        sprintf(version, "%d.%d.%d", m_CommandData.version1, m_CommandData.version2, m_CommandData.version3);
        //    LOGD("version:%s", version);
        outJsonObject["version"] = version;
        
        // Error Code
        outJsonObject["error_code"] = 0;
        
        CommandHardwardRecvJsonData commandHardwardRecvJsonData;
        commandHardwardRecvJsonData.pJsonObject = &outJsonObject;
        m_pCommandHardwardEvent->onCommandHardwardRecvJson(&commandHardwardRecvJsonData);
    }
    
    set<int>::iterator it = m_nChannelIDList.end();
    it--;
    
    std::string jsonString = outJsonObject.toStyledString();
    LOGD("JSON傳送資料:%s", jsonString.c_str());
    
    JsonRDTServerCommand_ParseSendData jsonParseSendData;
    jsonParseSendData.channelID = *it;
    jsonParseSendData.serno = outJsonObject["serno"].asUInt();
    jsonParseSendData.totalCount = 1;
    jsonParseSendData.count = 1;
    jsonParseSendData.pData = (BYTE*) jsonString.c_str();
    jsonParseSendData.dataLength = (int) jsonString.length();
    parseSendData(&jsonParseSendData);
}
