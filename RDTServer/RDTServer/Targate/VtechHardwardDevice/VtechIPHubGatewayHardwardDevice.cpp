//
//  VtechIPHubDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/11/18.
//  Copyright © 2015年 jakey. All rights reserved.
//

#include "VtechIPHubGatewayHardwardDevice.hpp"
#include <iostream>
#include <cstring>
#include "Common.hpp"

#include "unixclientstream.hpp"
#include "exception.hpp"

using libsocket::unix_stream_client; // need libsocket++

string socket_path = "/tmp/unixsocket";
unix_stream_client sock(socket_path); // need libsocket++

#pragma mark - Normal Method

VtechIPHubGatewayHardwardDevice::VtechIPHubGatewayHardwardDevice()
{
  LOGD("VtechIPHubGatewayHardwardDevice");
}

#pragma mark - CommandHardwardEvent

void VtechIPHubGatewayHardwardDevice::onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData)
{
	LOGD("onCommandHardwardRecvJson");

	std::string jsonString = pCommandHardwardRecvJsonData->pJsonObject->toStyledString();
	LOGD("jsonString:%s", jsonString.c_str());

	sendToGateway((char*)jsonString.c_str(), jsonString.length());
}

#pragma mark - Thread

void* VtechIPHubGatewayHardwardDevice::socketInput(void *arg)
{
   while(true)
   {
       unsigned char buffer[BUFFER_SIZE];
       memset(buffer, 0, BUFFER_SIZE);
       
       try {
           sock.rcv(buffer,BUFFER_SIZE-1);
           LOGD("we found the received payload = %s \n",buffer);
       }
       catch (const libsocket::socket_exception& exc)
       {
           std::cerr << exc.mesg;
       }
   }
   
   return NULL;
}

#pragma mark - Method

void VtechIPHubGatewayHardwardDevice::sendToGateway(char* payload, int length)
{
   LOGD("Vtech call to send to gateway");
   
   try
   {
       sock.snd(payload,length-1);
   }
   catch (const libsocket::socket_exception& exc)
   {
       std::cerr << exc.mesg;
   }
}

#pragma mark - CommandHardwardEvent

void VtechIPHubGatewayHardwardDevice::onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems)
{
    LOGD("onCommandHardwardRecv_CreateItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_CreateItems->dataType) {
        case DataType_Accessory: {
            // 將新增資料填入
            AccessoryData* pAccessoryData = (AccessoryData*) pCommandHardwardRecv_CreateItems->pBaseData;
            pAccessoryData->accessoryId = 1;
            pAccessoryData->accessoryType = 1;
            pAccessoryData->addFunctionCodeData("switch", 1);
            pAccessoryData->addFunctionCodeData("color", 1, 2);
        }   break;
            
        default:
            LOGE("對應不到dataType");
            break;
    }
    
}

void VtechIPHubGatewayHardwardDevice::onCommandHardwardRecv_DeleteItems(CommandHardwardRecv_DeleteItems* pCommandHardwardRecv_DeleteItems)
{
    LOGD("onCommandHardwardRecv_DeleteItems");
    
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

void VtechIPHubGatewayHardwardDevice::onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems)
{
    LOGD("onCommandHardwardRecv_ReadItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_ReadItems->dataType) {
        case DataType_Accessory: {
            // 針對收到的資料做為參考
            vector<AccessoryData*>* pAccessoryList = (vector<AccessoryData*>*) &pCommandHardwardRecv_ReadItems->baseDataList;
            for (int i=0 ; i<pAccessoryList->size() ; i++) {
                LOGD("accessoryId:%d", (*pAccessoryList)[i]->accessoryId);
                LOGD("accessoryType:%d", (*pAccessoryList)[i]->accessoryType);
            }
        }
            
        default:
            LOGE("對應不到dataType");
            break;
    }
}

void VtechIPHubGatewayHardwardDevice::onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems)
{
    LOGD("onCommandHardwardRecv_UpdateItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_UpdateItems->dataType) {
        case DataType_Accessory: {
            // 針對收到的資料做為更新硬體參考
            vector<AccessoryData*>* pAccessoryList = (vector<AccessoryData*>*) &pCommandHardwardRecv_UpdateItems->baseDataList;
            for (int i=0 ; i<pAccessoryList->size() ; i++) {
                LOGD("accessoryId:%d", (*pAccessoryList)[i]->accessoryId);
                LOGD("accessoryType:%d", (*pAccessoryList)[i]->accessoryType);
            }
        }
            
        default:
            LOGE("對應不到dataType");
            break;
    }
}
