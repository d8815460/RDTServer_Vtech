//
//  TUTKDoorDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "TUTKDoorDevice.hpp"
#include "TUTKDoorEnum.hpp"
#include "AccessoryTypeEnum.hpp"
#include "BinraryRDTServerCommand.hpp"

#pragma mark - Normal Method

void TUTKDoorDevice::generatorDataInfoList(Command* pCommand)
{
    BinraryRDTServerCommand *pBinraryRDTServerCommand = (BinraryRDTServerCommand*) pCommand;
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    pFunctionInfo = pBinraryRDTServerCommand->createFunctionInfo(Accessory_Type_Door);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKDoorFunctionCode_QuerySwitch, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKDoorFunctionCode_QueryConnectStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKDoorFunctionCode_QueryTriggeredStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKDoorFunctionCode_QueryAlarmStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKDoorFunctionCode_QuerySOSStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKDoorFunctionCode_QueryPowerStatus, 20);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'門');
}

#pragma mark - CommandEvent

unsigned short TUTKDoorDevice::onCommandGetProductCode()
{
    return 0x0EE;
}

const char* TUTKDoorDevice::onCommandGetProductName()
{
    return "TUTKDoorDevice";
}