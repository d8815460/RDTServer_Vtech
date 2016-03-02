//
//  RDTException.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/1.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef RDTException_hpp
#define RDTException_hpp

#include <stdio.h>
#include <map>
#include <string>
#include "Exception.hpp"
#include "RDTAPIs.h"

struct RDTException : public Exception
{
    static std::map<int, const char*> createMap()
    {
        std::map<int, const char*> map;
        map[RDT_ER_NOT_INITIALIZED]					= "RDT module is not initialized yet. Please use RDT_Initialize() for initialization.";
        map[RDT_ER_ALREADY_INITIALIZED]				= "RDT module is already initialized. It is not necessary to re-initialize.";
        map[RDT_ER_EXCEED_MAX_CHANNEL]				= "The number of RDT channels has reached maximum.\nPlease use RDT_Set_Max_Channel_Number() to set up the max number of RDT channels.\nBy default, the maximum channel number is #MAX_DEFAULT_RDT_CHANNEL_NUMBER.";
        map[RDT_ER_MEM_INSUFF]						= "Insufficient memory for allocation";
        map[RDT_ER_FAIL_CREATE_THREAD]              = "RDT module fails to create threads. Please check if OS has ability to\ncreate threads for RDT module.";
        map[RDT_ER_FAIL_CREATE_MUTEX]               = "RDT module fails to create Mutexs when doing initialization. Please check\nif OS has sufficient Mutexs for RDT module.";
        map[RDT_ER_RDT_DESTROYED]                   = "RDT channel has been destroyed. Probably caused by local or remote site\ncalls RDT_Destroy(); or remote site has closed IOTC session.";
        map[RDT_ER_TIMEOUT]                         = "The specified timeout has expired during the execution of some RDT module service.\nFor most cases, it is caused by slow response of remote site or network connection issues";
        map[RDT_ER_INVALID_RDT_ID]					= "The specified RDT channel ID is valid";
        map[RDT_ER_RCV_DATA_END]                    = "The remote site has finished sending data, then destroy the RDT channel.\nThe local site will get this error code by RDT_Read() when there is no\ndata from this RDT channel.";
        map[RDT_ER_REMOTE_ABORT]                    = "The remote site want to abort the RDT channel immediately and don't care data transmission.\nThe local site will get this error code by RDT_Read(), RDT_Write(), RDT_Destroy() for handling\nthis RDT channel to close.";
        map[RDT_ER_LOCAL_ABORT]						= "The local site called RDT_Abort() so the RDT channel is already not available.";
        map[RDT_ER_CHANNEL_OCCUPIED]                = "The specific IOTC session and channel ID is used now so can't use the same resource.\nYou can choose other IOTC channel for RDT use or wait RDT_Abort() to release resource automatically.";
        map[RDT_ER_NO_PERMISSION]					= "This is a lite UID and it does not support RDT module.";
        map[RDT_ER_INVALID_ARG]						= "The arguments passed to a function is invalid.";
        map[RDT_ER_LOCAL_EXIT]						= "The local site called RDT_Create_Exit() so the RDT channel exit creating.";
        map[RDT_ER_REMOTE_EXIT]						= "The remote site called RDT_Create_Exit() so the RDT channel exit creating.";
        map[RDT_ER_SEND_BUFFER_FULL]				= "The RDT write buffer is full. Try again after min 1ms  this Error code only return when RDT_Set_Max_SendBuff_Size is be set.";
        map[RDT_ER_UNCLOSED_CONNECTION_DETECTED]	= "All RDT connection should call RDT_Abort or RDT_Destroy before doing RDT_Deinitialize";
        
        return map;
    }
    
    static std::map<int, const char*> errorMessageMap;
    
    RDTException(const char* function, int line, int errorCode) : Exception(function, line, errorCode, errorMessageMap[errorCode]) {}
};
    
#endif /* RDTException_hpp" */
