#pragma once
#include <string>
#include <map>
#include <memory>
#include <functional>
#include "./DBSystemStruct.h"
#include "System/BaseSystem.h"
#include "EngineInclude.h"
using namespace std;


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
private:
    bool op(DBOperatorType opt_, const string& key_, DBQueryCB cb_, const string& val_ = "");

    const string m_dbserver_ip = "127.0.0.1";
    const uint32_t m_dbserver_port = 9000;
    enum class DBConnecState {
        close,
        connecting,
        open,
    };
    DBConnecState m_dbserver_connected_ok = DBConnecState::close;
    uint32_t m_dbserver_connected_id = 0;
    const uint32_t m_query_time_out = 6000; //∫¡√Î
    std::map<uint64_t, DBOpUnity_t> m_op_pool;
    
    std::vector<DataBaseReq_t> m_proto_send_cache;
};