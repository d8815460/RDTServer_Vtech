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
#include "BinraryRDTServerCommand.hpp"

#pragma mark - Normal Method

void TUTKVibrateDevice::generatorDataInfoList(Command* pCommand)
{
    BinraryRDTServerCommand *pBinraryRDTServerCommand = (BinraryRDTServerCommand*) pCommand;
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    pFunctionInfo = pBinraryRDTServerCommand->createFunctionInfo(Accessory_Type_Vibrate);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QuerySwitch, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QueryConnectStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QueryTriggeredStatus, 0);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QueryAlarmStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QuerySOSStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKVibrateFunctionCode_QueryPowerStatus, 20);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'a', u'鱻', u'鑫');
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