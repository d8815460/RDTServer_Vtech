//
//  RDTClientDevice.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/21.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "JsonRDTClientDevice.hpp"
#include "BinraryRDTClientConnect.hpp"
#include "JsonRDTClientCommand.hpp"

void JsonRDTClientDevice2::generatorDataInfoList(Command* pCommand)
{
//    static int locationIndex = 0;
//    static vector<unsigned short> locations[3] = { {u'客', u'廳'}, {u'廚', u'房'}, {u'浴', u'室'} };
//    
//    FunctionInfo* pFunctionInfo = NULL;
//    
//    /* Function Status */
//    pFunctionInfo = pCommand->createFunctionInfo(Accessory_Type_VtechOpenClosed);
//    Command::addFunctionStatus(pFunctionInfo, VtechOpenClosedFunctionCode_QuerySwitch, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechOpenClosedFunctionCode_QueryConnectStatus, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechOpenClosedFunctionCode_QueryTriggeredStatus, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechOpenClosedFunctionCode_QueryAlarmStatus, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechOpenClosedFunctionCode_QueryPowerStatus, 1);
//    Command::addFunctionStatusWithArray(pFunctionInfo, VtechOpenClosedFunctionCode_QueryLocationName, &locations[locationIndex]);
//    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'開', u'關', u'門');
}

#pragma mark - Device

#pragma mark - CommandEvent

unsigned short JsonRDTClientDevice2::onCommandGetProductCode()
{
    return 0xE1;
}

const char* JsonRDTClientDevice2::onCommandGetProductName()
{
    return "RDTClientDevice";
}
