//
//  TUTKGasDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "TUTKGasDevice.hpp"
#include "TUTKGasEnum.hpp"
#include "AccessoryTypeEnum.hpp"
#include "BinraryRDTServerCommand.hpp"

#pragma mark - Normal Method

void TUTKGasDevice::generatorDataInfoList(Command* pCommand)
{
    BinraryRDTServerCommand *pBinraryRDTServerCommand = (BinraryRDTServerCommand*) pCommand;
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    pFunctionInfo = pBinraryRDTServerCommand->createFunctionInfo(Accessory_Type_Gas);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKGasFunctionCode_QuerySwitch, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKGasFunctionCode_QueryConnectStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKGasFunctionCode_QueryTriggeredStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKGasFunctionCode_QueryAlarmStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKGasFunctionCode_QuerySOSStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKGasFunctionCode_QueryPowerStatus, 20);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'a', u'鱻', u'鑫');
}

#pragma mark - CommandEvent

unsigned short TUTKGasDevice::onCommandGetProductCode()
{
    return 0x0EA;
}

const char* TUTKGasDevice::onCommandGetProductName()
{
    return "TUTKGasDevice";
}
