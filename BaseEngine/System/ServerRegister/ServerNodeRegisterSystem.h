#pragma once
#include "System/BaseSystem.h"
#include "EngineInclude.h"
#include <map>
#include <set>
#include "proto/ServerLink.pb.h"

using ServerLink_t = shared_ptr<ServerLink>;
using ServerMessageRegister_t = shared_ptr<ServerMessageRegister>;

class ServerNodeRegisterSystem :public BaseSystem {
public:
    ServerNodeRegisterSystem() :BaseSystem(typeid(ServerNodeRegisterSystem).name()) {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();

public:
    bool ConnGateServer();

};