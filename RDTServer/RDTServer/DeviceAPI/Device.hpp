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
#include "Hardward.hpp"
#include "Command.hpp"
#include "CommandEvent.hpp"
#include "CommandHardwardEvent.hpp"

using namespace std;

//typedef void (*Callback)(FunctionInfo *pFunctionInfo);

//static map<int, int> g_sidChannelIDMap;

class Device : public CommandEvent
{
// 建構式
public:
    Device();
    virtual ~Device();
    
    void run(const char* parameter);
    
    // 註冊Callback
    //    void registerListener(Callback callback);
        
#pragma mark - Device
    virtual Hardward* createHardward();
    virtual Connect* createConnect(ConnectData* pConnectData);
    virtual Command* createCommand(Connect* pConnect, CommandHardwardEvent* pCommandHardwardEvent);
    virtual void constructorFinish() = 0;
    
#pragma mark - CommandEvent
public:
    virtual unsigned short onCommandGetProductCode() = 0;
    virtual const char* onCommandGetProductName() = 0;
    virtual void onCommandRecvData(CommandRecvData* pCommandRecvData);
    
    virtual void onCommandRecvCommand28(FunctionStatus* pFunctionStatus);
    virtual void onCommandRecvFullCommand28(int channelID, vector<FunctionInfo*>* pDataInfoList);
    
// 成員變數
protected:
    Command* m_pCommand;
    Hardward* m_pHardward;
    
//    Callback m_callback;
};

#endif /* defined(__RDTServer__Device__) */
