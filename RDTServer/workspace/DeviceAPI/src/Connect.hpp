//
//  Connect.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/13.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef Connect_hpp
#define Connect_hpp

#include <stdio.h>
#include "ConnectEvent.hpp"

struct ConnectData {};

class Connect
{
public:
    Connect(ConnectData* pConnectData);
    virtual ~Connect();
    
    void setConnectEvent(ConnectEvent* pConnectEvent);
    
#pragma mark - Connect
    virtual void initialize() = 0;
    virtual void deInitialize() = 0;
    virtual void run() = 0;
    virtual void connect() = 0;     // ip, port, ...
    virtual void disconnect() = 0;
    
// 成員變數
protected:
    bool m_isConnect;
    ConnectEvent* m_pConnectEvent;
};

#endif /* Connect_hpp */
