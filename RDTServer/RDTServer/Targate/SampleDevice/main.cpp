//
//  main.cpp
//  TestRDTServer
//
//  Created by jakey on 2016/2/4.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include <iostream>
#include "JsonRDTClientDevice.hpp"

int main(int argc, const char * argv[])
{
    JsonRDTClientDevice2* device = new JsonRDTClientDevice2();
    device->run("ELYU954WZZZC9G6GUHFJ");
    delete device;
    
    return 0;
}
