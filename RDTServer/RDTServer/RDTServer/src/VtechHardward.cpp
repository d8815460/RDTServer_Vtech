//
//  VtechHardward.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/28.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "VtechHardward.hpp"

VtechHardward::VtechHardward(HardwardEvent* pHardwardEvent, HardwardData* pHardwardData) : Hardward(pHardwardEvent, pHardwardData)
{
    LOGD("VtechHardward");
}

void VtechHardward::sendHardward(SendHardwardData* pSendHardwardData)
{
    // 轉型為VtechHardward_HardwardSendData
    VtechHardward_SendHardwardData* pVtechHardwardSendHardwardData = (VtechHardward_SendHardwardData*) pSendHardwardData;
    
    // 取得輸入與輸出的資料
    const Json::Value* pInJsonObject = pVtechHardwardSendHardwardData->pInJsonObject;
    Json::Value* pOutJsonObject = pVtechHardwardSendHardwardData->pOutJsonObject;
    
    // 將輸入資料打印出來
    std::string serno = (*pInJsonObject)["serno"].asString();
    LOGD("serno:%s", serno.c_str());
    
    // 填入輸出資料
    (*pOutJsonObject)["serno"] = "222222";
    (*pOutJsonObject)["operation"] = "read";
    (*pOutJsonObject)["target"] = "/accessory/0/product_name/";
}
