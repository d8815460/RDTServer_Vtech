//
//  TUTKSampoEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/26.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__VtechWallSwitchEnum__
#define __RDTServer__VtechWallSwitchEnum__

enum VtechWallSwitchFunctionCode
{
    // 查詢所有
    VtechWallSwitchFunctionCode_QueryAll                 = 0,
    
    // 開關詢問
    VtechWallSwitchFunctionCode_QuerySwitch              = 1,
    
    // 開關修改
    VtechWallSwitchFunctionCode_ModifySwitch             = 2,
    
    // 連線狀態詢問
    VtechWallSwitchFunctionCode_QueryConnectStatus       = 3,
    
    // 連線狀態修改
    VtechWallSwitchFunctionCode_ModifyConnectStatus      = 4,
    
    // 觸發狀態詢問
    VtechWallSwitchFunctionCode_QueryTriggeredStatus     = 5,
    
    // 觸發狀態修改
    VtechWallSwitchFunctionCode_ModifyTriggeredStatus    = 6,
    
    // 警⽰示狀態詢問
    VtechWallSwitchFunctionCode_QueryAlarmStatus         = 7,
    
    // 警⽰示狀態修改
    VtechWallSwitchFunctionCode_ModifyAlarmStatus        = 8,
    
    // ＳOS狀態詢問
    VtechWallSwitchFunctionCode_QuerySOSStatus           = 9,
    
    // SOS狀態修改
    VtechWallSwitchFunctionCode_ModifySOStatus           = 10,
    
    // 電量狀態詢問
    VtechWallSwitchFunctionCode_QueryPowerStatus         = 11,
    
    // 電量狀態修改
    VtechWallSwitchFunctionCode_ModifyPowertatus         = 12,
    
    // Location名稱詢問
    VtechWallSwitchFunctionCode_QueryLocationName        = 15,
    
    // Location名稱修改
    VtechWallSwitchFunctionCode_ModifyLocationName       = 16,
    
    // 第1組開或關狀態詢問
    VtechWallSwitchFunctionCode_QueryFourSwitchStatus1    = 19,
    
    // 第1組開或關狀態修改
    VtechWallSwitchFunctionCode_ModifyFourSwitchStatus1   = 20,
    
    // 第2組開或關狀態詢問
    VtechWallSwitchFunctionCode_QueryFourSwitchStatus2    = 21,
    
    // 第2組開或關狀態修改
    VtechWallSwitchFunctionCode_ModifyFourSwitchStatus2   = 22,
    
    // 第3組開或關狀態詢問
    VtechWallSwitchFunctionCode_QueryFourSwitchStatus3    = 23,
    
    // 第3組開或關狀態修改
    VtechWallSwitchFunctionCode_ModifyFourSwitchStatus3   = 24,
    
    // 第4組開或關狀態詢問
    VtechWallSwitchFunctionCode_QueryFourSwitchStatus4    = 25,
    
    // 第4組開或關狀態修改
    VtechWallSwitchFunctionCode_ModifyFourSwitchStatus4   = 26,
    
    //    // 智能PIR設備名稱詢問
    //    VtechWallSwitchFunctionCode_QueryDeviceName          = 253,
    //
    //    // 智能PIR設備名稱修改
    //    VtechWallSwitchFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__VtechWallSwitchEnum__) */
