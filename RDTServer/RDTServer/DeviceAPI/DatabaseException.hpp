//
//  DatabaseException.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/9.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef DatabaseException_hpp
#define DatabaseException_hpp

#include <stdio.h>
#include <map>
#include "Exception.hpp"

enum DatabaseException_ErrorCode
{
    DatabaseException_ErrorCode_Open_Database_Failed,
    DatabaseException_ErrorCode_Column_Over_The_Range,
    DatabaseException_ErrorCode_Error_Deleting_Database,
};

struct DatabaseException : public Exception
{
    static std::map<int, const char*> createMap()
    {
        std::map<int, const char*> map;
        map[DatabaseException_ErrorCode_Open_Database_Failed]       = "Open Database Failed";
        map[DatabaseException_ErrorCode_Column_Over_The_Range]      = "Column Over The Range";
        map[DatabaseException_ErrorCode_Error_Deleting_Database]    = "Error Deleting Database";
        
        return map;
    }
    
    static std::map<int, const char*> errorMessageMap;
    
    DatabaseException(const char* function, int line, int errorCode) : Exception(function, line, errorCode, errorMessageMap[errorCode]) {}
    DatabaseException(const char* function, int line, char* errorMessage) : Exception(function, line, -1, errorMessage) {}
};

#endif /* DatabaseException_hpp */
