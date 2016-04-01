//
//  JsonRDTServerCommand.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/21.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "JsonRDTServerCommand.hpp"
#include <iostream>
#include <unistd.h>
#include <string.h>
#include "Common.hpp"
#include "Utility.hpp"
#include "IOTCAPIs.h"
#include "RDTAPIs.h"
#include "BinraryRDTServerConnect.hpp"

#include "AccessoryTypeEnum.hpp"
#include "AccessoryDao.hpp"
#include "ElementDao.hpp"
#include "ElementNoDao.hpp"
#include "VtechHardwareException.hpp"

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

#pragma mark - Method

std::string JsonRDTServerCommand::findWord(std::string& string, const std::string& word)
{
    size_t startPos = string.find(word) + word.size() + 1;
    if (startPos != std::string::npos) {
        size_t endPos = string.find("/", startPos);
        return string.substr(startPos, endPos - startPos);
    }
    
    return "";
}

#pragma mark - JsonRDTServerCommand

void JsonRDTServerCommand::processCommandTarget(Json::Value& inJsonObject, Json::Value& outJsonObject) throw (CommandException)
{
    string function = inJsonObject["Function"].asString();
    Json::Value IfObject = inJsonObject["If"];
    
    LOGD("Function:%s", function.c_str());
    
    // 找出key
    //        Json::Value::Members members = IfKey.getMemberNames();
    //        for (int j=0 ; j<members.size() ; j++) {
    //            LOGD("key:%s", members[j].c_str());
    //        }
    
    CommandBase* pCommandBase = NULL;
    
    // 讀取
    if (function.find("read") != std::string::npos) {
        if (IfObject.isMember("List")) {
            std::string value = IfObject["List"].asString();
            
            if (value.find("ListAccessory") != std::string::npos) {
                // 讀取Accessory
                shared_ptr<vector<shared_ptr<Pojo>>> pojoList = AccessoryDao::readAll();
                
                // 寫入至輸出
                Utility::pojoListToJson(inJsonObject, outJsonObject, pojoList);
//                LOGD("產生json = \n%s", outJsonObject.toStyledString().c_str());
                
                pCommandBase = new CommandHardwardRecv_ReadItems();
                CommandHardwardRecv_ReadItems* pItems = (CommandHardwardRecv_ReadItems*) pCommandBase;
                pItems->dataType = DataType_Accessory;
                pItems->pojoList = pojoList;
                m_pCommandHardwardEvent->onCommandHardwardRecv_ReadItems(pItems);
            }
        }
        else if (IfObject.isMember("AID")) {
            Json::Value AIDArray = IfObject["AID"];
            
            // 查詢所有accessories, AID = [-1]
            if (AIDArray.size() == 1 && AIDArray[0] == -1) {
                // 讀取Accessory
                shared_ptr<vector<shared_ptr<Pojo>>> pojoList = AccessoryDao::readAll();
                
                // 寫入至輸出
                Utility::pojoListToJson(inJsonObject, outJsonObject, pojoList);
//                LOGD("產生json = \n%s", outJsonObject.toStyledString().c_str());
                
                pCommandBase = new CommandHardwardRecv_ReadItems();
                CommandHardwardRecv_ReadItems* pItems = (CommandHardwardRecv_ReadItems*) pCommandBase;
                pItems->dataType = DataType_Accessory;
                pItems->pojoList = pojoList;
                m_pCommandHardwardEvent->onCommandHardwardRecv_ReadItems(pItems);
            }
            else {
                vector<int> AIDList;
                for (int i=0 ; i<AIDArray.size() ; i++) {
                    int AID = AIDArray[i].asInt();
                    AIDList.push_back(AID);
                }
                
                // 讀取Accessory
                shared_ptr<vector<shared_ptr<Pojo>>> pojoList = AccessoryDao::read(AIDList);
                
                // 寫入至輸出
                Utility::pojoListToJson(inJsonObject, outJsonObject, pojoList);
                
                pCommandBase = new CommandHardwardRecv_ReadItems();
                CommandHardwardRecv_ReadItems* pItems = (CommandHardwardRecv_ReadItems*) pCommandBase;
                pItems->dataType = DataType_Accessory;
                pItems->pojoList = pojoList;
                m_pCommandHardwardEvent->onCommandHardwardRecv_ReadItems(pItems);
            }
        }
    }
    // 新增或修改
    else if (function.find("write") != std::string::npos) {
        if (IfObject.isMember("AID")) {
            Json::Value AIDArray = IfObject["AID"];
            
            // 新增accessory, AID = [-1]
            if (AIDArray.size() == 1 && AIDArray[0] == -1) {
                pCommandBase = new CommandHardwardRecv_CreateItems();
                CommandHardwardRecv_CreateItems* pItems = (CommandHardwardRecv_CreateItems*) pCommandBase;
                pItems->dataType = DataType_Accessory;
                m_pCommandHardwardEvent->onCommandHardwardRecv_CreateItem(pItems);
                
                // 新增成功
                if (pItems->errorCode == 0) {
                    for (shared_ptr<Pojo> pPojo : *pItems->pojoList) {
                        shared_ptr<AccessoryPojo>& pAccessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
                        
                        AccessoryDao::create(*pAccessoryPojo);
                        Utility::pojoToJson(inJsonObject, outJsonObject, pPojo);
                    }
                }
            }
        }
    }
    // 刪除
    else if (function.find("delete") != std::string::npos) {
        if (IfObject.isMember("AID")) {
            Json::Value AIDArray = IfObject["AID"];
            
            vector<int> AIDList;
            for (int i=0 ; i<AIDArray.size() ; i++) {
                int AID = AIDArray[i].asInt();
                AIDList.push_back(AID);
                
                pCommandBase = new CommandHardwardRecv_DeleteItems();
                CommandHardwardRecv_DeleteItems* pItems = (CommandHardwardRecv_DeleteItems*) pCommandBase;
                pItems->dataType = DataType_Accessory;
                pItems->pIDList = &AIDList;
                m_pCommandHardwardEvent->onCommandHardwardRecv_DeleteItems(pItems);
                
                // 刪除成功
                if (pItems->errorCode == 0) {
                    pCommandBase->errorCode = AccessoryDao::deleteWithAIDList(AIDList);
                }
            }
        }
    }
    
    // Common
    outJsonObject["SenderInfo"] = inJsonObject;
    outJsonObject["ErrorCode"] = pCommandBase->errorCode;
    
    delete pCommandBase;
    
//    // vertify
//    // 辨識最上面一層
//    if (target.find("product_code") != std::string::npos) {
//        CommandHardwardRecv_ProductCode commandHardwardRecv_ProductCode;
//        m_pCommandHardwardEvent->onCommandHardwardRecv_ProductCode(&commandHardwardRecv_ProductCode);
//        
//        // 上報通知
////        m_pCommandHardwardEvent->onCommandHardwardNotify(CommandHardwardNotifyData *pCommandHardwardNotifyData);
//        
//        // 輸出 JSON
//        Json::Value arraryItems;
//        Json::Value arrayObject;
//        arraryItems["index"] = "0";
//        arraryItems["value"] = commandHardwardRecv_ProductCode.productCode;
//        arrayObject.append(arraryItems);
//        outJsonObject["response"] = arrayObject;
//    }
//    else if (target.find("product_name") != std::string::npos) {
//        CommandHardwardRecv_ProductName commandHardwardRecv_ProductName;
//        m_pCommandHardwardEvent->onCommandHardwardRecv_ProductName(&commandHardwardRecv_ProductName);
//        
//        // 上報通知
////        m_pCommandHardwardEvent->onCommandHardwardNotify(CommandHardwardNotifyData *pCommandHardwardNotifyData);
//        
//        // 輸出 JSON
//        Json::Value arraryItems;
//        Json::Value arrayObject;
//        arraryItems["index"] = "0";
//        arraryItems["value"] = commandHardwardRecv_ProductName.productName;
//        arrayObject.append(arraryItems);
//        outJsonObject["response"] = arrayObject;
//    }
//    else if (target.find("accessory") != std::string::npos) {
//        std::string accessory = findWord(target, std::string("accessory"));
//        CommandBase* pCommand = NULL;
//        
//        // 新增
//        if (operation == "create") {
//            AccessoryData* pAccessoryData = new AccessoryData();
////            pAccessoryData->print();
//            pCommand = new CommandHardwardRecv_CreateItems();
//            CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems = (CommandHardwardRecv_CreateItems*) pCommand;
//            pCommandHardwardRecv_CreateItems->dataType = DataType_Accessory;
//            pCommandHardwardRecv_CreateItems->pBaseData = pAccessoryData;
//            m_pCommandHardwardEvent->onCommandHardwardRecv_CreateItem(pCommandHardwardRecv_CreateItems);
//            pAccessoryData->print();
//            
//            m_accessoryList.push_back(pAccessoryData);
//        }
//        // 刪除
//        else if (operation == "delete") {
//            size_t pos2 = target.rfind("/") - 1;
//            size_t pos1 = target.rfind("/", pos2);                                                                 
//            string number = target.substr(pos1 + 1, pos2 - pos1);
//            int accessoryId = stoi(number.c_str());
//            
//            pCommand = new CommandHardwardRecv_DeleteItems();
//            CommandHardwardRecv_DeleteItems* pDeleteItems = (CommandHardwardRecv_DeleteItems*) pCommand;
//            pDeleteItems->dataType = DataType_Accessory;
//            pDeleteItems->id = accessoryId;
//            m_pCommandHardwardEvent->onCommandHardwardRecv_DeleteItems(pDeleteItems);
////            m_accessoryList.erase();
//        }
//        // 查詢
//        else if (operation == "read") {
//            CommandHardwardRecv_ReadItems readItems;
//            pCommand = &readItems;
//            readItems.dataType = DataType_Accessory;
////            commandHardwardRecv_ReadItems.m_accessoryList
//            m_pCommandHardwardEvent->onCommandHardwardRecv_ReadItems(&readItems);
//        }
//        // 修改
//        else if (operation == "update") {
//            int accessoryId = stoi(accessory.c_str());
//            for (int i=0 ; i<m_accessoryList.size() ; i++) {
//                if (m_accessoryList[i]->accessoryId == accessoryId) {
//                    std::string functionCode = findWord(target, std::string("function_code"));
//                    for (int j=0 ; j<m_accessoryList[i]->functionCodeDataList.size() ; j++) {
//                        if (m_accessoryList[i]->functionCodeDataList[j]->functonCode == "switch") {
//                            std::string valueString = findWord(target, std::string("value"));
////                            LOGD("value:%s", value.c_str());
//                            int value = atoi(valueString.c_str());
//                            
//                            m_accessoryList[i]->functionCodeDataList[j]->functionCodeValueDataList[0]->value = value;
//                            
//                            FunctionCodeValueData* pFunctionCodeValueData = new FunctionCodeValueData();
//                            pFunctionCodeValueData->value = value;
//                            
//                            FunctionCodeData* pFunctionCodeData = new FunctionCodeData();
//                            pFunctionCodeData->functonCode = functionCode;
//                            pFunctionCodeData->functionCodeValueDataList.push_back(pFunctionCodeValueData);
//                            
//                            AccessoryData* pAccessoryData = new AccessoryData();
//                            pAccessoryData->accessoryId = accessoryId;
//                            pAccessoryData->functionCodeDataList.push_back(pFunctionCodeData);
//                            
//                            pCommand = new CommandHardwardRecv_UpdateItems();
//                            CommandHardwardRecv_UpdateItems* pUpdateItems = (CommandHardwardRecv_UpdateItems*) pCommand;
//                            pUpdateItems->dataType = DataType_Accessory;
//                            pUpdateItems->baseDataList.push_back(pAccessoryData);
//                            
//                            m_pCommandHardwardEvent->onCommandHardwardRecv_UpdateItems(pUpdateItems);
//                            
//                            break;
//                        }
//                    }
//                }
//            }
//        }
//        else {
//            throw CommandException(__PRETTY_FUNCTION__, __LINE__, CommandException_ErrorCode_No_Match_Command_Operation);
//        }
//        
//        // 發生錯誤
//        if (pCommand->errorCode != 0) {
//            // Error Code
//            outJsonObject["error_code"] = pCommand->errorCode;
//        }
//        else {
//            outJsonObject["error_code"] = 0;
//        }
//        delete pCommand;
//    }
    
//    else {
//        LOGE("processCommandTarget Error");
//        throw CommandException(__PRETTY_FUNCTION__, __LINE__, CommandException_ErrorCode_No_Match_Command_Target);
//    }
}

