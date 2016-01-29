//
//  BinraryRDTClientConnect.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/21.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "BinraryRDTClientConnect.hpp"
#include <cstring>
#include <unistd.h>
#include "Common.hpp"
#include "IOTCAPIs.h"
#include "RDTAPIs.h"
#include "AccessoryTypeEnum.hpp"
#include "BinraryRDTServerCommand.hpp"

BinraryRDTClientConnect::BinraryRDTClientConnect(ConnectData* pConnectData) : Connect(pConnectData), m_nMaxClientNumber(MAX_CLIENT_NUM)
{
    initialize();
    
    BinraryRDTClientConnect_ConnectData* pBinraryConnectData = (BinraryRDTClientConnect_ConnectData*) pConnectData;
    strcpy(m_sUid, pBinraryConnectData->uid);
    
    m_isConnect = false;
    m_nSid = -1;
    m_nClientCount = 0;
    m_ppThreadID = new pthread_t[m_nMaxClientNumber];
    m_ppThreadRun = new pthread_t;
}

BinraryRDTClientConnect::~BinraryRDTClientConnect()
{
    delete m_ppThreadRun;
    delete [] m_ppThreadID;
    
    deInitialize();
}

#pragma mark - Connect

void BinraryRDTClientConnect::initialize()
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

void BinraryRDTClientConnect::deInitialize()
{
    //LOGD("RDT Send Data Cost[%lu ms]....", IOTC_GetTickCount()-t);
    RDT_DeInitialize();
    LOGD("RDT_DeInitialize OK");
    
    IOTC_DeInitialize();
    LOGD("IOTC_DeInitialize OK");
}

void BinraryRDTClientConnect::run()
{
    connect();
    
    pthread_join(*m_ppThreadRun, NULL);
}

void BinraryRDTClientConnect::connect()
{
    pthread_create(m_ppThreadRun, NULL, &BinraryRDTClientConnect::threadRun, (void*)this);
    m_isConnect = true;
}

void BinraryRDTClientConnect::disconnect()
{
    m_isConnect = false;
}

#pragma mark - Threads

void* BinraryRDTClientConnect::threadRun(void *arg)
{
    BinraryRDTClientConnect* pBinraryRDTClientConnect = (BinraryRDTClientConnect*) arg;
    
    do {
        struct st_SInfo sInfo;
        //        LOGD("start IOTC_Listen...");
        pBinraryRDTClientConnect->m_nSid = IOTC_Get_SessionID();
        LOGD("IOTC_Get_SessionID:%d", pBinraryRDTClientConnect->m_nSid);
        if(pBinraryRDTClientConnect->m_nSid == IOTC_ER_NOT_INITIALIZED)
        {
            LOGE("Not Initialize!!!\n");
            return 0;
        }
        else if (pBinraryRDTClientConnect->m_nSid == IOTC_ER_EXCEED_MAX_SESSION)
        {
            LOGE("EXCEED MAX SESSION!!!\n");
            return 0;
        }
        
        if(pBinraryRDTClientConnect->m_nSid >= 0) {
            pBinraryRDTClientConnect->m_nSid = IOTC_Connect_ByUID_Parallel(pBinraryRDTClientConnect->m_sUid, pBinraryRDTClientConnect->m_nSid);
            LOGD("Step 2: call IOTC_Connect_ByUID_Parallel(%s) ret = %d\n", pBinraryRDTClientConnect->m_sUid, pBinraryRDTClientConnect->m_nSid);
            if(pBinraryRDTClientConnect->m_nSid < 0)
            {
                LOGE("p2pAPIs_Client connect failed...!!\n");
                continue;
            }
            
            IOTC_Session_Check(pBinraryRDTClientConnect->m_nSid, &sInfo);
            const char* mode[3] = {"P2P", "RLY", "LAN"};
            LOGD("Client from %s:%d Mode=%s", sInfo.RemoteIP, sInfo.RemotePort, mode[sInfo.Mode]);
            
            int channelID = RDT_Create(pBinraryRDTClientConnect->m_nSid, RDT_WAIT_TIMEMS, 0);
            
            if(channelID < 0)
            {
                LOGE("RDT_Create failed[%d]!!", channelID);
                IOTC_Session_Close(pBinraryRDTClientConnect->m_nSid);
            }
            else {
                LOGD("channelID = %d", channelID);
                // 新增channelID
                BinraryRDTServerCommand_ConnectCreateClient binraryConnectCreateClient;
                binraryConnectCreateClient.channelID = channelID;
                
                pBinraryRDTClientConnect->m_pConnectEvent->onConnectCreateClient(&binraryConnectCreateClient);
                pBinraryRDTClientConnect->m_nClientCount++;
                pBinraryRDTClientConnect->m_channelID = channelID;
                
                pthread_create(&pBinraryRDTClientConnect->m_ppThreadID[pBinraryRDTClientConnect->m_nClientCount], NULL, &BinraryRDTClientConnect::threadRecv, (void*)pBinraryRDTClientConnect);
                
                int nRet;
                st_RDT_Status statusStatus;
                while (true) {
                    nRet = RDT_Status_Check(channelID, &statusStatus);
                    
                    if (nRet < 0) {
                        LOGE("RDT_Status_Check nRet:%d", nRet);
                        break;
                    }
                    
                    sleep(RUN_WATTING_TIMES);
                };
                
                RDT_Destroy(channelID);
                IOTC_Session_Close(pBinraryRDTClientConnect->m_nSid);
            }
        }
        
    } while(pBinraryRDTClientConnect->m_isConnect);
    
    //    pthread_exit(0);
    return NULL;
}

void* BinraryRDTClientConnect::threadRecv(void *arg)
{
    BinraryRDTClientConnect* pBinraryRDTClientConnect = (BinraryRDTClientConnect*) arg;
    BYTE buffer[MAX_BUFFER_SIZE];
    
    while (true)
    {
        int ret = RDT_Read(pBinraryRDTClientConnect->m_channelID, (char*) buffer, MAX_BUFFER_SIZE, RDT_WAIT_TIMEMS);
        if (ret >= 0) {
            BinraryRDTClientConnect_ConnectRecvData binraryConnectRecvData;
            binraryConnectRecvData.channelID = pBinraryRDTClientConnect->m_channelID;
            binraryConnectRecvData.pBuffer = buffer;
            binraryConnectRecvData.length = ret;
            pBinraryRDTClientConnect->m_pConnectEvent->onConnectRecvData(&binraryConnectRecvData);
        }
        else if (ret != RDT_ER_TIMEOUT) {
            LOGD("RDT_Read failed:%d", ret);
            
            break;
        }
    }
    
    return NULL;
}

void BinraryRDTClientConnect::printIOTCVersion()
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

void BinraryRDTClientConnect::printRDTVersion()
{
    unsigned int ulRDTVer = RDT_GetRDTApiVer();
    char cRDTVer[4];
    cRDTVer[3] = (char)ulRDTVer;
    cRDTVer[2] = (char)(ulRDTVer >> 8);
    cRDTVer[1] = (char)(ulRDTVer >> 16);
    cRDTVer[0] = (char)(ulRDTVer >> 24);
    LOGD("RDT Version: %d.%d.%d.%d", cRDTVer[0], cRDTVer[1], cRDTVer[2], cRDTVer[3]);
}
