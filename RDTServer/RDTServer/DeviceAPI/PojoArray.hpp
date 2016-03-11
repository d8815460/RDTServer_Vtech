//
//  DaoManager.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef PojoArray_hpp
#define PojoArray_hpp

#include <stdio.h>
#include "Pojo.hpp"

struct PojoArray
{
public:
    vector<Pojo*> subPojoList;
//    PojoArray* pPojoArray;
    
    ~PojoArray()
    {
//        if (pPojoArray != NULL) {
//            delete pPojoArray;
//            pPojoArray = NULL;
//        }
        
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

#endif /* PojoArray_hpp */
