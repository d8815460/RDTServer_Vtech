//
//  TUTKLightingEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/15.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKLightingEnum__
#define __RDTServer__TUTKLightingEnum__

#include <stdio.h>

enum TUTKLightingFunctionCode
{
    // 查詢所有
    TUTKLightingFunctionCode_QueryAll               = 0,
    
    // 智能電燈開關狀態詢問
    TUTKLightingFunctionCode_QuerySwitch            = 1,
    
    // 智能電燈開關狀態修改
    TUTKLightingFunctionCode_ModifySwitch           = 2,
    
    // 智能電燈亮度詢問
    TUTKLightingFunctionCode_QueryBrightness        = 3,
    
    // 智能電燈亮度修改
    TUTKLightingFunctionCode_ModifyBrightness       = 4,
    
    // 智能電燈最終顯示顏色詢問
    TUTKLightingFunctionCode_QueryColor             = 5,
    
    // 智能電燈最終顯示顏色修改
    TUTKLightingFunctionCode_ModifyColor            = 6,
    
//    // 智能電燈設備名稱詢問
//    TUTKLightingFunctionCode_QueryDeviceName        = 7,
//    
//    // 智能電燈設備名稱修改
//    TUTKLightingFunctionCode_ModifyDeviceName       = 8,
    
    // 智能電燈調色盤顏色詢問
    TUTKLightingFunctionCode_QueryColorPalette      = 9,
    
    // 智能電燈調色盤顏色修改
    TUTKLightingFunctionCode_ModifyColorPalette     = 10,
    
    // 智能電燈飽和度詢問
    TUTKLightingFunctionCode_QuerySaturation        = 11,
    
    // 智能電燈飽和度修改
    TUTKLightingFunctionCode_ModifySaturation       = 12,
    
    // 智能電燈色溫詢問
    TUTKLightingFunctionCode_QueryColorTemperature  = 13,
    
    // 智能電燈色溫修改
    TUTKLightingFunctionCode_ModifyColorTemperature = 14,
    
    // 智能電燈開關機時間詢問
    TUTKLightingFunctionCode_QueryTiming            = 15,
    
    // 智能電燈開關機時間修改
    TUTKLightingFunctionCode_ModifyTiming           = 16,
    
//    // 智能電燈設備名稱詢問
//    TUTKLightingFunctionCode_QueryDeviceName        = 253,
//    
//    // 智能電燈設備名稱修改
//    TUTKLightingFunctionCode_ModifyDeviceName       = 254,
};

#endif /* defined(__RDTServer__TUTKLightingEnum__) */
