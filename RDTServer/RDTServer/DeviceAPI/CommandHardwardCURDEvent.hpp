//
//  CommandHardwardCURDEvent.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/4.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef CommandHardwardCURDEvent_hpp
#define CommandHardwardCURDEvent_hpp

#include <stdio.h>
#include <memory>
#include <json/reader.h>
#include "Pojo.hpp"
#include "BaseData.hpp"

struct CommandHardwardRecv_CreateItems : CommandBase
{
    shared_ptr<vector<shared_ptr<Pojo>>> pojoList;
    
    CommandHardwardRecv_CreateItems()
    {
        shared_ptr<vector<shared_ptr<Pojo>>> pp(new vector<shared_ptr<Pojo>>);
        pojoList = pp;
    }
};

struct CommandHardwardRecv_DeleteItems : CommandBase
{
    int id;
};

struct CommandHardwardRecv_ReadItems : CommandBase
{
    shared_ptr<vector<shared_ptr<Pojo>>> pojoList;
};

struct CommandHardwardRecv_UpdateItems : CommandBase
{
    vector<BaseData*> baseDataList;
};

class CommandHardwardCURDEvent
{
public:
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

#endif /* CommandHardwardCURDEvent_hpp */
