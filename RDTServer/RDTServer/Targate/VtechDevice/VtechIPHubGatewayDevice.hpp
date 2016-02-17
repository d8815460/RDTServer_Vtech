//
//  VtechIPHubDevice.hpp
//  RDTServer
//
//  Created by jakey on 2015/11/18.
//  Copyright © 2015年 jakey. All rights reserved.
//

#ifndef VtechIPHubDevice_hpp
#define VtechIPHubDevice_hpp

#include <stdio.h>
#include "Device.hpp"

using namespace std;

class VtechIPHubGatewayDevice : public Device
{
public:
    ~VtechIPHubGatewayDevice();
    
    void reset();
    
#pragma mark - Device
    virtual Command* createCommand(Connect* pConnect);
    virtual void constructorFinish() { reset(); }

#pragma mark - CommandHardwardEvent
    virtual void onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData);
    virtual void onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData);;

    virtual void onCommandHardwardRecvProductCode(CommandHardwardRecvProductCode* pCommandHardwardRecvProductCode);
    virtual void onCommandHardwardRecvProductName(CommandHardwardRecvProductName* pCommandHardwardRecvProductName);
    
#pragma mark - CommandEvent
protected:
    virtual unsigned short onCommandGetProductCode();
    virtual const char* onCommandGetProductName();
    virtual void onCommandRecvData(CommandRecvData* pCommandRecvData);
    
    virtual void onCommandRecvCommand28(FunctionStatus* pFunctionStatus);
    virtual void onCommandRecvFullCommand28(int channelID, vector<FunctionInfo*>* pDataInfoList);
    
//#pragma mark - Thread
//    static void* socketInput(void *arg);
//    
//#pragma mark - Method
//    void sendToGateway(char* payload, int length);
    
private:
};

#endif /* VtechIPHubDevice_hpp */
