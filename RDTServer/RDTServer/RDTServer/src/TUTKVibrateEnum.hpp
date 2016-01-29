//
//  TUTKVibrateEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKVibrateEnum__
#define __RDTServer__TUTKVibrateEnum__

#include <stdio.h>

enum TUTKVibrateFunctionCode
{
    // 查詢所有
    TUTKVibrateFunctionCode_QueryAll                 = 0,
    
    // 智能Vibrate開關詢問
    TUTKVibrateFunctionCode_QuerySwitch              = 1,
    
    // 智能Vibrate開關修改
    TUTKVibrateFunctionCode_ModifySwitch             = 2,
    
    // 智能Vibrate連線狀態詢問
    TUTKVibrateFunctionCode_QueryConnectStatus       = 3,
    
    // 智能Vibrate連線狀態修改
    TUTKVibrateFunctionCode_ModifyConnectStatus      = 4,
    
    // 智能Vibrate觸發狀態詢問
    TUTKVibrateFunctionCode_QueryTriggeredStatus     = 5,
    
    // 智能Vibrate觸發狀態修改
    TUTKVibrateFunctionCode_ModifyTriggeredStatus    = 6,
    
    // 智能Vibrate警⽰示狀態詢問
    TUTKVibrateFunctionCode_QueryAlarmStatus         = 7,
    
    // 智能Vibrate警⽰示狀態修改
    TUTKVibrateFunctionCode_ModifyAlarmStatus        = 8,
    
    // 智能Vibrate SOS狀態詢問
    TUTKVibrateFunctionCode_QuerySOSStatus           = 9,
    
    // 智能Vibrate SOS狀態修改
    TUTKVibrateFunctionCode_ModifySOStatus           = 10,
    
    // 智能Vibrate電量狀態詢問
    TUTKVibrateFunctionCode_QueryPowerStatus         = 11,
    
    // 智能Vibrate電量狀態修改
    TUTKVibrateFunctionCode_ModifyPowertatus         = 12,
    
//    // 智能Vibrate設備名稱詢問
//    TUTKVibrateFunctionCode_QueryDeviceName          = 13,
//    
//    // 智能Vibrate設備名稱修改
//    TUTKVibrateFunctionCode_ModifyDeviceName         = 14,
    
//    // 智能Vibrate設備名稱詢問
//    TUTKVibrateFunctionCode_QueryDeviceName          = 253,
//    
//    // 智能Vibrate設備名稱修改
//    TUTKVibrateFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__TUTKVibrateEnum__) */
