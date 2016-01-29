//
//  TUTKLightingDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/6/15.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "TUTKLightingDevice.hpp"
#include "TUTKLightingEnum.hpp"
#include "AccessoryTypeEnum.hpp"

#pragma mark - Normal Method

void TUTKLightingDevice::generatorDataInfoList(Command* pCommand)
{
    FunctionInfo* pFunctionInfo = NULL;
    pFunctionInfo = pCommand->createFunctionInfo(Accessory_Type_Light);
    
    // 查詢電燈開關 (on, off)
    Command::addFunctionStatus(pFunctionInfo, TUTKLightingFunctionCode_QuerySwitch, 1);
    
    // 智能電燈亮度詢問 (0 - 100)
    Command::addFunctionStatus(pFunctionInfo, TUTKLightingFunctionCode_QueryBrightness, 100);
    
    // 智能電燈最終顯示顏色詢問 (0 - 255)
    Command::addFunctionStatus(pFunctionInfo, TUTKLightingFunctionCode_QueryColor, 255, 255, 255);
    
    // 智能電燈設備名稱詢問 (N)
    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'雲', u'端');
    
    // 智能電燈調色盤HUE (0 - 100)
    Command::addFunctionStatus(pFunctionInfo, TUTKLightingFunctionCode_QueryColorPalette, 100);
    
    // 智能電燈飽和度 (0 - 100)
    Command::addFunctionStatus(pFunctionInfo, TUTKLightingFunctionCode_QuerySaturation, 100);
    
    // 智能電燈色溫 (0 - 100)
    Command::addFunctionStatus(pFunctionInfo, TUTKLightingFunctionCode_QueryColorTemperature, 100);
}

#pragma mark - CommandEvent

unsigned short TUTKLightingDevice::onCommandGetProductCode()
{
    return 0x0F1;
}

const char* TUTKLightingDevice::onCommandGetProductName()
{
    return "TUTKLightingDevice";
}
