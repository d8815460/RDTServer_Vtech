//
//  MotionSensorDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/11/25.
//  Copyright © 2015年 jakey. All rights reserved.
//

#include "VtechMotionSensorDevice.hpp"
#include "VtechMotionSensorEnum.hpp"
#include "AccessoryTypeEnum.hpp"

#pragma mark - Normal Method

void VtechMotionSensorDevice::generatorDataInfoList(Command* pCommand)
{
    static int locationIndex = 0;
    static vector<unsigned short> locations[3] = { {u'客', u'廳'}, {u'廚', u'房'}, {u'浴', u'室'} };
    
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status */
    pFunctionInfo = pCommand->createFunctionInfo(Accessory_Type_VtechMotionSensor);
    Command::addFunctionStatus(pFunctionInfo, VtechMotionFunctionCode_QuerySwitch, 1);
    Command::addFunctionStatus(pFunctionInfo, VtechMotionFunctionCode_QueryConnectStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, VtechMotionFunctionCode_QueryTriggeredStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, VtechMotionFunctionCode_QueryAlarmStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, VtechMotionFunctionCode_QuerySOSStatus, 1);
    Command::addFunctionStatus(pFunctionInfo, VtechMotionFunctionCode_QueryPowerStatus, 1);
    Command::addFunctionStatusWithArray(pFunctionInfo, VtechMotionFunctionCode_QueryLocationName, &locations[locationIndex]);
    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'移', u'動', u'偵', u'測');
}

#pragma mark - CommandEvent

unsigned short VtechMotionSensorDevice::onCommandGetProductCode()
{
    return 0xE1;
}

const char* VtechMotionSensorDevice::onCommandGetProductName()
{
    return "VtechMotionSensorDevice";
}
