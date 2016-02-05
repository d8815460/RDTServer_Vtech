//
//  TUTKSirenDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "TUTKSirenDevice.hpp"
#include "TUTKSirenEnum.hpp"
#include "AccessoryTypeEnum.hpp"

#pragma mark - Normal Method

void TUTKSirenDevice::generatorDataInfoList(Command* pCommand)
{
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    pFunctionInfo = pCommand->createFunctionInfo(Accessory_Type_Siren);
    Command::addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QuerySwitch, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QueryConnectStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QueryTriggeredStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QueryAlarmStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QuerySOSStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QueryPowerStatus, 20);
    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'a', u'鱻', u'鑫');
}

#pragma mark - CommandEvent

unsigned short TUTKSirenDevice::onCommandGetProductCode()
{
    return 0x0EB;
}

const char* TUTKSirenDevice::onCommandGetProductName()
{
    return "TUTKSirenDevice";
}