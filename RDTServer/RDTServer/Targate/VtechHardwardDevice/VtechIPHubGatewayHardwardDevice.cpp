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
       sock.snd(payload,length-2);
   }
   catch (const libsocket::socket_exception& exc)
   {
       std::cerr << exc.mesg;
   }
}
