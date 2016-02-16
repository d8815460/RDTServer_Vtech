//
//  VtechLightBulbEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/15.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__VtechLightBulbEnum__
#define __RDTServer__VtechLightBulbEnum__

enum VtechLightBulbFunctionCode
{
    // 查詢所有
    VtechLightBulbFunctionCode_QueryAll               = 0,
    
    // 智能電燈開關狀態詢問
    VtechLightBulbFunctionCode_QuerySwitch            = 1,
    
    // 智能電燈開關狀態修改
    VtechLightBulbFunctionCode_ModifySwitch           = 2,
    
    // 智能電燈亮度詢問
    VtechLightBulbFunctionCode_QueryBrightness        = 3,
    
    // 智能電燈亮度修改
    VtechLightBulbFunctionCode_ModifyBrightness       = 4,
    
    // 智能電燈最終顯示顏色詢問
    VtechLightBulbFunctionCode_QueryColor             = 5,
    
    // 智能電燈最終顯示顏色修改
    VtechLightBulbFunctionCode_ModifyColor            = 6,
    
    //    // 智能電燈設備名稱詢問
    //    VtechLightBulbFunctionCode_QueryDeviceName        = 7,
    //
    //    // 智能電燈設備名稱修改
    //    VtechLightBulbFunctionCode_ModifyDeviceName       = 8,
    
    // 智能電燈調色盤顏色詢問
    VtechLightBulbFunctionCode_QueryColorPalette      = 9,
    
    // 智能電燈調色盤顏色修改
    VtechLightBulbFunctionCode_ModifyColorPalette     = 10,
    
    // 智能電燈飽和度詢問
    VtechLightBulbFunctionCode_QuerySaturation        = 11,
    
    // 智能電燈飽和度修改
    VtechLightBulbFunctionCode_ModifySaturation       = 12,
    
    // 智能電燈色溫詢問
    VtechLightBulbFunctionCode_QueryColorTemperature  = 13,
    
    // 智能電燈色溫修改
    VtechLightBulbFunctionCode_ModifyColorTemperature = 14,
    
    // 智能電燈Location名稱詢問
    VtechLightBulbFunctionCode_QueryLocationName      = 15,
    
    // 智能電燈Location名稱修改
    VtechLightBulbFunctionCode_ModifyLocationName     = 16,
    
    // 智能電燈設定Effect詢問
    VtechLightBulbFunctionCode_QuerySettingEffect     = 17,
    
    // 智能電燈設定Effect修改
    VtechLightBulbFunctionCode_ModifySettingEffect    = 18,
    
    // Multi-Color LED Light Bulb  Location Index詢問
    VtechLightBulbFunctionCode_QueryLocationIndex     = 21,
    
    // Multi-Color LED Light Bulb  Location Index修改
    VtechLightBulbFunctionCode_ModifyLocationIndex    = 22,
    
    // Multi-Color LED Light Bulb  switch彩燈詢問
    VtechLightBulbFunctionCode_QuerySwitchColorLight  = 23,
    
    // Multi-Color LED Light Bulb  switch彩燈修改
    VtechLightBulbFunctionCode_ModifySwitchColorLight = 24,
    
    //    // 智能電燈設備名稱詢問
    //    VtechLightBulbFunctionCode_QueryDeviceName        = 253,
    //
    //    // 智能電燈設備名稱修改
    //    VtechLightBulbFunctionCode_ModifyDeviceName       = 254,
};

#endif /* defined(__RDTServer__VtechLightBulbEnum__) */
