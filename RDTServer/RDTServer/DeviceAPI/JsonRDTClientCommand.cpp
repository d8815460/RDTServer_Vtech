//
//  JsonRDTClientCommand.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/26.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "JsonRDTClientCommand.hpp"
#include <iostream>
#include <fstream>
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
            
            unsigned int serno = 87654321;
            string filename = "JsonList/";
            
            // Accessory
//            filename.append("Get_All_Accessories.json");
//            filename.append("Get_One_Accessory.json");
//            filename.append("Get_Two_Accessories.json");
            filename.append("Get_Not_Exist_Accessory.json");
//            filename.append("Add_Accessories.json");
//            filename.append("Delete_Accessories.json");
            
            // Element
//            filename.append("Get_Multiple_Element.json");
//            filename.append("Set_Multiple_Element.json");
            
            char jsonString[MAX_BUFFER_SIZE];
            fstream fp;
            fp.open(filename, ios::in); // 開啟檔案
            if(!fp){ // 如果開啟檔案失敗，fp為0；成功，fp為非0
                LOGE("Fail to open file");
                return NULL;
            }
            fp.read(jsonString, MAX_BUFFER_SIZE);
            fp.close(); // 關閉檔案
            LOGD("jsonString:%s", jsonString);
            
            JsonRDTClientCommand_ParseSendData parseSendData;
            parseSendData.channelID = *it;
            parseSendData.serno = serno;
            parseSendData.totalCount = 1;
            parseSendData.count = 1;
            parseSendData.pData = (BYTE*) jsonString;
            parseSendData.dataLength = (int) strlen(jsonString);
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
