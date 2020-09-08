#include "./BaseSystem.h"


const char* GetGateIP() {
    return "127.0.0.1";
}
uint32_t GetGatePort() {
    return 9001;
}


using System_t = std::shared_ptr<BaseSystem>;
using System_wt = std::weak_ptr<BaseSystem>;
bool SystemManager::Register(const std::string& str_, System_t sys_) {
    if (m_system_pool.find(str_) != m_system_pool.end()) {
        LogInfo << "[SYS] [" << str_ << "] is registed" << FlushLog;
        return false;
    }
    m_system_pool[str_] = sys_;
    return true;
}




bool SystemManager::EnvDefine() {
    for (auto&& _it : m_system_pool) {
        if (!_it.second->EnvDefine()) {
            return false;
        }
    }
    return true;
}
bool SystemManager::PreInit() {
    for (auto&& _it : m_system_pool) {
        if (!_it.second->PreInit()) {
            return false;
        }
    }
    return true;
}
bool SystemManager::Init() {
    for (auto&& _it : m_system_pool) {
        if (!_it.second->Init()) {
            return false;
        }
    }
    return true;
}
bool SystemManager::Loop(const uint64_t interval_) {
    for (auto&& _it : m_system_pool) {
        if (!_it.second->Loop(interval_)) {
            return false;
        }
    }
    return true;
}
bool SystemManager::Quit() {
    for (auto&& _it : m_system_pool) {
        if (!_it.second->Quit()) {
            return false;
        }
    }
    return true;
}
bool SystemManager::Destroy() {
    for (auto&& _it : m_system_pool) {
        if (!_it.second->Destroy()) {
            return false;
        }
    }
    
    return true;
}

