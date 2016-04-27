//
//  ServiceDao.hpp
//  DeviceAPI
//
//  Created by jakey on 2016/4/26.
//  Copyright © 2016年 jakey. All rights reserved.
//

#ifndef ServiceDao_hpp
#define ServiceDao_hpp

#include <stdio.h>
#include <vector>
#include <memory>
#include "Pojo.hpp"
#include "ServicePojo.hpp"

using namespace std;

class ServiceDao
{
public:
//    static void create(shared_ptr<ServiceDao> pServicePojo);
//    static void update(shared_ptr<ServiceDao> pServicePojo);
    
//    static int deleteAll();
//    static int deleteWithSerial(int elementSerial);
//    static int deleteWithFKAccessorySerialList(vector<int>& accessorySerialList);
    
    static shared_ptr<vector<shared_ptr<Pojo>>> read(vector<int>& accessorySerialList);
    static shared_ptr<vector<shared_ptr<Pojo>>> readWithSQL(string& SQL);
    
private:
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList, bool isNest);
};

#endif /* ServiceDao_hpp */
