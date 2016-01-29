//
//  TUTKGatewayDevice.h
//  RDTServer
//
//  Created by jakey on 2015/4/9.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKGatewayDevice__
#define __RDTServer__TUTKGatewayDevice__

#include <stdio.h>
#include "Device.hpp"
#include <set>
#include "TUTKGatewayEnum.hpp"
#include <list>

using namespace std;

class TUTKGatewayDevice : public Device
{
public:
    ~TUTKGatewayDevice();
    
#pragma mark - Device
    virtual void constructorFinish();
    
protected:
    virtual unsigned short onCommandGetProductCode();
    virtual const char* onCommandGetProductName();
    
    int strlen16(char16_t* strarg);
    int strcpy16(char16_t* descStr, char16_t* srcStr);
    size_t UTF16ToUTF8(char *mbBuffer, const char16_t *utf16String);
        
private:

};

#endif /* defined(__RDTServer__TUTKGatewayDevice__) */
