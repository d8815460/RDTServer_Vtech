//
//  BinraryRDTServerConnect.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/13.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "BinraryRDTServerConnect.hpp"
#include <cstring>
#include <unistd.h>
#include "Common.hpp"
#include "IOTCAPIs.h"
#include "RDTAPIs.h"
#include "BinraryRDTServerCommand.hpp"

BinraryRDTServerConnect::BinraryRDTServerConnect(ConnectData* pConnectData) : Connect(pConnectData), m_nMaxClientNumber(MAX_CLIENT_NUM)
{
    initialize();
    
    BinraryRDTServerConnect_ConnectData* pBinraryConnectData = (BinraryRDTServerConnect_ConnectData*) pConnectData;
    strcpy(m_sUid, pBinraryConnectData->uid);
    
    pthread_t threadID_Login;
    pthread_create(&threadID_Login, NULL, &BinraryRDTServerConnect::threadLogin, (void*)this);
    pthread_detach(threadID_Login);
    
    m_isConnect = false;
    m_nSid = -1;
    m_nClientCount = 0;
    m_ppThreadID = new pthread_t[m_nMaxClientNumber];
    m_ppThreadRun = new pthread_t;
}

BinraryRDTServerConnect::~BinraryRDTServerConnect()
{
    delete m_ppThreadRun;
    delete [] m_ppThreadID;
    
    deInitialize();
}

#pragma mark - Connect

void BinraryRDTServerConnect::initialize()
{
    int ret = IOTC_Initialize2(0);
    if (ret != IOTC_ER_NoERROR)
    {
        LOGE("IOTC_Initialize error!!");
        //        return 0;
    }
    
    int rdtCh = RDT_Initialize();
    if(rdtCh <= 0) {
        LOGE("RDT_Initialize error!!");
    }
    
    printIOTCVersion();
    printRDTVersion();
}

void BinraryRDTServerConnect::deInitialize()
{
    //LOGD("RDT Send Data Cost[%lu ms]....", IOTC_GetTickCount()-t);
    RDT_DeInitialize();
    LOGD("RDT_DeInitialize OK");
    
    IOTC_DeInitialize();
    LOGD("IOTC_DeInitialize OK");
}

void BinraryRDTServerConnect::run()
{
    connect();
    
    pthread_join(*m_ppThreadRun, NULL);
}

void BinraryRDTServerConnect::connect()
{
    pthread_create(m_ppThreadRun, NULL, &BinraryRDTServerConnect::threadRun, (void*)this);
    m_isConnect = true;
}

void BinraryRDTServerConnect::disconnect()
{
    m_isConnect = false;
}

#pragma mark - Threads

void* BinraryRDTServerConnect::threadLogin(void *arg)
{
    BinraryRDTServerConnect* pBinraryRDTServerConnect = (BinraryRDTServerConnect*) arg;
    int ret;
    
    while(true)
    {
        ret = IOTC_Device_Login(pBinraryRDTServerConnect->m_sUid, "TUTK", "1234");
        LOGD("Calling IOTC_Device_Login() ret = %d", ret);
        if(ret == IOTC_ER_NoERROR) {
            LOGD("Login OK");
            break;
        }
        else {
            sleep(60);
        }
    }
    
    //    pthread_exit(0);
    return NULL;
}

void* BinraryRDTServerConnect::threadRun(void *arg)
{
    BinraryRDTServerConnect* pBinraryRDTServerConnect = (BinraryRDTServerConnect*) arg;
    
    do {
        struct st_SInfo sInfo;
        //        LOGD("start IOTC_Listen...");
        pBinraryRDTServerConnect->m_nSid = IOTC_Listen(RDT_WAIT_TIMEMS);
        LOGD("m_nSid:%d", pBinraryRDTServerConnect->m_nSid);
        
        if(pBinraryRDTServerConnect->m_nSid >= 0) {
            IOTC_Session_Check(pBinraryRDTServerConnect->m_nSid, &sInfo);
            const char* mode[3] = {"P2P", "RLY", "LAN"};
            LOGD("Client from %s:%d Mode=%s", sInfo.RemoteIP, sInfo.RemotePort, mode[sInfo.Mode]);
            
            pthread_create(&pBinraryRDTServerConnect->m_ppThreadID[pBinraryRDTServerConnect->m_nClientCount], NULL, &BinraryRDTServerConnect::threadRecv, (void*)pBinraryRDTServerConnect);
        }
        
    } while(pBinraryRDTServerConnect->m_isConnect);
    
    //    pthread_exit(0);
    return NULL;
}

void* BinraryRDTServerConnect::threadRecv(void *arg)
{
    BinraryRDTServerConnect* pBinraryRDTServerConnect = (BinraryRDTServerConnect*) arg;
    
    BYTE buffer[MAX_BUFFER_SIZE];
    int channelID = RDT_Create(pBinraryRDTServerConnect->m_nSid, RDT_WAIT_TIMEMS, 0);
    
    if(channelID < 0)
    {
        LOGE("RDT_Create failed[%d]!!", channelID);
        IOTC_Session_Close(pBinraryRDTServerConnect->m_nSid);
    }
    else {
        LOGD("channelID = %d", channelID);
        // 新增channelID
        BinraryRDTServerCommand_ConnectCreateClient binraryConnectCreateClient;
        binraryConnectCreateClient.channelID = channelID;
        pBinraryRDTServerConnect->m_pConnectEvent->onConnectCreateClient(&binraryConnectCreateClient);
        pBinraryRDTServerConnect->m_nClientCount++;
        
        while (true)
        {
            int ret = RDT_Read(channelID, (char*) buffer, MAX_BUFFER_SIZE, RDT_WAIT_TIMEMS);
            if(ret >= 0) {
                BinraryRDTServerConnect_ConnectRecvData binraryConnectRecvData;
                binraryConnectRecvData.channelID = channelID;
                binraryConnectRecvData.pBuffer = buffer;
                binraryConnectRecvData.length = ret;
                pBinraryRDTServerConnect->m_pConnectEvent->onConnectRecvData(&binraryConnectRecvData);
            }
            else if (ret != RDT_ER_TIMEOUT) {
                LOGD("RDT_Read failed:%d", ret);
                
                break;
            }
        }
        
        RDT_Destroy(channelID);
        IOTC_Session_Close(pBinraryRDTServerConnect->m_nSid);
    }
    
    return NULL;
}

void BinraryRDTServerConnect::printIOTCVersion()
{
    unsigned int ulIOTCVer = 0;
    IOTC_Get_Version( &ulIOTCVer );
    char cIOTCVer[4];
    cIOTCVer[3] = (char)ulIOTCVer;
    cIOTCVer[2] = (char)(ulIOTCVer >> 8);
    cIOTCVer[1] = (char)(ulIOTCVer >> 16);
    cIOTCVer[0] = (char)(ulIOTCVer >> 24);
    LOGD("IOTC Version: %d.%d.%d.%d", cIOTCVer[0], cIOTCVer[1], cIOTCVer[2], cIOTCVer[3]);
}

void BinraryRDTServerConnect::printRDTVersion()
{
    unsigned int ulRDTVer = RDT_GetRDTApiVer();
    char cRDTVer[4];
    cRDTVer[3] = (char)ulRDTVer;
    cRDTVer[2] = (char)(ulRDTVer >> 8);
    cRDTVer[1] = (char)(ulRDTVer >> 16);
    cRDTVer[0] = (char)(ulRDTVer >> 24);
    LOGD("RDT Version: %d.%d.%d.%d", cRDTVer[0], cRDTVer[1], cRDTVer[2], cRDTVer[3]);
}
