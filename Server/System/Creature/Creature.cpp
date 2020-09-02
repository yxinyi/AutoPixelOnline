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

class CAttr {
public:
    CAttr(const string& name_) :m_attr_name(name_) {}
    virtual bool LoadForSaveProto(shared_ptr<Message> msg_) {
        if (msg_->GetTypeName() != m_attr_name) {
            return false;
        }
        return decodeSaveData(msg_);
    }
    virtual shared_ptr<Message> ToSaveProto() = 0;
    string GetName() { return m_attr_name; }
protected:
    virtual bool decodeSaveData(shared_ptr<Message> msg_) = 0;
    string m_attr_name;
};

class CAttrCreature: public CAttr {
public:
    CAttrCreature():CAttr("CAttrCreature") {}

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

private:
    float m_postion_x = 0.f;
    float m_postion_y = 0.f;
};



class CAttrs {
public:
    bool Register(shared_ptr<CAttr> attr_) {
        if (m_attr_pool.find(attr_->GetName()) == m_attr_pool.end()) {
            return false;
        }
        m_attr_pool[attr_->GetName()] = attr_;
        return true;
    }

    template<class T>
    shared_ptr<T> ApiGetAttr(const string& module_name_) {
        auto _attr_find = m_attr_pool.find(module_name_);
        if (_attr_find == m_attr_pool.end()) {
            return nullptr;
        }
        shared_ptr<T> _attr = std::dynamic_pointer_cast<T>(_attr_find->second);
        if (!_attr) {
            return false;
        }

        return _attr;
    }

private:
    std::map<string, shared_ptr<CAttr>> m_attr_pool;
};



using CAttrPrototype = CAttrs;
using CAttrPrototype_t = shared_ptr<CAttrPrototype>;
class CAttrManager :public Singleton<CAttrManager>{
public:
    void Register(const string& obj_name_, shared_ptr<CAttr> attr_) {
        m_prototype_pool[obj_name_]->Register(attr_);
    }

private:
    std::unordered_map<string, CAttrPrototype_t> m_prototype_pool;
};





bool CreatureManager::PreInit() {

    CAttrManager::getInstance()->Register("Player",make_shared<CAttrCreature>());

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

