#pragma once
#include "System/BaseSystem.h"
#include <vector>
#include <list>
#include "proto/Map.pb.h"
#include "proto/PlayerLogin.pb.h"
#include <set>

class AccountSystem :public BaseSystem {
public:
    AccountSystem() :BaseSystem(typeid(AccountSystem).name()) {}
    ~AccountSystem() {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();
};
