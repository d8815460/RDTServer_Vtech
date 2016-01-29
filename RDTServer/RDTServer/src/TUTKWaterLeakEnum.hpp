//
//  TUTKWaterLeakEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKWaterLeakEnum__
#define __RDTServer__TUTKWaterLeakEnum__

#include <stdio.h>

enum TUTKWaterLeakFunctionCode
{
    // 查詢所有
    TUTKWaterLeakFunctionCode_QueryAll                 = 0,
    
    // 智能WaterLeak開關詢問
    TUTKWaterLeakFunctionCode_QuerySwitch              = 1,
    
    // 智能WaterLeak開關修改
    TUTKWaterLeakFunctionCode_ModifySwitch             = 2,
    
    // 智能WaterLeak連線狀態詢問
    TUTKWaterLeakFunctionCode_QueryConnectStatus       = 3,
    
    // 智能WaterLeak連線狀態修改
    TUTKWaterLeakFunctionCode_ModifyConnectStatus      = 4,
    
    // 智能WaterLeak觸發狀態詢問
    TUTKWaterLeakFunctionCode_QueryTriggeredStatus     = 5,
    
    // 智能WaterLeak觸發狀態修改
    TUTKWaterLeakFunctionCode_ModifyTriggeredStatus    = 6,
    
    // 智能WaterLeak警⽰示狀態詢問
    TUTKWaterLeakFunctionCode_QueryAlarmStatus         = 7,
    
    // 智能WaterLeak警⽰示狀態修改
    TUTKWaterLeakFunctionCode_ModifyAlarmStatus        = 8,
    
    // 智能WaterLeak SOS狀態詢問
    TUTKWaterLeakFunctionCode_QuerySOSStatus           = 9,
    
    // 智能WaterLeak SOS狀態修改
    TUTKWaterLeakFunctionCode_ModifySOStatus           = 10,
    
    // 智能WaterLeak電量狀態詢問
    TUTKWaterLeakFunctionCode_QueryPowerStatus         = 11,
    
    // 智能WaterLeak電量狀態修改
    TUTKWaterLeakFunctionCode_ModifyPowertatus         = 12,
    
//    // 智能WaterLeak設備名稱詢問
//    TUTKWaterLeakFunctionCode_QueryDeviceName          = 13,
//    
//    // 智能WaterLeak設備名稱修改
//    TUTKWaterLeakFunctionCode_ModifyDeviceName         = 14,
    
//    // 智能WaterLeak設備名稱詢問
//    TUTKWaterLeakFunctionCode_QueryDeviceName          = 253,
//    
//    // 智能WaterLeak設備名稱修改
//    TUTKWaterLeakFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__TUTKWaterLeakEnum__) */
