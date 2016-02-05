//
//  RDTClientDevice.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/21.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef JsonRDTClientDevice2_hpp
#define JsonRDTClientDevice2_hpp

#include <stdio.h>
#include "Device.hpp"

class JsonRDTClientDevice2 : public Device
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

#endif /* JsonRDTClientDevice2_hpp */
