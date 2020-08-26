#pragma once
#include "../../Common/include/tool/SingletonTemplate.h"
#include "Connection.h"
#include "asio.hpp"
#include "../Common/google/protobuf/message.h"
#include <mutex>


class NetManager : public Singleton<NetManager> {
public:
    bool Start(const string& ip_, const uint32_t port_);
    bool Stop();
    //bool SendMessageData(const uint32_t conn_id_, const char* data_, const uint32_t length_);
    bool SendMessageBuff(const uint32_t conn_id_, shared_ptr<CBuffer> buff_);
    bool SendMessageBuff(const uint32_t conn_id_, shared_ptr<google::protobuf::Message> buff_);
    bool WaitConnect();
    
    CConnection* Connect(const string& ip_, const uint16_t port_);
private:
    asio::ip::tcp::acceptor* m_acceptor;
    asio::io_service m_service;
    std::thread m_run_thread;

    

};