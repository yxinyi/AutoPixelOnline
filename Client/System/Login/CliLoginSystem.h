#pragma once
#include "System/BaseSystem.h"
#include "Attribute/Attribute.h"
#include "tool/AStar.h"
#include <vector>
#include <list>
#include "proto/Map.pb.h"
#include "../Client/RenderManager.h"
#include "UI/UIManager.h"
#include <set>

class CliLoginSystem :public BaseSystem {
public:
    CliLoginSystem() :BaseSystem(typeid(CliLoginSystem).name()) {}
    ~CliLoginSystem() {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();
};
