//
//  BinraryRDTCommand.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/2/23.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef BinraryRDTCommand_hpp
#define BinraryRDTCommand_hpp

#include <stdio.h>
#include "Command.hpp"

struct FunctionCode
{
    unsigned short transferCode;
};

struct FunctionStatus
{
    bool isRuningStack;
    
    UBYTE functionCode;
    vector<FunctionCode*> functionCodeList;
    
    ~FunctionStatus()
    {
        if (isRuningStack == false) {
            for (int k=0 ; k<functionCodeList.size() ; k++) {
                delete functionCodeList[k];
            }
        }
    }
};

struct FunctionInfo
{
    bool isRuningStack;
    
    UBYTE aid;
    unsigned int type;
    
    vector<FunctionStatus*> functionStatusList;
    
    ~FunctionInfo()
    {
        if (isRuningStack == false) {
            for (int j=0 ; j<functionStatusList.size() ; j++) {
                delete functionStatusList[j];
            }
        }
    }
};

class BinraryRDTCommand : public Command
{
public:
    BinraryRDTCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData = NULL);
    virtual ~BinraryRDTCommand();
    
#pragma mark - Function Info
protected:
    void removeFunctionInfo(vector<FunctionInfo*>::iterator it);
    
public:
    FunctionInfo* createFunctionInfo(unsigned int type);
    
    void addFunctionCode(FunctionStatus* pFunctionStatus, unsigned short transferCode);
    void addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode);
    void addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2);
    void addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3);
    void addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3, unsigned short transferCode4);
    void addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3, unsigned short transferCode4, unsigned short transferCode5);
    void addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3, unsigned short transferCode4, unsigned short transferCode5, unsigned short transferCode6);
    
    void addFunctionStatusWithArray(FunctionInfo* pFunctionInfo, UBYTE functionCode, vector<unsigned short>* pTransferCodeArray);
    
#pragma mark - Method
public:
    bool isLength2Byte(BYTE* buffer, int length);
    bool isBasicVerificationPass(BYTE* buffer, int length);
    
#pragma mark - Member
    vector<FunctionInfo*>   m_dataInfoList;
};

#endif /* BinraryRDTCommand_hpp */
