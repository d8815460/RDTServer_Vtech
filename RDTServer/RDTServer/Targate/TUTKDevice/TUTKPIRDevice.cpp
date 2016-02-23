//
//  PIRDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/6/17.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "TUTKPIRDevice.hpp"
#include "TUTKPIREnum.hpp"
#include "AccessoryTypeEnum.hpp"
#include "BinraryRDTServerCommand.hpp"

#pragma mark - Normal Method

void TUTKPIRDevice::generatorDataInfoList(Command* pCommand)
{
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    BinraryRDTServerCommand *pBinraryRDTServerCommand = (BinraryRDTServerCommand*) pCommand;
    pFunctionInfo = pBinraryRDTServerCommand->createFunctionInfo(Accessory_Type_PIR);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKPIRFunctionCode_QuerySwitch, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKPIRFunctionCode_QueryConnectStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKPIRFunctionCode_QueryTriggeredStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKPIRFunctionCode_QueryAlarmStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKPIRFunctionCode_QuerySOSStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKPIRFunctionCode_QueryPowerStatus, 20);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'P', u'I', u'R');
}

#pragma mark - CommandEvent

unsigned short TUTKPIRDevice::onCommandGetProductCode()
{
    return 0x0EF;
}

const char* TUTKPIRDevice::onCommandGetProductName()
{
    return "TUTKPIRDevice";
}