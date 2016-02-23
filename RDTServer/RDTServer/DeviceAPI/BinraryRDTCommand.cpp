//
//  BinraryRDTCommand.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/2/23.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "BinraryRDTCommand.hpp"

BinraryRDTCommand::BinraryRDTCommand(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData) : Command(pCommandEvent, pCommandHardwardEvent, pConnect, pCommandData)
{
    LOGD("BinraryRDTCommand");
}

BinraryRDTCommand::~BinraryRDTCommand()
{
    LOGD("~BinraryRDTCommand");
    
    for (vector<FunctionInfo*>::iterator it = m_dataInfoList.end() ; it != m_dataInfoList.begin() ; it--) {
        removeFunctionInfo(it);
    }
}

#pragma mark - Method

bool BinraryRDTCommand::isLength2Byte(BYTE* buffer, int length)
{
    // recv command 29
    if ((length == 10 && buffer[7 - 1] == 29) ||
        // version 1.0.0
        (m_CommandData.version1 == 1 && m_CommandData.version2 == 0 && m_CommandData.version3 == 0))
    {
        return false;
    }
    else {
        return true;
    }
}

bool BinraryRDTCommand::isBasicVerificationPass(BYTE *buffer, int length)
{
    // 基本驗證
    if (buffer[0] == 'I' && buffer[1] == 'O' && buffer[2] == 'T' && buffer[3] == 'C' &&     // IOTC
        buffer[length - 2] == 'G' && buffer[length - 1] == 'C')                             // GC
        
    {
        if(isLength2Byte(buffer, length)) {
            // length == 2
            unsigned short* pLength = (unsigned short*)&buffer[4]; // 長度驗證
            if (*pLength == length - 4 - 2 - 2) {
                return true;
            }
        }
        else {
            // length == 1
            if (buffer[4] == length - 4 - 2 - 1) {
                return true;
            }
        }
        
        return false;
    }
    else {
        return false;
    }
}

#pragma mark - Function Info

FunctionInfo* BinraryRDTCommand::createFunctionInfo(unsigned int type)
{
    m_CommandData.TypeSet.insert(type);
    
    FunctionInfo* pFunctionInfo = new FunctionInfo();
    pFunctionInfo->aid = m_CommandData.nMaxAID++;
    pFunctionInfo->type = type;
    m_dataInfoList.push_back(pFunctionInfo);
    
    return pFunctionInfo;
}

void BinraryRDTCommand::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void BinraryRDTCommand::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode1);
    addFunctionCode(pFunctionStatus, transferCode2);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void BinraryRDTCommand::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode1);
    addFunctionCode(pFunctionStatus, transferCode2);
    addFunctionCode(pFunctionStatus, transferCode3);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void BinraryRDTCommand::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3, unsigned short transferCode4)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode1);
    addFunctionCode(pFunctionStatus, transferCode2);
    addFunctionCode(pFunctionStatus, transferCode3);
    addFunctionCode(pFunctionStatus, transferCode4);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void BinraryRDTCommand::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3, unsigned short transferCode4, unsigned short transferCode5)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode1);
    addFunctionCode(pFunctionStatus, transferCode2);
    addFunctionCode(pFunctionStatus, transferCode3);
    addFunctionCode(pFunctionStatus, transferCode4);
    addFunctionCode(pFunctionStatus, transferCode5);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void BinraryRDTCommand::addFunctionStatus(FunctionInfo* pFunctionInfo, UBYTE functionCode, unsigned short transferCode1, unsigned short transferCode2, unsigned short transferCode3, unsigned short transferCode4, unsigned short transferCode5, unsigned short transferCode6)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    addFunctionCode(pFunctionStatus, transferCode1);
    addFunctionCode(pFunctionStatus, transferCode2);
    addFunctionCode(pFunctionStatus, transferCode3);
    addFunctionCode(pFunctionStatus, transferCode4);
    addFunctionCode(pFunctionStatus, transferCode5);
    addFunctionCode(pFunctionStatus, transferCode6);
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void BinraryRDTCommand::addFunctionStatusWithArray(FunctionInfo* pFunctionInfo, UBYTE functionCode, vector<unsigned short>* pTransferCodeArray)
{
    FunctionStatus* pFunctionStatus = new FunctionStatus();
    pFunctionStatus->functionCode = functionCode;
    
    for (int i=0 ; i<pTransferCodeArray->size(); i++) {
        addFunctionCode(pFunctionStatus, (*pTransferCodeArray)[i]);
    }
    
    pFunctionInfo->functionStatusList.push_back(pFunctionStatus);
}

void BinraryRDTCommand::addFunctionCode(FunctionStatus* pFunctionStatus, unsigned short transferCode)
{
    FunctionCode* pFunctionCode = new FunctionCode();
    pFunctionCode->transferCode = transferCode;
    pFunctionStatus->functionCodeList.push_back(pFunctionCode);
}

void BinraryRDTCommand::removeFunctionInfo(vector<FunctionInfo*>::iterator it)
{
    delete (*it);
    m_dataInfoList.erase(it);
}
