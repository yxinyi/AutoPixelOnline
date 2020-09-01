#pragma once
#include "System/BaseSystem.h"
#include "./MapStruct.h"


class MapManager :public BaseSystem, public Singleton<MapManager> {
public:
    MapManager() :BaseSystem("MapManager") {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();

public:
    Map_t CreateMap(const uint32_t map_tbl_id_);

private:
    std::map<uint64_t, Map_t> m_map_pool;
};
