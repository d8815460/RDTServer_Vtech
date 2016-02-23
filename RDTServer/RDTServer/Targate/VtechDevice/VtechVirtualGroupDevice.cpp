//
//  VtechVirtualGroupDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/11/25.
//  Copyright © 2015年 jakey. All rights reserved.
//

#include "VtechVirtualGroupDevice.hpp"
#include "AccessoryTypeEnum.hpp"
#include "VtechVirtualGroupEnum.hpp"

#pragma mark - Normal Method

void VtechVirtualGroupDevice::generatorDataInfoList(Command* pCommand)
{
//    FunctionInfo* pFunctionInfo = NULL;
//    
//    /* Function Status */
//    pFunctionInfo = pCommand->createFunctionInfo(Accessory_Type_VtechVirtualGroup);
//    Command::addFunctionStatus(pFunctionInfo, VtechVirtualGroupFunctionCode_QuerySwitch, 1);
//    Command::addFunctionStatus(pFunctionInfo, VtechVirtualGroupFunctionCode_QueryGroupLocationName, u'測');
//    Command::addFunctionStatus(pFunctionInfo, VtechVirtualGroupFunctionCode_QueryGroupID, u'1');
//    Command::addFunctionStatus(pFunctionInfo, VtechVirtualGroupFunctionCode_QueryAddGroupID, u'1');
//    Command::addFunctionStatus(pFunctionInfo, VtechVirtualGroupFunctionCode_QueryLeaveGroupID, u'1');
//    Command::addFunctionStatus(pFunctionInfo, VtechVirtualGroupFunctionCode_QueryGroupLocationIndex, u'1');
//    Command::addFunctionStatus(pFunctionInfo, VtechVirtualGroupFunctionCode_QueryVetchGroupItem, 0, 0);   // aid, type
//    Command::addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'V', u'G');
}

#pragma mark - CommandEvent

unsigned short VtechVirtualGroupDevice::onCommandGetProductCode()
{
    return 0xE1;
}

const char* VtechVirtualGroupDevice::onCommandGetProductName()
{
    return "VtechVirtualGroupDevice";
}
