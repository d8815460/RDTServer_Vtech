//
//  BinraryRDTServerCommand.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/12.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef BinraryRDTServerCommand_hpp
#define BinraryRDTServerCommand_hpp

#include <stdio.h>
#include "BinraryRDTCommand.hpp"

using namespace std;

struct BinraryRDTServerCommand_RecvData : CommandRecvData
{
    int channelID;
    BYTE* pBuffer;
    int totalLength;
    
    unsigned short operators;
    UBYTE stage;
};

struct BinraryRDTServerCommand_ParseSendData : ParseSendData
{
    int channelID;
    BYTE stage;
    unsigned short operators;
    BYTE* pData;
    int dataLength;
};

struct BinraryRDTServerCommand_ParseRecvData : ParseRecvData
{
    int channelID;
    UBYTE* pBuffer;
    int length;
};

class BinraryRDTServerCommand : public BinraryRDTCommand
{
public:
    BinraryRDTServerCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData = NULL);
    virtual ~BinraryRDTServerCommand();
    
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
    
#pragma mark - Command
    virtual void parseSendData(ParseSendData* pParseSendData) throw (RDTException);
    virtual void parseRecvData(ParseRecvData* pParseRecvData);
    
#pragma mark - Thread
    static void* threadInput(void *arg);
    
#pragma mark - Private
private:
    void recvData(int channelID, BYTE* buffer, int totalLength);
    
#pragma mark - member
private:
    
};

#endif /* BinraryRDTServerCommand_hpp */
