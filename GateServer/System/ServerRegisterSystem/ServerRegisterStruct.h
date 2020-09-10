#pragma once
#include "System/BaseSystem.h"
#include <vector>
#include <string>
#include <memory>
#include "proto/ServerLink.pb.h"
#include "ServerTypeStruct.h"


enum class ServerState {
    Error,
    Touch,
    initializa,
    runing,
};

struct  ServerInfo{
    uint32_t m_conn_id;
    NodeType m_node_type;
    ServerState m_state = ServerState::Error;
    std::vector<std::string> m_message_register;

    uint32_t m_load_number = 0;
};
using ServerInfo_t = std::shared_ptr<ServerInfo>;
using ServerInfo_wt = std::weak_ptr<ServerInfo>;

using DataBaseNotify_t = std::shared_ptr<DataBaseNotify>;

//gate 将进行消息的分发


enum class GateSessionState {
    Error,
    Pass,
    NeedAuthenticate,
};

struct GateSession {
    /*
        假如一个服务器类型有多个集群形式
        那么需要指定当前客户端与哪一个在通信
    */
    uint32_t m_conn_id = 0;
    uint64_t m_session_id = 0;
    GateSessionState m_state = GateSessionState::Error;
    std::map<NodeType, uint32_t> m_type_conn;
};
using GateSession_t = std::shared_ptr<GateSession>;