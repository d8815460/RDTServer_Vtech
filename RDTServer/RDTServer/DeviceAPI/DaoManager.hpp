//
//  DaoManager.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef DaoManager_hpp
#define DaoManager_hpp

#include <stdio.h>
#include "Dao.hpp"

struct DaoManager
{
public:
    vector<Dao*> daoList;
    
    ~DaoManager()
    {
        for (Dao* pDao : daoList) {
            delete pDao;
        }
    }
    
    void push_back(Dao* pDao)
    {
        daoList.push_back(pDao);
    }
};

#endif /* DaoManager_hpp */
