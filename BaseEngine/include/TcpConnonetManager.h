#pragma once
#include "TcpClient.h"
#include "TcpBase.h"
#include "TcpServer.h"
#include "zmq/cppzmq/zmq_addon.hpp"
#include <map>
#include "tool/SingletonTemplate.h"


class CSendMsgPool : public Singleton<CSendMsgPool> {
public:
    void run() {
        for (auto&& _it : m_msg_list) {
            _it->m_channel->m_tcp_info->send(_it);
        }
        m_msg_list.clear();
    }
    void push_back(std::shared_ptr<SChannel> chl_,std::shared_ptr<google::protobuf::Message> msg_) {
        m_msg_list.push_back(std::shared_ptr<SMsgPacket>(new SMsgPacket{chl_,msg_}));
    }
private:
    std::vector<std::shared_ptr<SMsgPacket>> m_msg_list;
};

#define SendNetMsg Singleton<CSendMsgPool>::getInstance()->push_back

class CTcpConnonetManager : public Singleton<CTcpConnonetManager> {
    friend class Singleton<CTcpConnonetManager>;

public:
    bool registerTcp(std::shared_ptr<CTcpBase>);
    bool ShakeHand();
    std::shared_ptr<std::vector<std::shared_ptr<SMsgPacket>>>  pool();
    zmq::context_t* getContext() {return &m_context;}
private:
    CTcpConnonetManager() {};
    std::vector<std::shared_ptr<CTcpBase>> m_tcp_pool;
    zmq::context_t m_context;
};

#define TcpMgr Singleton<CTcpConnonetManager>::getInstance()

#define RegTcp Singleton<CTcpConnonetManager>::getInstance()->registerTcp