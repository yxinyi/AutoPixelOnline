#pragma once
#include <map>
#include <string>
#include <memory>
#include <vector>
#include "proto/ListServer.pb.h"


struct ServerConfig {
    ServerConfig(std::string listen_ip_, uint32_t listen_port_, 
                 std::string db_ip_, uint32_t db_port_,
                 std::string gate_ip_, uint32_t gate_port_):
        m_listen_ip(listen_ip_), m_listen_port(listen_port_),
        m_db_ip(db_ip_), m_db_port(db_port_),
        m_gate_ip(gate_ip_), m_gate_port(gate_port_)
    {}
    std::string m_listen_ip;
    uint32_t m_listen_port = 0;

    std::string m_db_ip;
    uint32_t m_db_port = 0;

    std::string m_gate_ip;
    uint32_t m_gate_port = 0;

};

using RetrieveServerConfigReq_t = std::shared_ptr<RetrieveServerConfigReq>;
using RetrieveServerConfigAck_t = std::shared_ptr<RetrieveServerConfigAck>;



