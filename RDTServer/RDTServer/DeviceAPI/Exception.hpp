//
//  Exception.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/1.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef Exception_hpp
#define Exception_hpp

#include <stdio.h>
#include <string>

using namespace std;

struct Exception
{
    const char* function;
    int line;
    string errorDomain;
    int errorCode;
    string errorMessage;
    
    Exception(const char* function, int line, const char* errorDomain, int errorCode, const char* errorMessage)
    {
        this->function = function;
        this->line = line;
        this->errorDomain = errorDomain;
        this->errorCode = errorCode;
        this->errorMessage = errorMessage;
    }
};

#endif /* Exception_hpp */
