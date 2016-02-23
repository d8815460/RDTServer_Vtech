//
//  VtechGarageDoorDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/11/25.
//  Copyright © 2015年 jakey. All rights reserved.
//

#include "VtechGarageDoorDevice.hpp"
#include "AccessoryTypeEnum.hpp"
#include "VtechGarageDoorEnum.hpp"

#pragma mark - Device

#pragma mark - Normal Method

void VtechGarageDoorDevice::generatorDataInfoList(Command* pCommand)
{
//    static int locationIndex = 0;
//    static vector<unsigned short> locations[3] = { {u'客', u'廳'}, {u'廚', u'房'}, {u'浴', u'室'} };
////    static unsigned short locations[3][2] = { {u'客', u'廳'}, {u'廚', u'房'}, {u'浴', u'室'} };
//    
//    FunctionInfo* pFunctionInfo = NULL;
//    
//    /* Function Status */
//    pFunctionInfo = pCommand->createFunctionInfo(Accessory_Type_VtechGarageDoor);
//    Command::addFunctionStatus(pFunctionInfo, VtechGarageDoorFunctionCode_QuerySwitch, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechGarageDoorFunctionCode_QueryConnectStatus, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechGarageDoorFunctionCode_QueryTriggeredStatus, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechGarageDoorFunctionCode_QueryAlarmStatus, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechGarageDoorFunctionCode_QuerySOSStatus, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechGarageDoorFunctionCode_QueryPowerStatus, 1);
//    Command::addFunctionStatusWithArray(pFunctionInfo, VtechGarageDoorFunctionCode_QueryLocationName, &locations[locationIndex]);
//    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'門', u'馳');
    
//    locationIndex++;
}

#pragma mark - CommandEvent

unsigned short VtechGarageDoorDevice::onCommandGetProductCode()
{
    return 0xE1;
}

const char* VtechGarageDoorDevice::onCommandGetProductName()
{
    return "VtechGarageDoorDevice";
}
