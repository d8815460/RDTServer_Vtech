//
//  ElementDao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/3/10.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef ElementDao_hpp
#define ElementDao_hpp

#include <stdio.h>
#include <string>
#include <memory>
#include "Pojo.hpp"
#include "ElementPojo.hpp"
#include "Common.hpp"

class ElementDao
{
public:
    static void create(shared_ptr<ElementPojo> pElementPojo);
    static void update(shared_ptr<ElementPojo> pElementPojo);
    
    static int deleteAll();
    static int deleteWithSerial(int elementSerial);
    static int deleteWithFKAccessorySerialList(vector<int>& accessorySerialList);
    
    static shared_ptr<vector<shared_ptr<Pojo>>> read(vector<int>& accessorySerialList);
    static shared_ptr<vector<shared_ptr<Pojo>>> readWithSQL(string& SQL);
    
private:
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList, bool isNest);
};

#endif /* ElementDao_hpp */
