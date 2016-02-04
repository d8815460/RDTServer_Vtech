//
//  UTF.h
//  RDTServer
//
//  Created by jakey on 2015/6/5.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#ifndef __RDTServer__UTF__
#define __RDTServer__UTF__

#include <stdio.h>
#include <string>

using namespace std;

//typedef byte_t unsigned char;
//#define byte_t UBYTE

typedef unsigned char byte_t;

class UTF
{
public:
    static bool utf8ToUtf16(wchar_t* dest, size_t& destLen, const char* src, size_t maxSrcLen);
    static bool utf8ToWStr(const char* utf8Str, size_t maxCount, wstring& wideStr);
    static bool utf8ToWStr(const std::string& utf8Str, std::wstring& wideStr);
    static bool utf16ToUtf8(char* dest, size_t& destLen, const wchar_t* src, size_t maxSrcLen);
    static bool wStrToUtf8(const wchar_t* wideStr, size_t maxCount, std::string& utf8Str);
    static bool wStrToUtf8(const std::wstring& wideStr, std::string& utf8Str);
    
private:
    // Reference: http://en.wikipedia.org/wiki/Utf8
    static const byte_t cUtf8Limits[];

};

#endif /* defined(__RDTServer__UTF__) */
