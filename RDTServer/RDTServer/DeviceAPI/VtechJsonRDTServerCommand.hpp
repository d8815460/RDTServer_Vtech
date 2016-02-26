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

struct GroupData : BaseData
{
    int groupId;
    
    void print()
    {
        LOGD("groupId:%d", groupId);
        
        BaseData::print();
    }
};

class VtechJsonRDTServerCommand : public JsonRDTServerCommand
{
public:
    VtechJsonRDTServerCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData = NULL);
    
    vector<GroupData*>* getGeoupList()
    {
        return &m_groupList;
    }
    
#pragma mark - JsonRDTCommand
protected:
    virtual bool processCommandTarget(const Json::Value& jsonObject, Json::Value& outJsonObject);
    
#pragma mark - Member
protected:
    vector<GroupData*>  m_groupList;
};

#endif /* VtechJsonRDTServerCommand_hpp */