#pragma mark - Command

void JsonRDTServerCommand::recvData(int channelID, BYTE* buffer, int totalLength)
{
//    LOGD("recvData");
    
    LOGD("Binrary 資料");
    Utility::printData(__PRETTY_FUNCTION__, __LINE__, buffer, totalLength);
    
    // 取得json的位置
    const int span = 10; // 開頭偏移量
    char* json = (char*) (buffer + span);
    
    // 清除最後header end 0x03 0x04
    json[totalLength-1-span] = NULL;
    json[totalLength-2-span] = NULL;
    
    LOGD("JSON 接收 Binrary 資料");
    Utility::printData(__PRETTY_FUNCTION__, __LINE__, (BYTE*)json, totalLength - span - 2);
    
    LOGD("JSON接收長度:%d", totalLength - span - 2);
    LOGD("JSON接收資料:%s", json);
    
    Json::Reader reader;
    Json::Value inJsonObject;
    Json::Value outJsonObject;
    if (reader.parse(json, inJsonObject))
    {
        processCommandTarget(inJsonObject, outJsonObject);
        
        // Common
//        outJsonObject["serno"] = inJsonObject["serno"];
//        outJsonObject["function"] = inJsonObject["function"];
        
//        // Version
//        char version[20];
//        sprintf(version, "%d.%d.%d", m_CommandData.version1, m_CommandData.version2, m_CommandData.version3);
//        //    LOGD("version:%s", version);
//        outJsonObject["version"] = version;
        
        CommandHardwardRecvJsonData commandHardwardRecvJsonData;
        commandHardwardRecvJsonData.pJsonObject = &outJsonObject;
        m_pCommandHardwardEvent->onCommandHardwardRecvJson(&commandHardwardRecvJsonData);
    }
    else {
        throw CommandException(__PRETTY_FUNCTION__, __LINE__, CommandException_ErrorCode_Json_Formate_Error);
    }
    
    sendJsonData(channelID, outJsonObject);
}
