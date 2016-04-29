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
#include "ServicePojo.hpp"
#include "ElementDao.hpp"
#include "ElementNODao.hpp"
#include "VtechHardwareException.hpp"

/*
 APP <-> 模擬器 <-> HW
 
 obj -> pojo
 
 parse 解析 json2obj
           obj2json -> senderInfo
 
 isSim = true
 新增 -> add
 輸入:AIDList
 輸出:objList, errorCode
 
 修改 -> update
 輸入:objList
 輸出:errorCode
 
 刪除 -> delete
 輸入:AIDList
 輸出:errorCode
 
 查詢 -> select
 1.
 輸入:
 "AID"=-1
 輸出:objList, errorCode
 
 2.
 輸入:
 "AID":[50]
 輸出:objList, errorCode
 
 3.
 輸入:
 "AID":[0]
 輸出:objList, errorCode
 
 4.
 輸入:
 "AID":[0, 1]
 輸出:objList, errorCode
 
 5.
 "AID":[0,1],
 "Element":["switch"],
 "ElementNO":[0,1]
 輸出:objList, errorCode
 
 6.
 "If": {
    "List": "ListAccessory"
 },
 "Then": {
     "ListAccessory": {
        "0": {
            "AccSeq": 4,
            "IsGateway": true,
            "Room": {
                "RoomSeq": 2
            }
        },
        "1": {
            "AccSeq": 2
        }
     }
 }
 輸出:objList, errorCode
 */

#define setIntVO(k) \
    if (vo.key.compare(#k) == 0) { \
        pAccessoryPojo->k = root[vo.key].asInt(); \
        LOGD("k:%d", pAccessoryPojo->k); \
    }

#define setStrVO(k) \
    if (vo.key.compare(#k) == 0) { \
        pAccessoryPojo->k = root[vo.key].asString(); \
        LOGD("k:%s", pAccessoryPojo->k.c_str()); \
    }

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
//                // 讀取Accessory
//                shared_ptr<vector<shared_ptr<Pojo>>> pojoList = AccessoryDao::readAll();
//                
//                // 寫入至json輸出
//                Utility::pojoListToJson(inJsonObject, outJsonObject, pojoList);
//                LOGD("產生json = \n%s", outJsonObject.toStyledString().c_str());
                
                // 填入清單
                pCommandBase = new CommandHardwardRecv_ReadItems();
                CommandHardwardRecv_ReadItems* pItems = (CommandHardwardRecv_ReadItems*) pCommandBase;
                pItems->dataType = DataType_Accessory;
                m_pCommandHardwardEvent->onCommandHardwardRecv_ReadItems(pItems);
                
                // obj2Json
                Utility::pojoListToJson(inJsonObject, outJsonObject, pItems->pPojoList);
            }
            else {
                string whereSQL = "";
                
//                // 依照查詢條件生成Accessory
//                vector<ValueObject> voList;
//                for (int i=0 ; i<jsonArray.size() ; i++) {
//                    int AID = jsonArray[i].asInt();
//                    voList.push_back(ValueObject("AID", AID));
//                }
//                
//                whereSQL = Pojo::genInSQL(voList, false);
//                
//                if (IfObject.isMember("Element")) {
//                    Json::Value jsonArray = IfObject["Element"];
//                    
//                    // 依照查詢條件生成
//                    vector<ValueObject> voList;
//                    for (int i=0 ; i<jsonArray.size() ; i++) {
//                        string Element = jsonArray[i].asString();
//                        voList.push_back(ValueObject("Element", Element));
//                    }
//                    
//                    whereSQL.append(Pojo::genInSQL(voList, true));
//                }
//                
//                if (IfObject.isMember("ElementNO")) {
//                    Json::Value jsonArray = IfObject["ElementNO"];
//                    
//                    // 依照查詢條件生成
//                    vector<ValueObject> voList;
//                    for (int i=0 ; i<jsonArray.size() ; i++) {
//                        int ElementNO = jsonArray[i].asInt();
//                        voList.push_back(ValueObject("ElementNO", ElementNO));
//                    }
//                    
//                    whereSQL.append(Pojo::genInSQL(voList, true));
//                }
//                
//                Json::Value json;
//                shared_ptr<vector<shared_ptr<Pojo>>> pojoList = AccessoryDao::readNestWithWhereSQL(whereSQL);
                
                shared_ptr<vector<shared_ptr<Pojo>>> pojoList = NULL;
                
                // 寫入至json輸出
                Utility::pojoListToJson(inJsonObject, outJsonObject, pojoList);
                
                pCommandBase = new CommandHardwardRecv_ReadItems();
                CommandHardwardRecv_ReadItems* pItems = (CommandHardwardRecv_ReadItems*) pCommandBase;
                pItems->dataType = DataType_Accessory;
                pItems->pPojoList = pojoList;
                m_pCommandHardwardEvent->onCommandHardwardRecv_ReadItems(pItems);
            }
        }
    }
    // 新增或修改
    else if (function.find("write") != std::string::npos) {
        string whereSQL = "";
        
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
                    // 新增Accessory
                    
                    if (pItems->pPojoList->size() == 0) {
                        /* 新增一筆Accessory資料 */
                        // param1: AID代表accessory id
                        // param2: Name 一個名字,用於標示目標類型的一種可視化手段
                        // param3: AccSeq The accessory's sequence , the default value is 0.
                        // param4: IconType 會面呈現的Icon所代表的型態，如IPHub
                        // param5: Connection 連線狀態
                        // param6: IsGateway is gateway or not
                        shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo(getMaxAID(), "Light", 2, 2, 2, false));
                        
                        // param1: Service 一個元件有單個或多個Element
                        shared_ptr<ServicePojo> pService1(new ServicePojo("LightService"));
                        
                        // param1: Element 一個元件有單個或多個element NO
                        shared_ptr<ElementPojo> pElement1(new ElementPojo("switch"));
                        
                        // param1: ElementNO 一個元件的編號
                        // param2: Value 由一個字串組成，字串的類型可能是數值，字串或整數，也有可能是其他的。它的類型由Metadata決定一個 key 通常會有一個 value
                        // param3: NtfyEnable 是否開啟推播
                        shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo(0, "轟天2", true));
                        shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo(1, "大鑫2", true));
                        
                        pAccessoryPojo->pSubPojoList->push_back(pService1);
                        pService1->pSubPojoList->push_back(pElement1);
                        pElement1->pSubPojoList->push_back(pNO1);
                        pElement1->pSubPojoList->push_back(pNO2);
                        
                        m_pAccessoryList->push_back(pAccessoryPojo);
                    }
                    else {
                        for (size_t i=0 ; i<pItems->pPojoList->size() ; i++) {
                            shared_ptr<AccessoryPojo>& pAccessoryPojo = (shared_ptr<AccessoryPojo>&) (*pItems->pPojoList)[i];
                            
                            m_pAccessoryList->push_back(pAccessoryPojo);
                        }
                    }
                    
                    // 寫入至json輸出
