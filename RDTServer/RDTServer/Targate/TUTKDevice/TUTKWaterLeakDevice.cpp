//
//  TUTKWaterLeakDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "TUTKWaterLeakDevice.hpp"
#include "AccessoryTypeEnum.hpp"
#include "TUTKWaterLeakEnum.hpp"

#pragma mark - Normal Method

void TUTKWaterLeakDevice::generatorDataInfoList(Command* pCommand)
{
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    pFunctionInfo = pCommand->createFunctionInfo(Accessory_Type_WaterLeak);
    Command::addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QuerySwitch, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QueryConnectStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QueryTriggeredStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QueryAlarmStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QuerySOSStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QueryPowerStatus, 20);
    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'a', u'鱻', u'鑫');
    
}

#pragma mark - CommandEvent

unsigned short TUTKWaterLeakDevice::onCommandGetProductCode()
{
    return 0x0ED;
}

const char* TUTKWaterLeakDevice::onCommandGetProductName()
{
    return "TUTKWaterLeakDevice";
}