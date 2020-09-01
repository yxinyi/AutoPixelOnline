#include "./Map.h"
RegSystem(MapManager)

bool MapManager::EnvDefine() {
    return true;
}
bool MapManager::PreInit() {
    return true;
}
bool MapManager::Init() {
    return true;
}
bool MapManager::Loop(const uint64_t interval_) {
    return true;
}
bool MapManager::Quit() {
    return true;
}
bool MapManager::Destroy() {
    return true;
}

Map_t MapManager::CreateMap(const uint32_t map_tbl_id_) {
    return nullptr;
}