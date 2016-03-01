//
//  BinraryRDTServerConnect.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/13.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef BinraryRDTServerConnect_hpp
#define BinraryRDTServerConnect_hpp

#include <stdio.h>
#include <set>
#include <pthread.h>
#include "Connect.hpp"
#include "Command.hpp"
#include "IOTCException.hpp"
#include "RDTException.hpp"

using namespace std;

#define RDT_WAIT_TIMEMS 60000
#define MAX_CLIENT_NUM 32

struct BinraryRDTServerConnect_ConnectData : ConnectData
{
    const char* uid;
};

struct BinraryRDTServerConnect_ConnectRecvData : ConnectRecvData
{
    int channelID;
    UBYTE* pBuffer;
    int length;
};

class BinraryRDTServerConnect : public Connect
{
// 建構式
public:
    BinraryRDTServerConnect(ConnectData* pConnectData);
    ~BinraryRDTServerConnect();
        
#pragma mark - Connect
    virtual void initialize() throw (IOTCException, RDTException);
    virtual void deInitialize();
    virtual void run();
    virtual void connect();
    virtual void disconnect();
    
// 功能
protected:
    static void* threadLogin(void *arg);
    static void* threadRun(void *arg);
    static void* threadRecv(void *arg) throw (RDTException);
    
    static void printIOTCVersion();
    static void printRDTVersion();
    
// 成員變數
protected:    
    const int   m_nMaxClientNumber;
    int         m_nClientCount;
    
    pthread_t*  m_ppThreadID;
    pthread_t*  m_ppThreadRun;
    
    int         m_nSid;
    
    char        m_sUid[20];
};

#endif /* BinraryRDTServerConnect_hpp */
