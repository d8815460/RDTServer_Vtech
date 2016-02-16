//
//  JsonRDTServerCommand.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/21.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef JsonRDTServerCommand_hpp
#define JsonRDTServerCommand_hpp

#include <stdio.h>
#include "JsonRDTCommand.hpp"
#include <json/reader.h>

using namespace std;

struct JsonRDTServerCommand_CommandRecvData : CommandRecvData
{
    int channelID;
    BYTE* pBuffer;
    int totalLength;
};

struct JsonRDTServerCommand_ParseSendData : JsonRDTCommand_ParseSendData
{
};

struct JsonRDTServerCommand_ParseRecvData : JsonRDTCommand_ParseRecvData
{
};

struct JsonRDTServerCommand_ConnectCreateClient : ConnectCreateClient
{
    int channelID;
};

class JsonRDTServerCommand : public JsonRDTCommand
{
public:
    JsonRDTServerCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData = NULL);
    
public:
#pragma mark - Report
    void sendReportWithCommand30(int channelID, vector<FunctionInfo*>* pFunctionInfoList);
    void sendReportWithCommand32(int channelID, int operations, int amount, int aids[], unsigned int types[], int statuses[]);
    void sendReportWithCommand33(int channelID, int operations, int status);
    
    void sendReportAllWithCommand30(int channelID, vector<FunctionInfo*>* pFunctionInfoList);
    void sendReportAllWithCommand32(int channelID, int operations, int aid, unsigned int type, int status);
    void sendReportAllWithCommand32(int channelID, int operations, int amount, int aids[], unsigned int types[], int statuses[]);
    void sendReportAllWithCommand33(int channelID, int operations, int status);
    
#pragma mark - ConnectEvent
public:
    virtual void onConnectRecvData(ConnectRecvData* pConnectRecvData);
    virtual void onConnectCreateClient(ConnectCreateClient* pConnectCreateClient);
    
#pragma mark - Command
//    virtual void parseSendData(ParseSendData* pParseSendData);
//    virtual void parseRecvData(ParseRecvData* pParseRecvData);
    
#pragma mark - Thread
    static void* threadInput(void *arg);
    
#pragma mark - Protected
protected:
    virtual void recvData(int channelID, BYTE* buffer, int totalLength);
    
#pragma mark - Private Method
private:
    void processCommandTarget(const Json::Value& jsonObject, Json::Value& outJsonObject);
    
#pragma mark - member
private:
    set<int>                m_nChannelIDList;
};

#endif /* JsonRDTServerCommand_hpp */
