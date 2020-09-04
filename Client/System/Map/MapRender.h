#pragma once
#include "System/BaseSystem.h"
#include "Attribute/Attribute.h"
#include "tool/AStar.h"
#include <vector>
#include <list>
#include "proto/Map.pb.h"
#include <set>

class MapRenderSystem:public BaseSystem, public Singleton<MapRenderSystem> {
public:
    MapRenderSystem() :BaseSystem("MapRenderSystem") {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();
};
