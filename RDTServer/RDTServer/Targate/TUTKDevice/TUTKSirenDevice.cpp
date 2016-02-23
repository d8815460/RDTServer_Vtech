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
#include "BinraryRDTServerCommand.hpp"

#pragma mark - Normal Method

void TUTKSirenDevice::generatorDataInfoList(Command* pCommand)
{
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    BinraryRDTServerCommand *pBinraryRDTServerCommand = (BinraryRDTServerCommand*) pCommand;
    pFunctionInfo = pBinraryRDTServerCommand->createFunctionInfo(Accessory_Type_Siren);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QuerySwitch, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QueryConnectStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QueryTriggeredStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QueryAlarmStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QuerySOSStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKSirenFunctionCode_QueryPowerStatus, 20);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'a', u'鱻', u'鑫');
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