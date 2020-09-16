#pragma once
#include "EngineInclude.h"
#include "System/BaseSystem.h"
#include "./ServerStartConfigRetrieveStruct.h"


/*
Ŀǰ�ƻ���һ�����������רע��ά��һ������,��������һ̨���������ά���������������,���Զ��� listserver ��˵,����ͨ�������� IP ��ַ��������ȷ�ķ���������,

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