//                    Utility::pojoListToJson(inJsonObject, outJsonObject, m_pAccessoryList);
                }
            }
            // 修改
            else {
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
                
                shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = AccessoryDao::readNestWithWhereSQL(whereSQL);
                
                pCommandBase = new CommandHardwardRecv_UpdateItems();
                CommandHardwardRecv_UpdateItems* pItems = (CommandHardwardRecv_UpdateItems*) pCommandBase;
                pItems->dataType = DataType_Accessory;
                pItems->pPojoList = pPojoList;
                m_pCommandHardwardEvent->onCommandHardwardRecv_UpdateItems(pItems);
                
                // 新增成功
                if (pItems->errorCode == 0) {
                    
                }
            }
        }
        
        vector<ValueObject> objList;
        Json::Value thenObject = inJsonObject["Then"];
        
        AccessoryPojo pojo;
        pojo.genValueObject();
//        vector<ValueObject>& propertyList = pojo.valueObjectList;
        
        // Accessory -> AccSeq
        if (thenObject.isMember("ListAccessory")) {
            Json::Value listAccessory = thenObject["ListAccessory"];
            
            Json::Value::Members listAccessoryMembers = listAccessory.getMemberNames();
            for (Json::Value AIDValue : listAccessoryMembers) {
                string AIDString = AIDValue.asString();
                int AID = stoi(AIDString);
                LOGD("AID:%d", AID);
                Json::Value accessory = listAccessory[AIDString];
//                LOGD("accessory:%s", accessory.toStyledString().c_str());
                
//                parse(accessory, AID, propertyList);
//                
//                // Set Accessory
//                setIntVO(AID)
//                setStrVO(AccName)
//                setIntVO(AccSeq)
//                setIntVO(AccIconType)
//                setIntVO(Connection)
//                setIntVO(IsGateway)
                
//                if (accessory.isMember("AccSeq")) {
//                    int AccSeq = accessory["AccSeq"].asInt();
//                    objList.push_back(ValueObject("AccSeq", AccSeq));
//                    
////                    if (accessory.isMember("Room")) {
////                        Json::Value Room = accessory["Room"];
////                        if (Room.isMember("RoomSeq")) {
////                            int RoomSeq = Room["RoomSeq"].asInt();
////                            objList.push_back(ValueObject("RoomSeq", RoomSeq));
////                        }
////                    }
//                    
//                    AccessoryDao::updateAccessoryWithWhereSQL(whereSQL, objList);
//                }
            }
        }
        
        // ElementNO -> Value
        if (thenObject.isMember("Value")) {
            string value = thenObject["Value"].asString();
            objList.push_back(ValueObject("ElementNO", value));
//            AccessoryDao::updateElementNOWithWhereSQL(whereSQL, objList);
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
            }
            
            pCommandBase = new CommandHardwardRecv_DeleteItems();
            CommandHardwardRecv_DeleteItems* pItems = (CommandHardwardRecv_DeleteItems*) pCommandBase;
            pItems->dataType = DataType_Accessory;
            pItems->pIDList = &AIDList;
            m_pCommandHardwardEvent->onCommandHardwardRecv_DeleteItems(pItems);
            
            // 刪除成功
            if (pItems->errorCode == 0) {
                for (int AID : AIDList) {
                    for(size_t i=m_pAccessoryList->size()-1 ; i>=0 ; i--) {
                        if ((*m_pAccessoryList)[i]->AID == AID) {
                            m_pAccessoryList->erase(m_pAccessoryList->begin() + i);
                            break;
                        }
                    }
                }
            }
        }
    }
    
    // Common
    outJsonObject["SenderInfo"] = inJsonObject;
    
    // 當DeviceAPI發生錯誤ErrorCode != 0, 就不去抓取硬體的ErrorCode，所以DeviceAPI發生錯誤就已DeviceAPI ErrorCode為主, DeivceAPI沒錯就抓看看硬體的ErrorCode
//    if (!outJsonObject["ErrorCode"] || outJsonObject["ErrorCode"] == 0) {
//        outJsonObject["ErrorCode"] = pCommandBase->errorCode;
//    }
    outJsonObject["ErrorCode"] = 0;
    
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
