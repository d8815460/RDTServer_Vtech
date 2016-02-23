//
//  Sampo.cpp
//  RDTServer
//
//  Created by jakey on 2015/4/21.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "SampoDevice.hpp"
#include "Utility.hpp"
#include "AccessoryTypeEnum.hpp"
#include "TUTKSampoEnum.hpp"
#include "BinraryRDTServerCommand.hpp"

void SampoDevice::constructorFinish()
{
    LOGD("constructorFinish");
    
    BinraryRDTServerCommand *pBinraryRDTServerCommand = (BinraryRDTServerCommand*) m_pCommand;
    FunctionInfo* pFunctionInfo = pFunctionInfo = pBinraryRDTServerCommand->createFunctionInfo(Accessory_Type_Air_Conditioner);
    
    /* functionStatus */
    // 冷 氣 開 關 狀 態
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryPowerOn, 1);
    
    // 舒 眠 狀 態 開 關
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QuerySleeping, 1);
    
    // P I C O 狀 態 開 關
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryPicoPure, 1);
    
    // 雙 倍 淨 開 關
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryDoubleClean, 1);
    
    // 狀 態 音 開 關
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryStatusTone, 0);
    
    // 故 障 狀 態
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryFaultStatus, 1, 31, 33, 4, 37);
    
    // 定 時 狀 態
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryTimingStatus, 0);
    
    // 模 式 選 擇 狀 態
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryModeSelectionStatus, 4);
    
    // 風 量 模 式 狀 態
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryAirVolume, 2);
    
    // 風 向 模 式 狀 態
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryWindDirection, 3);
    
    // 冷氣室內溫度狀態查詢(室內溫度 Only)
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryDeviceMode, 25, 0);
    
    // 其 他 運 轉 模 式 狀 態
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryOtherOperatingMode, 1);
    
    // 冷 氣 設 定 溫 度
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryTemperature, 25, 0);
    
    // 定 時 開 關 機 時 間
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryTiming, 0, 0);
    
    // 查 詢 冷 氣 設 備 名 稱
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'聲', u'寶');
    
    // 查 詢 冷 氣 裝 置 室 外 溫 度 狀 態
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, AirConditionerFunctionCode_QueryOutdoorStatus, 28, 0); 
}

SampoDevice::~SampoDevice()
{
}

#pragma mark - Normal Method

#pragma mark - CommandEvent

unsigned short SampoDevice::onCommandGetProductCode()
{
    return 0x0F3;
}

const char* SampoDevice::onCommandGetProductName()
{
    return "SampoDevice";
}

void SampoDevice::onCommandRecvCommand28(FunctionStatus* pFunctionStatus)
{
    // 查詢關機
    if (pFunctionStatus->functionCode == AirConditionerFunctionCode_QueryPowerOn) {
        // AirConditionerFunctionCode_QueryDoubleClean

        // 查詢 transferCode
        unsigned short transferCodeArray[pFunctionStatus->functionCodeList.size()];
        for (int i=0 ; i<pFunctionStatus->functionCodeList.size() ; i++) {
            LOGD("transferCode:%d", pFunctionStatus->functionCodeList[i]->transferCode);
            
            transferCodeArray[i] = pFunctionStatus->functionCodeList[i]->transferCode;
        }

        // 目前是關機
        if (transferCodeArray[0] == 0) {
            LOGD("目前是關機");
        }
    }
}