#pragma once
#include "./LogicSessionControlStruct.h"
#include "System/BaseSystem.h"
#include "System/Session/SessionStruct.h"
#include "EngineInclude.h"


class LogicSessionControlSystem :public BaseSystem {
public:
    LogicSessionControlSystem() :BaseSystem(typeid(LogicSessionControlSystem).name()) {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();

    uint32_t GetAccountKey(const Session session_) {
        auto _account_find = m_session_to_account.find(session_);
        if (_account_find == m_session_to_account.end()) {
            return 0;
        }
        return _account_find->second;
    }

private:
    std::map<uint32_t, uint32_t> m_session_to_account;

};
