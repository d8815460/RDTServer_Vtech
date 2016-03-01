//
//  JsonRDTcommand.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/28.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef JsonRDTCommand_hpp
#define JsonRDTCommand_hpp

#include <stdio.h>
#include "Command.hpp"
#include "BaseData.hpp"

struct JsonRDTCommand_ParseSendData : ParseSendData
{
    int channelID;
    unsigned int serno;
    UBYTE totalCount;
    UBYTE count;
    BYTE* pData;
    int dataLength;
};

struct JsonRDTCommand_ParseRecvData : ParseRecvData
{
    int channelID;
    UBYTE* pBuffer;
    int length;
};

struct JsonRDTCommand_ConnectCreateClient : ConnectCreateClient
{
    int channelID;
};

class JsonRDTCommand : public Command
{
public:
    JsonRDTCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData = NULL);
    ~JsonRDTCommand();
    
    vector<AccessoryData*>* getAccessoryList()
    {
        return &m_accessoryList;
    }
    
#pragma mark - ConnectEvent
public:
    virtual void onConnectRecvData(ConnectRecvData* pConnectRecvData) = 0;
    virtual void onConnectCreateClient(ConnectCreateClient* pConnectCreateClient);
    
#pragma mark - Command
    virtual void parseSendData(ParseSendData* pParseSendData) throw (RDTException);
    virtual void parseRecvData(ParseRecvData* pParseRecvData);

#pragma mark - JsonRDTCommand
protected:
    bool isBasicVerificationPass(BYTE* buffer, int length);
    virtual void recvData(int channelID, BYTE* buffer, int totalLength) = 0;
    
#pragma mark - Member
protected:
    set<int>                m_nChannelIDList;
    
    vector<AccessoryData*>  m_accessoryList;
};

#endif /* JsonRDTCommand_hpp */
