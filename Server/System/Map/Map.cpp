#include "./Map.h"
#include "MessageBus/MessageBus.h"
#include "Creature/Creature.h"
#include "tool/ObjectPool.h"
#include "tool/UniqueNumberFactory.h"

RegSystem(MapManager)

bool MapManager::EnvDefine() {
    MessageBus::getInstance()->Attach([](Creature_t creature_) {

    }, "PlayerLogin");
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
    const CMapConfig_t _cfg =  CMapConfigMgr::getInstance()->FindMapConfig(map_tbl_id_);
    if (!_cfg) {
        return nullptr;
    }
    const uint64_t _map_oid = UniqueNumberFactory::getInstance()->build();
    Map_t _map = CObjectPool<CMap>::getInstance()->Get(_map_oid,_cfg);
    m_map_pool[_map_oid] = _map;
    m_type_to_map[map_tbl_id_].push_back(_map);
    return _map;
}

Map_t MapManager::EnterMap(Creature_t creature_, const uint32_t map_tbl_id_) {
    Map_t _map = GetMinLoadMapByTableID(map_tbl_id_);
    if (!_map) {
        _map = CreateMap(map_tbl_id_);
    }

    _map->EnterScene(creature_);
    return _map;
}


Map_t MapManager::GetMinLoadMapByTableID(const uint32_t map_tbl_id_) {
    auto _maps_find = m_type_to_map.find(map_tbl_id_);
    if (_maps_find == m_type_to_map.end()) {
        return nullptr;
    }
    Map_t _min_map = nullptr;
    uint32_t _palyer_size = 0xFFFFFFFF;
    for (auto&& _map_it :_maps_find->second) {
        if (_map_it->GetPlayerSize() < _palyer_size) {
            _min_map = _map_it;
        }
    }
    return _min_map;
}
Map_t MapManager::GetMapByMapOid(const uint64_t map_oid_) {
    auto _map_find = m_map_pool.find(map_oid_);
    if (_map_find == m_map_pool.end()) {
        return nullptr;
    }
    return _map_find->second;
}
