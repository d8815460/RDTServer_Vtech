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
    vector<int>* pIDList;
};

struct CommandHardwardRecv_ReadItems : CommandBase
{
    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList;
    
    CommandHardwardRecv_ReadItems()
    {
        shared_ptr<vector<shared_ptr<Pojo>>> pp(new vector<shared_ptr<Pojo>>);
        pPojoList = pp;
    }
};

struct CommandHardwardRecv_UpdateItems : CommandBase
{
    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList;
    
    CommandHardwardRecv_UpdateItems()
    {
        shared_ptr<vector<shared_ptr<Pojo>>> pp(new vector<shared_ptr<Pojo>>);
        pPojoList = pp;
    }
};

class CommandHardwardCURDEvent
{
public:
    /**
     * \brief 硬體收到新增項目
     *
     * \details 請將資料存放在struct，必須根據實際DataType填入相關資料
     *
     * \param DataType dataType  實際資料型態，如DataType_Accessory
     * \param int errorCode      發生錯誤時的錯誤碼，0為成功，非0為失敗
     * \param shared_ptr<vector<shared_ptr<Pojo>>> pojoList 包含新增項目相關的資料，如dataType為DataType_Accessory，請參閱AccessoryDao.hpp中class AccessoryPojo所定義的屬性
     *
     */
    virtual void onCommandHardwardRecv_CreateItem(CommandHardwardRecv_CreateItems* pCommandHardwardRecv_CreateItems) = 0;
    
    /**
     * \brief 硬體收到刪除項目
     *
     * \details 請將資料存放在struct，必須根據實際DataType填入相關資料
     *
     * \param DataType dataType  實際資料型態，如DataType_Accessory
     * \param int errorCode      發生錯誤時的錯誤碼，0為成功，非0為失敗
     * \param pIDList            包含刪除項目的識別碼
     *
     */
    virtual void onCommandHardwardRecv_DeleteItems(CommandHardwardRecv_DeleteItems* pCommandHardwardRecv_DeleteItems) = 0;
    
    /**
     * \brief 硬體收到讀取資料項目清單
     *
     * \details 請將資料存放在struct，必須根據實際DataType填入相關資料
     *
     * \param DataType dataType  實際資料型態，如DataType_Accessory
     * \param int errorCode      發生錯誤時的錯誤碼，0為成功，非0為失敗
     * \param shared_ptr<vector<shared_ptr<Pojo>>> pojoList 包含新增項目相關的資料，如dataType為DataType_Accessory，請參閱AccessoryDao.hpp中class AccessoryPojo所定義的屬性
     *
     */
    virtual void onCommandHardwardRecv_ReadItems(CommandHardwardRecv_ReadItems* pCommandHardwardRecv_ReadItems) = 0;
    
    /**
     * \brief 硬體收到更新資料項目清單
     *
     * \details 請將資料存放在struct，必須根據實際DataType填入相關資料
     *
     * \param DataType dataType  實際資料型態，如DataType_Accessory
     * \param int errorCode      發生錯誤時的錯誤碼，0為成功，非0為失敗
     * \param shared_ptr<vector<shared_ptr<Pojo>>> pojoList 包含新增項目相關的資料，如dataType為DataType_Accessory，請參閱AccessoryDao.hpp中class AccessoryPojo所定義的屬性
     *
     */
    virtual void onCommandHardwardRecv_UpdateItems(CommandHardwardRecv_UpdateItems* pCommandHardwardRecv_UpdateItems) = 0;
};

#endif /* CommandHardwardCURDEvent_hpp */
