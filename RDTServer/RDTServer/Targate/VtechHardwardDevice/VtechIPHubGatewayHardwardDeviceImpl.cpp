//
//  VtechIPHubDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/11/18.
//  Copyright © 2015年 jakey. All rights reserved.
//

#include "VtechIPHubGatewayHardwardDeviceImpl.hpp"
#include <iostream>
#include <cstring>
#include "Common.hpp"
#include "AccessoryDao.hpp"

#include "unixclientstream.hpp"
#include "exception.hpp"

// Database
#include "AccessoryTypeEnum.hpp"
#include "AccessoryDao.hpp"
#include "ServiceDao.hpp"
#include "ElementDao.hpp"
#include "ElementNODao.hpp"

#include <unistd.h>

using libsocket::unix_stream_client; // need libsocket++

string socket_path = "/tmp/unixsocket";
unix_stream_client sock(socket_path); // need libsocket++

unsigned int ULEErrorCode = -999;

#pragma mark - Normal Method

VtechIPHubGatewayHardwardDeviceImpl::VtechIPHubGatewayHardwardDeviceImpl()
{
  LOGD("VtechIPHubGatewayHardwardDeviceImpl");


	LOGD("Vtech check to create socket input thread here");
    pthread_t pThreadsocketInput;
    pthread_create(&pThreadsocketInput, NULL, &VtechIPHubGatewayHardwardImpl::socketInput, (void*)this);

}

#pragma mark - Device

Hardward* VtechIPHubGatewayHardwardDeviceImpl::createHardward()
{
  return new VtechIPHubGatewayHardwardImpl();
}

#pragma mark - Thread

void* VtechIPHubGatewayHardwardImpl::socketInput(void *arg)
{
    while(true)
    {
        unsigned char buffer[BUFFER_SIZE];
        memset(buffer, 0, BUFFER_SIZE);
       
        try {
            sock.rcv(buffer,BUFFER_SIZE-1);
            LOGD("we found received payload from unix socket = %s \n",buffer);
            char* json = (char*) (buffer);
            LOGD("received json data:%s", json);
            Json::Reader reader;
            Json::Value inJsonObject;
                
            if (reader.parse(json, inJsonObject)) {
                LOGD("JSON object can be parsed");
                std::string operation= inJsonObject["operation"].asString();
                LOGD("received json operation = %s", operation.c_str());

                unsigned int accessoryId= inJsonObject["accessoryId"].asUInt();
                LOGD("received json accessoryId = %d", accessoryId);

                std::string functionCode= inJsonObject["functionCode"].asString();
                LOGD("received json functionCode = %s", functionCode.c_str());

                unsigned int value= inJsonObject["value"].asUInt();
                LOGD("received json value = %d", value);

                if (operation.compare("update") == 0) {
                    LOGD("Vtech check we need to call the update below \n");
                    
                    {
                        Device* pDevice = Device::getInstance();
                        JsonRDTCommand* pJsonRDTCommand = (JsonRDTCommand*) pDevice->getCommand();

                        /* 新增一筆Accessory資料 */
                        // param1: AID代表accessory id
                        // param2: Name 一個名字,用於標示目標類型的一種可視化手段
                        // param3: AccSeq The accessory's sequence , the default value is 0.
                        // param4: IconType 會面呈現的Icon所代表的型態，如IPHub
                        // param5: Connection 連線狀態，
                        // param6: IsGateway is gateway or not
                        shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo(pJsonRDTCommand->getMaxAID(), "PC Home", 1, 1, 1, true));

                        // param1: Service 一個元件有單個或多個Element
                        shared_ptr<ServicePojo> pService1(new ServicePojo("switchService"));

                        // param1: Element 一個元件有單個或多個ElementNO
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

                        CommandHardwardSend_UpdateItems items;
                        items.dataType = DataType_Accessory;
                        items.pPojoList->push_back(pAccessoryPojo);
                        pJsonRDTCommand->commandHardwardSend_UpdateItems(&items);

                        /*
                        會看到如下log
                        {
                           "1" : {
                              "Connection" : 1,
                              "IconType" : 1,
                              "IsGateway" : false,
                              "ListElement" : {
                                 "switch" : {
                                    "0" : "轟天2",
                                    "1" : "大鑫2",
                                    "NtfyEnable" : true
                                 }
                              },
                              "Name" : "PC Home"
                           }
                        }
                        */
                    }
				}
				else if (operation.compare("reply") == 0)
				{
					LOGD("Vtech check we check for error code below \n");
					ULEErrorCode = inJsonObject["errorCode"].asUInt();
					LOGD("received json errorCode= %d", ULEErrorCode);
				}
				else {
					LOGD("Vtech check it's not a valid operation \n");
			    }
            }
        }
        catch (const libsocket::socket_exception& exc)
        {
            std::cerr << exc.mesg;
        }
    }
    
    return NULL;
}

#pragma mark - Method

void VtechIPHubGatewayHardwardImpl::sendToGateway(char* payload, int length)
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


#pragma mark - VtechIPHubGatewayHardwardImpl::VtechIPHubGatewayHardwardImpl

