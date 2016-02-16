//
//  TUTKSampoEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/26.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__VtechVirtualGroupEnum__
#define __RDTServer__VtechVirtualGroupEnum__

enum VtechVirtualGroupFunctionCode
{
    // 查詢所有
    VtechVirtualGroupFunctionCode_QueryAll                 = 0,
    
    // 開關詢問
    VtechVirtualGroupFunctionCode_QuerySwitch              = 1,
    
    // 開關修改
    VtechVirtualGroupFunctionCode_ModifySwitch             = 2,
    
    //    // 連線狀態詢問
    //    VtechVirtualGroupFunctionCode_QueryConnectStatus       = 3,
    //
    //    // 連線狀態修改
    //    VtechVirtualGroupFunctionCode_ModifyConnectStatus      = 4,
    //
    //    // 觸發狀態詢問
    //    VtechVirtualGroupFunctionCode_QueryTriggeredStatus     = 5,
    //
    //    // 觸發狀態修改
    //    VtechVirtualGroupFunctionCode_ModifyTriggeredStatus    = 6,
    //
    //    // 警⽰示狀態詢問
    //    VtechVirtualGroupFunctionCode_QueryAlarmStatus         = 7,
    //
    //    // 警⽰示狀態修改
    //    VtechVirtualGroupFunctionCode_ModifyAlarmStatus        = 8,
    
    // Vetch Group Location名稱詢問
    VtechVirtualGroupFunctionCode_QueryGroupLocationName     = 9,
    
    // Vetch Group Location名稱修改
    VtechVirtualGroupFunctionCode_ModifyGroupLocationName    = 10,
    
    // IP Hub群組ID詢問
    VtechVirtualGroupFunctionCode_QueryGroupID             = 11,
    
    // IP Hub群組ID修改
    VtechVirtualGroupFunctionCode_ModifyGroupID            = 12,
    
    // IP Hub群組加入詢問
    VtechVirtualGroupFunctionCode_QueryAddGroupID          = 13,
    
    // IP Hub群組加入修改
    VtechVirtualGroupFunctionCode_ModifyAddGroupID         = 14,
    
    // IP Hub群組離開詢問
    VtechVirtualGroupFunctionCode_QueryLeaveGroupID        = 15,
    
    // IP Hub群組離開修改
    VtechVirtualGroupFunctionCode_ModifyLeaveGroupID       = 16,
    
    // Vetch Group Location Index詢問
    VtechVirtualGroupFunctionCode_QueryGroupLocationIndex  = 21,
    
    // Vetch Group Location Index修改
    VtechVirtualGroupFunctionCode_ModifyGroupLocationIndex = 22,
    
    // Vetch Group Item詢問
    VtechVirtualGroupFunctionCode_QueryVetchGroupItem      = 23,
    
    // VVetch Group Item修改
    VtechVirtualGroupFunctionCode_ModifyVetchGroupItem     = 24,
    
    //    // 智能PIR設備名稱詢問
    //    VtechVirtualGroupFunctionCode_QueryDeviceName          = 253,
    //
    //    // 智能PIR設備名稱修改
    //    VtechVirtualGroupFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__VtechVirtualGroupEnum__) */
