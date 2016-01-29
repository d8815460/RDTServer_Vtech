//
//  HardwardEvent.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/28.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef HardwardEvent_hpp
#define HardwardEvent_hpp

#include <stdio.h>

struct HardwardNotifyData {};

class HardwardEvent
{
public:
    virtual void onHardwardNotify(HardwardNotifyData* pHardwardRecvData) = 0;
};

#endif /* HardwardEvent_hpp */
