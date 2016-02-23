//
//  TUTKGatewayDevice.cpp
//  RDTServer
//
//  Created by jakey on 2015/4/9.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "TUTKGatewayDevice.hpp"
#include <map>
#include "Utility.hpp"
#include "TUTKPlugEnum.hpp"
#include "TUTKLightingEnum.hpp"
#include "TUTKLightingDevice.hpp"
#include "TUTKPlugDevice.hpp"
#include "TUTKPIRDevice.hpp"
#include "TUTKPIREnum.hpp"
#include "TUTKDoorDevice.hpp"
#include "TUTKWaterLeakDevice.hpp"
#include "TUTKSmokeDevice.hpp"
#include "TUTKSirenDevice.hpp"
#include "TUTKGasDevice.hpp"
#include "TUTKVibrateDevice.hpp"
#include "AccessoryTypeEnum.hpp"
#include "BinraryRDTServerCommand.hpp"

//size_t TUTKGatewayDevice::UTF16ToUTF8(char *mbBuffer, const char16_t *utf16String)
//{
//    if(mbBuffer == NULL || utf16String == NULL)
//        return 0;
//    
//    mbstate_t state = { };
//    
//    size_t mbIndex = 0;
//    for(int utf16Index = 0; utf16String[utf16Index] != u'\0'; utf16Index++)
//    {
//        const size_t length = c16rtomb(&mbBuffer[mbIndex], utf16String[utf16Index], &state);
//        mbIndex += length;
//    }
//    
//    mbBuffer[mbIndex] = '\0';
//    
//    return mbIndex;
//}

void TUTKGatewayDevice::constructorFinish()
{
    LOGD("constructorFinish");
    
//    const char16_t* utf16literal = u"我";
////    const char16_t * utf16literal = u"剝";
//                                                                                                        
//    LOGD("sizeof utf8literal:%d", strlen16((char16_t*)utf16literal));
////    LOGD("utf8literal :%s", utf16literal));
////    wprintf(L"alpha is:\n\t%s\n", utf8literal);
//    
//    char16_t newCh[50] = {0};
//    strcpy16(newCh, (char16_t*)utf16literal);
////    LOGD("newCh:%s", newCh);
    
//    set<UBYTE> typeSet;
    
//    char dest[50];
//    wchar_t src[] = L"我的前";
//    size_t len = 3;
////    UTF::utf16ToUtf8(dest, len, src, 3);
//    LOGD("dest:%s", dest);
    
    BinraryRDTServerCommand *pBinraryRDTServerCommand = (BinraryRDTServerCommand*) m_pCommand;
    FunctionInfo* pFunctionInfo = NULL;
    
    /* Function Status 1 */
    pFunctionInfo = pFunctionInfo = pBinraryRDTServerCommand->createFunctionInfo(Accessory_Type_Gateway);
    
    // 裝置名稱詢問 (N)
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKCommonFunctionCode_QueryDeviceName, u'閘', u'道');
    
    // 佈防模式詢問
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKGatewayFunctionCode_QueryAlarm, 1, 1);
    
    // 閘道即時報警詢問
    pBinraryRDTServerCommand->addFunctionStatus(pFunctionInfo, TUTKGatewayFunctionCode_QueryAlert, 1, 1);
    
//    // 長度測試
//    for (int i=0 ; i<150 ; i++) {
//        addFunctionCode(m_DataInfoList[0]->functionStatusList[m_DataInfoList[0]->functionStatusList.size()-1], u'蛋');
//    }
    
    // Sensor
//    TUTKPlugDevice::generatorDataInfoList(m_nMaxAID++, &m_DataInfoList, &m_TypeSet);
//    TUTKLightingDevice::generatorDataInfoList(m_nMaxAID++, &m_DataInfoList, &m_TypeSet);
    TUTKPIRDevice::generatorDataInfoList(m_pCommand);
    TUTKWaterLeakDevice::generatorDataInfoList(m_pCommand);
    TUTKDoorDevice::generatorDataInfoList(m_pCommand);
    TUTKSmokeDevice::generatorDataInfoList(m_pCommand);
    TUTKSirenDevice::generatorDataInfoList(m_pCommand);
    TUTKGasDevice::generatorDataInfoList(m_pCommand);
    TUTKVibrateDevice::generatorDataInfoList(m_pCommand);
    
//    TUTKSmokeDevice::generatorDataInfoList(m_nMaxAID++, &m_DataInfoList, &m_TypeSet);
//    TUTKSmokeDevice::generatorDataInfoList(m_nMaxAID++, &m_DataInfoList, &m_TypeSet);
//    TUTKSmokeDevice::generatorDataInfoList(m_nMaxAID++, &m_DataInfoList, &m_TypeSet);
//    TUTKSirenDevice::generatorDataInfoList(m_nMaxAID++, &m_DataInfoList, &m_TypeSet);
//    TUTKSirenDevice::generatorDataInfoList(m_nMaxAID++, &m_DataInfoList, &m_TypeSet);
//    TUTKSirenDevice::generatorDataInfoList(m_nMaxAID++, &m_DataInfoList, &m_TypeSet);
//    TUTKSmokeDevice::generatorDataInfoList(m_nMaxAID++, &m_DataInfoList, &m_TypeSet);
    
    TUTKPlugDevice::generatorDataInfoList(m_pCommand);
    TUTKPlugDevice::generatorDataInfoList(m_pCommand);
    TUTKPlugDevice::generatorDataInfoList(m_pCommand);
    TUTKPlugDevice::generatorDataInfoList(m_pCommand);
    TUTKPlugDevice::generatorDataInfoList(m_pCommand);
    
    TUTKLightingDevice::generatorDataInfoList(m_pCommand);
    TUTKLightingDevice::generatorDataInfoList(m_pCommand);
    TUTKLightingDevice::generatorDataInfoList(m_pCommand);
    TUTKLightingDevice::generatorDataInfoList(m_pCommand);
    TUTKLightingDevice::generatorDataInfoList(m_pCommand);
}

TUTKGatewayDevice::~TUTKGatewayDevice()
{
    LOGD("~TUTKGatewayDevice");
}

#pragma mark - Normal Method

int TUTKGatewayDevice::strlen16(char16_t* strarg)
{
    int count = 0;
    
    if(!strarg) {
        return -1; //strarg is NULL pointer
    }
    
    char16_t* str = strarg;
    while(*str)
    {
        count++;
        str++;
    }
    
    return count;
}

int TUTKGatewayDevice::strcpy16(char16_t* descStr, char16_t* srcStr)
{
    int count = 0;
    if(!srcStr) {
        return -1; //strarg is NULL pointer
    }
    
    char16_t* str = srcStr;
    while(*str)
    {
        descStr[count] = srcStr[count];
        
        count++;
        str++;
    }
    
    return count;
}

#pragma mark - CommandEvent

unsigned short TUTKGatewayDevice::onCommandGetProductCode()
{
    return 0x0F4;
}

const char* TUTKGatewayDevice::onCommandGetProductName()
{
    return "TUTKGatewayDevice";
}
