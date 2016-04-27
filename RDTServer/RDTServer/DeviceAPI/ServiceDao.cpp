//
//  ServiceDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/4/26.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "ServiceDao.hpp"
#include "ServicePojo.hpp"
#include "DatabaseManager.hpp"

void ServiceDao::readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList, bool isNest)
{
    shared_ptr<ServicePojo> pServicePojo(new ServicePojo());
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
        //        LOGD("data:%s", data);
        
        if (i == 0) {
//            pServicePojo->elementSerial = stoi(data);
//            //            LOGD("pServicePojo->elementSerial:%d", pServicePojo->elementSerial);
//            
//            if (isNest == true) {
//                /* 取得 pServicePojoList 裡所有的資料 */
//                vector<int> elementSerialList;
//                elementSerialList.push_back(pServicePojo->elementSerial);
////                pServicePojo->pSubPojoList = ElementNODao::read(elementSerialList);
//            }
        }
        /******************************************* 修改處 *****************************************************/
//        if_index_int_va(1, pServicePojo->fkAccessorySerial, data)
//        if_index_str_va(2, pServicePojo->Element, data)
        /******************************************* 修改處 *****************************************************/
        else {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Column_Over_The_Range);
        }
    }
    
    outPtrPojoList->push_back(pServicePojo);
}

shared_ptr<vector<shared_ptr<Pojo>>> ServiceDao::read(vector<int>& fkAccessorySerialList)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    vector<ValueObject> objList;
    for (int fkAccessorySerial : fkAccessorySerialList) {
        ValueObject obj("fkAccessorySerial", fkAccessorySerial);
        objList.push_back(obj);
    }
    
    string SQL = "SELECT * FROM Element WHERE";
    SQL.append(Pojo::genInSQL(objList, false));
    
    return databaseManager.read(SQL.c_str(), true, ServiceDao::readCallback);
}

shared_ptr<vector<shared_ptr<Pojo>>> ServiceDao::readWithSQL(string& SQL)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = databaseManager.read(SQL.c_str(), false, ServiceDao::readCallback);
    return pPojoList;
}

//void ServiceDao::create(shared_ptr<ServicePojo> pServicePojo)
//{
//    DatabaseManager& databaseManager = DatabaseManager::getInstance();
//    
//    pServicePojo->genValueObject();
//    std::string sql = Pojo::createSQL("INSERT INTO Element (elementSerial,", pServicePojo->valueObjectList);
//    databaseManager.exec(sql.c_str());
//    
//    int rowid = (int) sqlite3_last_insert_rowid(databaseManager.getSqliteDatabase());
//    
//    for (shared_ptr<Pojo> pPojo : *pServicePojo->pSubPojoList) {
//        shared_ptr<ElementNOPojo>& pElementNOPojo = (shared_ptr<ElementNOPojo>&) pPojo;
//        
//        pServicePojo->elementSerial = rowid;
//        pElementNOPojo->fkElementSerial = pServicePojo->elementSerial;
//        
//        //        LOGD("pServicePojo->name:%s", pServicePojo->name.c_str());
//        //        LOGD("pServicePojo->elementSerial:%d", pServicePojo->elementSerial);
//        
//        ElementNODao::create(pElementNOPojo);
//    }
//}
//
//void ServiceDao::update(shared_ptr<ServicePojo> pServicePojo)
//{
//    DatabaseManager& databaseManager = DatabaseManager::getInstance();
//    
//    pServicePojo->genValueObject();
//    
//    std::string SQL = "UPDATE Element ";
//    SQL.append(Pojo::genUpdateSetSQL(pServicePojo->valueObjectList));
//    databaseManager.exec(SQL.c_str());
//    
//    for (shared_ptr<Pojo> pPojo : *pServicePojo->pSubPojoList) {
//        shared_ptr<ElementNOPojo>& pElementNOPojo = (shared_ptr<ElementNOPojo>&) pPojo;
//        //        LOGD("pServicePojo->name:%s", pServicePojo->name.c_str());
//        
//        ElementNODao::update(pElementNOPojo);
//    }
//}
//
//int ServiceDao::deleteAll()
//{
//    DatabaseManager& databaseManager = DatabaseManager::getInstance();
//    
//    ElementNODao::deleteAll();
//    
//    return databaseManager.exec("DELETE FROM Element;");
//}
//
//int ServiceDao::deleteWithSerial(int elementSerial)
//{
//    DatabaseManager& databaseManager = DatabaseManager::getInstance();
//    
//    char buffer[Pojo_Buffer_Size];
//    sprintf(buffer, "DELETE FROM Element WHERE elementSerial = %d;", elementSerial);
//    LOGD("buffer:%s", buffer);
//    
//    return databaseManager.exec(buffer);
//}
//
//int ServiceDao::deleteWithFKAccessorySerialList(vector<int>& accessorySerialList)
//{
//    DatabaseManager& databaseManager = DatabaseManager::getInstance();
//    
//    // 呼叫下一層Delete
//    vector<int> elementSerialList;
//    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = ServiceDao::read(accessorySerialList);
//    for (shared_ptr<Pojo> pPojo : *pPojoList) {
//        shared_ptr<ServicePojo>& pServicePojo = (shared_ptr<ServicePojo>&) pPojo;
//        
//        elementSerialList.push_back(pServicePojo->fkAccessorySerial);
//    }
//    ElementNODao::deleteWithFKElementSerialList(elementSerialList);
//    
//    // 這一層的刪除
//    vector<ValueObject> objList;
//    for (int elementSerial : elementSerialList) {
//        ValueObject obj("elementSerial", elementSerial);
//        objList.push_back(obj);
//    }
//    
//    string SQL = "DELETE FROM Element WHERE";
//    SQL.append(Pojo::genInSQL(objList, false));
//    
//    return databaseManager.exec(SQL.c_str());
//}
