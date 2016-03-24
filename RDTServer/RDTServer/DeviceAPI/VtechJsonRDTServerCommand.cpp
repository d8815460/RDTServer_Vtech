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

#pragma mark - JsonRDTCommand

void VtechJsonRDTServerCommand::processCommandTarget(Json::Value& inJsonObject, Json::Value& outJsonObject) throw (CommandException)
{
    JsonRDTServerCommand::processCommandTarget(inJsonObject, outJsonObject);
    
//    string target = inJsonObject["target"].asString();
//    string operation = inJsonObject["operation"].asString();
//    
//    if (target.find("group") != std::string::npos) {
//        // 新增
//        if (operation.find("create") != std::string::npos) {
//            GroupData* pGroupData = new GroupData();
//            //            pAccessoryData->print();
//            CommandHardwardRecv_CreateItems commandHardwardRecv_CreateItems;
//            commandHardwardRecv_CreateItems.dataType = DataType_Accessory;
//            commandHardwardRecv_CreateItems.pBaseData = pGroupData;
//            m_pCommandHardwardEvent->onCommandHardwardRecv_CreateItem(&commandHardwardRecv_CreateItems);
//            pGroupData->print();
//            
//            m_groupList.push_back(pGroupData);
//        }
//        // 刪除
//        else if (operation.find("delete") != std::string::npos) {
//            size_t pos2 = target.rfind("/") - 1;
//            size_t pos1 = target.rfind("/", pos2);
//            string number = target.substr(pos1 + 1, pos2 - pos1);
//            int accessoryId = atoi(number.c_str());
//            CommandHardwardRecv_DeleteItems commandHardwardRecv_DeleteItems;
//            commandHardwardRecv_DeleteItems.dataType = DataType_Accessory;
//            commandHardwardRecv_DeleteItems.id = accessoryId;
//            m_pCommandHardwardEvent->onCommandHardwardRecv_DeleteItems(&commandHardwardRecv_DeleteItems);
//            //            m_accessoryList.erase();
//        }
//        // 查詢
//        else if (operation.find("read") != std::string::npos) {
//            CommandHardwardRecv_ReadItems commandHardwardRecv_ReadItems;
//            commandHardwardRecv_ReadItems.dataType = DataType_Accessory;
//            //            commandHardwardRecv_ReadItems.m_accessoryList
//            m_pCommandHardwardEvent->onCommandHardwardRecv_ReadItems(&commandHardwardRecv_ReadItems);
//        }
//        // 修改
//        else if (operation.find("update") != std::string::npos) {
//            throw CommandException(__PRETTY_FUNCTION__, __LINE__, CommandException_ErrorCode_No_Match_Command_Operation);
//        }
//        else {
//            throw CommandException(__PRETTY_FUNCTION__, __LINE__, CommandException_ErrorCode_No_Match_Command_Operation);
//        }
//    }
    
//    else {
//        throw CommandException(__PRETTY_FUNCTION__, __LINE__, CommandException_ErrorCode_No_Match_Command_Target);
//    }
}
