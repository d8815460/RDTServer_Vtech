//
//  JsonRDTServerHardward.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/29.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "JsonRDTServerHardward.hpp"

JsonRDTServerHardward::JsonRDTServerHardward(HardwardEvent* pHardwardEvent, HardwardData* pHardwardData) : Hardward(pHardwardEvent, pHardwardData)
{
    LOGD("JsonRDTServerHardward");
}

void JsonRDTServerHardward::sendHardward(SendHardwardData* pSendHardwardData)
{
    // 轉型為VtechHardward_HardwardSendData
    JsonRDTServerHardward_SendHardwardData* pJsonRDTServerHardwardSendHardwardData = (JsonRDTServerHardward_SendHardwardData*) pSendHardwardData;
    
    // 取得輸入與輸出的資料
    const Json::Value* pInJsonObject = pJsonRDTServerHardwardSendHardwardData->pInJsonObject;
    Json::Value* pOutJsonObject = pJsonRDTServerHardwardSendHardwardData->pOutJsonObject;
    
    // 將輸入資料打印出來
    std::string serno = (*pInJsonObject)["serno"].asString();
    LOGD("serno:%s", serno.c_str());
    
    // 填入輸出資料
    (*pOutJsonObject)["serno"] = "222222";
    (*pOutJsonObject)["operation"] = "read";
    (*pOutJsonObject)["target"] = "/accessory/0/product_name/";
    
    // 上報資料
    JsonRDTServerHardward_HardwardNotifyData jsonRDTServerHardwardHardwardNotifyData;
    Json::Value outReportJsonObject;
    jsonRDTServerHardwardHardwardNotifyData.pOutJsonObject = &outReportJsonObject;
    outReportJsonObject["serno"] = "333333";
    outReportJsonObject["operation"] = "update";
    outReportJsonObject["target"] = "/accessory/0/product_code/";
    m_pHardwardEvent->onHardwardNotify(&jsonRDTServerHardwardHardwardNotifyData);
}
