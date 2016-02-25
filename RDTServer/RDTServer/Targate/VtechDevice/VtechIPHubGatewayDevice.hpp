//
//  VtechIPHubDevice.hpp
//  RDTServer
//
//  Created by jakey on 2015/11/18.
//  Copyright © 2015年 jakey. All rights reserved.
//

#ifndef VtechIPHubGatewayDevice_hpp
#define VtechIPHubGatewayDevice_hpp

#include <stdio.h>
#include "Device.hpp"

using namespace std;

class VtechIPHubGatewayDevice : public Device
{
public:
    VtechIPHubGatewayDevice();
    ~VtechIPHubGatewayDevice();
    
    void reset();
    
#pragma mark - Device
    virtual Command* createCommand(Connect* pConnect);
    virtual void constructorFinish() { reset(); }
    
#pragma mark - CommandHardwardEvent
    virtual void onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData);
    virtual void onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData);
    
    virtual void onCommandHardwardRecv_ProductCode(CommandHardwardRecv_ProductCode* pCommandHardwardRecv_ProductCode);
    virtual void onCommandHardwardRecv_ProductName(CommandHardwardRecv_ProductName* pCommandHardwardRecv_ProductName);
    
#pragma mark - CommandEvent
protected:
    virtual unsigned short onCommandGetProductCode();
    virtual const char* onCommandGetProductName();
    virtual void onCommandRecvData(CommandRecvData* pCommandRecvData);
    
    virtual void onCommandRecvCommand28(FunctionStatus* pFunctionStatus);
    virtual void onCommandRecvFullCommand28(int channelID, vector<FunctionInfo*>* pDataInfoList);
    
private:
};

#endif /* VtechIPHubGatewayDevice_hpp */
