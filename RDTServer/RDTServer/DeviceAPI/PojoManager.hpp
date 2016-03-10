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
#include "Pojo.hpp"

struct PojoManager
{
public:
    vector<Pojo*> pojoList;
    
    ~PojoManager()
    {
        for (Pojo* pPojo : pojoList) {
            delete pPojo;
        }
    }
    
    void push_back(Pojo* pPojo)
    {
        pojoList.push_back(pPojo);
    }
};

#endif /* DaoManager_hpp */
