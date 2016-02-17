//
//  VtechIPHubDevice.hpp
//  RDTServer
//
//  Created by jakey on 2015/11/18.
//  Copyright © 2015年 jakey. All rights reserved.
//

#ifndef VtechIPHubGatewayHardwardDevice_hpp
#define VtechIPHubGatewayHardwardDevice_hpp

#include "VtechIPHubGatewayDevice.hpp"
#include <stdio.h>

using namespace std;

class VtechIPHubGatewayHardwardDevice : public VtechIPHubGatewayDevice
{
public:
	VtechIPHubGatewayHardwardDevice();
	
#pragma mark - Thread
   static void* socketInput(void *arg);
   
#pragma mark - Method
   void sendToGateway(char* payload, int length);
    
#pragma mark - CommandHardwardEvent
   virtual void onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData);

private:
};

#endif /* VtechIPHubGatewayHardwardDevice_hpp */
