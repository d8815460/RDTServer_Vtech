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

using namespace std;

//enum DataType
//{
//    DataType_AccessoryData,
//};

struct FunctionCodeValueData
{
    int value;
    
    void print()
    {
        LOGD("value:%d", value);
    }
};

struct FunctionCodeData
{
    string functonCode;
    vector<FunctionCodeValueData*> functionCodeValueDataList;
    
    FunctionCodeData()
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
    
    BaseData()
    {
    }
    
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
    
    void print()
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
    
    void print()
    {
        LOGD("accessoryId:%d", accessoryId);
        LOGD("accessoryType:%d", accessoryType);
        
        BaseData::print();
    }
};

#endif /* BaseData_hpp */
