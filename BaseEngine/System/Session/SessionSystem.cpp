#include "./SessionSystem.h"
#include "Tcp/NetManager.h"

bool Session::SendMessageBuff(std::shared_ptr<google::protobuf::Message> msg_) const {
    SessionPack_t _pack = std::make_shared<SessionPack>();
    _pack->set_seesion_id(m_session_id);
    _pack->set_pack_name(msg_->GetTypeName());
    _pack->set_pack_str(msg_->SerializeAsString());
    NetManager::getInstance()->SendMessageBuff(m_conn_id, _pack);
    return true;
}

bool SessionSystem::EnvDefine() {

    ProtobufDispatch::getInstance()->registerMessageCallback<SessionPack>([this](const uint32_t conn_id_,
        const SessionPack_t& message_,
        const int64_t& receive_time_) {

        const uint64_t _session_id = message_->seesion_id();
        Session_t _session = FindSession(_session_id);
        if (!_session) {
            RETURN_VOID;
        }
        const std::string _msg_data = message_->pack_str();
        const std::string _msg_name = message_->pack_name();
        MessagePtr _msg(ProtobufCodec::getInstance()->decode(_msg_name, _msg_data));
        MessageBus::getInstance()->SendReq<Session_t, MessagePtr>(_session, _msg, _msg_name);
    });

    ProtobufDispatch::getInstance()->registerMessageCallback<SessionCreate>([this](const uint32_t conn_id_,
        const SessionCreate_t& message_,
        const int64_t& receive_time_) {
        CreateSession(message_->seesion_id(), conn_id_);
    });
    ProtobufDispatch::getInstance()->registerMessageCallback<SessionDestory>([this](const uint32_t conn_id_,
        const SessionDestory_t& message_,
        const int64_t& receive_time_) {
        DestorySession(message_->seesion_id());
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

Session_t SessionSystem::FindSession(const uint64_t session_id_) {
    auto _session_find = m_session_pool.find(session_id_);
    if (_session_find == m_session_pool.end()) {
        RETURN_NULLPTR;
    }
    return _session_find->second;
}bool SessionSystem::CreateSession(const uint64_t session_id_, const uint32_t conn_id_) {
    auto _session_find = m_session_pool.find(session_id_);
    if (_session_find != m_session_pool.end()) {
        RETURN_FALSE;
    }
    Session_t _sesstion = std::make_shared<Session>(session_id_, conn_id_);
    m_session_pool[session_id_] = _sesstion;
    return true;
}
bool SessionSystem::DestorySession(const uint64_t session_id_) {
    auto _session_find = m_session_pool.find(session_id_);
    if (_session_find == m_session_pool.end()) {
        RETURN_FALSE;
    }
    m_session_pool.erase(session_id_);
    return true;
}

