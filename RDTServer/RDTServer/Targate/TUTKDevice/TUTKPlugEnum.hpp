//
//  TUTKPlugEnum.h
//  RDTServer
//
//  Created by jakey on 2015/6/4.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__TUTKPlugEnum__
#define __RDTServer__TUTKPlugEnum__

#include <stdio.h>

enum TUTKPlugFunctionCode
{
    // 查詢所有
    TUTKPlugFunctionCode_QueryAll           = 0,
    
    // 智能插座開關狀態詢問
    TUTKPlugFunctionCode_QuerySwitch        = 1,
    
    // 智能插座開關狀態修改
    TUTKPlugFunctionCode_ModifySwitch       = 2,
    
    // 智能插座瓦數詢問
    TUTKPlugFunctionCode_QueryWattage       = 3,
    
    // 智能插座瓦數修改
    TUTKPlugFunctionCode_ModifyWattage      = 4,
    
    // 智能插座安培數詢問
    TUTKPlugFunctionCode_QueryAmpere        = 5,
    
    // 智能插座安培數修改
    TUTKPlugFunctionCode_ModifyAmpere       = 6,
    
    // 智能插座伏特數詢問
    TUTKPlugFunctionCode_QueryVolt          = 7,
    
    // 智能插座伏特數修改
    TUTKPlugFunctionCode_ModifyVolt         = 8,
    
//    // 智能插座裝置名稱詢問
//    TUTKPlugFunctionCode_QueryDeviceName    = 9,
//    
//    // 智能插座裝置名稱修改
//    TUTKPlugFunctionCode_ModifyDeviceName   = 10,
    
//    // 智能插座裝置名稱詢問
//    TUTKPlugFunctionCode_QueryDeviceName    = 253,
//    
//    // 智能插座裝置名稱修改
//    TUTKPlugFunctionCode_ModifyDeviceName   = 254,
};

#endif /* defined(__RDTServer__TUTKPlugEnum__) */
