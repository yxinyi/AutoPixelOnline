#include "./Map.h"
#include "EngineInclude.h"
#include "Creature/Creature.h"
#include <math.h>
#include "tool/Random.h"
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
        SceneMapInfo_t _proto = _map->ToProto();
        creature_->SendProtoMsg(_proto);
    }, PlayerLoginEvent);


    MessageBus::getInstance()->Attach([this](uint64_t ply_oid_)   {
        std::shared_ptr<CreatureManager> _sys = SystemManager::getInstance()->GetSystem<CreatureManager>();
        Creature_t _ply = _sys->FindCreatureByOid(ply_oid_);
        CAttrMap_t _attr_map = _ply->GetAttrs()->ApiGetAttr<CAttrMap>("CAttrMap");
        if (Map_t _map = FindMapByMapOid(_attr_map->m_map_oid)) {
            _map->ExitScene(_ply);
        }

    }, PlayerOutBeforeEvent);

    ProtobufDispatch::getInstance()->registerMessageCallback<PlayerMoveTo>([this](const SessionConn conn_,
        const std::shared_ptr<PlayerMoveTo>& message_,
        const int64_t& receive_time_) {

        const float _x = message_->postion().postion_x();
        const float _y = message_->postion().postion_y();

        std::shared_ptr<CreatureManager> _sys = SystemManager::getInstance()->GetSystem<CreatureManager>();
        Creature_t _palyer = _sys->FindCreatureBySession(ApiGetSession(conn_));
        CAttrMap_t _map_data = _palyer->GetAttrs()->ApiGetAttr<CAttrMap>("CAttrMap");
        //_map_data->m_map_postion.m_postion_x = _x;
        //_map_data->m_map_postion.m_postion_y = _y;
        if (Map_t _map = FindMapByMapOid(_map_data->m_map_oid)) {
            _map->MoveTo(_palyer, {_x,_y});
            LogError << "[MapManager] PlayerMoveTo x: " << _x << "y: " << _y << FlushLog;
        }

    });


    return true;
}
bool MapManager::PreInit() {
    CAttrManager::getInstance()->Register("Player", std::make_shared<CAttrMap>());
    CAttrManager::getInstance()->Register("Monster", std::make_shared<CAttrMap>());
    CMapConfigMgr::getInstance()->init();
    return true;
}
bool MapManager::Init() {
    const float _interval = 150.f;
    TimerTaskManager::getInstance()->RegisterTask("MapLoop",0, (uint64_t)_interval,-1,[this](uint64_t interval_) {
        std::shared_ptr<CreatureManager> _sys = SystemManager::getInstance()->GetSystem<CreatureManager>();
        if (!_sys) {
            return;
        }

        for (auto&& _map_it : m_map_pool) {
            const std::set<uint64_t>& _players = _map_it.second->GetPlayer();
            MapTickUpdate_t _update_msg = std::make_shared<MapTickUpdate>();
            for (auto&& _ply_it : _players) {

                Creature_t _player = _sys->FindCreatureByOid(_ply_it);
                if (!_player) {
                    LogError << "[MapManager::Loop]" << _ply_it << FlushLog;
                    continue;
                }

                //move postion
                CAttrMap_t _attr_map = _player->GetAttrs()->ApiGetAttr<CAttrMap>("CAttrMap");
                if (!_attr_map) {
                    continue;
                }
                if (_attr_map->m_path_pos.size()) {
                    //如果当前有点没有到位,则计算当前向量
                    CPosition& _now_pos = _attr_map->m_map_postion;
                    CPosition& _now_vector = _attr_map->m_vector;
                    CPosition _target_pos = _attr_map->m_path_pos.front();
                    if (_now_vector.m_y == 0.f && _now_vector.m_x == 0.f) {
                        //计算向量
                        LogError << "[MapManager::Loop] _target_pos : [" << _target_pos.m_x << " : " << _target_pos.m_y << "] taget pos[" << _now_pos.m_x << " : " << _now_pos.m_y <<"] "<< FlushLog;

                        float _distance = sqrt(pow(abs(_target_pos.m_y - _now_pos.m_y), 2) + pow(abs(_target_pos.m_x - _now_pos.m_x), 2));
                        
                        float _move_rate = (_attr_map->m_speed / _distance);
                        if (_move_rate >= 1.f) {
                            _move_rate = 1.f;
                        }
                        _now_vector.m_x = (_target_pos.m_x - _now_pos.m_x) * _move_rate;;
                        _now_vector.m_y = (_target_pos.m_y - _now_pos.m_y) * _move_rate;
                        LogError << "[MapManager::Loop] vector xy : [" << _now_vector.m_x << " : " << _now_vector.m_y << "] move rate : [" << _move_rate << "]" << FlushLog;
                    }




                    //float _distance = sqrt(pow(abs(_target_pos.m_y - _now_pos.m_y), 2) * pow(abs(_target_pos.m_x - _now_pos.m_x), 2));
                    //
                    //float _move_rate = (_attr_map->m_speed * (_interval / 1000.f) / _distance);
                    //if (_move_rate >= 1.f) {
                    //    _move_rate = 1.f;
                    //}

                    float _tick_proportion = interval_ / 1000.f;

                    float _growup_x = _now_vector.m_x * _tick_proportion;;
                    float _growup_y = _now_vector.m_y * _tick_proportion;;
                    if (abs(_growup_x) > abs(_target_pos.m_x - _now_pos.m_x)) {
                        _growup_x = _target_pos.m_x - _now_pos.m_x;
                    }
                    if (abs(_growup_y) > abs(_target_pos.m_y - _now_pos.m_y)) {
                        _growup_y = _target_pos.m_y - _now_pos.m_y;
                    }
                    //
                    _now_pos.m_y += _growup_y;
                    _now_pos.m_x += _growup_x;
                    float _after_distance = sqrt(pow((_target_pos.m_y - _now_pos.m_y), 2) + pow((_target_pos.m_x - _now_pos.m_x), 2));
                    LogError << "[MapManager::Loop] growup xy : [" << _growup_x << " : " << _growup_y << "] after pos : [" << _now_pos.m_x << " : " << _now_pos.m_y << "] targetpos : [" << _target_pos.m_x << " : " << _target_pos.m_y << "] tick_proportion rate : [" << _tick_proportion << " ] after_distance: [" << _after_distance << "]" << FlushLog;


                    if (_after_distance < 0.1f) {
                        _attr_map->m_path_pos.pop_front();
                        _now_vector.m_x = 0.f;
                        _now_vector.m_y = 0.f;
                        _now_pos = _target_pos;
                    }
                }

                _update_msg->add_map_infos(_attr_map->ToClientStr());
            }


            //向当前场景所有玩家进行同步
            for (auto&& _ply_it : _players) {
                Creature_t _player = _sys->FindCreatureByOid(_ply_it);
                if (!_player) {
                    LogError << "[MapManager::Loop]" << _ply_it << FlushLog;
                    continue;
                }
                _player->SendProtoMsg(_update_msg);
            }
        }

    });

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
    Map_t _map = CObjectPool<CRandomMap>::getInstance()->Get(_map_oid,_cfg);
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
    if (_map) {
        _map->EnterScene(creature_);
        
    }
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
Map_t MapManager::FindMapByMapOid(const uint64_t map_oid_) {
    auto _map_find = m_map_pool.find(map_oid_);
    if (_map_find == m_map_pool.end()) {
        return nullptr;
    }
    return _map_find->second;
}


bool CMap::PosMoveCheck(const CPosition& pos_) {
    if (pos_.m_x > m_maze_max_x || pos_.m_y > m_maze_max_y) {
        return false;
    }
    uint32_t _x_block = uint32_t(pos_.m_x / m_maze_cell_size);
    uint32_t _y_block = uint32_t(pos_.m_y / m_maze_cell_size);
    if (m_maze[_y_block][_x_block] == 1) {
        return false;
    }

    return true;
}

SceneMapInfo_t CMap::ToProto() {
    SceneMapInfo_t _proto = std::make_shared<SceneMapInfo>();
    _proto->set_map_block_size(m_maze_cell_size);
    for (auto&& _colmn_it : m_maze) {
        auto _colmn = _proto->add_map_info();
        for (auto&& _row_it: _colmn_it) {
            auto _block = _colmn->add_rows();
            _block->set_state(_row_it);
        }
    }
    return _proto;
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

    uint32_t _start_x_block = uint32_t(_attr_map->m_map_postion.m_x / m_maze_cell_size);
    uint32_t _start_y_block = uint32_t(_attr_map->m_map_postion.m_y / m_maze_cell_size);

    uint32_t _end_x_block = uint32_t(tar_pos_.m_x / m_maze_cell_size);
    uint32_t _end_y_block = uint32_t(tar_pos_.m_y / m_maze_cell_size);
    SAstarPoint_t _path = m_astar->getPath(_start_x_block, _start_y_block, _end_x_block, _end_y_block);
    
    while (_path) {
        CPosition _tmp_pos;
        _tmp_pos.m_x = _path->m_x * m_maze_cell_size + float((float)m_maze_cell_size / 2.f);
        _tmp_pos.m_y = _path->m_y * m_maze_cell_size + float((float)m_maze_cell_size / 2.f);
        _attr_map->m_path_pos.push_front(_tmp_pos);
        _path = _path->m_parent;
    }

    for (auto _path_node_it : _attr_map->m_path_pos) {
        LogInfo << "[CMap::MoveTo]: _path_node_it [" << _path_node_it.m_x << " : " << _path_node_it.m_y << "]" << FlushLog;
    }

    return true;
}