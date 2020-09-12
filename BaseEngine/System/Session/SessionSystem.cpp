#include "./SessionSystem.h"
#include "Tcp/NetManager.h"


Session ApiGetSession(SessionConn session_conn_id_) {
    return (Session)(session_conn_id_ >> 32);
}
uint32_t ApiGetConnID(SessionConn session_conn_id_) {
    return (uint32_t)(session_conn_id_);
}

bool SessionSystem::EnvDefine() {

    ProtobufDispatch::getInstance()->registerMessageCallback<SessionPack>([this](const uint64_t conn_id_,
        const SessionPack_t& message_,
        const int64_t& receive_time_) {
        const uint32_t _conn_id = (uint32_t)conn_id_;
        const uint32_t _session_id = message_->seesion_id();
        SessionConn _session_conn_id = BuildSessionConn(_session_id, _conn_id);
        const Session _session = ApiGetSession(_session_conn_id);
        const uint32_t _conn = ApiGetConnID(_session_conn_id);
        if (m_session_pool.find(_session_conn_id) == m_session_pool.end()) {
            CreateSession(_session_id, _conn_id);
        }

        const std::string _msg_data = message_->pack_str();
        const std::string _msg_name = message_->pack_name();
        MessagePtr _msg(ProtobufCodec::getInstance()->decode(_msg_name, _msg_data));
        LogInfo << "[SessionSystem] SessionPack dispatch [" << message_->pack_name()<<"]" << FlushLog;
        ProtobufDispatch::getInstance()->onProtobufMessage(_session_conn_id,_msg, receive_time_);
    });

    ProtobufDispatch::getInstance()->registerMessageCallback<SessionDestory>([this](const uint64_t conn_id_,
        const SessionDestory_t& message_,
        const int64_t& receive_time_) {
        const uint32_t _conn_id = (uint32_t)conn_id_;
        SessionConn _session_conn_id = BuildSessionConn(message_->seesion_id(), _conn_id);
        DestorySession(_session_conn_id);
    });
    return true;
}
bool SessionSystem::PreInit() {
    return true;
}
bool SessionSystem::Init() {
    return true;
}
bool SessionSystem::Loop(const uint64_t interval_) {
    return true;
}
bool SessionSystem::Quit() {
    return true;
}
bool SessionSystem::Destroy() {
    return true;
}
SessionConn SessionSystem::BuildSessionConn(const uint32_t session_id_, const uint32_t conn_id_) {
    return ((uint64_t)session_id_ << 32 | (uint64_t)conn_id_);
}

bool SessionSystem::CreateSession(const uint32_t session_id_, const uint32_t conn_id_) {
    SessionConn _session_conn_id = BuildSessionConn(session_id_, conn_id_);
    if (m_session_pool.find(_session_conn_id) != m_session_pool.end()) {
        RETURN_FALSE;
    }
    m_session_pool.insert(_session_conn_id);
    return true;
}
bool SessionSystem::DestorySession(const SessionConn session_conn_id_) {
    auto _session_find = m_session_pool.find(session_conn_id_);
    if (_session_find == m_session_pool.end()) {
        RETURN_FALSE;
    }
    m_session_pool.erase(session_conn_id_);
    return true;
}

