#pragma once
#include "System/BaseSystem.h"
#include "./CreatureStruct.h"
#include "include/proto/PlayerLogin.pb.h"
#include "Attribute/Attribute.h"

using PlayerLoginEvent_t = std::shared_ptr<PlayerLogin>;

class CreatureManager :public BaseSystem{
public:
    CreatureManager() :BaseSystem(typeid(CreatureManager).name()) {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();
public:
    Creature_t CreateCreature(const SessionConn session_conn_);
    Creature_t FindCreatureByOid(const uint64_t& oid_);


private:
    std::map<uint32_t, Creature_t> m_session_to_player;
    std::map<uint64_t, Creature_t> m_oid_to_player;

};
