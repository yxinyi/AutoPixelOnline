#include "./Map.h"
#include "MessageBus/MessageBus.h"
#include "Creature/Creature.h"

RegSystem(MapManager)

bool MapManager::EnvDefine() {
    MessageBus::getInstance()->Attach([](Creature_t creature_) {
        ApiGetAttr(creature_->GetAttr(),"");
    }, "PlayerLogin");
    return true;
}
bool MapManager::PreInit() {
    ApiAttrDefine("Player", "Map", "map_id:int:-1", AttrCfg::NONE);
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