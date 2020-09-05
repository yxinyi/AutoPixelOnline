#include "./Map.h"
#include "MessageBus/MessageBus.h"
#include "Creature/Creature.h"
#include "tool/ObjectPool.h"
#include "tool/UniqueNumberFactory.h"
#include "Error/Error.h"
#include "Tcp/NetManager.h"
#include <math.h>

RegSystem(MapManager)

bool MapManager::EnvDefine() {
    MessageBus::getInstance()->Attach([this](Creature_t creature_) {
        CAttrMap_t _attr_map = creature_->GetAttrs()->ApiGetAttr<CAttrMap>("CAttrMap");
        if (!_attr_map) {
            return;
        }
        if (_attr_map->m_last_map_tid != 0) {
            _attr_map->m_last_map_tid = m_default_map_tid;
        }
        Map_t _map = EnterMap(creature_, _attr_map->m_last_map_tid);
        if (!_map) {
            LogError << "[EnterMap] " << creature_->GetOid() << "enter map err" << _attr_map->m_last_map_tid << FlushLog;
        }



    }, "PlayerLogin");






    //MessageBus::getInstance()->Attach([this](Creature_t creature_, CPosition pos_) {
    //    CAttrMap_t _attr_map = creature_->GetAttrs()->ApiGetAttr<CAttrMap>("CAttrMap");
    //    if (_attr_map->m_last_map_tid != 0) {
    //        _attr_map->m_last_map_tid = m_default_map_tid;
    //    }
    //    Map_t _map = MapManager::getInstance()->GetMapByMapOid(_attr_map->m_map_oid);
    //    if (!_map) {
    //        NetManager::getInstance()->SendMessageBuff(creature_->GetConnID(), ApiBuildErrorMsg(LOG_POS_NOT_EXISTS));
    //        return;
    //    }
    //
    //}, "PlayerMoveTo");

    return true;
}
bool MapManager::PreInit() {
    CAttrManager::getInstance()->Register("Player", make_shared<CAttrMap>());
    CAttrManager::getInstance()->Register("Monster", make_shared<CAttrMap>());
    return true;
}
bool MapManager::Init() {
    return true;
}
bool MapManager::Loop(const uint64_t interval_) {
    for (auto&& _map_it :m_map_pool) {
        const std::set<uint32_t>& _players = _map_it.second->GetPlayer();
        MapTickUpdate_t _update_msg = make_shared<MapTickUpdate>();
        for (auto&& _ply_it : _players) {
            Creature_t _player = CreatureManager::getInstance()->FindCreatureByOid(_ply_it);
            if (!_player) {
                LogError << "[MapManager::Loop]" << _ply_it << FlushLog;
                continue;
            }

            //move postion
            CAttrMap_t _attr_map = _player->GetAttrs()->ApiGetAttr<CAttrMap>("CAttrMap");
            if (!_attr_map) {
                return false;
            }
            if (_attr_map->m_path_pos.size()) {
                CPosition _target_pos = _attr_map->m_path_pos.front();
                
                CPosition _speed_vec;

                CPosition _now_pos = _attr_map->m_map_postion;


                float _distance = sqrt(pow((_target_pos.m_postion_y - _now_pos.m_postion_y), 2) * pow((_target_pos.m_postion_x - _now_pos.m_postion_x), 2));
                
                float _move_rate = (_attr_map->m_speed * (interval_ / 1000) / _distance);
                
                _now_pos.m_postion_y += (_target_pos.m_postion_y - _now_pos.m_postion_y) * _move_rate;
                _now_pos.m_postion_x += (_target_pos.m_postion_x - _now_pos.m_postion_x) * _move_rate;

                if (sqrt(pow((_target_pos.m_postion_y - _now_pos.m_postion_y), 2) * pow((_target_pos.m_postion_x - _now_pos.m_postion_x), 2)) < 0.1f) {
                    _attr_map->m_path_pos.pop_front();
                }
            }

            _update_msg->add_map_infos(_attr_map->ToClientStr());
        }


        //向当前场景所有玩家进行同步
        for (auto&& _ply_it : _players) {
            Creature_t _player = CreatureManager::getInstance()->FindCreatureByOid(_ply_it);
            if (!_player) {
                LogError << "[MapManager::Loop]" << _ply_it << FlushLog;
                continue;
            }
            _player->SendProtoMsg(_update_msg);
        }
    }

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
        const CMapConfig_t _cfg = CMapConfigMgr::getInstance()->FindMapConfig(map_tbl_id_);
        if (_cfg && _cfg->m_auto_create) {
            _map = CreateMap(map_tbl_id_);
        }
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
SceneMapInfo_t CMap::ToProto() {
    SceneMapInfo_t _proto = make_shared<SceneMapInfo>();
    
    
    _proto->set_map_block_size(m_config->m_cell_size);
    return _proto;
}


bool CMap::PosMoveCheck(const CPosition& pos_) {
    if (pos_.m_postion_x > m_config->m_max_x || pos_.m_postion_y > m_config->m_max_y) {
        return false;
    }
    uint32_t _x_block = uint32_t(pos_.m_postion_x / m_config->m_cell_size);
    uint32_t _y_block = uint32_t(pos_.m_postion_y / m_config->m_cell_size);
    if (m_maze_shape[_y_block][_x_block] == 1) {
        return false;
    }

    return true;
}

bool CMap::MoveTo(Creature_t creature_, CPosition tar_pos_) {
    if (!PosMoveCheck(tar_pos_)) {
        return false;
    }
    CAttrMap_t _attr_map = creature_->GetAttrs()->ApiGetAttr<CAttrMap>("CAttrMap");
    if (!_attr_map) {
        return false;
    }

    _attr_map->m_path_pos.clear();

    uint32_t _start_x_block = _attr_map->m_map_postion.m_postion_x / m_config->m_cell_size;
    uint32_t _start_y_block = _attr_map->m_map_postion.m_postion_y / m_config->m_cell_size;

    uint32_t _end_x_block = uint32_t(tar_pos_.m_postion_x / m_config->m_cell_size);
    uint32_t _end_y_block = uint32_t(tar_pos_.m_postion_y / m_config->m_cell_size);
    SAstarPoint_t _path = m_astar->getPath(_start_x_block, _start_y_block, _end_x_block, _end_y_block);
    
    while (_path) {
        CPosition _tmp_pos;
        _tmp_pos.m_postion_x = _path->m_x * m_config->m_cell_size + float((float)m_config->m_cell_size / 2.f);
        _tmp_pos.m_postion_y = _path->m_y * m_config->m_cell_size + float((float)m_config->m_cell_size / 2.f);
        _attr_map->m_path_pos.push_front(_tmp_pos);
        _path = _path->m_parent;
    }


    return true;
}