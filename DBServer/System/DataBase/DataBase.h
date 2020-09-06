#pragma once
#include "EngineInclude.h"
#include "System/BaseSystem.h"
#include "System/DataBase/DBSystemStruct.h"
#include "proto/DataBase.pb.h"
#include "leveldb/db.h"
class CDataBaseSystem :public BaseSystem, public Singleton<CDataBaseSystem> {
public:
    CDataBaseSystem() :BaseSystem("CDataBaseSystem") {}
    ~CDataBaseSystem() {}
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
