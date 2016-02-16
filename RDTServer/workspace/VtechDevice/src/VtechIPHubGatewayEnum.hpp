//
//  TUTKSampoEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/26.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__VtechIPHubGatewayEnum__
#define __RDTServer__VtechIPHubGatewayEnum__

enum VtechIPHubGatewayFunctionCode
{
    // 查詢所有
    VtechIPHubGatewayFunctionCode_QueryAll                 = 0,
    
    // IP Hub開關詢問
    VtechIPHubGatewayFunctionCode_QuerySwitch              = 1,
    
    // IP Hub開關修改
    VtechIPHubGatewayFunctionCode_ModifySwitch             = 2,
    
    // IP Hub連線狀態詢問
    VtechIPHubGatewayFunctionCode_QueryConnectStatus       = 3,
    
    // IP Hub連線狀態修改
    VtechIPHubGatewayFunctionCode_ModifyConnectStatus      = 4,
    
    // IP Hub電量狀態詢問
    VtechIPHubGatewayFunctionCode_QueryPowerStatus         = 5,
    
    // IP Hub電量狀態修改
    VtechIPHubGatewayFunctionCode_ModifyPowertatus         = 6,
    
    // IP Hub配對狀態詢問
    VtechIPHubGatewayFunctionCode_QueryPairStatus          = 7,
    
    // IP Hub配對狀態修改
    VtechIPHubGatewayFunctionCode_ModifyPairatus           = 8,
    
    // IP Hub Location名稱詢問
    VtechIPHubGatewayFunctionCode_QueryLocationName        = 9,
    
    // IP Hub Location名稱修改
    VtechIPHubGatewayFunctionCode_ModifyLocationName       = 10,
    
    //    // IP Hub群組ID詢問
    //    VtechIPHubGatewayFunctionCode_QueryGroupID             = 11,
    //
    //    // IP Hub群組ID修改
    //    VtechIPHubGatewayFunctionCode_ModifyGroupID            = 12,
    //
    //    // IP Hub群組加入詢問
    //    VtechIPHubGatewayFunctionCode_QueryAddGroupID          = 13,
    //
    //    // IP Hub群組加入修改
    //    VtechIPHubGatewayFunctionCode_ModifyAddGroupID         = 14,
    //
    //    // IP Hub群組離開詢問
    //    VtechIPHubGatewayFunctionCode_QueryLeaveGroupID        = 15,
    //
    //    // IP Hub群組離開修改
    //    VtechIPHubGatewayFunctionCode_ModifyLeaveGroupID       = 16,
    
    //    // IP Hub設備名稱詢問
    //    VtechIPHubGatewayFunctionCode_QueryDeviceName          = 253,
    //
    //    // IP Hub設備名稱修改
    //    VtechIPHubGatewayFunctionCode_ModifyDeviceName         = 254,
};

#endif /* defined(__RDTServer__VtechIPHubGatewayEnum__) */
