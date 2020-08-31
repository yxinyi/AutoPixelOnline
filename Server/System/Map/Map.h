#pragma once
#include "System/BaseSystem.h"
#include "./MapStruct.h"


class MapManager {
public:

private:
    std::map<uint64_t, shared_ptr<Map>> m_map_pool;
};
