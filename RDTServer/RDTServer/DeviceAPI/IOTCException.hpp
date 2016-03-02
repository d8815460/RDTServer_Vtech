//
//  IOTCException.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/1.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef IOTCException_hpp
#define IOTCException_hpp

#include <stdio.h>
#include <map>
#include "Exception.hpp"
#include "IOTCAPIs.h"

struct IOTCException : public Exception
{
    static std::map<int, const char*> createMap()
    {
        std::map<int, const char*> map;
        map[IOTC_ER_NoERROR]                = "The function is performed successfully.";
        map[IOTC_ER_SERVER_NOT_RESPONSE]    = "IOTC servers have no response, probably caused by many types of Internet connection issues.";
        map[IOTC_ER_FAIL_RESOLVE_HOSTNAME]  = "IOTC masters cannot be resolved their domain name, probably caused\nby network connection or DNS setting issues.";
        map[IOTC_ER_ALREADY_INITIALIZED]    = "IOTC module is already initialized. It is not necessary to re-initialize.";
        map[IOTC_ER_FAIL_CREATE_MUTEX]      = "IOTC module fails to create Mutexs when doing initialization. Please\ncheck if OS has sufficient Mutexs for IOTC platform.";
        map[IOTC_ER_FAIL_CREATE_THREAD]     = "IOTC module fails to create threads. Please check if OS has ability\nto create threads for IOTC module.";
        map[IOTC_ER_FAIL_CREATE_SOCKET]     = "IOTC module fails to create sockets. Please check if OS supports socket service";
        map[IOTC_ER_FAIL_SOCKET_OPT]        = "IOTC module fails to set up socket options.";
        map[IOTC_ER_FAIL_SOCKET_BIND]       = "IOTC module fails to bind sockets";
        map[IOTC_ER_UNLICENSE]              = "The specified UID is not licensed or expired.";
        map[IOTC_ER_LOGIN_ALREADY_CALLED]   = "The device is already under login process currently\nso it is prohibited to invoke login again at this moment.";
        map[IOTC_ER_NOT_INITIALIZED]        = "IOTC module is not initialized yet. Please use IOTC_Initialize() or\nIOTC_Initialize2() for initialization.";
        map[IOTC_ER_TIMEOUT]                = "The specified timeout has expired during the execution of some IOTC\nmodule service. For most cases, it is caused by slow response of remote\nsite or network connection issues";
        map[IOTC_ER_INVALID_SID]            = "The specified IOTC session ID is not valid";
        map[IOTC_ER_UNKNOWN_DEVICE]         = "The specified device's name is unknown to the IOTC servers";
        map[IOTC_ER_FAIL_GET_LOCAL_IP]      = "IOTC module fails to get the local IP address";
        map[IOTC_ER_LISTEN_ALREADY_CALLED]  = "The device already start to listen for connections from clients. It is\nnot necessary to listen again.";
        map[IOTC_ER_EXCEED_MAX_SESSION]     = "The number of IOTC sessions has reached maximum.\nTo increase the max number of IOTC sessions, please use IOTC_Set_Max_Session_Number()\nbefore initializing IOTC module.";
        map[IOTC_ER_CAN_NOT_FIND_DEVICE]    = "IOTC servers cannot locate the specified device, probably caused by\ndisconnection from the device or that device does not login yet.";
        map[IOTC_ER_CONNECT_IS_CALLING]     = "The client is already connecting to a device currently\nso it is prohibited to invoke connection again at this moment.";
        map[IOTC_ER_SESSION_CLOSE_BY_REMOTE]    = "The remote site already closes this IOTC session.\nPlease call IOTC_Session_Close() to release IOTC session resource in locate site.";
        map[IOTC_ER_REMOTE_TIMEOUT_DISCONNECT]  = "This IOTC session is disconnected because remote site has no any response\n after a specified timeout expires, i.e. #IOTC_SESSION_ALIVE_TIMEOUT";
        map[IOTC_ER_DEVICE_NOT_LISTENING]   = "The client fails to connect to a device because the device is not listening for connections.";
        map[IOTC_ER_CH_NOT_ON]              = "The IOTC channel of specified channel ID is not turned on before transferring data.";
        map[IOTC_ER_FAIL_CONNECT_SEARCH]    = "A client stops connecting to a device by calling IOTC_Connect_Stop()";
        map[IOTC_ER_MASTER_TOO_FEW]         = "Too few masters are specified when initializing IOTC module.\nTwo masters are required for initialization at minimum.";
        map[IOTC_ER_AES_CERTIFY_FAIL]       = "A client fails to pass certification of a device due to incorrect key.";
        map[IOTC_ER_SESSION_NO_FREE_CHANNEL]    = "The number of IOTC channels for a IOTC session has reached maximum, say, #MAX_CHANNEL_NUMBER";
        map[IOTC_ER_TCP_TRAVEL_FAILED]      = "Cannot connect to masters neither UDP mode nor TCP mode by IP or host name ways";
        map[IOTC_ER_TCP_CONNECT_TO_SERVER_FAILED]   = "Cannot connect to IOTC servers in TCP";
        map[IOTC_ER_CLIENT_NOT_SECURE_MODE]     = "A client wants to connect to a device in non-secure mode while that device\nsupports secure mode only.";
        map[IOTC_ER_CLIENT_SECURE_MODE]     = "A client wants to connect to a device in secure mode while that device does\nnot support secure mode.";
        map[IOTC_ER_DEVICE_NOT_SECURE_MODE] = "A device does not support connection in secure mode";
        map[IOTC_ER_DEVICE_SECURE_MODE]     = "A device does not support connection in non-secure mode";
        map[IOTC_ER_INVALID_MODE]           = "The IOTC session mode specified in IOTC_Listen2(), IOTC_Connect_ByUID2()\nis not valid. Please see #IOTCSessionMode for possible modes.";
        map[IOTC_ER_EXIT_LISTEN]            = "A device stops listening for connections from clients.";
        map[IOTC_ER_NO_PERMISSION]          = "The specified device does not support advance function\n(TCP relay and P2PTunnel module)";
        map[IOTC_ER_NETWORK_UNREACHABLE]    = "Network is unreachable, please check the network settings";
        map[IOTC_ER_FAIL_SETUP_RELAY]       = "A client fails to connect to a device via relay mode";
        map[IOTC_ER_NOT_SUPPORT_RELAY]      = "A client fails to use UDP relay mode to connect to a device\nbecause UDP relay mode is not supported for that device by IOTC servers";
        map[IOTC_ER_NO_SERVER_LIST]         = "No IOTC server information while device login or client connect\nbecause no IOTC server is running or not add IOTC server list";
        map[IOTC_ER_DEVICE_MULTI_LOGIN]     = "The connecting device duplicated loggin and may unconnectable.";
        map[IOTC_ER_INVALID_ARG]            = "The arguments passed to a function is invalid.";
        map[IOTC_ER_NOT_SUPPORT_PE]         = "The remote device not support partial encoding.";
        map[IOTC_ER_DEVICE_EXCEED_MAX_SESSION]  = "The remote device no more free session can be connected.";
        map[IOTC_ER_BLOCKED_CALL]               = "The function call is a blocking call and was called by other thread.";
        map[IOTC_ER_SESSION_CLOSED]         = "The session was closed.";
        map[IOTC_ER_REMOTE_NOT_SUPPORTED]   = "Remote doesn't support this function.";
        map[IOTC_ER_ABORTED]                = "The function is aborted by related function.";
        map[IOTC_ER_EXCEED_MAX_PACKET_SIZE]     = "The buffer size exceed maximum packet size.";
        map[IOTC_ER_SERVER_NOT_SUPPORT]     = "Server does not support this feature.";
        map[IOTC_ER_NO_PATH_TO_WRITE_DATA]  = "Cannot find a path to write data";
        map[IOTC_ER_SERVICE_IS_NOT_STARTED] = "Start function is not called";
        map[IOTC_ER_STILL_IN_PROCESSING]    = "Already in processing";
        map[IOTC_ER_NOT_ENOUGH_MEMORY]      = "Out of memory";
        map[IOTC_ER_DEVICE_IS_BANNED]       = "The device is banned and locked";
        map[IOTC_ER_MASTER_NOT_RESPONSE]    = "IOTC master servers have no response, probably caused by many types of Internet connection issues.";
        map[IOTC_ER_DEVICE_OFFLINE]         = "All Server response can not find device";
        
        return map;
    }
    
    static std::map<int, const char*> errorMessageMap;
    
    IOTCException(const char* function, int line, int errorCode) : Exception(function, line, errorCode, errorMessageMap[errorCode]) {}
};

#endif /* IOTCException_hpp */
