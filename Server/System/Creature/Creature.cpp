#include "./Creature.h"
#include "EngineInclude.h"
#include "Error/Error.h"
#include <memory>

RegSystem(CreatureManager)

bool CreatureManager::EnvDefine() {
    //先忽略前置,假设已经通过验证并从数据库拿出玩家存档

    ProtobufDispatch::getInstance()->registerMessageCallback<PlayerLoginEvent>([this](const uint32_t conn_,
        const PlayerLoginEvent_t& message_,
        const int64_t& receive_time_) {
        Creature_t _creature = CreateCreature(conn_, message_);
        if (!_creature) {
            LogError << "[PlayerLoginEvent] create err " << FlushLog;
            NetManager::getInstance()->SendMessageBuff(conn_, ApiBuildErrorMsg(LOG_ERR));
            return;
        }
        MessageBus::getInstance()->SendReq<Creature_t>(_creature, "PlayerLogin");
    });

    return true;
}







bool CreatureManager::PreInit() {


    return true;
}
bool CreatureManager::Init() {
    return true;
}
bool CreatureManager::Loop(const uint64_t interval_) {
    return true;
}
bool CreatureManager::Quit() {
    return true;
}
bool CreatureManager::Destroy() {
    return true;
}


shared_ptr<Creature> CreatureManager::CreateCreature(const uint32_t conn_, const PlayerLoginEvent_t& message_) {
    auto _conn_find = m_conid_to_player.find(conn_);
    if (_conn_find != m_conid_to_player.end()) {
        return _conn_find->second;
    }
    Creature_t _login_create = CObjectPool<Creature>::getInstance()->Get("Player", conn_);
    const uint64_t _oid = _login_create->GetOid();
    if (m_oid_to_player.find(_oid) != m_oid_to_player.end()) {
        return nullptr;
    }
    m_oid_to_player[_oid] = _login_create;
    m_conid_to_player[conn_] = _login_create;
    return _login_create;
}

Creature_t CreatureManager::FindCreatureByOid(const uint64_t& oid_) {
    auto _ply_find = m_oid_to_player.find(oid_);
    if (_ply_find == m_oid_to_player.end()) {
        return nullptr;
    }
    return _ply_find->second;
}


