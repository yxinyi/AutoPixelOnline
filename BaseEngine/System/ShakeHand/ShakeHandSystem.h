#pragma once
#include "System/BaseSystem.h"
#include "Tcp/NetManager.h"
#include <set>

std::vector<ConnectTargetConfig> getConnectConfig();
class ShakeHandSystem :public BaseSystem {
public:
    ShakeHandSystem():BaseSystem(typeid(ShakeHandSystem).name()){}
    bool EnvDefine(); 
    bool PreInit();
    bool Init(); 
    bool Loop(const uint64_t interval_); 
    bool Quit();
    bool Destroy();

public:
    bool ShakeHandForEveryOne();
    bool ShakeHandCheck();
    
private:
    void ShakeHandPrint(const uint32_t conn_);
    std::set<uint32_t> m_conne_vec;

    std::map<uint32_t, uint64_t> m_remote;
};


