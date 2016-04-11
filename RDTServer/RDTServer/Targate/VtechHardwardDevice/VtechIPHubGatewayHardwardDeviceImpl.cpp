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
			
//        if (reader.parse(json, inJsonObject))
//  			{
// 				LOGD("JSON object can be parsed");		
// 				std::string operation= inJsonObject["operation"].asString();
// 				LOGD("received json operation = %s", operation.c_str());

// 				unsigned int accessoryId= inJsonObject["accessoryId"].asUInt();
// 				LOGD("received json accessoryId = %d", accessoryId);

// 				std::string functionCode= inJsonObject["functionCode"].asString();
// 				LOGD("received json functionCode = %s", functionCode.c_str());

// 				unsigned int value= inJsonObject["value"].asUInt();
// 				LOGD("received json value = %d", value);

// 				if (operation.compare("update") == 0)
// 				{
// 					LOGD("Vtech check we need to call the update below \n");
// /*
// 					we should now call the update api below
// */

//         // 通知update
//         FunctionCodeValueData* pFunctionCodeValueData = new FunctionCodeValueData();
//         pFunctionCodeValueData->value = value;
        
//         FunctionCodeData* pFunctionCodeData = new FunctionCodeData();
//         pFunctionCodeData->functonCode = functionCode.c_str();
//         pFunctionCodeData->functionCodeValueDataList.push_back(pFunctionCodeValueData);

//         AccessoryData* pAccessoryData = new AccessoryData();
//         pAccessoryData->accessoryId = accessoryId;
//         pAccessoryData->functionCodeDataList.push_back(pFunctionCodeData);
        
//         CommandHardwardSend_UpdateItems sendUpdateItems;
//         sendUpdateItems.baseDataList.push_back(pAccessoryData);
//         sendUpdateItems.dataType = DataType_Accessory;
//         sendUpdateItems.errorCode = 0;
        
//         Device* pDevice = Device::getInstance();
//         JsonRDTCommand* jsonRDTCommand = (JsonRDTCommand*) pDevice->getCommand();
//         jsonRDTCommand->commandHardwardSend_UpdateItems(&sendUpdateItems);
        
//         執行後在Server上看到
//         收到 hardward json = 
//         {
//            "operation" : "update",
//            "request" : {
//               "accessories" : [
//                  {
//                     "accessory_id" : 1,
//                     "accessory_type" : 0,
//                     "function_codes" : [
//                        {
//                           "functon_code" : "motion",
//                           "index" : 0,
//                           "value" : 1
//                        }
//                     ]
//                  }
//               ]
//            },
//            "serno" : 12345678,
//            "target" : "/accessory/"
//         }
        

// 				// FunctionCodeValueData* pFunctionCodeValueData = new FunctionCodeValueData();
// 				// pFunctionCodeValueData->value = value;
				
// 				// FunctionCodeData* pFunctionCodeData = new FunctionCodeData();
// 				// pFunctionCodeData->functonCode = functionCode;
// 				// pFunctionCodeData->functionCodeValueDataList.push_back(pFunctionCodeValueData);

// 				// AccessoryData* pAccessoryData = new AccessoryData();
// 				// pAccessoryData->accessoryId = accessoryId;
// 				// pAccessoryData->functionCodeDataList.push_back(pFunctionCodeData);

// 				// CommandBase* pCommand = NULL;
// 				// pCommand = new CommandHardwardRecv_UpdateItems();
// 				// CommandHardwardRecv_UpdateItems* pUpdateItems = (CommandHardwardRecv_UpdateItems*) pCommand;
// 				// pUpdateItems->dataType = DataType_Accessory;
// 				// pUpdateItems->baseDataList.push_back(pAccessoryData);

// 				// // 通知update
// 				// LOGD("通知update");
// 				// CommandHardwardSend_UpdateItems sendUpdateItems;
// 				// sendUpdateItems.baseDataList = pUpdateItems->baseDataList;
// 				// sendUpdateItems.dataType = pUpdateItems->dataType;
// 				// sendUpdateItems.errorCode = pUpdateItems->errorCode;
				
// 				// Device* pDevice = Device::getInstance();
// 				// JsonRDTCommand* jsonRDTCommand = (JsonRDTCommand*) pDevice->getCommand();
// 				// jsonRDTCommand->commandHardwardSend_UpdateItems(&sendUpdateItems);



// 				}

// 				else if (operation.compare("reply") == 0)
// 				{
// 					LOGD("Vtech check we check for error code below \n");
// 					ULEErrorCode = inJsonObject["errorCode"].asUInt();
// 					LOGD("received json errorCode= %d", ULEErrorCode);

// 				}

// 				else
// 					LOGD("Vtech check it's not a valid operation \n");
//			   }
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
            /* 新增一筆資料 */
            
            // 建立accessoryPojo
            shared_ptr<AccessoryPojo> pAccessoryPojo(new AccessoryPojo);
            pAccessoryPojo->AID = 10;
            pAccessoryPojo->Name = "PIR Sensor";
            pAccessoryPojo->IconType = 1;
            pAccessoryPojo->Connection = 1;
            pAccessoryPojo->IsGateway = true;
            
            // 建立ElementPojo
            shared_ptr<ElementPojo> pElement1(new ElementPojo);
            pElement1->Element = "switch";
            
            // 建立ElementNOPojo
            shared_ptr<ElementNOPojo> pNO1(new ElementNOPojo);
            pNO1->ElementNO = 0;
            pNO1->Value = "1";
            pNO1->NtfyEnable = true;
            
            // 建立ElementNOPojo
            shared_ptr<ElementNOPojo> pNO2(new ElementNOPojo);
            pNO2->ElementNO = 1;
            pNO2->Value = "100";
            pNO2->NtfyEnable = true;
            
            // 放入相關階層
            pAccessoryPojo->pSubPojoList->push_back(pElement1);
            pElement1->pSubPojoList->push_back(pNO1);
            pElement1->pSubPojoList->push_back(pNO2);
            
            // 將accessoryPojo放入pojoList
            pCommandHardwardRecv_CreateItems->pojoList->push_back(pAccessoryPojo);
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
                LOGD("iconType:%d", accessoryPojo->IconType);
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
                LOGD("iconType:%d", accessoryPojo->IconType);
                // Update資料
            }
        }   break;
        
        default: {
            LOGE("對應不到dataType");
        }   break;
    }
}