VtechIPHubGatewayHardwardImpl::VtechIPHubGatewayHardwardImpl()
{
  LOGD("VtechIPHubGatewayHardwardImpl");
}

#pragma mark - VtechIPHubGatewayHardwardImpl::CommandHardwardEvent

void VtechIPHubGatewayHardwardImpl::onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData)
{
	LOGD("onCommandHardwardRecvJson");

// 	std::string jsonString = pCommandHardwardRecvJsonData->pJsonObject->toStyledString();
// 	LOGD("jsonString:%s", jsonString.c_str());

// 	sendToGateway((char*)jsonString.c_str(), jsonString.length());
}

void VtechIPHubGatewayHardwardImpl::onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems)
{
    LOGD("onCommandHardwardRecv_CreateItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_CreateItems->dataType) {
        case DataType_Accessory: {
            Device* pDevice = Device::getInstance();
            JsonRDTCommand* pJsonRDTCommand = (JsonRDTCommand*) pDevice->getCommand();
            
            /* 新增一筆Accessory資料 */
            // param1: AID代表accessory id
            // param2: Name 一個名字,用於標示目標類型的一種可視化手段
            // param3: AccSeq The accessory's sequence , the default value is 0.
            // param4: IconType 會面呈現的Icon所代表的型態，如IPHub
            // param5: Connection 連線狀態，
            // param6: IsGateway is gateway or not
            shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo(pJsonRDTCommand->getMaxAID(), "PC Home", 1, 1, 1, true));
            
            // param1: Service 一個元件有單個或多個Element
            shared_ptr<ServicePojo> pService1(new ServicePojo("switchService"));
            
            // param1: Element 一個元件有單個或多個ElementNO
            shared_ptr<ElementPojo> pElement1(new ElementPojo("switch"));
            
            // param1: ElementNO 一個元件的編號
            // param2: Value 由一個字串組成，字串的類型可能是數值，字串或整數，也有可能是其他的。它的類型由Metadata決定一個 key 通常會有一個 value
            // param3: NtfyEnable 是否開啟推播
            shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo(0, "轟天1", true));
            shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo(1, "大鑫1", true));
            
            pAccessoryPojo->pSubPojoList->push_back(pService1);
            pService1->pSubPojoList->push_back(pElement1);
            pElement1->pSubPojoList->push_back(pNO1);
            pElement1->pSubPojoList->push_back(pNO2);
            
            pCommandHardwardRecv_CreateItems->pPojoList->push_back(pAccessoryPojo);
            
            // 模擬器儲存
            pJsonRDTCommand->getAccessoryList()->push_back(pAccessoryPojo);
        }   break;
            
        default: {
            LOGE("對應不到dataType");
        }   break;
    }
    
}

void VtechIPHubGatewayHardwardImpl::onCommandHardwardRecv_DeleteItems(CommandHardwardRecv_DeleteItems* pCommandHardwardRecv_DeleteItems)
{
    LOGD("onCommandHardwardRecv_DeleteItems");
    
    // 針對特定的硬體刪除關聯
    // 如移除燈的關聯
    switch (pCommandHardwardRecv_DeleteItems->dataType) {
        case DataType_Accessory: {
            // remove pCommandHardwardRecv_DeleteItems->id;
        }   break;
        
        default: {
            LOGE("對應不到dataType");
        }   break;
    }
    
}

void VtechIPHubGatewayHardwardImpl::onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems)
{
    LOGD("onCommandHardwardRecv_ReadItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_ReadItems->dataType) {
        case DataType_Accessory: {
            // 針對收到的資料做為參考
            shared_ptr<vector<shared_ptr<Pojo>>> pAccessoryList = (shared_ptr<vector<shared_ptr<Pojo>>>) pCommandHardwardRecv_ReadItems->pPojoList;
            for (shared_ptr<Pojo> pPojo : *pAccessoryList) {
                shared_ptr<AccessoryPojo>& accessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
                
                LOGD("AID:%d", accessoryPojo->AID);
                LOGD("AccIconType:%d", accessoryPojo->AccIconType);
            }
        }   break;
        
        default: {
            LOGE("對應不到dataType");
        }   break;
    }
}

void VtechIPHubGatewayHardwardImpl::onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems)
{
    LOGD("onCommandHardwardRecv_UpdateItems");
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_UpdateItems->dataType) {
        case DataType_Accessory: {
            // 針對收到的資料做為參考
            shared_ptr<vector<shared_ptr<Pojo>>> pAccessoryList = (shared_ptr<vector<shared_ptr<Pojo>>>) pCommandHardwardRecv_UpdateItems->pPojoList;
            for (shared_ptr<Pojo> pPojo : *pAccessoryList) {
                shared_ptr<AccessoryPojo>& accessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
                
                LOGD("AID:%d", accessoryPojo->AID);
                LOGD("AccIconType:%d", accessoryPojo->AccIconType);
                // Update資料
            }
        }   break;
        
        default: {
            LOGE("對應不到dataType");
        }   break;
    }
}
