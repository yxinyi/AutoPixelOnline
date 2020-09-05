#pragma once
#include "System/BaseSystem.h"
#include "Attribute/Attribute.h"
#include "Creature/CreatureStruct.h"
#include "tool/AStar.h"
#include <vector>
#include <list>
#include "proto/Map.pb.h"
#include <set>

struct CPosition {
    float m_postion_x = 0.f;
    float m_postion_y = 0.f;
};
using MapData_t = shared_ptr<MapData>;
using MapTickUpdate_t = shared_ptr<MapTickUpdate>;
using SceneMapInfo_t = shared_ptr<SceneMapInfo>;
class CAttrMap : public CAttr {
public:
    CAttrMap() :CAttr("CAttrMap") {}
    ~CAttrMap() {}
    Message_t ToSaveProto() {
        return nullptr;
    }
    bool decodeSaveData(Message_t msg_) {
        MapData_t _msg = std::dynamic_pointer_cast<MapData>(msg_);

        if (!_msg) {
            return false;
        }
        m_speed = _msg->speed();
        m_map_postion.m_postion_x = _msg->map_postion().postion_x();
        m_map_postion.m_postion_y = _msg->map_postion().postion_y();

        m_vector_x = _msg->vector().postion_x();
        m_vector_y = _msg->vector().postion_y();

        uint64_t m_map_oid = _msg->map_oid();
        return true;
    }

    bool decodeSaveData(const std::string& msg_) {
        MapData_t _msg = make_shared<MapData>();
        if (!_msg) {
            return false;
        }
        _msg->ParseFromString(msg_);

        return decodeSaveData(_msg);
    }

    Message_t ToClientProto() {
        MapData_t _msg = make_shared<MapData>();

        auto _pos = _msg->mutable_map_postion();
        _pos->set_postion_x(m_map_postion.m_postion_x);
        _pos->set_postion_y(m_map_postion.m_postion_y);

        _msg->set_map_oid(m_map_oid);
        _msg->set_speed(m_speed);
        _msg->set_last_map_tid(m_last_map_tid);
        return _msg;
    };

    shared_ptr<CAttr> Clone() {
        shared_ptr<CAttrMap> _attr = make_shared<CAttrMap>();
        _attr->m_map_postion = m_map_postion;
        return _attr;
    }

    float m_speed = 5.f;
    CPosition m_map_postion;
    float m_vector_x = 0.f;
    float m_vector_y = 0.f;
    uint64_t m_map_oid = 0;
    uint32_t m_last_map_tid = 0; //最后一次地图
    std::list<CPosition> m_path_pos;
    
};
using CAttrMap_t = shared_ptr<CAttrMap>;

struct CMapConfig {
    CMapConfig() {
        m_max_x = m_maze_shape[0].size() * m_cell_size;
        m_max_y = m_maze_shape.size() * m_cell_size;
    }
    std::vector<std::vector<uint32_t>> m_maze_shape = { 
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {0,1,0,1,0,1,0,1,0,1,0,1,0,1,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    CPosition m_default_postion = { 0.0f ,0.f};
    uint32_t m_cell_size = 30;
    uint32_t m_tid = 0;
    uint32_t m_auto_create = 1; //是否自动创建
    uint32_t m_max_x = 0;
    uint32_t m_max_y = 0;
};
using CMapConfig_t = shared_ptr<CMapConfig>;



class CMap {
public:
    bool init(const uint64_t oid_, const CMapConfig_t cfg_) {
        m_config = cfg_;
        m_map_oid = oid_;
        m_astar = make_shared<Astar>(cfg_->m_maze_shape);
        return true;
    }
    bool reset() { return true; }

public:
    bool EnterScene(Creature_t creature_) {
        CAttrMap_t _attr_map = creature_->GetAttrs()->ApiGetAttr<CAttrMap>("CAttrMap");
        if (!_attr_map) {
            return false;
        }
        _attr_map->m_map_oid = m_map_oid;
        _attr_map->m_last_map_tid = m_config->m_tid;
        _attr_map->m_map_postion = m_config->m_default_postion;
        return true;
    }
    uint32_t GetPlayerSize() { return (uint32_t)m_players.size(); }
    const std::set<uint32_t>& GetPlayer() { return m_players; }

    bool PosMoveCheck(const CPosition& pos_);
    SceneMapInfo_t ToProto();
    bool MoveTo(Creature_t creature_, CPosition pos_);

private:
    std::set<uint32_t>              m_players;
    std::vector<std::vector<uint32_t>> m_maze_shape;

private: //map confg
    CMapConfig_t m_config;
    uint64_t m_map_oid;
    Astar_t m_astar = nullptr;
};

using Map_t = shared_ptr<CMap>;

