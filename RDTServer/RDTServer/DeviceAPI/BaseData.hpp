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
    
    void addFunctionCodeData(int functonCode, int value)
    {
        FunctionCodeValueData *functionCodeValueData = new FunctionCodeValueData();
        functionCodeValueData->value = value;
        
        FunctionCodeData* functionCodeData = new FunctionCodeData();
        functionCodeData->functonCode = functonCode;
        functionCodeData->functionCodeValueDataList.push_back(functionCodeValueData);
        functionCodeDataList.push_back(functionCodeData);
    }
    
    //    void addFunctionCodeData(int functonCode, int value1, int value2);
    
};

struct AccessoryData : BaseData
{
    int accessoryId;
    int accessoryType;
};

#endif /* BaseData_hpp */
