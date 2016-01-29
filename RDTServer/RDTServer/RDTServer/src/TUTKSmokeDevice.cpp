//
//  TUTKSmokeDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "TUTKSmokeDevice.hpp"
#include "TUTKSmokeEnum.hpp"
#include "AccessoryTypeEnum.hpp"

#pragma mark - Normal Method

void TUTKSmokeDevice::generatorDataInfoList(Command* pCommand)
{
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    pFunctionInfo = pCommand->createFunctionInfo(Accessory_Type_Smoke);
    Command::addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QuerySwitch, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QueryConnectStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QueryTriggeredStatus, 0);
    Command::addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QueryAlarmStatus, 0);
    Command::addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QuerySOSStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QueryPowerStatus, 50);
    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'a', u'鱻', u'鑫');
}

#pragma mark - CommandEvent

unsigned short TUTKSmokeDevice::onCommandGetProductCode()
{
    return 0x0EC;
}

const char* TUTKSmokeDevice::onCommandGetProductName()
{
    return "TUTKSmokeDevice";
}
