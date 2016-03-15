//
//  BaseData.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/2/24.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef BaseData_hpp
#define BaseData_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include "Common.hpp"
#include <json/reader.h>

using namespace std;

enum DataType
{
    DataType_None,
    DataType_Accessory,
    DataType_Group,
};

struct CommandBase
{
    DataType dataType;
    int errorCode;
};

struct FunctionCodeValueData
{
    int value;
    
    std::string toJson()
    {
        std::string json;
        json.append(QUOTES).append("value").append(QUOTES_COLON).append(to_string(value)).append(NEW_LINE);
        
        return json;
    }
    
    void print()
    {
        LOGD("value:%d", value);
    }
};

struct FunctionCodeData
{
    string functonCode;
    vector<FunctionCodeValueData*> functionCodeValueDataList;
    
    ~FunctionCodeData()
    {
        for (int i=0 ; i<functionCodeValueDataList.size() ; i++) {
            delete functionCodeValueDataList[i];
        }
    }
    
    void addFunctionCodeValueData(int value)
    {
        FunctionCodeValueData* pFunctionCodeValueData = new FunctionCodeValueData();
        pFunctionCodeValueData->value = value;
        
        functionCodeValueDataList.push_back(pFunctionCodeValueData);
    }
    
    std::string toJson()
    {
        std::string json;
        
        json.append(QUOTES).append("functon_code").append(QUOTES_COLON).append(QUOTES).append(functonCode).append(QUOTES).append(COMMA).append(NEW_LINE);
        for (int i=0 ; i<functionCodeValueDataList.size() ; i++) {
            json.append(QUOTES).append("index").append(QUOTES_COLON).append(to_string(i)).append(COMMA).append(NEW_LINE);
            json.append(functionCodeValueDataList[i]->toJson());
        }
        
        return json;
    }
    
    void print()
    {
        LOGD("functonCode:%s", functonCode.c_str());
        
        for (int i=0 ; i<functionCodeValueDataList.size() ; i++) {
            functionCodeValueDataList[i]->print();
        }
    }
};

struct BaseData
{
    vector<FunctionCodeData*> functionCodeDataList;
    
    ~BaseData()
    {
        for (int i=0 ; i<functionCodeDataList.size() ; i++) {
            delete functionCodeDataList[i];
        }
    }
    
    void addFunctionCodeData(string functonCode, int value)
    {
        FunctionCodeValueData *functionCodeValueData = new FunctionCodeValueData();
        functionCodeValueData->value = value;
        
        FunctionCodeData* functionCodeData = new FunctionCodeData();
        functionCodeData->functonCode = functonCode;
        functionCodeData->functionCodeValueDataList.push_back(functionCodeValueData);
        functionCodeDataList.push_back(functionCodeData);
    }
    
    void addFunctionCodeData(string functonCode, int value1, int value2)
    {
        FunctionCodeData* functionCodeData = new FunctionCodeData();
        functionCodeData->functonCode = functonCode;
        functionCodeData->addFunctionCodeValueData(value1);
        functionCodeData->addFunctionCodeValueData(value2);
        functionCodeDataList.push_back(functionCodeData);
    }
    
    virtual std::string toJson()
    {
        std::string json;
        
        json.append(QUOTES).append("function_codes").append(QUOTES_COLON_BRACKETS).append(NEW_LINE);
        json.append("{").append(NEW_LINE);
        for (int i=0 ; i<functionCodeDataList.size() ; i++) {
            json.append(functionCodeDataList[i]->toJson());
        }
        json.append("}").append(NEW_LINE);
        json.append("]").append(NEW_LINE);
        
        return json;
    }
    
    virtual void print()
    {
        for (int i=0 ; i<functionCodeDataList.size() ; i++) {
            functionCodeDataList[i]->print();
        }
    }
};

struct AccessoryData : BaseData
{
    int accessoryId;
    int accessoryType;
    
    virtual std::string toJson()
    {
        std::string json;
        
        json.append("{").append(NEW_LINE);
        
        json.append(QUOTES).append("accessories").append(QUOTES_COLON_BRACKETS).append(NEW_LINE);
        json.append("{").append(NEW_LINE);
        json.append(QUOTES).append("accessory_id").append(QUOTES_COLON).append(to_string(accessoryId)).append(COMMA).append(NEW_LINE);
        json.append(QUOTES).append("accessory_type").append(QUOTES_COLON).append(to_string(accessoryType)).append(COMMA).append(NEW_LINE);
        json.append(BaseData::toJson());
        json.append("}").append(NEW_LINE);
        json.append("]").append(NEW_LINE);
        
        json.append("}");
        
        return json;
    }
    
    virtual void print()
    {
        LOGD("accessoryId:%d", accessoryId);
        LOGD("accessoryType:%d", accessoryType);
        
        BaseData::print();
    }
};

#endif /* BaseData_hpp */
