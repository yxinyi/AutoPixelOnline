#pragma once
#include<map>
#include<memory>
#include "google/protobuf/message.h"
#include "System/BaseSystem.h"
#include "./SessionStruct.h"
#include "BaseEngine.h"


class SessionSystem : public BaseSystem {
public:
    SessionSystem() :BaseSystem(typeid(SessionSystem).name()) {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();

    Session_t FindSession(const uint64_t session_id_);
    bool CreateSession(const uint64_t session_id_, const uint32_t conn_id_);
    bool DestorySession(const uint64_t session_id_);

private:
    std::map<uint64_t, Session_t> m_session_pool;


};