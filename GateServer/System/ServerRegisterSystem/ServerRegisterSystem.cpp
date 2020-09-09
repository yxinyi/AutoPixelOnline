#include "./ServerRegisterSystem.h"
RegSystem(ServerRegisterSystem)





bool ServerRegisterSystem::EnvDefine() {
    ProtobufDispatch::getInstance()->SetDefaultCallback([this](const uint32_t conn_,
        const std::shared_ptr<Message>& msg_,
        const int64_t& tm_) {
        //û�н���ע��Ķ�����ת��
        const string& _msg_name = msg_->GetTypeName();
        auto _info_find = m_msg_str_to_server.find(_msg_name);
        if (_info_find == m_msg_str_to_server.end()) {
            NetManager::getInstance()->SendMessageBuff(conn_, ApiBuildErrorMsg(SERVER_IS_CLOSE));
            return;
        }
        
        for (auto _wk_it = _info_find->second.begin(); _wk_it != _info_find->second.end(); ) {
            if (ServerInfo_t _info = _wk_it->lock()) {
                NetManager::getInstance()->SendMessageBuff(_info->m_conn_id, msg_);
                _wk_it++;
            }
            else {
                _wk_it = _info_find->second.erase(_wk_it);
            }
        }
    });


    ProtobufDispatch::getInstance()->registerMessageCallback<ServerLink>([this](const uint32_t conn_,
        const std::shared_ptr<ServerLink>& msg_,
        const int64_t& tm_) {


        auto _conn_find = m_id_to_server.find(conn_);
        if (_conn_find == m_id_to_server.end()) {
            LogError << "[ServerRegisterSystem] ServerLink ERR" << msg_->node_type() << FlushLog;
            return;
        }
        _conn_find->second->m_node_type = (NodeType)msg_->node_type();
        _conn_find->second->m_state = ServerState::initializa;
        DataBaseNotify_t _notify = std::make_shared<DataBaseNotify>();

        LogInfo << "[ServerRegisterSystem] ServerLink Touch" << conn_ << FlushLog;

        auto _obj = Json::parse("{ \"db_ip\": \"127.0.0.1\", \"db_port\": 9000 }");
        _notify->set_db_ip(_obj["db_ip"]);
        _notify->set_db_port(_obj["db_port"]);
        NetManager::getInstance()->SendMessageBuff(conn_,_notify);
    });


    ProtobufDispatch::getInstance()->registerMessageCallback<ServerMessageRegister>([this](const uint32_t conn_,
        const std::shared_ptr<ServerMessageRegister>& msg_,
        const int64_t& tm_) {
        auto _conn_find = m_id_to_server.find(conn_);
        if (_conn_find == m_id_to_server.end()) {
            LogError << "[ServerRegisterSystem] ServerMessageRegister ERR" << conn_ << FlushLog;
            return;
        }
        LogInfo << "[ServerRegisterSystem] ServerLink runing" << (uint32_t)conn_ << FlushLog;
        for (auto&& _it :msg_->message_str()) {
            LogInfo << "[ServerRegisterSystem] msg str " << _it  << FlushLog;
        }
        _conn_find->second->m_state = ServerState::runing;

        int _msg_size = msg_->message_str_size();
        for (int _msg_idx = 0; _msg_idx < _msg_size;_msg_idx++) {
            const string& _msg_str = msg_->message_str(_msg_idx);
            _conn_find->second->m_message_register.push_back(_msg_str);
            ServerInfo_wt _weak_info(_conn_find->second);
            m_msg_str_to_server[_msg_str].push_back(_weak_info);
        }
    });
    

    MessageBus::getInstance()->Attach([this](uint32_t conn_) {
        if (m_id_to_server.find(conn_) != m_id_to_server.end()) {
            LogError << "[ServerRegisterSystem] OpenConnect ERR" << conn_ << FlushLog;
            return;
        }
        ServerInfo_t _info = std::make_shared<ServerInfo>();
        _info->m_state = ServerState::Touch;
        _info->m_conn_id = conn_;
        LogInfo << "[ServerRegisterSystem] OpenConnect" << (uint32_t)conn_ << FlushLog;

        m_id_to_server[_info->m_conn_id] = _info;
    }, "AcceptConnect");

    MessageBus::getInstance()->Attach([this](uint32_t conn_) {
        if (m_id_to_server.find(conn_) != m_id_to_server.end()) {
            LogInfo << "[ServerRegisterSystem] CloseConnect" << (uint32_t)conn_ << FlushLog;
            m_id_to_server.erase(conn_);
        }


    }, "CloseConnect");

    return true;
}
bool ServerRegisterSystem::PreInit() {
    return true;
}
bool ServerRegisterSystem::Init() {
    return true;
}
bool ServerRegisterSystem::Loop(const uint64_t interval_) {
    return true;
}
bool ServerRegisterSystem::Quit() {
    return true;
}
bool ServerRegisterSystem::Destroy() {
    return true;
}