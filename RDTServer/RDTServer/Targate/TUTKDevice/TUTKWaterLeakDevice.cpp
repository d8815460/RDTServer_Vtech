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
#include "BinraryRDTServerCommand.hpp"

#pragma mark - Normal Method

void TUTKWaterLeakDevice::generatorDataInfoList(Command* pCommand)
{
    BinraryRDTServerCommand *pBinraryRDTServerCommand = (BinraryRDTServerCommand*) pCommand;
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    pFunctionInfo = pBinraryRDTServerCommand->createFunctionInfo(Accessory_Type_WaterLeak);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QuerySwitch, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QueryConnectStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QueryTriggeredStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QueryAlarmStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QuerySOSStatus, 1);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKWaterLeakFunctionCode_QueryPowerStatus, 20);
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'a', u'鱻', u'鑫');
    
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