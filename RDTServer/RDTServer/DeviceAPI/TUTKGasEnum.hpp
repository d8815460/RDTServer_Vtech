//
//  TUTKGasEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKGasEnum__
#define __RDTServer__TUTKGasEnum__

#include <stdio.h>

enum TUTKGasFunctionCode
{
    // 查詢所有
    TUTKGasFunctionCode_QueryAll                 = 0,
    
    // 智能Gas開關詢問
    TUTKGasFunctionCode_QuerySwitch              = 1,
    
    // 智能Gas開關修改
    TUTKGasFunctionCode_ModifySwitch             = 2,
    
    // 智能Gas連線狀態詢問
    TUTKGasFunctionCode_QueryConnectStatus       = 3,
    
    // 智能Gas連線狀態修改
    TUTKGasFunctionCode_ModifyConnectStatus      = 4,
    
    // 智能Gas觸發狀態詢問
    TUTKGasFunctionCode_QueryTriggeredStatus     = 5,
    
    // 智能Gas觸發狀態修改
    TUTKGasFunctionCode_ModifyTriggeredStatus    = 6,
    
    // 智能Gas警⽰示狀態詢問
    TUTKGasFunctionCode_QueryAlarmStatus         = 7,
    
    // 智能Gas警⽰示狀態修改
    TUTKGasFunctionCode_ModifyAlarmStatus        = 8,
    
    // 智能Gas SOS狀態詢問
    TUTKGasFunctionCode_QuerySOSStatus           = 9,
    
    // 智能Gas SOS狀態修改
    TUTKGasFunctionCode_ModifySOStatus           = 10,
    
    // 智能Gas電量狀態詢問
    TUTKGasFunctionCode_QueryPowerStatus         = 11,
    
    // 智能Gas電量狀態修改
    TUTKGasFunctionCode_ModifyPowertatus         = 12,
    
//    // 智能Gas設備名稱詢問
//    TUTKGasFunctionCode_QueryDeviceName          = 13,
//    
//    // 智能Gas設備名稱修改
//    TUTKGasFunctionCode_ModifyDeviceName         = 14,
    
//    // 智能Gas設備名稱詢問
//    TUTKGasFunctionCode_QueryDeviceName          = 253,
//    
//    // 智能Gas設備名稱修改
//    TUTKGasFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__TUTKGasEnum__) */
