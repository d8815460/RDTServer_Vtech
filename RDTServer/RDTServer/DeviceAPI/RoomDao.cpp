//
//  RoomDao.cpp
//  DeviceAPI
//
//  Created by jakey on 2016/4/8.
//  Copyright © 2016年 jakey. All rights reserved.
//

#include "RoomDao.hpp"
#include "DatabaseManager.hpp"

void RoomDao::readCallback(shared_ptr<vector<shared_ptr<Pojo>>> outPtrPojoList, int row, vector<char*>& colList, bool isNest)
{
    shared_ptr<RoomPojo> pRoomPojo(new RoomPojo());
    
    for (size_t i=0 ; i<colList.size() ; i++) {
        char* data = colList[i];
        //        LOGD("data:%s", data);
        
        if (i == 0) {
            pRoomPojo->RoomSerial = stoi(data);
        }
        /******************************************* 修改處 *****************************************************/
        if_index_int_va(1, pRoomPojo->RoomName, data)
        if_index_int_va(2, pRoomPojo->RoomSeq, data)
        /******************************************* 修改處 *****************************************************/
        else {
            throw DatabaseException(__PRETTY_FUNCTION__, __LINE__, DatabaseException_ErrorCode_Column_Over_The_Range);
        }
    }
    
    outPtrPojoList->push_back(pRoomPojo);
}

shared_ptr<vector<shared_ptr<Pojo>>> RoomDao::read(vector<int>& elementSerialList)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    vector<ValueObject> objList;
    for (int RoomSerial : elementSerialList) {
        ValueObject obj("RoomSerial", RoomSerial);
        objList.push_back(obj);
    }
    
    string SQL = "SELECT * FROM Room WHERE";
    SQL.append(Pojo::genInSQL(objList, false));
    
    return databaseManager.read(SQL.c_str(), true, RoomDao::readCallback);
}

shared_ptr<vector<shared_ptr<Pojo>>> RoomDao::readWithSQL(string& SQL)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    shared_ptr<vector<shared_ptr<Pojo>>> pPojoList = databaseManager.read(SQL.c_str(), false, RoomDao::readCallback);
    return pPojoList;
}

void RoomDao::create(shared_ptr<RoomPojo> pRoomPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    pRoomPojo->genValueObject();
    std::string sql = Pojo::createSQL("INSERT INTO Room (RoomSerial,", pRoomPojo->valueObjectList);
    databaseManager.exec(sql.c_str());
}

void RoomDao::update(shared_ptr<RoomPojo> pRoomPojo)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    pRoomPojo->genValueObject();
    std::string SQL = "UPDATE Room ";
    SQL.append(Pojo::genUpdateSetSQL(pRoomPojo->valueObjectList));
    databaseManager.exec(SQL.c_str());
}

int RoomDao::deleteAll()
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    return databaseManager.exec("DELETE FROM Room;");
}

int RoomDao::deleteWithSerial(int RoomSerial)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    char buffer[Pojo_Buffer_Size];
    sprintf(buffer, "DELETE FROM Room WHERE elementSerial = %d;", RoomSerial);
    LOGD("buffer:%s", buffer);
    
    return databaseManager.exec(buffer);
}

int RoomDao::deleteWithFKElementSerialList(vector<int>& elementSerialList)
{
    DatabaseManager& databaseManager = DatabaseManager::getInstance();
    
    vector<ValueObject> objList;
    for (int fkElementSerial : elementSerialList) {
        ValueObject obj("fkElementSerial", fkElementSerial);
        objList.push_back(obj);
    }
    
    string SQL = "DELETE FROM Room WHERE";
    SQL.append(Pojo::genInSQL(objList, false));
    
    return databaseManager.exec(SQL.c_str());
}
