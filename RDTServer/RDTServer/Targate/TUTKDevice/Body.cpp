//
//  Body.cpp
//  RDTServer
//
//  Created by jakey on 2015/5/22.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "Body.hpp"
#include <cstring>

// Devices
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
#include "JsonRDTClientDevice.hpp"

#define DECLARE_CLASS_CREATE(class_name) \
    static CObject* CreateClass## class_name ();

#define IMPL_CLASS_CREATE(class_name) \
    static CObject* CreateClass## class_name () {  \
        return new class_name;             \
    };

#define REG_CLASS_CREATE(class_name) \
    RegisterFactoryCreate(class_name::CreateClass## class_name, #class_name);


#define CREATE_DEVICE(deviceName, uid) \
    new deviceName

void Body::runBody(Device **ppOutDevice, char deviceName[20])
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
    
//    ppOutDevice = CREATE_DEVICE(deviceName, );
    
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
    else if (strcmp(deviceName, "JsonRDTClientDevice") == 0) {
        *ppOutDevice = new JsonRDTClientDevice();
    }
    else {
        string error = "Device Not Found!";
        const char* newLine = "\n";
        
        error.append("請使用RDTServer Device").append(newLine);
        error.append("如:Command TUTKGatewayDevice 00000000000000000000").append(newLine);
        error.append("可以使用的Devices:").append(newLine);
        error.append("AbocomDevice").append(newLine);
        error.append("ZhongHanDevice").append(newLine);
        error.append("PhilipsDevice").append(newLine);
        error.append("TUTKGatewayDevice").append(newLine);
        error.append("TUTKPlugDevice").append(newLine);
        error.append("SampoDevice").append(newLine);
        error.append("TUTKLightingDevice").append(newLine);
        error.append("TUTKDoorDevice").append(newLine);
        error.append("TUTKWaterLeakDevice").append(newLine);
        error.append("TUTKSirenDevice").append(newLine);
        error.append("TUTKGasDevice").append(newLine);
        error.append("TUTKVibrateDevice").append(newLine);
        error.append("TUTKSmokeDevice").append(newLine);
        error.append("JsonRDTClientDevice").append(newLine);
        
        throw error;
    }
}