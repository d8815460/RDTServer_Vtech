//
//  CommandException.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/2.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef CommandException_hpp
#define CommandException_hpp

#include <stdio.h>
#include <map>
#include "RDTAPIs.h"
#include "Exception.hpp"

enum CommandException_ErrorCode
{
    CommandException_ErrorCode_Packet_Not_Match,
    CommandException_ErrorCode_No_Match_RDT_Command,
    CommandException_ErrorCode_No_Match_Command_Target,
    CommandException_ErrorCode_No_Match_Command_Operation,
    CommandException_ErrorCode_DataType_Not_Found,
    CommandException_ErrorCode_Json_Formate_Error,
};

struct CommandException : public Exception
{
    static std::map<int, const char*> createMap()
    {
        std::map<int, const char*> map;
        map[CommandException_ErrorCode_Packet_Not_Match]			= "Packet Not Match";
        map[CommandException_ErrorCode_No_Match_RDT_Command]        = "No Match RDT Command";
        map[CommandException_ErrorCode_No_Match_Command_Target]     = "No Match Command Target";
        map[CommandException_ErrorCode_No_Match_Command_Operation]  = "No Match Command Operation";
        map[CommandException_ErrorCode_DataType_Not_Found]          = "DataType Not Found";
        map[CommandException_ErrorCode_Json_Formate_Error]          = "Json Formate Error";
        
        return map;
    }
    
    static std::map<int, const char*> errorMessageMap;
    
    CommandException(const char* function, int line, int errorCode) : Exception(function, line, errorCode, errorMessageMap[errorCode]) {}
};

#endif /* CommandException_hpp */
