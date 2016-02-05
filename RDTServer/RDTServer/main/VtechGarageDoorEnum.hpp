//
//  TUTKSampoEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/26.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__VtechGarageDoorEnum__
#define __RDTServer__VtechGarageDoorEnum__

enum VtechGarageDoorFunctionCode
{
    // 查詢所有
    VtechGarageDoorFunctionCode_QueryAll                 = 0,
    
    // 開關詢問
    VtechGarageDoorFunctionCode_QuerySwitch              = 1,
    
    // 開關修改
    VtechGarageDoorFunctionCode_ModifySwitch             = 2,
    
    // 連線狀態詢問
    VtechGarageDoorFunctionCode_QueryConnectStatus       = 3,
    
    // 連線狀態修改
    VtechGarageDoorFunctionCode_ModifyConnectStatus      = 4,
    
    // 觸發狀態詢問
    VtechGarageDoorFunctionCode_QueryTriggeredStatus     = 5,
    
    // 觸發狀態修改
    VtechGarageDoorFunctionCode_ModifyTriggeredStatus    = 6,
    
    // 警⽰示狀態詢問
    VtechGarageDoorFunctionCode_QueryAlarmStatus         = 7,
    
    // 警⽰示狀態修改
    VtechGarageDoorFunctionCode_ModifyAlarmStatus        = 8,
    
    // ＳOS狀態詢問
    VtechGarageDoorFunctionCode_QuerySOSStatus           = 9,
    
    // SOS狀態修改
    VtechGarageDoorFunctionCode_ModifySOStatus           = 10,
    
    // 電量狀態詢問
    VtechGarageDoorFunctionCode_QueryPowerStatus         = 11,
    
    // 電量狀態修改
    VtechGarageDoorFunctionCode_ModifyPowertatus         = 12,
    
    // Location名稱詢問
    VtechGarageDoorFunctionCode_QueryLocationName        = 13,
    
    // Location名稱修改
    VtechGarageDoorFunctionCode_ModifyLocationName       = 14,
    
    //    // 智能PIR設備名稱詢問
    //    VtechGarageDoorFunctionCode_QueryDeviceName          = 253,
    //
    //    // 智能PIR設備名稱修改
    //    VtechGarageDoorFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__VtechGarageDoorEnum__) */
