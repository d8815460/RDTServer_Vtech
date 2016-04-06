//
//  RDTProtocolException.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/4/6.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef RDTProtocolException_hpp
#define RDTProtocolException_hpp

#include <stdio.h>
#include <map>
#include "Exception.hpp"

enum RDTProtocolException_ErrorCode
{
    RDTProtocolException_Data_Access_Error = 1,
};

struct RDTProtocolException : public Exception
{
    static std::map<int, const char*> createMap()
    {
        std::map<int, const char*> map;
        map[RDTProtocolException_Data_Access_Error]       = "Data Access Error";
        
        return map;
    }
    
    static std::map<int, const char*> errorMessageMap;
    
    RDTProtocolException(const char* function, int line, int errorCode) : Exception(function, line, "RDTProtocolException", errorCode, errorMessageMap[errorCode]) {}
};

#endif /* RDTProtocolException_hpp */
