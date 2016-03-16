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

struct ElementPojo : public Pojo
{
    int elementSerial;
    int fkAccessorySerial;
    std::string name;
    std::string value;
            
    virtual void print()
    {
        LOGD("ElementSerial:%d", elementSerial);
        LOGD("fkAccessorySerial:%d", fkAccessorySerial);
        LOGD("name:%s", name.c_str());
        LOGD("value:%s", value.c_str());
        LOGD();
    }
};

class ElementDao
{
public:
    static void create(shared_ptr<ElementPojo> pElementPojo);
    static void update(shared_ptr<ElementPojo> pElementPojo);
    
    static int deleteAll();
    static int deleteWithSerial(int elementSerial);
    static int deleteWithFKAccessorySerial(int fkAccessorySerial);
    
    static shared_ptr<vector<shared_ptr<Pojo>>> read(int fkAccessorySerial);
    
private:
    static void readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList);
};

#endif /* ElementDao_hpp */
