#pragma once
#include "./TcpConnonetManager.h"


bool CTcpConnonetManager::registerTcp(std::shared_ptr<CTcpBase> tcp_base_) {
    m_tcp_pool.push_back(tcp_base_);
    return true;
}
bool CTcpConnonetManager::ShakeHand() {
    for (auto&& _it : m_tcp_pool) {
        _it->shankhand();
    }
    return true;
}
std::shared_ptr<std::vector<std::shared_ptr<SMsgPacket>>> CTcpConnonetManager::pool() {
    std::shared_ptr<std::vector<std::shared_ptr<SMsgPacket>>> _vec_t(new std::vector<std::shared_ptr<SMsgPacket>> );
    for (auto&& _it : m_tcp_pool) {
        _it->recv(_vec_t);
    }
    return _vec_t;    
}

