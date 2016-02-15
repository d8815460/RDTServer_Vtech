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
//    virtual void onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData);
    
#pragma mark - CommandEvent
protected:
    virtual unsigned short onCommandGetProductCode();
    virtual const char* onCommandGetProductName();
    virtual void onCommandRecvData(CommandRecvData* pCommandRecvData);
    
    virtual void onCommandRecvCommand28(FunctionStatus* pFunctionStatus);
    virtual void onCommandRecvFullCommand28(int channelID, vector<FunctionInfo*>* pDataInfoList);
    
private:
};

#endif /* VtechIPHubDevice_hpp */
