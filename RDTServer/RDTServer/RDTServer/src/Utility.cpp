//
//  Utility.cpp
//  RDTServer
//
//  Created by jakey on 2015/4/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "Utility.hpp"
#include <cstring>
#include "IOTCAPIs.h"
#include "RDTAPIs.h"
#include "Common.hpp"
#include "ZhongHanDevice.hpp"
#include "TUTKGatewayDevice.hpp"
#include "SampoDevice.hpp"
#include "TUTKPlugDevice.hpp"
#include "TUTKLightingDevice.hpp"
#include "TUTKPIRDevice.hpp"
#include "TUTKDoorDevice.hpp"
#include "TUTKWaterLeakDevice.hpp"
#include "TUTKSmokeDevice.hpp"
#include "TUTKSirenDevice.hpp"
#include "TUTKGasDevice.hpp"
#include "TUTKVibrateDevice.hpp"
#include "VtechIPHubGatewayDevice.hpp"

void Utility::reverse(BYTE* data, const int length)
{
    int SIZE = length;
    UBYTE temp;
    
    for (int i = 0; i < SIZE/2 ; i++)
    {
        temp = data[i];
        data[i] = data[SIZE-1 - i];
        data[SIZE - 1 - i] = temp;
    }
}

unsigned long Utility::bytes2UnsignedLong(BYTE* data, const int length)
{
//    LOGD("data:%s length:%d", data, length);
    reverse(data, length);         // c 的特性需要反轉
//    LOGD("data:%s length:%d", data, length);
    
    int mask = 0xFF;
    int temp = 0;
    unsigned long n = 0;
    for(int i=0 ; i<length ; i++) {
        n <<= 8;
        temp = data[i] & mask;
        //        LOGD("temp:%d", temp);
        n |= temp;
    }
    
    //    LOGD("n = %lld", n);
    return n;
}

unsigned long Utility::bytes2UnsignedLongWithBeginData(BYTE* data, int* pIndex, const int length)
{
    unsigned long value = bytes2UnsignedLong(&data[*pIndex], length);
    *pIndex += length;
    
    return value;
}

void Utility::printData(const char* function, int line, const BYTE* data, const int length)
{
//    LOGD("length:%d", length);
//    LOGD("data:");

    LOGD("\n%s [Line:%d]", function, line);

    for (int i=0 ; i<length ; i++) {
        LOG("%d ", data[i]);
    }

//    for (int i=0 ; i<length ; i++) {
//        LOG("0x%X ", data[i]);
//    }

    LOG("\n\n");
}

void Utility::runBody(Device **ppOutDevice, char deviceName[20], char uid[20])
{
    //    vector<string> deviceList;
    //    deviceList.push_back("PowerStripDevice");
    //    deviceList.push_back("AbocomDevice");
    //    deviceList.push_back("ZhongHanDevice");
    //    deviceList.push_back("PhilipsDevice");
    //    deviceList.push_back("TUTKGatewayDevice");
    //    deviceList.push_back("TUTKPlugDevice");
    //    deviceList.push_back("SampoDevice");
    //    deviceList.push_back("TUTKLightingDevice");
    
    //    ppOutDevice = CREATE_DEVICE(deviceName, uid);
    
    if (strcmp(deviceName, "ZhongHanDevice") == 0) {
        *ppOutDevice = new ZhongHanDevice();
    }
    else if (strcmp(deviceName, "TUTKGatewayDevice") == 0) {
        *ppOutDevice = new TUTKGatewayDevice();
    }
    else if (strcmp(deviceName, "TUTKPlugDevice") == 0) {
        *ppOutDevice = new TUTKPlugDevice();
    }
    else if (strcmp(deviceName, "SampoDevice") == 0) {
        *ppOutDevice = new SampoDevice();
    }
    else if (strcmp(deviceName, "TUTKLightingDevice") == 0) {
        *ppOutDevice = new TUTKLightingDevice();
    }
    else if (strcmp(deviceName, "TUTKPIRDevice") == 0) {
        *ppOutDevice = new TUTKPIRDevice();
    }
    else if (strcmp(deviceName, "TUTKDoorDevice") == 0) {
        *ppOutDevice = new TUTKDoorDevice();
    }
    else if (strcmp(deviceName, "TUTKWaterLeakDevice") == 0) {
        *ppOutDevice = new TUTKWaterLeakDevice();
    }
    else if (strcmp(deviceName, "TUTKSirenDevice") == 0) {
        *ppOutDevice = new TUTKSirenDevice();
    }
    else if (strcmp(deviceName, "TUTKGasDevice") == 0) {
        *ppOutDevice = new TUTKGasDevice();
    }
    else if (strcmp(deviceName, "TUTKVibrateDevice") == 0) {
        *ppOutDevice = new TUTKVibrateDevice();
    }
    else if (strcmp(deviceName, "TUTKSmokeDevice") == 0) {
        *ppOutDevice = new TUTKSmokeDevice();
    }
    else if (strcmp(deviceName, "VtechIPHubGatewayDevice") == 0) {
        *ppOutDevice = new VtechIPHubGatewayDevice();
    }
    else {
        LOGE("Device Not Found!");
        
        LOGE("請使用RDTServer Device UID");
        LOGE("如:RDTServer PowerStripDevice 00000000000000000000");
        LOGE("可以使用的Devices:");
        LOGE("PowerStripDevice");
        LOGE("AbocomDevice");
        LOGE("ZhongHanDevice");
        LOGE("PhilipsDevice");
        LOGE("TUTKGatewayDevice");
        LOGE("TUTKPlugDevice");
        LOGE("SampoDevice");
        LOGE("TUTKLightingDevice");
        LOGE("TUTKDoorDevice");
        LOGE("TUTKWaterLeakDevice");
        LOGE("TUTKSirenDevice");
        LOGE("TUTKGasDevice");
        LOGE("TUTKVibrateDevice");
        LOGE("TUTKSmokeDevice");
        LOGE("VtechIPHubGatewayDevice");
    }
}