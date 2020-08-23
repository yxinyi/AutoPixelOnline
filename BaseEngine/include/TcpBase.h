#pragma once
#include "zmq/cppzmq/zmq_addon.hpp"
#include <memory>
#include <string>
#include "google/protobuf/message.h"

const size_t g_shakehand_time = 1;
class CTcpBase;
struct SChannel {
    std::shared_ptr<CTcpBase> m_tcp_info;
    std::string  m_route_id;
    uint64_t m_last_shakehand_time;
};


struct  SMsgPacket{
    std::shared_ptr<SChannel> m_channel;
    std::shared_ptr<google::protobuf::Message> m_msg;
};
using fd_t = size_t;
class CTcpBase{
public:
    virtual bool init(const std::string& address_, const uint32_t port_) = 0;
    virtual bool shankhand() = 0;
    virtual bool recv(std::shared_ptr<std::vector<std::shared_ptr<SMsgPacket>>> msg_vec_) = 0;
    virtual bool send(std::shared_ptr<SMsgPacket> msg_vec_) = 0;
    std::string get_feature_str() { return m_feature_str; }
    std::shared_ptr<zmq::socket_t> get_socket() { return m_socket; }
protected:
    std::shared_ptr<zmq::socket_t> m_socket;
    std::string m_feature_str;
};
