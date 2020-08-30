#pragma once
#include "../../../BaseEngine/System/BaseSystem.h"
#include "../../../BaseEngine/Tcp/NetManager.h"
#include <set>




std::vector<ConnectTargetConfig> getConnectConfig();


class ShakeHandSystem :public BaseSystem {
public:
    ShakeHandSystem():BaseSystem("ShakeHandSystem"){}
    bool EnvDefine(); 
    bool PreInit(); 
    bool Init(); 
    bool Loop(const uint64_t interval_); 
    bool Quit();
    bool Destroy();

public:
    bool ShakeHandForEveryOne();
private:
    void ShakeHandPrint();
    std::set<uint32_t> m_conne_vec;
};


