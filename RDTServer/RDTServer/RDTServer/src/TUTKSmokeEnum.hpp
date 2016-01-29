//
//  TUTKSmokeEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKSmokeEnum__
#define __RDTServer__TUTKSmokeEnum__

#include <stdio.h>

enum TUTKSmokeFunctionCode
{
    // 查詢所有
    TUTKSmokeFunctionCode_QueryAll                 = 0,
    
    // 智能Smoke開關詢問
    TUTKSmokeFunctionCode_QuerySwitch              = 1,
    
    // 智能Smoke開關修改
    TUTKSmokeFunctionCode_ModifySwitch             = 2,
    
    // 智能Smoke連線狀態詢問
    TUTKSmokeFunctionCode_QueryConnectStatus       = 3,
    
    // 智能Smoke連線狀態修改
    TUTKSmokeFunctionCode_ModifyConnectStatus      = 4,
    
    // 智能Smoke觸發狀態詢問
    TUTKSmokeFunctionCode_QueryTriggeredStatus     = 5,
    
    // 智能Smoke觸發狀態修改
    TUTKSmokeFunctionCode_ModifyTriggeredStatus    = 6,
    
    // 智能Smoke警⽰示狀態詢問
    TUTKSmokeFunctionCode_QueryAlarmStatus         = 7,
    
    // 智能Smoke警⽰示狀態修改
    TUTKSmokeFunctionCode_ModifyAlarmStatus        = 8,
    
    // 智能Smoke SOS狀態詢問
    TUTKSmokeFunctionCode_QuerySOSStatus           = 9,
    
    // 智能Smoke SOS狀態修改
    TUTKSmokeFunctionCode_ModifySOStatus           = 10,
    
    // 智能Smoke電量狀態詢問
    TUTKSmokeFunctionCode_QueryPowerStatus         = 11,
    
    // 智能Smoke電量狀態修改
    TUTKSmokeFunctionCode_ModifyPowertatus         = 12,
    
//    // 智能Smoke設備名稱詢問
//    TUTKSmokeFunctionCode_QueryDeviceName          = 13,
//    
//    // 智能Smoke設備名稱修改
//    TUTKSmokeFunctionCode_ModifyDeviceName         = 14,
    
//    // 智能Smoke設備名稱詢問
//    TUTKSmokeFunctionCode_QueryDeviceName          = 253,
//    
//    // 智能Smoke設備名稱修改
//    TUTKSmokeFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__TUTKSmokeEnum__) */
