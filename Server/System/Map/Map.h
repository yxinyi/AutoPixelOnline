#pragma once
#include "./MapStruct.h"
#include "System/BaseSystem.h"


class CMapConfigMgr :public Singleton<CMapConfigMgr> {
    friend class Singleton<CMapConfigMgr>;
public:
    bool init() {
        CMapConfig_t _tmp_cfg = make_shared<CMapConfig>();
        m_configs[_tmp_cfg->m_tbl_id] = _tmp_cfg;
    };

    const CMapConfig_t FindMapConfig(const uint32_t map_tbl_id_)const {
        auto _find = m_configs.find(map_tbl_id_);
        if (_find == m_configs.end()) {
            return nullptr;
        }
        return _find->second;
    }
private:
    CMapConfigMgr() {};
    std::map<uint32_t, CMapConfig_t> m_configs;
};

class MapManager :public BaseSystem, public Singleton<MapManager> {
public:
    MapManager() :BaseSystem("MapManager") {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();

public:
    Map_t CreateMap(const uint32_t map_tbl_id_);
    Map_t EnterMap(Creature_t creature_, const uint32_t map_tbl_id_);
    Map_t GetMinLoadMapByTableID(const uint32_t map_tbl_id_);
    Map_t GetMapByMapOid(const uint64_t map_oid_);

private:
    std::map<uint64_t, Map_t> m_map_pool;
    std::map<uint32_t, std::vector<Map_t>> m_type_to_map;

};
