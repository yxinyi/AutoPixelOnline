#pragma once
#include <string>
#include <map>
#include <memory>
#include <functional>
#include "./DBSystemStruct.h"
#include "System/BaseSystem.h"
#include "EngineInclude.h"


class CDataBaseSystem :public BaseSystem {
public:
    CDataBaseSystem() :BaseSystem(typeid(CDataBaseSystem).name()) {}
    ~CDataBaseSystem() {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();

public:
    bool Query(const string& key_, DBQueryCB cb_);
    bool Delete(const string& key_, DBQueryCB cb_);
    bool Update(const string& key_, const string& val_, DBQueryCB cb_);
    bool Insert(const string& key_, const string& val_, DBQueryCB cb_);
    bool Upsert(const string& key_, const string& val_, DBQueryCB cb_);

    bool ConnecDBServer();

private:
    bool op(DBOperatorType opt_, const string& key_, DBQueryCB cb_, const string& val_ = "");

    string m_dbserver_ip = "";
    uint32_t m_dbserver_port = 0;
    enum class DBConnecState {
        WaitDBInfo,
        Close,
        Connecting,
        Open,
    };
    DBConnecState m_dbserver_connected_ok = DBConnecState::WaitDBInfo;
    uint32_t m_dbserver_connected_id = 0;
    const uint32_t m_query_time_out = 6000; //����
    std::map<uint64_t, DBOpUnity_t> m_op_pool;
    
    std::vector<DataBaseReq_t> m_proto_send_cache;
};