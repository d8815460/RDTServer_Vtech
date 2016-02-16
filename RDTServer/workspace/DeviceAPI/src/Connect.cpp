//
//  Connect.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/13.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "Connect.hpp"

Connect::Connect(ConnectData* pConnectData)
{
//    LOGD("Connect");
}

Connect::~Connect()
{
    
}

void Connect::setConnectEvent(ConnectEvent* pConnectEvent)
{
    m_pConnectEvent = pConnectEvent;
}