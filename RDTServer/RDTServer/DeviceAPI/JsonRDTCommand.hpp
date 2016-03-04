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
#include "CommandException.hpp"

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
    virtual void parseRecvData(ParseRecvData* pParseRecvData) throw (CommandException);

    /**
     * \brief 硬體主動更新資料項目清單
     *
     * \details 當硬體主動更新項目，如將燈打開或是PIR觸發，硬體針對實際狀況發送BaseData清單，存放在struct，必須根據實際DataType更新相關資料
     *
     * \param dataType      實際資料型態
     * \param errorCode     發生錯誤時的錯誤碼
     * \param baseDataList  包含更新項目清單
     *
     */
    virtual void hardwardUpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems) throw (CommandException);
    
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
