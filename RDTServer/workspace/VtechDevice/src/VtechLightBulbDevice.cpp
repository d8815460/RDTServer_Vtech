//
//  LightBulbDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/11/25.
//  Copyright © 2015年 jakey. All rights reserved.
//

#include "VtechLightBulbDevice.hpp"
#include "VtechLightBulbEnum.hpp"
#include "AccessoryTypeEnum.hpp"

#pragma mark - Normal Method

void VtechLightBulbDevice::generatorDataInfoList(Command* pCommand)
{
    static int locationIndex = 0;
    static vector<unsigned short> locations[4] = { {u'B', u'A', u'T', u'H', u'R', u'O', u'O', u'M'}, {u'K', u'I', u'T', u'C', u'H', u'E', u'N'}, {u'L', u'I', u'V', u'I', u'N', u' ', u'R', u'O', u'O', u'M'},  {u'K', u'I', u'T', u'C', u'H', u'E', u'N'}};
    
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status */
    pFunctionInfo = pCommand->createFunctionInfo(Accessory_Type_VtechLightBulb);
    Command::addFunctionStatus(pFunctionInfo, VtechLightBulbFunctionCode_QuerySwitch, 1);
    Command::addFunctionStatus(pFunctionInfo, VtechLightBulbFunctionCode_QueryBrightness, 50);
    Command::addFunctionStatus(pFunctionInfo, VtechLightBulbFunctionCode_QueryColor, 128, 128, 128);
    Command::addFunctionStatus(pFunctionInfo, VtechLightBulbFunctionCode_QueryColorPalette, 50);
    Command::addFunctionStatus(pFunctionInfo, VtechLightBulbFunctionCode_QuerySaturation, 50);
    Command::addFunctionStatus(pFunctionInfo, VtechLightBulbFunctionCode_QueryColorTemperature, 20);
    Command::addFunctionStatus(pFunctionInfo, VtechLightBulbFunctionCode_QuerySettingEffect, 20);
    Command::addFunctionStatus(pFunctionInfo, VtechLightBulbFunctionCode_QueryLocationIndex, 1);
    Command::addFunctionStatus(pFunctionInfo, VtechLightBulbFunctionCode_QuerySwitchColorLight, 1);
    Command::addFunctionStatusWithArray(pFunctionInfo, VtechLightBulbFunctionCode_QueryLocationName, &locations[locationIndex]);
    
    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'彩', u'燈');
}

#pragma mark - CommandEvent

unsigned short VtechLightBulbDevice::onCommandGetProductCode()
{
    return 0xE1;
}

const char* VtechLightBulbDevice::onCommandGetProductName()
{
    return "VtechLightBulbDevice";
}

