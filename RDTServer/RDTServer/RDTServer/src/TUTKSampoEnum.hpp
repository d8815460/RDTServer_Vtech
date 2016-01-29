//
//  TUTKSampoEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/26.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKSampoEnum__
#define __RDTServer__TUTKSampoEnum__

#include <stdio.h>

enum AirConditionerFunctionCode
{
    // 查詢所有
    AirConditionerFunctionCode_QueryAll                     = 0,
    
    // 查詢冷氣開關
    AirConditionerFunctionCode_QueryPowerOn                 = 1,
    // 修改冷氣開關
    AirConditionerFunctionCode_ModifyPowerOn                = 2,
    
    // 查詢舒眠狀態開關
    AirConditionerFunctionCode_QuerySleeping                = 3,
    // 修改舒眠狀態開關
    AirConditionerFunctionCode_ModifySleeping               = 4,
    
    // 查詢PICO狀態開關
    AirConditionerFunctionCode_QueryPicoPure                = 5,
    // 修改PICO狀態開關
    AirConditionerFunctionCode_ModifyPicoPure               = 6,
    
    // 查詢雙倍淨開關
    AirConditionerFunctionCode_QueryDoubleClean             = 7,
    // 修改雙倍淨開關
    AirConditionerFunctionCode_ModifyDoubleClean            = 8,
    
    // 查詢狀態音開關
    AirConditionerFunctionCode_QueryStatusTone              = 9,
    // 修改狀態音開關
    AirConditionerFunctionCode_ModifyStatusTone             = 10,
    
    // 查詢冷氣故障狀態
    AirConditionerFunctionCode_QueryFaultStatus             = 11,
    // 修改冷氣故障狀態
    AirConditionerFunctionCode_ModifyFaultStatus            = 12,
    
    // 查詢定時狀態
    AirConditionerFunctionCode_QueryTimingStatus            = 13,
    // 修改定時狀態
    AirConditionerFunctionCode_ModifyTimingStatus           = 14,
    
    // 查詢模式選擇狀態
    AirConditionerFunctionCode_QueryModeSelectionStatus     = 15,
    // 修改模式選擇狀態
    AirConditionerFunctionCode_ModifyModeSelectionStatus    = 16,
    
    // 查詢風量模式狀態
    AirConditionerFunctionCode_QueryAirVolume               = 17,
    // 修改風量模式狀態
    AirConditionerFunctionCode_ModifyAirVolume              = 18,
    
    // 查詢風向模式狀態
    AirConditionerFunctionCode_QueryWindDirection           = 19,
    // 修改風向模式狀態
    AirConditionerFunctionCode_ModifyWindDirection          = 20,
    
    // 冷氣室內溫度狀態查詢(室內溫度 Only)
    AirConditionerFunctionCode_QueryDeviceMode              = 21,
    // 冷氣室內溫度狀態修改(室內溫度 Only)
    AirConditionerFunctionCode_ModifyDeviceMode             = 22,
    
    // 查詢其他運轉模式狀態
    AirConditionerFunctionCode_QueryOtherOperatingMode      = 23,
    // 修改其他運轉模式狀態
    AirConditionerFunctionCode_ModifyOtherOperatingMode     = 24,
    
    // 查詢冷氣設定溫度
    AirConditionerFunctionCode_QueryTemperature             = 25,
    // 修改冷氣設定溫度
    AirConditionerFunctionCode_ModifyTemperature            = 26,
    
    // 查詢定時開關機時間
    AirConditionerFunctionCode_QueryTiming                  = 27,
    // 修改定時開關機時間
    AirConditionerFunctionCode_ModifyTiming                 = 28,
    
//    // 查詢冷氣設備名稱
//    AirConditionerFunctionCode_QueryDeviceName              = 29,
//    // 修改冷氣設備名稱
//    AirConditionerFunctionCode_ModifyDeviceName             = 30,
    
    // 查詢冷氣裝置室外溫度狀態
    AirConditionerFunctionCode_QueryOutdoorStatus           = 31,
    // 修改冷氣裝置室外溫度狀態
    AirConditionerFunctionCode_ModifyOutdoorStatus          = 32,
    
//    // 查詢冷氣設備名稱
//    AirConditionerFunctionCode_QueryDeviceName              = 253,
//    // 修改冷氣設備名稱
//    AirConditionerFunctionCode_ModifyDeviceName             = 254,
};

#endif /* defined(__RDTServer__TUTKSampoEnum__) */
