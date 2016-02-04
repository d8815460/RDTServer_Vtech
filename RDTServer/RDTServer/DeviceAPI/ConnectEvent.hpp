//
//  ConnectEvent.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/13.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef ConnectEvent_hpp
#define ConnectEvent_hpp

#include <stdio.h>
#include "Event.hpp"

struct ConnectRecvData {};
struct ConnectCreateClient {};

class ConnectEvent : public Event
{
#pragma mark - ConnectEvent
public:
    virtual void onConnectRecvData(ConnectRecvData* pConnectRecvData) = 0;
    virtual void onConnectCreateClient(ConnectCreateClient* pConnectCreateClient) = 0;
};

#endif /* ConnectEvent_hpp */
