#include "NetManager.h"


bool NetManager::Start() {


    asio::ip::tcp::endpoint _end_point(boost::asio::ip::address_v4::from_string("0.0.0.0"), 8888);

    m_acceptor = new asio::ip::tcp::acceptor(m_service, _end_point, true);
    WaitConnect();

    m_run_thread = std::thread([](this) {
        m_service.run();
    });

    return true;
}
bool NetManager::Stop() {
    m_service.stop();
    m_acceptor->close();
    m_run_thread.join();
    return true;
}
bool NetManager::SendMessageData(const uint32_t conn_id_, const char* data_, const uint32_t length_);
bool NetManager::SendMessageBuff(const uint32_t conn_id_, const CBuffer* buff_);
bool NetManager::WaitConnect() {
    CConnection* _new_connection = CConnectionMgr::getInstance()->CreateConnection();
    m_acceptor->async_accept(_new_connection->GetSocket(), [](CConnection* _new_connection, const error_code& err_{
        if (!err_) {
            _new_connection->Recv();
            WaitConnect();
        }
        else {
            _new_connection->close();
        }
    };
}

CConnection* NetManager::Connect(const string& ip_, const uint16_t port_);