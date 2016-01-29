//
//  TUTKSampoEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/26.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__VtechMotionSensorEnum__
#define __RDTServer__VtechMotionSensorEnum__

enum VtechMotionFunctionCode
{
    // 查詢所有
    VtechMotionFunctionCode_QueryAll                 = 0,
    
    // 開關詢問
    VtechMotionFunctionCode_QuerySwitch              = 1,
    
    // 開關修改
    VtechMotionFunctionCode_ModifySwitch             = 2,
    
    // 連線狀態詢問
    VtechMotionFunctionCode_QueryConnectStatus       = 3,
    
    // 連線狀態修改
    VtechMotionFunctionCode_ModifyConnectStatus      = 4,
    
    // 觸發狀態詢問
    VtechMotionFunctionCode_QueryTriggeredStatus     = 5,
    
    // 觸發狀態修改
    VtechMotionFunctionCode_ModifyTriggeredStatus    = 6,
    
    // 警⽰示狀態詢問
    VtechMotionFunctionCode_QueryAlarmStatus         = 7,
    
    // 警⽰示狀態修改
    VtechMotionFunctionCode_ModifyAlarmStatus        = 8,
    
    // ＳOS狀態詢問
    VtechMotionFunctionCode_QuerySOSStatus           = 9,
    
    // SOS狀態修改
    VtechMotionFunctionCode_ModifySOStatus           = 10,
    
    // 電量狀態詢問
    VtechMotionFunctionCode_QueryPowerStatus         = 11,
    
    // 電量狀態修改
    VtechMotionFunctionCode_ModifyPowertatus         = 12,
    
    // Location名稱詢問
    VtechMotionFunctionCode_QueryLocationName        = 13,
    
    // Location名稱修改
    VtechMotionFunctionCode_ModifyLocationName       = 14,
    
    //    // 智能PIR設備名稱詢問
    //    VtechMotionFunctionCode_QueryDeviceName          = 253,
    //
    //    // 智能PIR設備名稱修改
    //    VtechMotionFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__VtechMotionSensorEnum__) */
