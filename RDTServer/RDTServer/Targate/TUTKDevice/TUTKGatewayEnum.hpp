//
//  TUTKGatewayEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/1.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKGatewayEnum__
#define __RDTServer__TUTKGatewayEnum__

enum TUTKGatewayFunctionCode
{
    // 查詢所有
    TUTKGatewayFunctionCode_QueryAll           = 0,
    
//    // 智能插座開關狀態詢問
//    TUTKGatewayFunctionCode_QuerySwitch        = 1,
//
//    // 智能插座開關狀態修改
//    TUTKGatewayFunctionCode_ModifySwitch       = 2,
    
    // 智能閘道器佈防模式詢問
    TUTKGatewayFunctionCode_QueryAlarm         = 3,
    
    // 智能閘道器佈防模式修改
    TUTKGatewayFunctionCode_ModifyAlarm        = 4,
    
    // 智能閘道即時報警狀態詢問
    TUTKGatewayFunctionCode_QueryAlert         = 5,
    
    // 智能閘道即時報警狀態修改
    TUTKGatewayFunctionCode_ModifyAlert        = 6,
};

enum TUTKGatewaySensorFunctionCode
{
    // 查詢所有
    TUTKGatewaySensorFunctionCode_QueryAll              = 0,
    
    // 智能PIR開關詢問
    TUTKGatewaySensorFunctionCode_QuerySwitch           = 1,
    
    // 智能PIR開關修改
    TUTKGatewaySensorFunctionCode_ModifySwitch          = 2,
    
    // 智能PIR連線狀態詢問
    TUTKGatewaySensorFunctionCode_QueryConnectStatus    = 3,
    
    // 智能PIR連線狀態修改
    TUTKGatewaySensorFunctionCode_ModifyConnectStatus   = 4,
    
    // 智能PIR觸發狀態詢問
    TUTKGatewaySensorFunctionCode_QueryTriggeredStatus  = 5,
    
    // 智能PIR觸發狀態修改
    TUTKGatewaySensorFunctionCode_ModifyTriggeredStatus = 6,
    
    // 智能PIR警⽰示狀態詢問
    TUTKGatewaySensorFunctionCode_QueryAlarmStatus      = 7,
    
    // 智能PIR警⽰示狀態修改
    TUTKGatewaySensorFunctionCode_ModifyAlarmStatus     = 8,
    
    // 智能PIR SOS狀態詢問
    TUTKGatewaySensorFunctionCode_QuerySOSStatus        = 9,
    
    // 智能PIR SOS狀態修改
    TUTKGatewaySensorFunctionCode_ModifySOStatus        = 10,
    
    // 智能PIR電量狀態詢問
    TUTKGatewaySensorFunctionCode_QueryPowerStatus      = 11,
    
    // 智能PIR電量狀態修改
    TUTKGatewaySensorFunctionCode_ModifyPowertatus      = 12,
    
    //    // 智能PIR裝置名稱詢問
    //    TUTKGatewaySensorFunctionCode_QueryDeviceName      = 253,
    //
    //    // 智能PIR裝置名稱修改
    //    TUTKGatewaySensorFunctionCode_ModifyDeviceName     = 254,
};

//enum TUTKGatewayAccessoryStatus
//{
//    TUTKGatewayAccessoryStatus_Unknown = 0,
//    TUTKGatewayAccessoryStatus_Normal,
//    TUTKGatewayAccessoryStatus_Triggered,
//    TUTKGatewayAccessoryStatus_Alarm,
//    TUTKGatewayAccessoryStatus_DisAlarm,
//    TUTKGatewayAccessoryStatus_SOS,
//    TUTKGatewayAccessoryStatus_LowPower,
//    TUTKGatewayAccessoryStatus_Unavailable,
//};

#endif /* defined(__RDTServer__TUTKGatewayEnum__) */
