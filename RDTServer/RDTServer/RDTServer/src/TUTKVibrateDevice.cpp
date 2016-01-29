//
//  TUTKVibrateDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "TUTKVibrateDevice.hpp"
#include "TUTKVibrateEnum.hpp"
#include "AccessoryTypeEnum.hpp"

#pragma mark - Normal Method

void TUTKVibrateDevice::generatorDataInfoList(Command* pCommand)
{
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    pFunctionInfo = pCommand->createFunctionInfo(Accessory_Type_Vibrate);
    Command::addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QuerySwitch, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QueryConnectStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QueryTriggeredStatus, 0);
    Command::addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QueryAlarmStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QuerySOSStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QueryPowerStatus, 20);
    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'a', u'鱻', u'鑫');
}

#pragma mark - CommandEvent

unsigned short TUTKVibrateDevice::onCommandGetProductCode()
{
    return 0x0E9;
}

const char* TUTKVibrateDevice::onCommandGetProductName()
{
    return "TUTKVibrateDevice";
}