#pragma once
#include "System/BaseSystem.h"
#include "Attribute/Attribute.h"
#include "Creature/CreatureStruct.h"
#include <vector>
#include <set>

struct CPosition {
    float m_postion_x = 0.f;
    float m_postion_y = 0.f;
};
class CAttrMap : public CAttr {
public:
    CAttrMap() :CAttr("CAttrMap") {}

    shared_ptr<Message> ToSaveProto() {
        return nullptr;
    }
    bool decodeSaveData(shared_ptr<Message> msg_) {
        shared_ptr<Message> _msg = std::dynamic_pointer_cast<Message>(msg_);

        if (!_msg) {
            return false;
        }
        return true;
    }

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
    std::vector<CPosition> m_path_pos;
    
};
using CAttrMap_t = shared_ptr<CAttrMap>;

struct CMapConfig {
    std::vector<std::vector<uint32_t>> m_maze_shape = { 
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0}, 
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    CPosition m_default_postion = { 0.0f ,0.f};
    uint32_t m_cell_size = 30;
    uint32_t m_tbl_id = 1;
};
using CMapConfig_t = shared_ptr<CMapConfig>;



class CMap {
public:
    bool init(const uint64_t oid_, const CMapConfig_t cfg_) {
        m_config = cfg_;
        m_map_oid = oid_;
        return true;
    }
    bool reset() { return true; }

public:
    bool EnterScene(Creature_t creature_) {
        CAttrMap_t _attr_map = creature_->GetAttr()->ApiGetAttr<CAttrMap>("CAttrMap");
        if (!_attr_map) {
            return false;
        }
        _attr_map->m_map_oid = m_map_oid;
        _attr_map->m_map_postion = m_config->m_default_postion;
        return true;
    }
    uint32_t GetPlayerSize() { return (uint32_t)m_players.size(); }
private:
    std::set<uint32_t>              m_players;
    std::vector<std::vector<uint32_t>> m_maze_shape;

private: //map confg
    CMapConfig_t m_config;
    uint64_t m_map_oid;
};
using Map_t = shared_ptr<CMap>;

