//
//  TUTKDoorEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKDoorEnum__
#define __RDTServer__TUTKDoorEnum__

#include <stdio.h>

enum TUTKDoorFunctionCode
{
    // 查詢所有
    TUTKDoorFunctionCode_QueryAll                 = 0,
    
    // 智能Door開關詢問
    TUTKDoorFunctionCode_QuerySwitch              = 1,
    
    // 智能Door開關修改
    TUTKDoorFunctionCode_ModifySwitch             = 2,
    
    // 智能Door連線狀態詢問
    TUTKDoorFunctionCode_QueryConnectStatus       = 3,
    
    // 智能Door連線狀態修改
    TUTKDoorFunctionCode_ModifyConnectStatus      = 4,
    
    // 智能Door觸發狀態詢問
    TUTKDoorFunctionCode_QueryTriggeredStatus     = 5,
    
    // 智能Door觸發狀態修改
    TUTKDoorFunctionCode_ModifyTriggeredStatus    = 6,
    
    // 智能Door警⽰示狀態詢問
    TUTKDoorFunctionCode_QueryAlarmStatus         = 7,
    
    // 智能Door警⽰示狀態修改
    TUTKDoorFunctionCode_ModifyAlarmStatus        = 8,
    
    // 智能Door SOS狀態詢問
    TUTKDoorFunctionCode_QuerySOSStatus           = 9,
    
    // 智能Door SOS狀態修改
    TUTKDoorFunctionCode_ModifySOStatus           = 10,
    
    // 智能Door電量狀態詢問
    TUTKDoorFunctionCode_QueryPowerStatus         = 11,
    
    // 智能Door電量狀態修改
    TUTKDoorFunctionCode_ModifyPowertatus         = 12,
    
//    // 智能Door設備名稱詢問
//    TUTKDoorFunctionCode_QueryDeviceName          = 13,
//    
//    // 智能Door設備名稱修改
//    TUTKDoorFunctionCode_ModifyDeviceName         = 14,
    
//    // 智能Door設備名稱詢問
//    TUTKDoorFunctionCode_QueryDeviceName          = 253,
//    
//    // 智能Door設備名稱修改
//    TUTKDoorFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__TUTKDoorEnum__) */
