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

class JsonRDTServerCommand : public JsonRDTCommand
{
public:
    JsonRDTServerCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData = NULL);
        
#pragma mark - ConnectEvent
public:
    virtual void onConnectRecvData(ConnectRecvData* pConnectRecvData);
    
#pragma mark - Thread
public:
    static void* threadInput(void *arg);
    
#pragma mark - Command
public:
//    virtual void parseSendData(ParseSendData* pParseSendData);
//    virtual void parseRecvData(ParseRecvData* pParseRecvData);
    
#pragma mark - JsonRDTCommand
protected:
    virtual void recvData(int channelID, BYTE* buffer, int totalLength);
    
#pragma mark - JsonRDTServerCommand
protected:
    virtual void processCommandTarget(const Json::Value& jsonObject, Json::Value& outJsonObject) throw (CommandException);
    
#pragma mark - member
protected:
};

#endif /* JsonRDTServerCommand_hpp */
