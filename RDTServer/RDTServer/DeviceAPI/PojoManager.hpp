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
    vector<Pojo*> subPojoList;
    PojoManager* pPojoManager;
    
    ~PojoManager()
    {
        if (pPojoManager != NULL) {
            delete pPojoManager;
            pPojoManager = NULL;
        }
        
        for (Pojo* pPojo : subPojoList) {
            delete pPojo;
            pPojo = NULL;
        }
    }
    
    void push_back(Pojo* pPojo)
    {
        subPojoList.push_back(pPojo);
    }
    
    void clear()
    {
        subPojoList.clear();
    }
};

#endif /* PojoManager_hpp */
