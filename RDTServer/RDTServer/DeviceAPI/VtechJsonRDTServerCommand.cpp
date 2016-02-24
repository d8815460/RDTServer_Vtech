//
//  VtechJsonRDTServerCommand.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/2/24.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "VtechJsonRDTServerCommand.hpp"

VtechJsonRDTServerCommand::VtechJsonRDTServerCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData) : JsonRDTServerCommand(pCommandEvent, pCommandHardwardEvent, pConnect, pCommandData)
{
    LOGD("VtechJsonRDTServerCommand");
}
