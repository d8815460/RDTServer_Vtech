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
#include "JsonRDTCommand.hpp"

using namespace std;

class VtechIPHubGatewayDevice : public Device
{
public:
    VtechIPHubGatewayDevice();
    ~VtechIPHubGatewayDevice();
    
    void reset();
    
#pragma mark - Device
    virtual Hardward* createHardward();
    virtual Command* createCommand(Connect* pConnect, CommandHardwardEvent* pCommandHardwardEvent);
    virtual void constructorFinish() { reset(); }
    
#pragma mark - CommandEvent
protected:
    virtual unsigned short onCommandGetProductCode();
    virtual const char* onCommandGetProductName();
    virtual void onCommandRecvData(CommandRecvData* pCommandRecvData);
    
    virtual void onCommandRecvCommand28(FunctionStatus* pFunctionStatus);
    virtual void onCommandRecvFullCommand28(int channelID, vector<FunctionInfo*>* pDataInfoList);
    
private:
};

class VtechIPHubGatewayHardward : public Hardward
{
public:
    VtechIPHubGatewayHardward(JsonRDTCommand* pJsonRDTCommand);
    
#pragma mark - CommandHardwardEvent
    virtual void onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems);
    virtual void onCommandHardwardRecv_DeleteItems(CommandHardwardRecv_DeleteItems* pCommandHardwardRecv_DeleteItems);
    virtual void onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems);
    virtual void onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems);
    
protected:
    JsonRDTCommand* m_pJsonRDTCommand;
};

#endif /* VtechIPHubGatewayDevice_hpp */
