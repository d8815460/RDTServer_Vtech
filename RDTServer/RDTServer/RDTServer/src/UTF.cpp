//
//  UTF.cpp
//  RDTServer
//
//  Created by jakey on 2015/6/5.
//  Copyright (c) 2015年 jakey. All rights reserved.
//

#include "UTF.hpp"

const byte_t UTF::cUtf8Limits[] =
{
    0xC0, // Start of a 2-byte sequence
    0xE0, // Start of a 3-byte sequence
    0xF0, // Start of a 4-byte sequence
    0xF8, // Start of a 5-byte sequence
    0xFC, // Start of a 6-byte sequence
    0xFE // Invalid: not defined by original UTF-8 specification
};

/*! Usually it is a 2 steps process to convert the string, invoke utf8ToUtf16() with
 dest equals to null so that it gives you destLen (not including null terminator),
 then allocate the destination with that amount of memory and call utf8ToUtf16() once
 again to perform the actual conversion. You can skip the first call if you sure
 the destination buffer is large enough to store the data.
 
 \note Here we assum sizeof(wchar_t) == 2
 \ref Modify from 7zip LZMA sdk
 */
bool UTF::utf8ToUtf16(wchar_t* dest, size_t& destLen, const char* src, size_t maxSrcLen)
{
    size_t destPos = 0, srcPos = 0;
    
    while(true)
    {
        byte_t c; // Note that byte_t should be unsigned
        size_t numAdds;
        
        if(srcPos == maxSrcLen || src[srcPos] == '\0') {
            if(dest && destLen != destPos) {
//                assert(false && "The provided destLen should equals to what we calculated here");
                return false;
            }
            
            destLen = destPos;
            return true;
        }
        
        c = src[srcPos++];
        
        if(c < 0x80) { // 0-127, US-ASCII (single byte)
            if(dest)
                dest[destPos] = (wchar_t)c;
            ++destPos;
            continue;
        }
        
        if(c < 0xC0) // The first octet for each code point should within 0-191
            break;
        
        for(numAdds = 1; numAdds < 5; ++numAdds)
            if(c < UTF::cUtf8Limits[numAdds])
                break;
        uint32_t value = c - UTF::cUtf8Limits[numAdds - 1];
        
        do {
            byte_t c2;
            if(srcPos == maxSrcLen || src[srcPos] == '\0')
                break;
            c2 = src[srcPos++];
            if(c2 < 0x80 || c2 >= 0xC0)
                break;
            value <<= 6;
            value |= (c2 - 0x80);
        } while(--numAdds != 0);
        
        if(value < 0x10000) {
            if(dest)
                dest[destPos] = (wchar_t)value;
            ++destPos;
        }
        else {
            value -= 0x10000;
            if(value >= 0x100000)
                break;
            if(dest) {
                dest[destPos + 0] = (wchar_t)(0xD800 + (value >> 10));
                dest[destPos + 1] = (wchar_t)(0xDC00 + (value & 0x3FF));
            }
            destPos += 2;
        }
    }
    
    destLen = destPos;
    return false;
}

bool UTF::utf8ToWStr(const char* utf8Str, size_t maxCount, std::wstring& wideStr)
{
    size_t destLen = 0;
    
    // Get the length of the wide string
    if(!utf8ToUtf16(nullptr, destLen, utf8Str, maxCount))
        return false;
    
    wideStr.resize(destLen);
    if(wideStr.size() != destLen)
        return false;
    
    return utf8ToUtf16(const_cast<wchar_t*>(wideStr.c_str()), destLen, utf8Str, maxCount);
}

bool UTF::utf8ToWStr(const std::string& utf8Str, std::wstring& wideStr)
{
    return UTF::utf8ToWStr(utf8Str.c_str(), utf8Str.size(), wideStr);
}

//! See the documentation for utf8ToUtf16()
bool UTF::utf16ToUtf8(char* dest, size_t& destLen, const wchar_t* src, size_t maxSrcLen)
{
    size_t destPos = 0, srcPos = 0;
    
    while(true)
    {
        uint32_t value;
        size_t numAdds;
        
        if(srcPos == maxSrcLen || src[srcPos] == L'\0') {
            if(dest && destLen != destPos) {
//                assert(false && "The provided destLen should equals to what we calculated here");
                return false;
            }
            destLen = destPos;
            return true;
        }
        
        value = src[srcPos++];
        
        if(value < 0x80) { // 0-127, US-ASCII (single byte)
            if(dest)
                dest[destPos] = char(value);
            ++destPos;
            continue;
        }
        
        if(value >= 0xD800 && value < 0xE000) {
            if(value >= 0xDC00 || srcPos == maxSrcLen)
                break;
            uint32_t c2 = src[srcPos++];
            if(c2 < 0xDC00 || c2 >= 0xE000)
                break;
            value = ((value - 0xD800) << 10) | (c2 - 0xDC00);
        }
        
        for(numAdds = 1; numAdds < 5; ++numAdds)
            if(value < (uint32_t(1) << (numAdds * 5 + 6)))
                break;
        
        if(dest)
            dest[destPos] = char(UTF::cUtf8Limits[numAdds - 1] + (value >> (6 * numAdds)));
        ++destPos;
        
        do {
            --numAdds;
            if(dest)
                dest[destPos] = char(0x80 + ((value >> (6 * numAdds)) & 0x3F));
            ++destPos;
        } while(numAdds != 0);
    }
    
    destLen = destPos;
    return false;
}

bool UTF::wStrToUtf8(const wchar_t* wideStr, size_t maxCount, std::string& utf8Str)
{
    size_t destLen = 0;
    
    // Get the length of the utf-8 string
    if(!UTF::utf16ToUtf8(nullptr, destLen, wideStr, maxCount))
        return false;
    
    utf8Str.resize(destLen);
    if(utf8Str.size() != destLen)
        return false;
    
    return UTF::utf16ToUtf8(const_cast<char*>(utf8Str.c_str()), destLen, wideStr, maxCount);
}

bool UTF::wStrToUtf8(const std::wstring& wideStr, std::string& utf8Str)
{
    return UTF::wStrToUtf8(wideStr.c_str(), wideStr.size(), utf8Str);
}