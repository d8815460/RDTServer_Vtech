//
//  Utility.h
//  RDTServer
//
//  Created by jakey on 2015/4/24.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__Utility__
#define __RDTServer__Utility__

#include <stdio.h>
#include "Device.hpp"

typedef void (*JsonRecvDataCallback)(int channelID, BYTE* buffer, int totalLength);

class Utility
{
public:
    static void reverse(BYTE* data, const int length);
    static unsigned long bytes2UnsignedLong(BYTE* data, const int length);
    static unsigned long bytes2UnsignedLongWithBeginData(BYTE* data, int* pIndex, const int length);
    
    static void printData(const char* function, int line, const BYTE* data, const int length);
    
//    template <typename T>
//    static T setValue(BYTE* pBuffer, int* pIndex, T value);
    
};

// 全域變數
template <typename T>
T setValue(BYTE* pBuffer, int* pIndex, T value)
{
    //    LOGD("pIndex:%d", *pIndex);
    //    LOGD("value:%lu sizeof(T):%lu", value, sizeof(T));
    
    T* pValue = (T*) &pBuffer[*pIndex];;
    *pValue = value;
    *pIndex += sizeof(T);
    
    return *pValue;
};

#endif /* defined(__RDTServer__Utility__) */
