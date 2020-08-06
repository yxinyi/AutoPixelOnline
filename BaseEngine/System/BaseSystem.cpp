#include "./BaseSystem.h"
using namespace std;

using System_t = shared_ptr<BaseSystem>;
using System_wt = weak_ptr<BaseSystem>;
bool SystemManager::Register(const string& str_, System_t sys_) {
    if (m_system_pool.find(str_) == m_system_pool.end()) {
        LogInfo << "[SYS] [" << str_ << "] is registed" << FlushLog
            return false;
    }
    m_system_pool[str_] = sys_;
    return true;
}


System_wt SystemManager::GetSystem(const string& str_) {
    map<string, System_t>::iterator _find = m_system_pool.find(str_);
    if (_find == m_system_pool.end()) {
        LogInfo << "[SYS] [" << str_ << "] is registed" << FlushLog
            return System_wt();
    }

    return System_wt(_find->second);
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

