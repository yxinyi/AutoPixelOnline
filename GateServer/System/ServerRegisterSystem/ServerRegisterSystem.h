#pragma once
#include "System/BaseSystem.h"
#include "./ServerRegisterStruct.h"
#include "EngineInclude.h"
#include <map>
#include <set>

//gate ��������Ϣ�ķַ�

//version 1 , �����Ƿֲ�ʽ, ÿ��������ֵ�������һ��

class ServerRegisterSystem :public BaseSystem {
public:
    ServerRegisterSystem() :BaseSystem(typeid(ServerRegisterSystem).name()) {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();

private:
    std::map<std::string, std::vector<ServerInfo_wt>> m_msg_str_to_server;
    std::map<uint32_t, ServerInfo_t> m_id_to_server;

};