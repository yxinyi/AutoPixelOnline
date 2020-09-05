#include "NetManager.h"


bool NetManager::Start(const string& ip_, const uint32_t port_) {


    asio::ip::tcp::endpoint _end_point(asio::ip::address_v4::from_string(ip_), port_);

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
    CConnection_t _new_connection = CConnectionMgr::getInstance()->CreateConnection(m_service);
    m_acceptor->async_accept(_new_connection->GetSocket(), [this,_new_connection](const error_code& err_){
        if (!err_) {
            _new_connection->ConnectedOK();
            _new_connection->Recv();
            WaitConnect();
        }
        else {
            _new_connection->close();
        }
    });
    return true;
}

CConnection_t NetManager::Connect(const string& ip_, const uint16_t port_, const string& nick_name_) {
    CConnection_t _conn = CConnectionMgr::getInstance()->CreateConnection(m_service, nick_name_);

    asio::ip::tcp::resolver _resolver(m_service);
    asio::ip::tcp::resolver::iterator _endpoints = _resolver.resolve(asio::ip::tcp::resolver::query(ip_, to_string(port_)));
    asio::async_connect(_conn->GetSocket(), _endpoints,
        [=](error_code err_, asio::ip::tcp::resolver::iterator)
    {
        if (err_.value() == 10061) {
            Connect(ip_, port_);
        }
        else 
        if (!err_)
        {
            _conn->ConnectedOK();
            _conn->Recv();
        }
        else {
            _conn->close();
        }
    });
    return _conn;
}

bool NetManager::SendMessageBuff(const uint32_t conn_id_, shared_ptr<CBuffer> buff_) {

    CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
    if (!_conn) {
        return false;
    }
    if (!_conn->isConnection()) {
        return false;
    }
    _conn->Send(buff_);
    if (!_conn->inSended()) {
        m_service.post([=]() {
            _conn->DoSend();
        });
    }
    return true;
}

bool NetManager::SendMessageBuff(const uint32_t conn_id_, shared_ptr<google::protobuf::Message> buff_) {
    shared_ptr<CBuffer> _buffer = CObjectPool<CBuffer>::getInstance()->Get();
    _buffer->appendInt32(buff_->GetTypeName().size());
    _buffer->append(buff_->GetTypeName());
    _buffer->append(buff_->SerializePartialAsString());

    return SendMessageBuff(conn_id_, _buffer);
}
