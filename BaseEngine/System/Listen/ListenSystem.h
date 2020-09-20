#pragma once
#include "System/BaseSystem.h"
#include "Tcp/NetManager.h"
#include "./ListenStruct.h"
#include <set>



class ListenSystem :public BaseSystem {
public:
    ListenSystem():BaseSystem(typeid(ListenSystem).name()){}
    bool EnvDefine(); 
    bool PreInit();
    bool Init(); 
    bool Loop(const uint64_t interval_); 
    bool Quit();
    bool Destroy();
private:
    bool connectListServer(const std::string& str_ = "", uint32_t port_ = 0);
    enum class ListenInitState{
        initial,
        success,
    };
    ListenInitState m_init_state = ListenInitState::initial;
};


