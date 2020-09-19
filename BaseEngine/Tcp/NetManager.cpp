#include "./NetManager.h"


bool NetManager::Start() {

    m_run_thread = std::thread([this]() {
        m_service.run();
    });
    return true;
}

bool NetManager::Accept(const std::string& ip_, const uint32_t port_) {
    asio::ip::tcp::endpoint _end_point(asio::ip::address_v4::from_string(ip_), port_);
    m_acceptor = new asio::ip::tcp::acceptor(m_service, _end_point, true);
    WaitConnect();
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
    m_acceptor->async_accept(_new_connection->GetSocket(), [this,_new_connection](const std::error_code& err_){
        if (!err_) {
            _new_connection->AcceptOK();
            _new_connection->Recv();
            WaitConnect();
        }
        else {
            _new_connection->close();
        }
    });
    return true;
}


CConnection_t NetManager::Connect(const std::string& ip_, const uint16_t port_, const NodeType& node_type_) {
    CConnection_t _conn = CConnectionMgr::getInstance()->CreateConnection(m_service, node_type_);
    _conn->setIPStr(ip_,port_);
    asio::ip::tcp::resolver _resolver(m_service);
    asio::ip::tcp::resolver::iterator _endpoints = _resolver.resolve(asio::ip::tcp::resolver::query(ip_, std::to_string(port_)));
    asio::async_connect(_conn->GetSocket(), _endpoints,
        [=](std::error_code err_, asio::ip::tcp::resolver::iterator)
    {
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

bool NetManager::SendMessageBuff(const uint32_t conn_id_, std::shared_ptr<CBuffer> buff_) {

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


bool NetManager::SendMessageBuff(const uint32_t conn_id_, std::string msg_str_, std::string msg_data_) {
    std::shared_ptr<CBuffer> _buffer = CObjectPool<CBuffer>::getInstance()->Get();
    _buffer->appendInt32((int32_t)msg_str_.size());
    _buffer->append(msg_str_);
    _buffer->append(msg_data_);

    return SendMessageBuff(conn_id_, _buffer);
}

bool NetManager::SendMessageBuff(const uint32_t conn_id_, std::shared_ptr<google::protobuf::Message> buff_) {
    return SendMessageBuff(conn_id_, buff_->GetTypeName(), buff_->SerializePartialAsString());
}


bool NetManager::SendMessageBuff(const SessionConn session_conn_, std::shared_ptr<google::protobuf::Message> msg_) {
    Session _session = ApiGetSession(session_conn_);
    if (_session) {
        SessionPack_t _pack = std::make_shared<SessionPack>();
        _pack->set_seesion_id(ApiGetSession(session_conn_));
        _pack->set_pack_name(msg_->GetTypeName());
        _pack->set_pack_str(msg_->SerializeAsString());

        return SendMessageBuff(ApiGetConnID(session_conn_), _pack);
    }
    else {
        return SendMessageBuff(ApiGetConnID(session_conn_), msg_);
    }
    return false;
}

bool ApiSendMessageToSessionConnect(const SessionConn session_conn_, std::shared_ptr<google::protobuf::Message> msg_) {
    return NetManager::getInstance()->SendMessageBuff(session_conn_,msg_);
}

