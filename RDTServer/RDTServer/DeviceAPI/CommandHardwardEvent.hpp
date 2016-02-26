//
//  HardwardEvent.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/28.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef CommandHardwardEvent_hpp
#define CommandHardwardEvent_hpp

#include <stdio.h>
#include <string>
#include <json/reader.h>
#include "BaseData.hpp"

struct CommandBase
{
    DataType dataType;
    int errorCode;
};

struct CommandHardwardRecvJsonData
{
    Json::Value* pJsonObject;
};

struct CommandHardwardNotifyData : CommandBase
{
    vector<BaseData*> baseDataList;
};

struct CommandHardwardRecv_ProductCode : CommandBase
{
    int productCode;
};

struct CommandHardwardRecv_ProductName : CommandBase
{
    string productName;
};

struct CommandHardwardRecv_CreateItems : CommandBase
{
    BaseData* pBaseData;
};

struct CommandHardwardRecv_DeleteItems : CommandBase
{
    int id;
};

struct CommandHardwardRecv_ReadItems : CommandBase
{
    vector<BaseData*> baseDataList;
};

struct CommandHardwardRecv_UpdateItems : CommandBase
{
    vector<BaseData*> baseDataList;
};

class CommandHardwardEvent
{
public:
    virtual void onCommandHardwardNotify(CommandHardwardNotifyData* pCommandHardwardNotifyData) = 0;
    virtual void onCommandHardwardRecvJson(CommandHardwardRecvJsonData* pCommandHardwardRecvJsonData) = 0;
    
    virtual void onCommandHardwardRecv_ProductCode(CommandHardwardRecv_ProductCode* pCommandHardwardRecv_ProductCode) = 0;
    virtual void onCommandHardwardRecv_ProductName(CommandHardwardRecv_ProductName* pCommandHardwardRecv_ProductCode) = 0;
    
    /**
     * \brief 硬體收到新增項目
     *
     * \details 當收到新增項目時，系統將會建立新項目，存放在struct，包含資料項目BaseData,必須根據實際DataType填入相關資料
     *
     * \param dataType  實際資料型態
     * \param errorCode 發生錯誤時的錯誤碼
     * \param pBaseData 包含新增項目相關的資料
     *
     */
    virtual void onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems) = 0;
    
    /**
     * \brief 硬體收到刪除項目
     *
     * \details 當收到刪除項目時，系統將會發送id，存放在struct,必須根據實際DataType刪除相關資料
     *
     * \param dataType  實際資料型態
     * \param errorCode 發生錯誤時的錯誤碼
     * \param id        包含刪除項目的識別碼
     *
     */
    virtual void onCommandHardwardRecv_DeleteItems(CommandHardwardRecv_DeleteItems* pCommandHardwardRecv_DeleteItems) = 0;
    
    /**
     * \brief 硬體收到讀取資料項目清單
     *
     * \details 當收到讀取資料項目時，系統將會發送BaseData清單，存放在struct，必須根據實際DataType查詢相關資料
     *
     * \param dataType      實際資料型態
     * \param errorCode     發生錯誤時的錯誤碼
     * \param baseDataList  包含查詢項目清單
     *
     */
    virtual void onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems) = 0;
    
    /**
     * \brief 硬體收到更新資料項目清單
     *
     * \details 當收到讀取資料項目時，系統將會發送BaseData清單，存放在struct，必須根據實際DataType更新相關資料
     *
     * \param dataType      實際資料型態
     * \param errorCode     發生錯誤時的錯誤碼
     * \param baseDataList  包含更新項目清單
     *
     */
    virtual void onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems) = 0;
};

#endif /* CommandHardwardEvent_hpp */
