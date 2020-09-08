#pragma once
#include <string>
#include <map>
#include <memory>
#include "tool/SingletonTemplate.h"
#include "tool/LogInfo.h"


class BaseSystem {
public:
    BaseSystem(const std::string& name_):m_system_name(name_) {}
    virtual ~BaseSystem() {}
    virtual bool EnvDefine() = 0;
    virtual bool PreInit() = 0;
    virtual bool Init() = 0;
    virtual bool Loop(const uint64_t interval_) = 0;
    virtual bool Quit() = 0;
    virtual bool Destroy() = 0;
    std::string GetSystemName() {
        return m_system_name;
    }

protected:
    std::string m_system_name;
};

using System_t = std::shared_ptr<BaseSystem>;
using System_wt = std::weak_ptr<BaseSystem>;
class SystemManager : public  Singleton<SystemManager>{
public:
    bool Register(const std::string& str_,System_t sys_);

    template <class T>
    std::shared_ptr<T> GetSystem() {
        std::map<std::string, System_t>::iterator _find = m_system_pool.find(typeid(T).name());
        if (_find == m_system_pool.end()) {
            LogInfo << "[SYS] [" << typeid(T).name() << "] not registed" << FlushLog;
            return nullptr;
        }
        std::shared_ptr<T> _system = std::dynamic_pointer_cast<T>(_find->second);
        if (!_system) {
            return nullptr;
        }
        return _system;
    }

    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();
private:
    std::map<std::string, System_t> m_system_pool;
};



class RegisterHelper {
public:
    RegisterHelper(std::shared_ptr<BaseSystem> syst_) {
        SystemManager::getInstance()->Register(syst_->GetSystemName(), syst_);
    }
};

#define RegSystem(system_class) \
    static RegisterHelper _reg_helper_##system_class##(std::shared_ptr<system_class>(new system_class));



