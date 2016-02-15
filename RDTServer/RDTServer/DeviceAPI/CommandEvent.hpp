//
//  CommandEvent.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/13.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef CommandEvent_hpp
#define CommandEvent_hpp

#include <stdio.h>
#include <vector>

class FunctionStatus;
class FunctionInfo;

using namespace std;

struct CommandRecvData {};

class CommandEvent
{
#pragma mark - CommandEvent
public:
    virtual unsigned short onCommandGetProductCode() = 0;
    virtual const char* onCommandGetProductName() = 0;
    virtual void onCommandRecvData(CommandRecvData* pCommandRecvData) = 0;
        
    virtual void onCommandRecvCommand28(FunctionStatus* pFunctionStatus) = 0;
    virtual void onCommandRecvFullCommand28(int channelID, vector<FunctionInfo*>* pDataInfoList) = 0;
};

#endif /* CommandEvent_hpp */
