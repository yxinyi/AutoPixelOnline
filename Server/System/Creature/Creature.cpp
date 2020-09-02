#include "./Creature.h"
#include "tool/ProtobufDispatcher.h"
#include "MessageBus/MessageBus.h"
#include "tool/ObjectPool.h"
#include "tool/LogInfo.h"
#include "Tcp/NetManager.h"
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


class CAttrCreature : public CAttr {
public:
    CAttrCreature() :CAttr("CAttrCreature") {}

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
        shared_ptr<CAttrCreature> _attr = make_shared<CAttrCreature>();
        _attr->m_postion_x = m_postion_x;
        _attr->m_postion_y = m_postion_y;
        return _attr;
    }
private:
    float m_postion_x = 0.f;
    float m_postion_y = 0.f;
};





bool CreatureManager::PreInit() {

    CAttrManager::getInstance()->Register("Player", make_shared<CAttrCreature>());
    CAttrManager::getInstance()->Register("Monster", make_shared<CAttrCreature>());

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
    Creature_t _login_create = CObjectPool<Creature>::getInstance()->Get("Player", conn_);
    const uint64_t _oid = _login_create->GetOid();
    if (m_oid_to_player.find(_oid) != m_oid_to_player.end()) {
        return nullptr;
    }
    if (m_conid_to_player.find(conn_) != m_conid_to_player.end()) {
        return nullptr;
    }
    m_oid_to_player[_oid] = _login_create;
    m_conid_to_player[conn_] = _login_create;
    return _login_create;
}

