//
//  ZhongHanDevice.h
//  RDTServer
//
//  Created by jakey on 2015/4/9.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__ZhongHanDevice__
#define __RDTServer__ZhongHanDevice__

#include <stdio.h>
#include "Device.hpp"

class ZhongHanDevice : public Device
{
public:
#pragma mark - Device
    virtual void constructorFinish() { }
    
protected:
    virtual unsigned short onCommandGetProductCode();
    virtual const char* onCommandGetProductName();
    
private:
    bool m_bOnOff;
};

#endif /* defined(__RDTServer__ZhongHanDevice__) */
