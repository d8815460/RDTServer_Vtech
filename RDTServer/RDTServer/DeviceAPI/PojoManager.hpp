//
//  DaoManager.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef PojoManager_hpp
#define PojoManager_hpp

#include <stdio.h>
#include "Pojo.hpp"

struct PojoManager
{
public:
    vector<Pojo*> pojoList;
    PojoManager* pPojoManager;
    
    ~PojoManager()
    {
        if (pPojoManager != NULL) {
            delete pPojoManager;
            pPojoManager = NULL;
        }
        
        for (Pojo* pPojo : pojoList) {
            delete pPojo;
            pPojo = NULL;
        }
    }
    
    void push_back(Pojo* pPojo)
    {
        pojoList.push_back(pPojo);
    }
    
    void clear()
    {
        pojoList.clear();
    }
};

#endif /* PojoManager_hpp */
