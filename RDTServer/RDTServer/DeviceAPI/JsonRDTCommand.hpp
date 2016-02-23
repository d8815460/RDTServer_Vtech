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

struct FunctionCodeValueData
{
    int value;
};

struct FunctionCodeData
{
    string functonCode;
    
    vector<FunctionCodeValueData*> functionCodeValueData;
    
    FunctionCodeData()
    {
        for (int i=0 ; i<functionCodeValueData.size() ; i++) {
            delete functionCodeValueData[i];
        }
    }
};

struct AccessoryData
{
    int accessoryId;
    int accessoryType;
    
    vector<FunctionCodeData*> functionCodeDatas;
    
    AccessoryData()
    {
        for (int i=0 ; i<functionCodeDatas.size() ; i++) {
            delete functionCodeDatas[i];
        }
    }
};

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

class JsonRDTCommand : public Command
{
public:
    JsonRDTCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData = NULL);
    
#pragma mark - Command
    virtual void parseSendData(ParseSendData* pParseSendData);
    virtual void parseRecvData(ParseRecvData* pParseRecvData);
    
protected:
    bool isBasicVerificationPass(BYTE* buffer, int length);
    virtual void recvData(int channelID, BYTE* buffer, int totalLength) = 0;
    
#pragma mark - member
    vector<AccessoryData*>   m_accessories;
};

#endif /* JsonRDTCommand_hpp */
