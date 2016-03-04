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

struct CommandHardwardSend_CreateItems : CommandHardwardRecv_CreateItems
{
    
};

struct CommandHardwardSend_DeleteItems : CommandHardwardRecv_DeleteItems
{
    
};

struct CommandHardwardSend_ReadItems : CommandHardwardRecv_ReadItems
{
    
};

struct CommandHardwardSend_UpdateItems : CommandHardwardRecv_UpdateItems
{
    
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
     * \brief 硬體傳送新增項目
     *
     * \details 當收到新增項目時，系統將會建立新項目，存放在struct，包含資料項目BaseData,必須根據實際DataType填入相關資料
     *
     * \param dataType  實際資料型態
     * \param errorCode 發生錯誤時的錯誤碼
     * \param pBaseData 包含新增項目相關的資料
     *
     */
    virtual void commandHardwardSend_CreateItem(CommandHardwardSend_CreateItems* pCommandHardwardRecv_CreateItems);
    
    /**
     * \brief 硬體傳送刪除項目
     *
     * \details 硬體傳送刪除項目時，系統將會發送id，存放在struct,必須根據實際DataType刪除相關資料
     *
     * \param dataType  實際資料型態
     * \param errorCode 發生錯誤時的錯誤碼
     * \param id        包含刪除項目的識別碼
     *
     */
    virtual void commandHardwardSend_DeleteItems(CommandHardwardSend_DeleteItems* pCommandHardwardRecv_DeleteItems);
    
    /**
     * \brief 硬體傳送讀取資料項目清單
     *
     * \details 硬體傳送讀取資料項目時，系統將會發送BaseData清單，存放在struct，必須根據實際DataType查詢相關資料
     *
     * \param dataType      實際資料型態
     * \param errorCode     發生錯誤時的錯誤碼
     * \param baseDataList  包含查詢項目清單
     *
     */
    virtual void commandHardwardSend_ReadItems(CommandHardwardSend_ReadItems* pCommandHardwardRecv_ReadItems);
    
    /**
     * \brief 硬體傳送更新資料項目清單
     *
     * \details 硬體傳送更新項目，如將燈打開或是PIR觸發，硬體針對實際狀況發送BaseData清單，存放在struct，必須根據實際DataType更新相關資料
     *
     * \param dataType      實際資料型態
     * \param errorCode     發生錯誤時的錯誤碼
     * \param baseDataList  包含更新項目清單
     *
     */
    virtual void commandHardwardSend_UpdateItems(CommandHardwardSend_UpdateItems* pCommandHardwardSend_UpdateItems) throw (CommandException);
    
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
