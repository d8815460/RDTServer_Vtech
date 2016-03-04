//
//  RDTClientDevice.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/21.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef JsonRDTClientDevice_hpp
#define JsonRDTClientDevice_hpp

#include <stdio.h>
#include "Device.hpp"

class JsonRDTClientDevice : public Device
{
public:
    static void generatorDataInfoList(Command* pCommand);
    
#pragma mark - Device
    virtual Connect* createConnect(ConnectData* pConnectData);
    virtual Command* createCommand(Connect* pConnect, CommandHardwardEvent* pCommandHardwardEvent);
    virtual void constructorFinish() { generatorDataInfoList(m_pCommand); }
    
protected:
    virtual unsigned short onCommandGetProductCode();
    virtual const char* onCommandGetProductName();
    
private:
    bool m_bOnOff;
};

#endif /* JsonRDTClientDevice_hpp */
