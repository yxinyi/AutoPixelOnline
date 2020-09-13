#pragma once
#include "System/BaseSystem.h"
#include "Attribute/Attribute.h"
#include "tool/AStar.h"
#include <vector>
#include <list>
#include "RenderManager.h"
#include "proto/Map.pb.h"
#include <set>

class CliMapSystem:public BaseSystem {
public:
    CliMapSystem() :BaseSystem(typeid(CliMapSystem).name()) {}
    ~CliMapSystem() {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();
public:
    void InitMap(std::shared_ptr<SceneMapInfo>);
    void MapRender(SDL_Window* windows_, SDL_Renderer* render_);
private:
    std::vector<std::vector<uint32_t>> m_maze_shape;
    std::vector<std::shared_ptr<MapData>> m_move_block_data;
    
    uint32_t m_cell_size = 0;
};
