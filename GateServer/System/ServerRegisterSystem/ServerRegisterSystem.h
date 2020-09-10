#pragma once
#include "System/BaseSystem.h"
#include "./ServerRegisterStruct.h"
#include "EngineInclude.h"
#include <map>
#include <set>
#include <memory>
#include <vector>



class ServerRegisterSystem :public BaseSystem {
public:
    ServerRegisterSystem() :BaseSystem(typeid(ServerRegisterSystem).name()) {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();

    uint32_t GetMinLoadServerInfo(NodeType);
private:
    std::map<std::string, std::vector<ServerInfo_wt>> m_msg_str_to_server;
    std::map<uint32_t, ServerInfo_t> m_id_to_server;

    std::map<NodeType, ServerInfo_wt> m_nodetype_to_server;

    //对于Gate来说, session 和 conn 是一一对应
    //逻辑服务器 可以通过 session id 找到对应的 客户端
    //客户端发送消息至Gate时, Gate 需加上对应的 session id 再转发至对应的 目标服务器

    std::map<uint32_t, GateSession_t> m_session_to_conn;
    std::map<uint32_t, GateSession_t> m_conn_to_session;
};