#pragma once
#include "google/protobuf/message.h"
#include "System/BaseSystem.h"
#include "./SessionStruct.h"
#include "BaseEngine.h"
#include<set>
#include<memory>


class SessionSystem : public BaseSystem {
public:
    SessionSystem() :BaseSystem(typeid(SessionSystem).name()) {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();

    SessionConn BuildSessionConn(const uint32_t session_id_, const uint32_t conn_id_);

    bool CreateSession(const uint32_t session_id_, const uint32_t conn_id_);
    bool DestorySession(const SessionConn session_id_);

private:
    std::set<SessionConn> m_session_pool;
    

};