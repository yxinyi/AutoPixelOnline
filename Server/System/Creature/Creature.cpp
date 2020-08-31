#include "./Creature.h"
#include "tool/ProtobufDispatcher.h"
#include "MessageBus/MessageBus.h"
#include "tool/ObjectPool.h"
#include "tool/LogInfo.h"
#include "Tcp/NetManager.h"
#include "Error/Error.h"

RegSystem(CreatureManager)

bool CreatureManager::EnvDefine() {
    //先忽略前置,假设已经通过验证并从数据库拿出玩家存档
    EventRegister(PlayerLoginEvent, [this](const uint32_t conn_,
        const PlayerLoginEvent_t& message_,
        const int64_t& receive_time_) {

        if (!CreateCreature(conn_, message_)) {
            LogError << "[PlayerLoginEvent] create err " << FlushLog;
            NetManager::getInstance()->SendMessageBuff(conn_,ApiBuildErrorMsg(LOG_ERR));
        }
    });

    return true;
}
bool CreatureManager::PreInit() {

    ApiAttrDefine("Player", "BaseAttr", "postion_x:float:0", AttrCfg::NONE);
    ApiAttrDefine("Player", "BaseAttr", "postion_y:float:0", AttrCfg::NONE);

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


bool CreatureManager::CreateCreature(const uint32_t conn_, const PlayerLoginEvent_t& message_) {
    Creature_t _login_create = CObjectPool<Creature>::getInstance()->Get("Player");
    const uint64_t _oid = _login_create->GetOid();
    if (m_oid_to_player.find(_oid) != m_oid_to_player.end()) {
        return false;
    }
    if (m_conid_to_player.find(conn_) != m_conid_to_player.end()) {
        return false;
    }
    m_oid_to_player[_oid] = _login_create;
    m_conid_to_player[conn_] = _oid;
    return true;
}

