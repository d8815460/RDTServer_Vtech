//
//  VtechJsonRDTServerCommand.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/2/24.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef VtechJsonRDTServerCommand_hpp
#define VtechJsonRDTServerCommand_hpp

#include <stdio.h>
#include "JsonRDTServerCommand.hpp"

class VtechJsonRDTServerCommand : public JsonRDTServerCommand
{
public:
    VtechJsonRDTServerCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData = NULL);
    
#pragma mark - Member
protected:
    vector<AccessoryData*>  m_groupList;
};

#endif /* VtechJsonRDTServerCommand_hpp */
