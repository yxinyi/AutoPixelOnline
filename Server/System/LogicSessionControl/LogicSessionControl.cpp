#include "./LogicSessionControl.h"
#include "EngineInclude.h"

RegSystem(LogicSessionControlSystem)

bool LogicSessionControlSystem::EnvDefine() {

    ProtobufDispatch::getInstance()->registerMessageCallback<LogicEnterFromAccountServer>([this](const SessionConn conn_,
        const LogicEnterFromAccountServer_t& message_,
        const int64_t& receive_time_) {
        
        LogInfo << "[PlayerLoginEvent] LogicEnterFromAccountServer " << message_->account_key() << " " << message_->session_key() << FlushLog;

        const uint64_t _account_key = message_->account_key();
        const uint32_t _session_key = message_->session_key();

        if (m_session_to_account.find(_session_key) != m_session_to_account.end()) {
            LogInfo << "[LogicSessionControlSystem] session exists " << message_->account_key() << " " << message_->session_key() << FlushLog;
            return;
        }

        m_session_to_account[_session_key] = _account_key;
        MessageBus::getInstance()->SendReq<uint32_t>(_session_key, ClientEnterEvent);
    });

    //
    ProtobufDispatch::getInstance()->registerMessageCallback<SessionDestory>([this](const SessionConn conn_,
        const SessionDestory_t& message_,
        const int64_t& receive_time_) {

        const uint32_t _session_id = message_->seesion_id();
        auto _session_find = m_session_to_account.find(_session_id);
        if (_session_find == m_session_to_account.end()) {
            LogInfo << "[LogicSessionControlSystem] session  not exists " << message_->seesion_id() << FlushLog;
            return;
        }
        MessageBus::getInstance()->SendReq<uint32_t>(_session_id, ClientOutEvent);
        m_session_to_account.erase(_session_find);
    });
    

    return true;
}
bool LogicSessionControlSystem::PreInit() {
    return true;
}
bool LogicSessionControlSystem::Init() {
    return true;
}
bool LogicSessionControlSystem::Loop(const uint64_t interval_) {
    return true;
}
bool LogicSessionControlSystem::Quit() {
    return true;
}
bool LogicSessionControlSystem::Destroy() {
    return true;
}