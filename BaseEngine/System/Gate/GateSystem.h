#pragma once
#include "System/BaseSystem.h"
#include "Tcp/NetManager.h"
#include <set>



class GateSystem :public BaseSystem {
public:
    GateSystem():BaseSystem(typeid(GateSystem).name()){}
    bool EnvDefine(); 
    bool PreInit();
    bool Init(); 
    bool Loop(const uint64_t interval_); 
    bool Quit();
    bool Destroy();
private:
    bool ConnGateServer();
    std::string m_gateserver_ip = "";
    uint32_t m_gateserver_port = 0;
};


