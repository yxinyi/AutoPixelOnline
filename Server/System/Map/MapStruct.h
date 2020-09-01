#pragma once
#include "System/BaseSystem.h"
#include <vector>
#include <set>

class Map {
public:



private:
    std::set<uint32_t>              m_players;
    std::vector<std::vector<uint32_t>> m_maze_shape;
};
using Map_t = shared_ptr<Map>;

