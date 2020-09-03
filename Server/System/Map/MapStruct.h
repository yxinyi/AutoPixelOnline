#pragma once
#include "System/BaseSystem.h"
#include "Attribute/Attribute.h"
#include <vector>
#include <set>


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
        _attr->m_postion_x = m_postion_x;
        _attr->m_postion_y = m_postion_y;
        return _attr;
    }
private:
    float m_postion_x = 0.f;
    float m_postion_y = 0.f;
};


struct CMapConfig {
    std::vector<std::vector<uint32_t>> m_maze_shape = { 
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0}
    };
    float m_default_bron_postion_x = 0.0f;
    float m_default_bron_postion_y = 0.0f;
};

class CMap {
public:
    bool EnterScene(shared_ptr<Creature> creature_, float postion_x = 0.f, float postion_y = 0.f) {

    }

    bool init(const CMapConfig& cfg_) {
        m_config = cfg_;
    }
    bool reset() {}
private:
    std::set<uint32_t>              m_players;
    std::vector<std::vector<uint32_t>> m_maze_shape;

private: //map confg
    CMapConfig m_config;
};
using Map_t = shared_ptr<CMap>;

