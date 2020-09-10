#pragma once
#include "EngineInclude.h"
#include "System/BaseSystem.h"
#include "System/DataBase/DBSystemStruct.h"
#include "System/Session/SessionStruct.h"
#include "proto/DataBase.pb.h"
#include "leveldb/db.h"
class CDBServerSystem :public BaseSystem{
public:
    CDBServerSystem() :BaseSystem(typeid(CDBServerSystem).name()) {}
    ~CDBServerSystem() {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();


private:
    leveldb::DB* m_db;
    leveldb::Options m_options;
};
