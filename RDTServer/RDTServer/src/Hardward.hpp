//
//  Hardward.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/28.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef Hardward_hpp
#define Hardward_hpp

#include <stdio.h>
#include "HardwardEvent.hpp"

struct HardwardData {};

struct SendHardwardData {};

class Hardward
{
public:
    Hardward(HardwardEvent* pHardwardEvent, HardwardData* pHardwardData);
    virtual ~Hardward();
    
#pragma mark - Hardward
    virtual void sendHardward(SendHardwardData* pSendHardwardData) = 0;
    
protected:
    HardwardEvent* m_pHardwardEvent;
    HardwardData m_HardwardData;
};

#endif /* Hardward_hpp */
