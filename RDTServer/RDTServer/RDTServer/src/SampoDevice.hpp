//
//  Sampo.h
//  RDTServer
//
//  Created by jakey on 2015/4/21.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__Sampo__
#define __RDTServer__Sampo__

#include <stdio.h>
#include "Device.hpp"

class SampoDevice : public Device
{
public:
    ~SampoDevice();

#pragma mark - Device
    virtual void constructorFinish();
    
protected:
    virtual unsigned short onCommandGetProductCode();
    virtual const char* onCommandGetProductName();
    virtual void onCommandRecvCommand28(FunctionStatus* pFunctionStatus);
        
private:
};

#endif /* defined(__RDTServer__Sampo__) */
