#pragma once
#include "System/BaseSystem.h"
#include "include/proto/PlayerLogin.pb.h"
#include "Attribute/Attribute.h"


class CreatureSystem :public BaseSystem{
public:
    CreatureSystem() :BaseSystem(typeid(CreatureSystem).name()) {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();

};
