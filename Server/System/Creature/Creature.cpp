#include "./Creature.h"
#include "EngineInclude.h"
#include "Error/Error.h"
#include "LogicSessionControl/LogicSessionControl.h"
#include <memory>

RegSystem(CreatureManager)
std::string g_role_query = "QueryRoleDataBase:";
bool CreatureManager::EnvDefine() {
    //先忽略前置,假设已经通过验证并从数据库拿出玩家存档

    //ProtobufDispatch::getInstance()->registerMessageCallback<PlayerLogin>([this](const uint32_t conn_,
    //    const PlayerLoginEvent_t& message_,
    //    const int64_t& receive_time_) {
    //    Creature_t _creature = CreateCreature(conn_, message_);
    //    if (!_creature) {
    //        LogError << "[PlayerLoginEvent] create err " << FlushLog;
    //        NetManager::getInstance()->SendMessageBuff(conn_, ApiBuildErrorMsg(LOG_ERR));
    //        return;
    //    }
    //    MessageBus::getInstance()->SendReq<Creature_t>(_creature, "PlayerLogin");
    //});


    ProtobufDispatch::getInstance()->registerMessageCallback<PlayerEnter>([this](const SessionConn conn_,
        const std::shared_ptr<PlayerEnter>& message_,
        const int64_t& receive_time_) {
        Creature_t _creature = CreateCreature(ApiGetSession(conn_));
        if (!_creature) {
            LogError << "[PlayerLoginEvent] create err " << FlushLog;
            NetManager::getInstance()->SendMessageBuff(conn_, ApiBuildErrorMsg(LOG_ERR));
            return;
        }

        std::shared_ptr<LogicSessionControlSystem> _sys =  SystemManager::getInstance()->GetSystem<LogicSessionControlSystem>();
        if (!_sys) {
            LogError << "[PlayerLoginEvent] LogicSessionControlSystem not exsits " << FlushLog;
            return;
        }

        CDataBaseSystem_t _db_sys = SystemManager::getInstance()->GetSystem<CDataBaseSystem>();
        if (!_db_sys) {
            LogError << "[PlayerLoginEvent] LogicSessionControlSystem not exsits " << FlushLog;
            return;
        }

        uint32_t _account_key = _sys->GetAccountKey(ApiGetSession(conn_));
        std::string _role_query = g_role_query+std::to_string(_account_key);
        _db_sys->Query(_role_query, [](DBOperatorErr err_, std::string val_) {
            uint64_t _oid = 0;
            
            if (err_ == DBOperatorErr::ERR) {
                //是新玩家
                _oid = UniqueNumberFactory::getInstance()->build();
            }
            123122321


        
        });

        //去数据库查询账号信息

        MessageBus::getInstance()->SendReq<Creature_t>(_creature, "PlayerLogin");
    });

    //PlayerEnter

    return true;
}





bool CreatureManager::PreInit() {


    return true;
}
bool CreatureManager::Init() {
    //TimerTaskManager::getInstance()->RegisterTask("CreatureManager::Loop", 0, 50, -1, []() {
    //    if (shared_ptr<CDataBaseSystem> _sys = SystemManager::getInstance()->GetSystem<CDataBaseSystem>()) {
    //        static uint64_t _key = 1;
    //        uint64_t _test_kv = _key++;
    //        _sys->Upsert(to_string(_test_kv), to_string(_test_kv), [_sys, _test_kv](DBOperatorErr err_, string rst_) {
    //            if (err_ == DBOperatorErr::SUCCESS) {
    //                _sys->Query(to_string(_test_kv), [_test_kv](DBOperatorErr err_, string rst_) {
    //                    LogInfo << "[DBTest query]: err_: " << (uint32_t)err_ << " key: [" << _test_kv << "] vale: " << rst_ << FlushLog;
    //                });
    //            }
    //        });
    //    }
    //});
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


Creature_t CreatureManager::CreateCreature(const uint32_t session_) {
    auto _conn_find = m_session_to_player.find(session_);
    if (_conn_find != m_session_to_player.end()) {
        return _conn_find->second;
    }
    Creature_t _login_create = CObjectPool<Creature>::getInstance()->Get("Player", session_);
    const uint64_t _oid = _login_create->GetOid();
    if (m_oid_to_player.find(_oid) != m_oid_to_player.end()) {
        return nullptr;
    }
    m_oid_to_player[_oid] = _login_create;
    m_session_to_player[session_] = _login_create;
    return _login_create;
}

Creature_t CreatureManager::FindCreatureByOid(const uint64_t& oid_) {
    auto _ply_find = m_oid_to_player.find(oid_);
    if (_ply_find == m_oid_to_player.end()) {
        return nullptr;
    }
    return _ply_find->second;
}


