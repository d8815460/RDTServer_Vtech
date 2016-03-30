//
//  VtechHardwareException.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/30.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef VtechHardwareException_hpp
#define VtechHardwareException_hpp

#include <stdio.h>

#include <stdio.h>
#include <map>
#include "Exception.hpp"

enum VtechHardwareException_ErrorCode
{
    VtechHardwareException_ErrorCode_device_link_error = 1,
    VtechHardwareException_ErrorCode_device_command_handle_error,
    VtechHardwareException_ErrorCode_device_not_found,
    VtechHardwareException_ErrorCode_device_type_error,
    VtechHardwareException_ErrorCode_device_registration_error,
    VtechHardwareException_ErrorCode_device_registration_timeout,
    VtechHardwareException_ErrorCode_device_delete_failed,
    VtechHardwareException_ErrorCode_device_record_is_corrupted,
    VtechHardwareException_ErrorCode_function_code_not_supported,
    VtechHardwareException_ErrorCode_function_code_value_is_out_of_range,
    VtechHardwareException_ErrorCode_function_code_value_type_error,
    VtechHardwareException_ErrorCode_cannot_contact_OTA_server,
    VtechHardwareException_ErrorCode_OTA_file_download_error,
    VtechHardwareException_ErrorCode_device_OTA_update_failed,
    VtechHardwareException_ErrorCode_IP_hub_OTA_update_failed,
    VtechHardwareException_ErrorCode_cannot_register_to_TUTK_push_notification_server,
    VtechHardwareException_ErrorCode_No_internet_connection,
    VtechHardwareException_ErrorCode_No_LAN_connection,
    VtechHardwareException_ErrorCode_user_authentication_error,
    VtechHardwareException_ErrorCode_group_create_failed,
    VtechHardwareException_ErrorCode_delete_group_failed,
    VtechHardwareException_ErrorCode_add_device_to_group_failed,
    VtechHardwareException_ErrorCode_remove_device_to_group_failed,
    VtechHardwareException_ErrorCode_backup_failed,
    VtechHardwareException_ErrorCode_restore_failed,
    VtechHardwareException_ErrorCode_activity_log_access_error,
    VtechHardwareException_ErrorCode_activity_log_file_is_full,
    VtechHardwareException_ErrorCode_ULE_system_error,
    VtechHardwareException_ErrorCode_ULE_system_busy,
    VtechHardwareException_ErrorCode_system_storage_is_full,
    VtechHardwareException_ErrorCode_general_system_error,
};

struct VtechHardwareException : public Exception
{
    static std::map<int, const char*> createMap()
    {
        std::map<int, const char*> map;
        map[VtechHardwareException_ErrorCode_device_link_error]                 = "device link error (note that device means sensor in this document, e.g. motion, door....)";
        map[VtechHardwareException_ErrorCode_device_command_handle_error]       = "device command handle error";
        map[VtechHardwareException_ErrorCode_device_not_found]                  = "device not found (accessoryId not found)";
        map[VtechHardwareException_ErrorCode_device_type_error]                 = "device type error (e.g. device exists but it's supposed to be a light bulb instead of a motion sensor)";
        map[VtechHardwareException_ErrorCode_device_registration_error]         = "device registration error";
        map[VtechHardwareException_ErrorCode_device_registration_timeout]       = "device registration timeout";
        map[VtechHardwareException_ErrorCode_device_delete_failed]              = "device delete failed";
        map[VtechHardwareException_ErrorCode_device_record_is_corrupted]        = "device record is corrupted (when this happened the user may need to re-register all the devices again)";
        map[VtechHardwareException_ErrorCode_function_code_not_supported]       = "function code not supported (applied to both device and ip-hub itself)";
        map[VtechHardwareException_ErrorCode_function_code_value_is_out_of_range]   =   "function code value is out of range";
        map[VtechHardwareException_ErrorCode_function_code_value_type_error]        =   "function code value type error";
        map[VtechHardwareException_ErrorCode_cannot_contact_OTA_server]             =   "cannot contact OTA server";
        map[VtechHardwareException_ErrorCode_OTA_file_download_error]               =   "OTA file download error";
        map[VtechHardwareException_ErrorCode_device_OTA_update_failed]              =   "device OTA update failed";
        map[VtechHardwareException_ErrorCode_IP_hub_OTA_update_failed]              =   "IP-hub OTA update failed";
        map[VtechHardwareException_ErrorCode_cannot_register_to_TUTK_push_notification_server] = "cannot register to TUTK push notification server";
        map[VtechHardwareException_ErrorCode_No_internet_connection]            = "No internet connection (e.g. software OTA, push notification would not work)";
        map[VtechHardwareException_ErrorCode_No_LAN_connection]                 = "No LAN connection";
        map[VtechHardwareException_ErrorCode_user_authentication_error]         = "user authentication error (reserved for account management)";
        map[VtechHardwareException_ErrorCode_group_create_failed]               = "group create failed";
        map[VtechHardwareException_ErrorCode_delete_group_failed]               = "delete group failed";
        map[VtechHardwareException_ErrorCode_add_device_to_group_failed]        = "add device to group failed";
        map[VtechHardwareException_ErrorCode_remove_device_to_group_failed]     = "remove device to group failed";
        map[VtechHardwareException_ErrorCode_backup_failed]                     = "backup failed";
        map[VtechHardwareException_ErrorCode_restore_failed]                    = "restore failed";
        map[VtechHardwareException_ErrorCode_activity_log_access_error]         = "activity log access error";
        map[VtechHardwareException_ErrorCode_activity_log_file_is_full]         = "activity log file is full";
        map[VtechHardwareException_ErrorCode_ULE_system_error]                  = "ULE system error (i.e. sensor RF system)";
        map[VtechHardwareException_ErrorCode_ULE_system_busy]                   = "ULE system busy";
        map[VtechHardwareException_ErrorCode_system_storage_is_full]            = "system storage is full";
        map[VtechHardwareException_ErrorCode_general_system_error]              = "general system error (would require a soft reboot or power cycle)";
                           
        return map;
    }
    
    static std::map<int, const char*> errorMessageMap;
    
    VtechHardwareException(const char* function, int line, int errorCode) : Exception(function, line, "VtechHardwareException", errorCode, errorMessageMap[errorCode]) {}
};

#endif /* VtechHardwareException_hpp */
