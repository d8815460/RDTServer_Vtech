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
#include "config.h"
#include "RDTProtocolException.hpp"

// curl
#include <cstdlib>
#include <cerrno>
#include <curlpp/cURLpp.hpp>
#include <curlpp/Easy.hpp>
#include <curlpp/Options.hpp>
#include <curlpp/Exception.hpp>

void Utility::displayVersion()
{
    LOGD("Device API Version: %d.%d.%d", DEVICE_API_VERSION_MAJOR, DEVICE_API_VERSION_MINOR, DEVICE_API_VERSION_PATCH);
}

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

void Utility::pojoToJson(Json::Value& inJsonObject, Json::Value& outJsonObject, shared_ptr<Pojo>& pPojo)
{
    shared_ptr<vector<shared_ptr<Pojo>>> pojoList(new vector<shared_ptr<Pojo>>);
    pojoList->push_back(pPojo);
    
    pojoListToJson(inJsonObject, outJsonObject, pojoList);
}

void Utility::pojoListToJson(Json::Value& inJsonObject, Json::Value& outJsonObject, shared_ptr<vector<shared_ptr<AccessoryPojo>>>& pAccessoryPojoList)
{
    shared_ptr<vector<shared_ptr<Pojo>>>& pojo = (shared_ptr<vector<shared_ptr<Pojo>>>&) pAccessoryPojoList;
    pojoListToJson(inJsonObject, outJsonObject, pojo);
}

void Utility::pojoListToJson(Json::Value& inJsonObject, Json::Value& outJsonObject, shared_ptr<vector<shared_ptr<Pojo>>>& pojoList)
{
    Json::Value listAccessory;
    
    Json::Value subObject;
    
    if (pojoList->size() > 0) {
        for (shared_ptr<Pojo> pPojo : *pojoList) {
            pPojo->toJson(subObject);
    //        LOGD("產生json = \n%s", accessoryJson.toStyledString().c_str());
        }
    }
    else {
        outJsonObject["ErrorCode"] = RDTProtocolException_Data_Access_Error;
    }
    
    listAccessory["ListAccessory"] = subObject;
    outJsonObject["Response"] = listAccessory;
    
//    LOGD("產生json = \n%s", root.toStyledString().c_str());
}

void Utility::sendParseRest(const char *url, const char* appID, const char* masterKey, const char* restKey, const char* json)
{
    try {
        curlpp::Cleanup cleaner;
        curlpp::Easy request;
        
        request.setOpt(new curlpp::options::Url(url));
        request.setOpt(new curlpp::options::Verbose(true));
        
        std::list<std::string> header;
        std::string str = "";
        str.append("X-Parse-Application-Id: ");
        str.append(appID);
        header.push_back(str);
        
        str = "";
        str.append("X-Parse-Master-Key: ");
        str.append(masterKey);
        header.push_back(str);
        
        str = "";
        str.append("X-Parse-REST-API-Key: ");
        str.append(restKey);
        header.push_back(str);
        
        header.push_back("Content-Type: application/json");
        request.setOpt(new curlpp::options::HttpHeader(header));
        
        request.setOpt(new curlpp::options::PostFields(json));
        request.setOpt(new curlpp::options::PostFieldSize(strlen(json)));
        
        request.perform();
    }
    catch ( curlpp::LogicError & e ) {
        std::cout << e.what() << std::endl;
    }
    catch ( curlpp::RuntimeError & e ) {
        std::cout << e.what() << std::endl;
    }
}

void Utility::parse(shared_ptr<vector<shared_ptr<AccessoryPojo>>>& pAccessoryPojoList, Json::Value& root, int AID, vector<ValueObject>& propertyList, Parse_Callback& callback)
{
    for (shared_ptr<AccessoryPojo>& pAccessoryPojo : *pAccessoryPojoList) {
        if (AID == pAccessoryPojo->AID) {
            for (ValueObject vo : propertyList) {
                if (root.isMember(vo.key)) {
                    LOGD("key:%s", vo.key.c_str());
                    LOGD("value:%s", root[vo.key].asString().c_str());
                    
                    callback(root, AID, propertyList);
                }
            }
        }
    }
}
