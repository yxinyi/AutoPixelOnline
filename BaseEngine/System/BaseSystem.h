#pragma once
#include <string>
#include <map>
#include <memory>
#include "tool/SingletonTemplate.h"
#include "tool/LogInfo.h"
using namespace std;


class BaseSystem {
public:
    BaseSystem(const string& name_):m_system_name(name_) {}
    virtual ~BaseSystem() {}
    virtual bool EnvDefine() = 0;
    virtual bool PreInit() = 0;
    virtual bool Init() = 0;
    virtual bool Loop(const uint64_t interval_) = 0;
    virtual bool Quit() = 0;
    virtual bool Destroy() = 0;
    string GetSystemName() {
        return m_system_name;
    }

protected:
    string m_system_name;
};

using System_t = shared_ptr<BaseSystem>;
using System_wt = weak_ptr<BaseSystem>;
class SystemManager : public  Singleton<SystemManager>{
public:
    bool Register(const string& str_,System_t sys_);
    bool GetSystem(System_wt& out_, const string& str_);
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();
private:
    map<string, System_t> m_system_pool;
};



class RegisterHelper {
public:
    RegisterHelper(shared_ptr<BaseSystem> syst_) {
        SystemManager::getInstance()->Register(syst_->GetSystemName(), syst_);
    }
};

#define RegSystem(system_class) \
    static RegisterHelper _reg_helper_##system_class##(shared_ptr<system_class>(new system_class));



