//
//  VtechVirtualGroupDevice.hpp
//  RDTServer
//
//  Created by jakey on 2015/11/25.
//  Copyright © 2015年 jakey. All rights reserved.
//

#ifndef VtechVirtualGroupDevice_hpp
#define VtechVirtualGroupDevice_hpp

#include <stdio.h>
#include "Device.hpp"

class VtechVirtualGroupDevice : public Device
{
public:
    static void generatorDataInfoList(Command* pCommand);
    
#pragma mark - Device
    virtual void constructorFinish() { generatorDataInfoList(m_pCommand); }
    
protected:
    virtual unsigned short onCommandGetProductCode();
    virtual const char* onCommandGetProductName();
    
private:
    bool m_bOnOff;
};

#endif /* VtechVirtualGroupDevice_hpp */
