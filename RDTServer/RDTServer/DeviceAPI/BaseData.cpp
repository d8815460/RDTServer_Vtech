//
//  BaseData.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/2/24.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "BaseData.hpp"

#pragma mark - BaseData

//BaseData* BaseData::createData(DataType dataType, unsigned int type)
//{
//    BaseData* baseData = NULL;
//    
//    switch (dataType) {
//        case DataType_AccessoryData: {
//            m_CommandData.TypeSet.insert(type);
//            
//            AccessoryData* pAccessory = new AccessoryData();
//            pAccessory->id = m_CommandData.nMaxAID++;
//            pAccessory->type = type;
//            m_accessories.push_back(pAccessory);
//            
//            baseData = pAccessory;
//        } break;
//            
//        default:
//            LOGE("找不到指定型態");
//            return NULL;
//    }
//    
//    return baseData;
//}
//
//void BaseData::removeData(vector<BaseData*>::iterator iterator)
//{
//    DataType dataType = (*iterator)->dataType;
//    
//    //    if (typeid(iterator->)) {
//    //
//    //    }
//    //    m_accessories.erase(iterator);
//    
//    //    delete (*iterator);
//}

//void BaseData::addFunctionCodeData(BaseData* pBaseData, int functonCode, int value)
//{
//    switch (pBaseData->dataType) {
//        case DataType_AccessoryData: {
//            
//        }
//    }
//}