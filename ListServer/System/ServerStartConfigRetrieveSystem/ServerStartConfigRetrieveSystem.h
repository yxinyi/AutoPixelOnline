#pragma once
#include "EngineInclude.h"
#include "System/BaseSystem.h"
#include "./ServerStartConfigRetrieveStruct.h"


/*
目前计划是一组物理服务器专注于维护一个区服,并不打算一台物理服务器维护两个区服的情况,所以对于 listserver 来说,可以通过用物理 IP 地址来返回正确的服务器配置,

*/

class ServerStartConfigRetrieveSystem :public BaseSystem{
public:
    ServerStartConfigRetrieveSystem() :BaseSystem(typeid(ServerStartConfigRetrieveSystem).name()) {}
    ~ServerStartConfigRetrieveSystem() {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();

private:
    std::map<std::string, std::map<NodeType, ServerConfig>> m_servers_config;

};
