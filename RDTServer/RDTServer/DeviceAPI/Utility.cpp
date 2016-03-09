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

void Utility::showException(Exception& e)
{
    LOGE("\nFunction:%s\nLine:%d\nErrorCode:%d\nErrorMessage:%s\n", e.function, e.line, e.errorCode, e.errorMessage.c_str());
}
