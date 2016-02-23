//
//  WallSwitchDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/11/25.
//  Copyright © 2015年 jakey. All rights reserved.
//

#include "VtechWallSwitchDevice.hpp"
#include "VtechWallSwitchEnum.hpp"
#include "AccessoryTypeEnum.hpp"

#pragma mark - Normal Method

void VtechWallSwitchDevice::generatorDataInfoList(Command* pCommand)
{
//    FunctionInfo* pFunctionInfo = NULL;
//    
//    /* Function Status */
//    pFunctionInfo = pCommand->createFunctionInfo(Accessory_Type_VtechWallSwitch);
//    Command::addFunctionStatus(pFunctionInfo, VtechWallSwitchFunctionCode_QuerySwitch, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechWallSwitchFunctionCode_QueryConnectStatus, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechWallSwitchFunctionCode_QueryTriggeredStatus, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechWallSwitchFunctionCode_QueryAlarmStatus, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechWallSwitchFunctionCode_QuerySOSStatus, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechWallSwitchFunctionCode_QueryPowerStatus, 20);
//    Command::addFunctionStatus(pFunctionInfo, VtechWallSwitchFunctionCode_QueryLocationName, 20);
//    
//    // aid, type
//    vector<unsigned short> fourSwitchStatus1 = { 1, Accessory_Type_VtechLightBulb };
//    vector<unsigned short> fourSwitchStatus2 = { 1, Accessory_Type_VtechLightBulb, 2, Accessory_Type_VtechLightBulb};
//    vector<unsigned short> fourSwitchStatus3 = { 1, Accessory_Type_VtechLightBulb, 2, Accessory_Type_VtechLightBulb, 3, Accessory_Type_VtechLightBulb};
//    vector<unsigned short> fourSwitchStatus4 = { 1, Accessory_Type_VtechLightBulb, 2, Accessory_Type_VtechLightBulb, 3, Accessory_Type_VtechLightBulb, 4, Accessory_Type_VtechLightBulb};
//    
//    Command::addFunctionStatusWithArray(pFunctionInfo, VtechWallSwitchFunctionCode_QueryFourSwitchStatus1, &fourSwitchStatus1);
//    Command::addFunctionStatusWithArray(pFunctionInfo, VtechWallSwitchFunctionCode_QueryFourSwitchStatus2, &fourSwitchStatus2);
//    Command::addFunctionStatusWithArray(pFunctionInfo, VtechWallSwitchFunctionCode_QueryFourSwitchStatus3, &fourSwitchStatus3);
//    Command::addFunctionStatusWithArray(pFunctionInfo, VtechWallSwitchFunctionCode_QueryFourSwitchStatus4, &fourSwitchStatus4);
//    
//    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'牆', u'開', u'關');
}

#pragma mark - CommandEvent

unsigned short VtechWallSwitchDevice::onCommandGetProductCode()
{
    return 0xE1;
}

const char* VtechWallSwitchDevice::onCommandGetProductName()
{
    return "VtechWallSwitchDevice";
}
