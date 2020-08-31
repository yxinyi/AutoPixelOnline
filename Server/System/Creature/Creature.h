#pragma once
#include "System/BaseSystem.h"
#include "./CreatureStruct.h"
#include "include/proto/PlayerLogin.pb.h"

using PlayerLoginEvent_t = shared_ptr<PlayerLoginEvent>;
class CreatureManager :public BaseSystem {
public:
    CreatureManager() :BaseSystem("CreatureManager") {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();
public:
    bool CreateCreature(const uint32_t conn_,const PlayerLoginEvent_t& message_);


private:
    std::map<uint32_t, uint64_t> m_conid_to_player;
    
    std::map<uint64_t,shared_ptr<Creature>> m_oid_to_player;

};
