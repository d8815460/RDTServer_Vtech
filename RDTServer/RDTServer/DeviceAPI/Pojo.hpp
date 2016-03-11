//
//  Dao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef Dao_hpp
#define Dao_hpp

#include <stdio.h>
#include <vector>
#include <string>

#define Pojo_Buffer_Size 100

using namespace std;

struct Pojo
{
    virtual ~Pojo() {}
    
    virtual void print() = 0;
};

#endif /* Dao_hpp */
