//
//  VtechIPHubDevice.hpp
//  RDTServer
//
//  Created by jakey on 2015/11/18.
//  Copyright © 2015年 jakey. All rights reserved.
//

#ifndef VtechIPHubGatewayHardwardDevice_hpp
#define VtechIPHubGatewayHardwardDevice_hpp

#include <stdio.h>
#include "Hardward.hpp"
#include "VtechIPHubGatewayDevice.hpp"

using namespace std;

class VtechIPHubGatewayHardwardDeviceImpl : public VtechIPHubGatewayDevice
{
public:
    VtechIPHubGatewayHardwardDeviceImpl();
    
#pragma mark - Device
    virtual Hardward* createHardward();
    
private:
};

class VtechIPHubGatewayHardwardImpl : public VtechIPHubGatewayHardward
{
public:
	VtechIPHubGatewayHardwardImpl();
	
#pragma mark - Thread
   static void* socketInput(void *arg);
   
#pragma mark - Method
   void sendToGateway(char* payload, int length);

#pragma mark - Method
   static void test_sendToGateway(char* payload, int length);

    
#pragma mark - CommandHardwardEvent
	virtual void onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData);

    virtual void onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems);
    virtual void onCommandHardwardRecv_DeleteItems(CommandHardwardRecv_DeleteItems* pCommandHardwardRecv_DeleteItems);
    virtual void onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems);
    virtual void onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems);

private:
};

#endif /* VtechIPHubGatewayHardwardDevice_hpp */
