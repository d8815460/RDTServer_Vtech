//
//  Device.h
//  RDTServer
//
//  Created by jakey on 2015/4/7.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__Device__
#define __RDTServer__Device__

#include <set>
#include <map>
#include <pthread.h>
#include "Command.hpp"
#include "CommandEvent.hpp"
#include "CommandHardwardEvent.hpp"

using namespace std;

//typedef void (*Callback)(FunctionInfo *pFunctionInfo);

//static map<int, int> g_sidChannelIDMap;

class Device : public CommandEvent, public CommandHardwardEvent
{
// 建構式
public:
    Device();
    virtual ~Device();
    
    void run(const char* parameter);
    
    // 註冊Callback
    //    void registerListener(Callback callback);
        
#pragma mark - Device
    virtual Connect* createConnect(ConnectData* pConnectData);
    virtual Command* createCommand(Connect* pConnect);
    virtual void constructorFinish() = 0;
    
#pragma mark - CommandEvent
public:
    virtual unsigned short onCommandGetProductCode() = 0;
    virtual const char* onCommandGetProductName() = 0;
    virtual void onCommandRecvData(CommandRecvData* pCommandRecvData);
    
    virtual void onCommandRecvCommand28(FunctionStatus* pFunctionStatus);
    virtual void onCommandRecvFullCommand28(int channelID, vector<FunctionInfo*>* pDataInfoList);
    
#pragma mark - CommandHardwardEvent
    virtual void onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData);
    virtual void onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData);
    
    virtual void onCommandHardwardRecv_ProductCode(CommandHardwardRecv_ProductCode* pCommandHardwardRecv_ProductCode);
    virtual void onCommandHardwardRecv_ProductName(CommandHardwardRecv_ProductName* pCommandHardwardRecv_ProductName);
    
    virtual void onCommandHardwardRecv_CreateAccessoryItems(CommandHardwardRecv_CreateAccessoryItems* pCommandHardwardRecv_CreateAccessoryItems);
    virtual void onCommandHardwardRecv_DeleteAccessoryItems(CommandHardwardRecv_DeleteAccessoryItems* pCommandHardwardRecv_DeleteAccessoryItems);
    virtual void onCommandHardwardRecv_ReadAccessoryByType(CommandHardwardRecv_ReadAccessoryByType* pCommandHardwardRecv_ReadAccessoryByType);
    virtual void onCommandHardwardRecv_UpdateAccessoryFunctionCode(CommandHardwardRecv_UpdateAccessoryFunctionCode* pCommandHardwardRecv_UpdateAccessoryFunctionCode);
    
// 成員變數
protected:
    Command* m_pCommand;
//    Hardward* m_pHardward;
    
//    Callback m_callback;
};

#endif /* defined(__RDTServer__Device__) */
