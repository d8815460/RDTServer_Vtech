//
//  SystemException.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/30.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef SystemException_hpp
#define SystemException_hpp

#include <stdio.h>
#include <map>
#include "Exception.hpp"

enum SystemException_ErrorCode
{
    SystemException_ErrorCode_Device_two_constrator_error = 1,
};

struct SystemException : public Exception
{
    static std::map<int, const char*> createMap()
    {
        std::map<int, const char*> map;
        map[SystemException_ErrorCode_Device_two_constrator_error]       = "Device two constrator error";
        
        return map;
    }
    
    static std::map<int, const char*> errorMessageMap;
    
    SystemException(const char* function, int line, int errorCode) : Exception(function, line, "SystemException", errorCode, errorMessageMap[errorCode]) {}
};

#endif /* SystemException_hpp */
