//
//  Command.hpp
//  RDTServer
//
//  Created by jakey on 2016/1/12.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef Command_hpp
#define Command_hpp

#include <stdio.h>
#include <set>
#include <vector>
#include "CommandEvent.hpp"
#include "CommandHardwardEvent.hpp"
#include "Connect.hpp"

using namespace std;

struct WifiInfo
{
    char ssid[128];
    char security[64];
    UBYTE signal;
};

struct CommandData
{
//    std::string             productName;
//    int                     productCode;
    
    unsigned short          version1;
    unsigned short          version2;
    unsigned short          version3;
    
    char                    pPassword[32];
    
    char                    pSSID[128];
    char                    pSSIDPassword[32];
    
    vector<WifiInfo*>       WifinInfo;
    
    int                     nMaxAID;
    set<unsigned int>       TypeSet;
};

struct ParseSendData { };
struct ParseRecvData { };

class Command : public ConnectEvent
{
public:
    Command(CommandEvent* pCommandEvent, CommandHardwardEvent* pCommandHardwardEvent, Connect* pConnect, CommandData* pCommandData = NULL);
    virtual ~Command();
    
    Connect* getConnect();
    
    unsigned short getVersion1() { return m_CommandData.version1; }
    unsigned short getVersion2() { return m_CommandData.version2; }
    unsigned short getVersion3() { return m_CommandData.version3; }
    char* getPassword()          { return m_CommandData.pPassword; }
    char* getSSID()              { return m_CommandData.pSSID; }
    char* getSSIDPassword()      { return m_CommandData.pSSIDPassword; }
    
private:
    void init();
    
#pragma mark - ConnectEvent
public:
    virtual void onConnectRecvData(ConnectRecvData* pConnectRecvData) = 0;
    virtual void onConnectCreateClient(ConnectCreateClient* pConnectCreateClient) = 0;
    
#pragma mark - Command
public:
    virtual void reset();
    virtual void parseSendData(ParseSendData* pParseSendData) = 0;
    virtual void parseRecvData(ParseRecvData* pParseRecvData) = 0;
    
// 變數
protected:
    CommandEvent*           m_pCommandEvent;
    CommandHardwardEvent*   m_pCommandHardwardEvent;
    Connect*                m_pConnect;
    
    CommandData             m_CommandData;
};

#endif /* Command_hpp */
