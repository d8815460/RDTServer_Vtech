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

using libsocket::unix_stream_client; // need libsocket++

string socket_path = "/tmp/unixsocket";
unix_stream_client sock(socket_path); // need libsocket++

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
// 			LOGD("we found received payload from unix socket = %s \n",buffer);
			char* json = (char*) (buffer);
    		LOGD("received json data:%s", json);
			Json::Reader reader;
			Json::Value inJsonObject;
			if (reader.parse(json, inJsonObject))
			{
				LOGD("JSON object can be parsed");		
				std::string operation= inJsonObject["operation"].asString();
				LOGD("received json operation = %s", operation.c_str());

				unsigned int accessoryId= inJsonObject["accessoryId"].asUInt();
				LOGD("received json accessoryId = %d", accessoryId);

				std::string functionCode= inJsonObject["functionCode"].asString();
				LOGD("received json functionCode = %s", functionCode.c_str());

				unsigned int value= inJsonObject["value"].asUInt();
				LOGD("received json value = %d", value);

				if (operation.compare("update") == 0)
				{
					LOGD("Vtech check we need to call the update below \n");
/*
					we should now call the update api below
*/
				}
				else
					LOGD("Vtech check it's not a valid operation \n");

				
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
            // 將新增資料填入
            AccessoryData* pAccessoryData = (AccessoryData*) pCommandHardwardRecv_CreateItems->pBaseData;
            pAccessoryData->accessoryId = 1;
            pAccessoryData->accessoryType = 1;
            pAccessoryData->addFunctionCodeData("switch", 1);
            pAccessoryData->addFunctionCodeData("color", 1, 2);
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
            shared_ptr<vector<shared_ptr<Pojo>>> pAccessoryList = (shared_ptr<vector<shared_ptr<Pojo>>>) pCommandHardwardRecv_ReadItems->pojoList;
            for (shared_ptr<Pojo> pPojo : *pAccessoryList) {
                shared_ptr<AccessoryPojo>& accessoryPojo = (shared_ptr<AccessoryPojo>&) pPojo;
                
                LOGD("AID:%d", accessoryPojo->AID);
                LOGD("iconType:%d", accessoryPojo->iconType);
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

/*
Vtech added on 14/3/2016
*/
	Json::Value root;
	root["operation"] = "update";
    
    // 根據不同的DataType取得資料
    switch (pCommandHardwardRecv_UpdateItems->dataType) {
        case DataType_Accessory: {
            // 針對收到的資料做為更新硬體參考
            vector<AccessoryData*> accessoryList = (vector<AccessoryData*>&) pCommandHardwardRecv_UpdateItems->baseDataList;
            
            for (int i=0 ; i<accessoryList.size() ; i++) {
                LOGD("accessoryId:%d", accessoryList[i]->accessoryId);

				root["accessoryId"] = accessoryList[i]->accessoryId;
                
                for (int j=0 ; j<accessoryList[i]->functionCodeDataList.size() ; j++) {
                    LOGD("functionCode:%s", accessoryList[i]->functionCodeDataList[j]->functonCode.c_str());

					root["functionCode"] = accessoryList[i]->functionCodeDataList[j]->functonCode.c_str();
                    
                    for (int k=0 ; k<accessoryList[i]->functionCodeDataList[j]->functionCodeValueDataList.size() ; k++) {
                        LOGD("value:%d", accessoryList[i]->functionCodeDataList[j]->functionCodeValueDataList[k]->value);

					root["value"] = accessoryList[i]->functionCodeDataList[j]->functionCodeValueDataList[k]->value;

                    }
                }
            }
		std::string json = root.toStyledString();
		LOGD("Received JSON string in UpdateItems - jsonString:%s", json.c_str());
		pCommandHardwardRecv_UpdateItems->errorCode = -1; // Vtech - 我們這樣放errorCode嗎?
		sendToGateway((char*)json.c_str(), json.length());
        }   break;
            
        default: {
            LOGE("對應不到dataType");
        }   break;
    }

    // 通知update
    LOGD("通知update");
    CommandHardwardSend_UpdateItems sendUpdateItems;
    sendUpdateItems.baseDataList = pCommandHardwardRecv_UpdateItems->baseDataList;
    sendUpdateItems.dataType = pCommandHardwardRecv_UpdateItems->dataType;
    sendUpdateItems.errorCode = pCommandHardwardRecv_UpdateItems->errorCode;
    
    Device* pDevice = Device::getInstance();
    JsonRDTCommand* jsonRDTCommand = (JsonRDTCommand*) pDevice->getCommand();
    jsonRDTCommand->commandHardwardSend_UpdateItems(&sendUpdateItems);
}
