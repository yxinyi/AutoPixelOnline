#include "NetManager.h"


bool NetManager::Start() {


    asio::ip::tcp::endpoint _end_point(asio::ip::address_v4::from_string("0.0.0.0"), 8888);

    m_acceptor = new asio::ip::tcp::acceptor(m_service, _end_point, true);
    WaitConnect();

    m_run_thread = std::thread([this]() {
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
bool NetManager::WaitConnect() {
    CConnection* _new_connection = CConnectionMgr::getInstance()->CreateConnection(m_service);
    m_acceptor->async_accept(_new_connection->GetSocket(), [this,_new_connection](const error_code& err_){
        if (!err_) {
            _new_connection->Recv();
            WaitConnect();
        }
        else {
            _new_connection->close();
        }
    });
}

CConnection* NetManager::Connect(const string& ip_, const uint16_t port_) {
    CConnection* _conn = CConnectionMgr::getInstance()->CreateConnection(m_service);

    asio::ip::tcp::resolver _resolver(m_service);
    asio::ip::tcp::resolver::iterator _endpoints = _resolver.resolve(asio::ip::tcp::resolver::query(ip_, to_string(port_)));
    asio::async_connect(_conn->GetSocket(), _endpoints,
        [=](error_code err_, asio::ip::tcp::resolver)
    {
        if (!err_)
        {
            _conn->Recv();
        }
        else {
            _conn->close();
        }
    });

}
bool NetManager::SendMessageData(const uint32_t conn_id_, const char* data_, const uint32_t length_) {
    CConnection* _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
    if (!_conn) {
        return false;
    }
    if (!_conn->isConnection()) {
        return false;
    }
    _conn->appendSendBuf(data_,length_);
    _conn->Send();

    return true;
}
bool NetManager::SendMessageBuff(const uint32_t conn_id_, const CBuffer* buff_) {
    return SendMessageData(conn_id_, buff_->peek(),buff_->readableBytes());
}