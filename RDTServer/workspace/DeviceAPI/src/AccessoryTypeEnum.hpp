//
//  AccessoryTypeEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__AccessoryTypeEnum__
#define __RDTServer__AccessoryTypeEnum__
 
#include <stdio.h>

enum AccessoryType
{
    Accessory_Type_Gateway                       = 1,       //中翰Gateway
    Accessory_Type_Light                         = 2,       //大陽Light
    Accessory_Type_Plug                          = 3,       //大陽Plug
    Accessory_Type_IPCam                         = 4,       //TUTK IPCamera
    Accessory_Type_Door                          = 11,      //中翰Door
    Accessory_Type_Smoke                         = 12,      //中翰Smoke
    Accessory_Type_WaterLeak                     = 13,      //中翰Water
    Accessory_Type_PIR                           = 14,      //中翰PIR
    Accessory_Type_Gas                           = 15,      //TUTK Gas
    Accessory_Type_Vibrate                       = 16,      //TUTK Vibrate
    Accessory_Type_IP_Camera                     = 17,      // (中翰原本使⽤用17需要改成4)
    Accessory_Type_Leak                          = 18,      //TUTK Water
    Accessory_Type_Air_Conditioner               = 19,      //聲寶冷氣
    Accessory_Type_Siren                         = 20,      //中翰Siren
    
    Accessory_Type_DayangPlug1                   = 21,      //大阳PLug1
    Accessory_Type_DayangPlug2                   = 22,      //大阳Plug2
    Accessory_Type_DayangLight1                  = 23,      //大阳Light1
    Accessory_Type_DayangLight2                  = 24,      //大阳Light2
    Accessory_Type_DayangPir                     = 25,      //大阳Pir
    Accessory_Type_DayangDoor                    = 26,      //大阳Door
    
    Accessory_Type_VtechIPHubGateway             = 33,      //VtechIPHubGateway
    Accessory_Type_VtechGarageDoor               = 34,      //VtechGarageDoor
    Accessory_Type_VtechOpenClosed               = 35,      //VtechOpenClosed
    Accessory_Type_VtechMotionSensor             = 36,      //VtechMotionSensor
    Accessory_Type_VtechLightBulb                = 37,      //VtechLightBulb
    Accessory_Type_VtechWallSwitch               = 38,      //VtechWallSwitch
    Accessory_Type_VtechVirtualGroup             = 39,      //VtechVirtualGroup
};

enum TUTKCommonFunctionCode
{
    // 裝置名稱詢問
    TUTKCommonFunctionCode_QueryDeviceName    = 253,
    
    // 裝置名稱修改
    TUTKCommonFunctionCode_ModifyDeviceName   = 254,
};

#endif /* defined(__RDTServer__AccessoryTypeEnum__) */
