//
//  JsonRDTClientCommand.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/26.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef JsonRDTClientCommand_hpp
#define JsonRDTClientCommand_hpp

#include <stdio.h>
#include "JsonRDTCommand.hpp"
#include <json/reader.h>

using namespace std;

struct JsonRDTClientCommand_CommandRecvData : CommandRecvData
{
    int channelID;
    BYTE* pBuffer;
    int totalLength;
};

struct JsonRDTClientCommand_ParseSendData : JsonRDTCommand_ParseSendData
{
};

struct JsonRDTClientCommand_ParseRecvData : JsonRDTCommand_ParseRecvData
{
};

struct JsonRDTClientCommand_ConnectCreateClient : ConnectCreateClient
{
    int channelID;
};

class JsonRDTClientCommand : public JsonRDTCommand
{
public:
    JsonRDTClientCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData = NULL);
    
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
    
#pragma mark - member
private:
    set<int>                m_nChannelIDList;
};

#endif /* JsonRDTClientCommand_hpp */
