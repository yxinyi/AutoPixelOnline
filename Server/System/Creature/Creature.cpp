#include "./Creature.h"
#include "tool/ProtobufDispatcher.h"
#include "MessageBus/MessageBus.h"
#include "tool/ObjectPool.h"
#include "tool/LogInfo.h"
#include "Tcp/NetManager.h"
#include "Error/Error.h"

RegSystem(CreatureManager)

bool CreatureManager::EnvDefine() {
    //�Ⱥ���ǰ��,�����Ѿ�ͨ����֤�������ݿ��ó���Ҵ浵

    ProtobufDispatch::getInstance()->registerMessageCallback<PlayerLoginEvent>([this](const uint32_t conn_,
        const PlayerLoginEvent_t& message_,
        const int64_t& receive_time_) {
        shared_ptr<Creature> _creature = CreateCreature(conn_, message_);
        if (!_creature) {
            LogError << "[PlayerLoginEvent] create err " << FlushLog;
            NetManager::getInstance()->SendMessageBuff(conn_, ApiBuildErrorMsg(LOG_ERR));
            return;
        }
        MessageBus::getInstance()->SendReq<uint64_t>(_creature->GetOid(), "CreateCreature");
    });

    //EventRegister(PlayerLoginEvent, [this](const uint32_t conn_,
    //    const PlayerLoginEvent_t& message_,
    //    const int64_t& receive_time_) {
    //    shared_ptr<Creature> _creature = CreateCreature(conn_, message_);
    //    if (!_creature) {
    //        LogError << "[PlayerLoginEvent] create err " << FlushLog;
    //        NetManager::getInstance()->SendMessageBuff(conn_, ApiBuildErrorMsg(LOG_ERR));
    //        return;
    //    }
    //    MessageBus::getInstance()->SendReq<uint64_t,int>(_creature->GetOid(),1, "CreateCreature");
    //});



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

