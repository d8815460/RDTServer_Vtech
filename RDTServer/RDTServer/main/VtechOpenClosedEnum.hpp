//
//  TUTKSampoEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/26.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__VtechOpenClosedEnum__
#define __RDTServer__VtechOpenClosedEnum__

enum VtechOpenClosedFunctionCode
{
    // 查詢所有
    VtechOpenClosedFunctionCode_QueryAll                 = 0,
    
    // 開關詢問
    VtechOpenClosedFunctionCode_QuerySwitch              = 1,
    
    // 開關修改
    VtechOpenClosedFunctionCode_ModifySwitch             = 2,
    
    // 連線狀態詢問
    VtechOpenClosedFunctionCode_QueryConnectStatus       = 3,
    
    // 連線狀態修改
    VtechOpenClosedFunctionCode_ModifyConnectStatus      = 4,
    
    // 觸發狀態詢問
    VtechOpenClosedFunctionCode_QueryTriggeredStatus     = 5,
    
    // 觸發狀態修改
    VtechOpenClosedFunctionCode_ModifyTriggeredStatus    = 6,
    
    // 警⽰示狀態詢問
    VtechOpenClosedFunctionCode_QueryAlarmStatus         = 7,
    
    // 警⽰示狀態修改
    VtechOpenClosedFunctionCode_ModifyAlarmStatus        = 8,
    
    // ＳOS狀態詢問
    VtechOpenClosedFunctionCode_QuerySOSStatus           = 9,
    
    // SOS狀態修改
    VtechOpenClosedFunctionCode_ModifySOStatus           = 10,
    
    // 電量狀態詢問
    VtechOpenClosedFunctionCode_QueryPowerStatus         = 11,
    
    // 電量狀態修改
    VtechOpenClosedFunctionCode_ModifyPowertatus         = 12,
    
    // Location名稱詢問
    VtechOpenClosedFunctionCode_QueryLocationName        = 13,
    
    // Location名稱修改
    VtechOpenClosedFunctionCode_ModifyLocationName       = 14,
    
    //    // 智能PIR設備名稱詢問
    //    VtechOpenClosedFunctionCode_QueryDeviceName          = 253,
    //
    //    // 智能PIR設備名稱修改
    //    VtechOpenClosedFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__VtechOpenClosedEnum__) */
