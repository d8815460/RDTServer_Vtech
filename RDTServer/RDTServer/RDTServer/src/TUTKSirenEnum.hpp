//
//  TUTKSirenEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKSirenEnum__
#define __RDTServer__TUTKSirenEnum__

#include <stdio.h>

enum TUTKSirenFunctionCode
{
    // 查詢所有
    TUTKSirenFunctionCode_QueryAll                 = 0,
    
    // 智能Siren開關詢問
    TUTKSirenFunctionCode_QuerySwitch              = 1,
    
    // 智能Siren開關修改
    TUTKSirenFunctionCode_ModifySwitch             = 2,
    
    // 智能Siren連線狀態詢問
    TUTKSirenFunctionCode_QueryConnectStatus       = 3,
    
    // 智能Siren連線狀態修改
    TUTKSirenFunctionCode_ModifyConnectStatus      = 4,
    
    // 智能Siren觸發狀態詢問
    TUTKSirenFunctionCode_QueryTriggeredStatus     = 5,
    
    // 智能Siren觸發狀態修改
    TUTKSirenFunctionCode_ModifyTriggeredStatus    = 6,
    
    // 智能Siren警⽰示狀態詢問
    TUTKSirenFunctionCode_QueryAlarmStatus         = 7,
    
    // 智能Siren警⽰示狀態修改
    TUTKSirenFunctionCode_ModifyAlarmStatus        = 8,
    
    // 智能Siren SOS狀態詢問
    TUTKSirenFunctionCode_QuerySOSStatus           = 9,
    
    // 智能Siren SOS狀態修改
    TUTKSirenFunctionCode_ModifySOStatus           = 10,
    
    // 智能Siren電量狀態詢問
    TUTKSirenFunctionCode_QueryPowerStatus         = 11,
    
    // 智能Siren電量狀態修改
    TUTKSirenFunctionCode_ModifyPowertatus         = 12,
    
//    // 智能Siren設備名稱詢問
//    TUTKSirenFunctionCode_QueryDeviceName          = 13,
//    
//    // 智能Siren設備名稱修改
//    TUTKSirenFunctionCode_ModifyDeviceName         = 14,
    
//    // 智能Siren設備名稱詢問
//    TUTKSirenFunctionCode_QueryDeviceName          = 253,
//    
//    // 智能Siren設備名稱修改
//    TUTKSirenFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__TUTKSirenEnum__) */
