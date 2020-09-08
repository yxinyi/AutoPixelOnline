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
};
using ServerInfo_t = std::shared_ptr<ServerInfo>;
using ServerInfo_wt = std::weak_ptr<ServerInfo>;

using DataBaseNotify_t = std::shared_ptr<DataBaseNotify>;