//
//  JsonRDTcommand.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/28.
//  Copyright © 2016年 jakey. All rights reserved.
//

/*
Revision Table
------------|------------------|---------------|-------------------
 Version    | Name             | Date          | Description
------------|------------------|---------------|-------------------
 0.1.2      | jakey            | 3月           | 實作protocol 2.0版本對應的Hardward interface
------------|------------------|---------------|-------------------
 0.1.3      | jakey            | 4月12日        | 實作protocol 2.1版本對應的Hardward interface
            |                  |               | commandHardwardSend_CreateItem  修改項目 shared_ptr<vector<shared_ptr<Pojo>>> pojoList
            |                  |               | commandHardwardSend_DeleteItems 修改項目 shared_ptr<vector<shared_ptr<Pojo>>> pojoList
            |                  |               | commandHardwardSend_ReadItems   修改項目 vector<int>* pIDList 包含刪除項目的識別碼清單
            |                  |               | commandHardwardSend_UpdateItems 修改項目 shared_ptr<vector<shared_ptr<Pojo>>> pojoList
            |                  |               |
            |                  |               | 如果 DataType dataType = DataType_Accessory，則指的是AccessoryPojo，AccessoryPojo包含多個ElementPojo
            |                  |               | shared_ptr<vector<shared_ptr<Pojo>>> pojoList
            |                  |               | AccessoryPojo 在 AccessoryDao.hpp，pSubPojoList包含多個ElementPojo
            |                  |               | ElementPojo 在 ElementDao.hpp，pSubPojoList包含多個ElementNOPojo
            |                  |               | ElementNOPojo 在 ElementNODao.hpp
            |                  |               |
------------|------------------|---------------|-------------------
*/

#ifndef JsonRDTCommand_hpp
#define JsonRDTCommand_hpp

#include <stdio.h>
#include "Command.hpp"
#include "CommandException.hpp"
#include "AccessoryDao.hpp"

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
    
    shared_ptr<vector<shared_ptr<AccessoryPojo>>>& getAccessoryList()
    {
        return m_pAccessoryList;
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
     * \details 請將資料存放在struct，必須根據實際DataType填入相關資料
     *
     * \param DataType dataType  實際資料型態，如DataType_Accessory
     * \param int errorCode      發生錯誤時的錯誤碼，0為成功，非0為失敗
     * \param shared_ptr<vector<shared_ptr<Pojo>>> pojoList 包含新增項目相關的資料，如dataType為DataType_Accessory，請參閱AccessoryDao.hpp中class AccessoryPojo所定義的屬性
     *
     */
    virtual void commandHardwardSend_CreateItem(CommandHardwardSend_CreateItems* pCommandHardwardRecv_CreateItems);
    
    /**
     * \brief 硬體傳送刪除項目
     *
     * \details 請將資料存放在struct，必須根據實際DataType填入相關資料
     *
     * \param DataType dataType  實際資料型態，如DataType_Accessory
     * \param int errorCode      發生錯誤時的錯誤碼，0為成功，非0為失敗
     * \param vector<int>* pIDList 包含刪除項目的識別碼清單
     *
     */
    virtual void commandHardwardSend_DeleteItems(CommandHardwardSend_DeleteItems* pCommandHardwardRecv_DeleteItems);
    
    /**
     * \brief 硬體傳送讀取資料項目清單
     *
     * \details 請將資料存放在struct，必須根據實際DataType填入相關資料
     *
     * \param DataType dataType  實際資料型態，如DataType_Accessory
     * \param int errorCode      發生錯誤時的錯誤碼，0為成功，非0為失敗
     * \param shared_ptr<vector<shared_ptr<Pojo>>> pojoList 包含新增項目相關的資料，如dataType為DataType_Accessory，請參閱AccessoryDao.hpp中class AccessoryPojo所定義的屬性
     *
     */
    virtual void commandHardwardSend_ReadItems(CommandHardwardSend_ReadItems* pCommandHardwardRecv_ReadItems);
    
    /**
     * \brief 硬體傳送更新資料項目清單
     *
     * \details 請將資料存放在struct，必須根據實際DataType填入相關資料
     *
     * \param DataType dataType  實際資料型態，如DataType_Accessory
     * \param int errorCode      發生錯誤時的錯誤碼，0為成功，非0為失敗
     * \param shared_ptr<vector<shared_ptr<Pojo>>> pojoList 包含新增項目相關的資料，如dataType為DataType_Accessory，請參閱AccessoryDao.hpp中class AccessoryPojo所定義的屬性
     *
     */
    virtual void commandHardwardSend_UpdateItems(CommandHardwardSend_UpdateItems* pCommandHardwardSend_UpdateItems) throw (CommandException);
    
#pragma mark - JsonRDTCommand
protected:
    bool isBasicVerificationPass(BYTE* buffer, int length);
    virtual void recvData(int channelID, BYTE* buffer, int totalLength) = 0;
    
#pragma mark - Method
protected:
    void sendJsonData(int channelID, Json::Value& jsonObject);
    
#pragma mark - Member
protected:
    set<int>                m_nChannelIDList;
    
    shared_ptr<vector<shared_ptr<AccessoryPojo>>>  m_pAccessoryList;
};

#endif /* JsonRDTCommand_hpp */
