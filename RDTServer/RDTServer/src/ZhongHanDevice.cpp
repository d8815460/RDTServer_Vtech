//
//  ZhongHanDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/4/9.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "ZhongHanDevice.hpp"
#include "AccessoryTypeEnum.hpp"

#pragma mark - Normal Method

#pragma mark - CommandEvent

unsigned short ZhongHanDevice::onCommandGetProductCode()
{
    return 0x0F0;
}

const char* ZhongHanDevice::onCommandGetProductName()
{
    return "ZhongHanDevice";
}
