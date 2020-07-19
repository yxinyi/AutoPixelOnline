#pragma once
#include "./TcpBase.h"


class CTcpClient : public CTcpBase, public std::enable_shared_from_this<CTcpClient> {
public:
    bool init(const std::string& address_, const uint16_t port_);
    bool shankhand();
    std::shared_ptr<SChannel> getChannel(const std::string& route_id_);
    bool recv(std::shared_ptr<std::vector<std::shared_ptr<SMsgPacket>>> msg_vec_);
    bool send(std::shared_ptr<SMsgPacket> msg_vec_);
protected:
    std::shared_ptr<SChannel> m_channel;
    int m_shakehand_state;
};