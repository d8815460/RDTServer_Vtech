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
#include "CommandEvent.hpp"
#include "Command.hpp"
#include "Hardward.hpp"

using namespace std;

//typedef void (*Callback)(FunctionInfo *pFunctionInfo);

//static map<int, int> g_sidChannelIDMap;

class Device : public CommandEvent, public HardwardEvent
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
    virtual Hardward* createHardward();
    virtual void constructorFinish() = 0;
    
#pragma mark - CommandEvent
public:
    virtual unsigned short onCommandGetProductCode() = 0;
    virtual const char* onCommandGetProductName() = 0;
    virtual void onCommandRecvData(CommandRecvData* pCommandRecvData);
    
    virtual void onCommandSendHardward(SendHardwardData* pSendHardwardData);
    
    virtual void onCommandRecvCommand28(FunctionStatus* pFunctionStatus);
    virtual void onCommandRecvFullCommand28(int channelID, vector<FunctionInfo*>* pDataInfoList);

#pragma mark - HardwardEvent
    virtual void onHardwardNotify(HardwardNotifyData* pHardwardRecvData);
    
// 成員變數
protected:
    Command* m_pCommand;
    Hardward* m_pHardward;
    
//    Callback m_callback;
};

#endif /* defined(__RDTServer__Device__) */
