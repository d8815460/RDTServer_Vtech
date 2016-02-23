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
#include "BinraryRDTServerCommand.hpp"

#pragma mark - Normal Method

void TUTKSmokeDevice::generatorDataInfoList(Command* pCommand)
{
    BinraryRDTServerCommand *pBinraryRDTServerCommand = (BinraryRDTServerCommand*) pCommand;
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    pFunctionInfo = pBinraryRDTServerCommand->createFunctionInfo(Accessory_Type_Smoke);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QuerySwitch, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QueryConnectStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QueryTriggeredStatus, 0);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QueryAlarmStatus, 0);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QuerySOSStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSmokeFunctionCode_QueryPowerStatus, 50);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'a', u'鱻', u'鑫');
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
