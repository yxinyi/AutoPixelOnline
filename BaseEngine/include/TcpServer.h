#pragma once
#include "./TcpBase.h"

class CTcpServer : public CTcpBase , public std::enable_shared_from_this<CTcpServer>{
public:
    bool init(const std::string& address_, const uint16_t port_) ;
    bool shankhand();
    std::shared_ptr<SChannel> getChannel(const std::string& route_id_);
    bool recv(std::shared_ptr<std::vector<std::shared_ptr<SMsgPacket>>> msg_vec_);
    bool send(std::shared_ptr<SMsgPacket> msg_vec_);
protected:
    bool CheckAndClear();
    std::map<std::string, std::shared_ptr<SChannel>> m_channel_pool;
};