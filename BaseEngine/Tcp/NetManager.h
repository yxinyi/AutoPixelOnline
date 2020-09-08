#pragma once
#include "../../Common/include/tool/SingletonTemplate.h"
#include "Connection.h"
#include "asio.hpp"
#include "../Common/google/protobuf/message.h"
#include <mutex>

struct ConnectTargetConfig {
    ConnectTargetConfig(const string& str_, const uint32_t port_, const NodeType& node_type_= NodeType::Client):m_ip(str_),m_port(port_), m_node_type(node_type_){}
    std::string m_ip;
    NodeType m_node_type;
    uint32_t m_port;
};

class NetManager : public Singleton<NetManager> {
public:
    bool Start(const string& ip_ = "0.0.0.0", const uint32_t port_ = 9000);
    bool Stop();
    //bool SendMessageData(const uint32_t conn_id_, const char* data_, const uint32_t length_);
    bool SendMessageBuff(const uint32_t conn_id_, shared_ptr<CBuffer> buff_);
    bool SendMessageBuff(const uint32_t conn_id_, shared_ptr<google::protobuf::Message> buff_);
    bool WaitConnect();

    CConnection_t Connect(const string& ip_, const uint16_t port_, const NodeType& node_type_ = NodeType::Client);
private:
    asio::ip::tcp::acceptor* m_acceptor;
    asio::io_service m_service;
    std::thread m_run_thread;



};