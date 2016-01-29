//
//  TUTKPIREnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKPIREnum__
#define __RDTServer__TUTKPIREnum__

#include <stdio.h>

enum TUTKPIRFunctionCode
{
    // 查詢所有
    TUTKPIRFunctionCode_QueryAll                 = 0,
    
    // 智能PIR開關詢問
    TUTKPIRFunctionCode_QuerySwitch              = 1,
    
    // 智能PIR開關修改
    TUTKPIRFunctionCode_ModifySwitch             = 2,
    
    // 智能PIR連線狀態詢問
    TUTKPIRFunctionCode_QueryConnectStatus       = 3,
    
    // 智能PIR連線狀態修改
    TUTKPIRFunctionCode_ModifyConnectStatus      = 4,
    
    // 智能PIR觸發狀態詢問
    TUTKPIRFunctionCode_QueryTriggeredStatus     = 5,
    
    // 智能PIR觸發狀態修改
    TUTKPIRFunctionCode_ModifyTriggeredStatus    = 6,
    
    // 智能PIR警⽰示狀態詢問
    TUTKPIRFunctionCode_QueryAlarmStatus         = 7,
    
    // 智能PIR警⽰示狀態修改
    TUTKPIRFunctionCode_ModifyAlarmStatus        = 8,
    
    // 智能PIR SOS狀態詢問
    TUTKPIRFunctionCode_QuerySOSStatus           = 9,
    
    // 智能PIR SOS狀態修改
    TUTKPIRFunctionCode_ModifySOStatus           = 10,
    
    // 智能PIR電量狀態詢問
    TUTKPIRFunctionCode_QueryPowerStatus         = 11,
    
    // 智能PIR電量狀態修改
    TUTKPIRFunctionCode_ModifyPowertatus         = 12,
    
//    // 智能PIR設備名稱詢問
//    TUTKPIRFunctionCode_QueryDeviceName          = 13,
//    
//    // 智能PIR設備名稱修改
//    TUTKPIRFunctionCode_ModifyDeviceName         = 14,
    
//    // 智能PIR設備名稱詢問
//    TUTKPIRFunctionCode_QueryDeviceName          = 253,
//    
//    // 智能PIR設備名稱修改
//    TUTKPIRFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__TUTKPIREnum__) */
