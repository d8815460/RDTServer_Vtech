//
//  BinraryRDTClientCommand.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/21.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef BinraryRDTClientCommand_hpp
#define BinraryRDTClientCommand_hpp

#include <stdio.h>
#include "Command.hpp"

using namespace std;

struct BinraryRDTClientCommand_CommandRecvData : CommandRecvData
{
    int channelID;
    BYTE* pBuffer;
    int totalLength;
    
    unsigned short operators;
    UBYTE stage;
};

struct BinraryRDTClientCommand_ParseSendData : ParseSendData
{
    int channelID;
    BYTE stage;
    unsigned short operators;
    BYTE* pData;
    int dataLength;
};

struct BinraryRDTClientCommand_ParseRecvData : ParseRecvData
{
    int channelID;
    UBYTE* pBuffer;
    int length;
};

struct BinraryRDTClientCommand_ConnectCreateClient : ConnectCreateClient
{
    int channelID;
};

class BinraryRDTClientCommand : public Command
{
public:
    BinraryRDTClientCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData = NULL);
    
public:
    bool isLength2Byte(BYTE* buffer, int length);
        
#pragma mark - ConnectEvent
public:
    virtual void onConnectRecvData(ConnectRecvData* pConnectRecvData);
    virtual void onConnectCreateClient(ConnectCreateClient* pConnectCreateClient);
    
#pragma mark - Command
    virtual void parseSendData(ParseSendData* pParseSendData);
    virtual void parseRecvData(ParseRecvData* pParseRecvData);

#pragma mark - Thread
    static void* threadInput(void *arg);
    
#pragma mark - Private
private:
    void recvData(int channelID, BYTE* buffer, int totalLength);
    bool isBasicVerificationPass(BYTE* buffer, int length);
    
#pragma mark - member
private:
    set<int>                m_nChannelIDList;
};

#endif /* BinraryRDTClientCommand_hpp */
