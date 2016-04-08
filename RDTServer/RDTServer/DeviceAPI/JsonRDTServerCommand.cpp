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
#include "ElementNODao.hpp"
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
//    Json::Value::Members members = IfKey.getMemberNames();
//    for (int j=0 ; j<members.size() ; j++) {
//        LOGD("key:%s", members[j].c_str());
//    }
    
    CommandBase* pCommandBase = NULL;
    
    // 讀取
    if (function.find("read") != std::string::npos) {
        if (IfObject.isMember("AID")) {
            Json::Value jsonArray = IfObject["AID"];
            
            // 查詢所有accessories, AID = [-1]
            if (jsonArray.size() == 1 && jsonArray[0] == -1) {
                // 讀取Accessory
                shared_ptr<vector<shared_ptr<Pojo>>> pojoList = AccessoryDao::readAll();
                
                // 寫入至json輸出
                Utility::pojoListToJson(inJsonObject, outJsonObject, pojoList);
//                LOGD("產生json = \n%s", outJsonObject.toStyledString().c_str());
                
                pCommandBase = new CommandHardwardRecv_ReadItems();
                CommandHardwardRecv_ReadItems* pItems = (CommandHardwardRecv_ReadItems*) pCommandBase;
                pItems->dataType = DataType_Accessory;
                pItems->pojoList = pojoList;
                m_pCommandHardwardEvent->onCommandHardwardRecv_ReadItems(pItems);
            }
            else {
                string whereSQL = "";
                
                // 依照查詢條件生成Accessory
                vector<ValueObject> voList;
                for (int i=0 ; i<jsonArray.size() ; i++) {
                    int AID = jsonArray[i].asInt();
                    voList.push_back(ValueObject("AID", AID));
                }
                
                whereSQL = Pojo::genInSQL(voList, false);
                
                if (IfObject.isMember("Element")) {
                    Json::Value jsonArray = IfObject["Element"];
                    
                    // 依照查詢條件生成
                    vector<ValueObject> voList;
                    for (int i=0 ; i<jsonArray.size() ; i++) {
                        string Element = jsonArray[i].asString();
                        voList.push_back(ValueObject("Element", Element));
                    }
                    
                    whereSQL.append(Pojo::genInSQL(voList, true));
                }
                
                if (IfObject.isMember("ElementNO")) {
                    Json::Value jsonArray = IfObject["ElementNO"];
                    
                    // 依照查詢條件生成
                    vector<ValueObject> voList;
                    for (int i=0 ; i<jsonArray.size() ; i++) {
                        int ElementNO = jsonArray[i].asInt();
                        voList.push_back(ValueObject("ElementNO", ElementNO));
                    }
                    
                    whereSQL.append(Pojo::genInSQL(voList, true));
                }
                
                Json::Value json;
                shared_ptr<vector<shared_ptr<Pojo>>> pojoList = AccessoryDao::readNestWithWhereSQL(whereSQL);
                
                // 寫入至json輸出
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
            Json::Value jsonArray = IfObject["AID"];
            
            // 新增accessory, AID = [-1]
            if (jsonArray.size() == 1 && jsonArray[0] == -1) {
                pCommandBase = new CommandHardwardRecv_CreateItems();
                CommandHardwardRecv_CreateItems* pItems = (CommandHardwardRecv_CreateItems*) pCommandBase;
                pItems->dataType = DataType_Accessory;
                m_pCommandHardwardEvent->onCommandHardwardRecv_CreateItem(pItems);
                
                // 新增成功
                if (pItems->errorCode == 0) {
                    for (shared_ptr<Pojo> pPojo : *pItems->pojoList) {
                        shared_ptr<AccessoryPojo>& pAccessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
                        
                        // 新增Accessory
                        AccessoryDao::create(*pAccessoryPojo);
                        
                        // 寫入至json輸出
                        Utility::pojoToJson(inJsonObject, outJsonObject, pPojo);
                    }
                }
            }
            else {
                pCommandBase = new CommandHardwardRecv_CreateItems();
                CommandHardwardRecv_CreateItems* pItems = (CommandHardwardRecv_CreateItems*) pCommandBase;
                pItems->dataType = DataType_Accessory;
                m_pCommandHardwardEvent->onCommandHardwardRecv_CreateItem(pItems);
                
                // 新增成功
                if (pItems->errorCode == 0) {
                    string whereSQL = "";
                    
                    // 依照查詢條件生成Accessory
                    vector<ValueObject> voList;
                    for (int i=0 ; i<jsonArray.size() ; i++) {
                        int AID = jsonArray[i].asInt();
                        voList.push_back(ValueObject("AID", AID));
                    }
                    
                    whereSQL = Pojo::genInSQL(voList, false);
                    
                    if (IfObject.isMember("Element")) {
                        Json::Value jsonArray = IfObject["Element"];
                        
                        // 依照查詢條件生成
                        vector<ValueObject> voList;
                        for (int i=0 ; i<jsonArray.size() ; i++) {
                            string Element = jsonArray[i].asString();
                            voList.push_back(ValueObject("Element", Element));
                        }
                        
                        whereSQL.append(Pojo::genInSQL(voList, true));
                    }
                    
                    if (IfObject.isMember("ElementNO")) {
                        Json::Value jsonArray = IfObject["ElementNO"];
                        
                        // 依照查詢條件生成
                        vector<ValueObject> voList;
                        for (int i=0 ; i<jsonArray.size() ; i++) {
                            int ElementNO = jsonArray[i].asInt();
                            voList.push_back(ValueObject("ElementNO", ElementNO));
                        }
                        
                        whereSQL.append(Pojo::genInSQL(voList, true));
                    }
                    
                    LOGD("SQL:%s", whereSQL.c_str());
                    Json::Value json;
                    vector<ValueObject> objList;
                    
                    Json::Value thenObject = inJsonObject["Then"];
                    if (thenObject.isMember("Value")) {
                        string value = thenObject["Value"].asString();
                        objList.push_back(ValueObject("ElementNO", value));
                        AccessoryDao::updateNestWithWhereSQL(whereSQL, objList);
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
    
    // 當DeviceAPI發生錯誤ErrorCode != 0, 就不去抓取硬體的ErrorCode，所以DeviceAPI發生錯誤就已DeviceAPI ErrorCode為主, DeivceAPI沒錯就抓看看硬體的ErrorCode
    if (!outJsonObject["ErrorCode"] || outJsonObject["ErrorCode"] == 0) {
        outJsonObject["ErrorCode"] = pCommandBase->errorCode;
    }
    
    delete pCommandBase;
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
//    LOGD("JSON接收資料:\n%s", json);
    
    Json::Reader reader;
    Json::Value inJsonObject;
    Json::Value outJsonObject;
    if (reader.parse(json, inJsonObject))
    {
        LOGD("inJsonObject:\n%s", inJsonObject.toStyledString().c_str());
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
