//
//  Hardward.cpp
//  RDTServer
//
//  Created by jakey on 2016/1/28.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "Hardward.hpp"
#include <cstring>

Hardward::Hardward(HardwardEvent* pHardwardEvent, HardwardData* pHardwardData) : m_pHardwardEvent(pHardwardEvent)
{
//    LOGD("Hardward");
    
    std::memcpy(&m_HardwardData, pHardwardData, sizeof(HardwardData));
}

Hardward::~Hardward()
{
//    LOGD("~Hardward");
}