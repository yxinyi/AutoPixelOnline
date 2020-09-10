#include "./ServerRegisterSystem.h"
RegSystem(ServerRegisterSystem)

const uint32_t g_server_notfind_conn_id = 0XFFFFFFFF;

uint32_t ServerRegisterSystem::GetMinLoadServerInfo(NodeType node_type_) {
    uint32_t _rst_load_num = 0XFFFFFFFF;
    uint32_t _rst_cnn_id = g_server_notfind_conn_id;
    for (auto&& _it : m_id_to_server) {
        if (_it.second->m_node_type == node_type_) {
            if (_it.second->m_load_number < _rst_load_num) {
                _rst_cnn_id = _it.second->m_conn_id;
            }
        }
    }
    return _rst_cnn_id;
}



bool ServerRegisterSystem::EnvDefine() {
    ProtobufDispatch::getInstance()->SetDefaultCallback([this](const uint32_t conn_,
        const std::shared_ptr<Message>& msg_,
        const int64_t& tm_) {

        auto _session_find = m_conn_to_session.find(conn_);
        if (_session_find == m_conn_to_session.end()) {
            RETURN_VOID;
        }

        //检查是否通过认证
        if (_session_find->second->m_state != GateSessionState::Pass) {
            //如果没通过,且是客户端,则判断是否是登陆,如果是登陆验证则允许放行
            auto _serverinfo_find = m_id_to_server.find(conn_);
            if (_serverinfo_find->second->m_node_type != NodeType::Client || msg_->GetTypeName() != "PlayerLogin") {
                RETURN_VOID;
            }
        }
        //根据消息找到注册了该消息的服务器,
        const string& _msg_name = msg_->GetTypeName();
        auto _info_find = m_msg_str_to_server.find(_msg_name);
        if (_info_find == m_msg_str_to_server.end()) {
            NetManager::getInstance()->SendMessageBuff(conn_, ApiBuildErrorMsg(SERVER_IS_CLOSE));
            return;
        }

        if (!_info_find->second.size()) {
            NetManager::getInstance()->SendMessageBuff(conn_, ApiBuildErrorMsg(SERVER_IS_CLOSE));
            return;
        }
        //找到对应消息包服务器的类型
        NodeType _type = NodeType::NodeError;
        for (auto _it = _info_find->second.begin(); _it != _info_find->second.end();) {
            if (ServerInfo_t _info = _it->lock()) {
                _type = _info->m_node_type;
                break;
            }
            else {
                _it = _info_find->second.erase(_it);
            }
        }

        if (_type == NodeType::NodeError) {
            NetManager::getInstance()->SendMessageBuff(conn_, ApiBuildErrorMsg(SERVER_IS_CLOSE));
            return;
        }

        //判断之前是否有曾经连接
        if (_session_find->second->m_type_conn.find(_type) == _session_find->second->m_type_conn.end()) {
            //如果之前没有连接过该类型的服务器,则进行指定
            uint32_t _conn_id = GetMinLoadServerInfo(_type);
            if (_conn_id == g_server_notfind_conn_id) {
                NetManager::getInstance()->SendMessageBuff(conn_, ApiBuildErrorMsg(SERVER_IS_CLOSE));
                return;
            }
            //通知目标服务器建立session
            SessionCreate_t _create_msg = std::make_shared<SessionCreate>();
            _create_msg->set_seesion_id(_session_find->second->m_session_id);
            NetManager::getInstance()->SendMessageBuff(_conn_id, _create_msg);

            _session_find->second->m_type_conn[_type] = _conn_id;
            m_id_to_server[_conn_id]->m_load_number++;
        }

        LogInfo << "[ServerRegisterSystem] forward msg " << msg_->GetTypeName() << " to target " << GetNodeTypeStr(_type) << FlushLog;

        //打包转发
        SessionPack_t _pack = std::make_shared<SessionPack>();
        _pack->set_seesion_id(_session_find->second->m_session_id);
        _pack->set_pack_name(msg_->GetTypeName());
        _pack->set_pack_str(msg_->SerializeAsString());
        NetManager::getInstance()->SendMessageBuff(_session_find->second->m_type_conn[_type], _pack);
    });

    //SessionPack 如果Gate收到该消息,则为转发消息,通过消息中的session 找到对应的链接
    ProtobufDispatch::getInstance()->registerMessageCallback<SessionPack>([this](const uint32_t conn_,
        const std::shared_ptr<SessionPack>& msg_,
        const int64_t& tm_) {
        const uint64_t _session_id = msg_->seesion_id();
        auto _session_find = m_session_to_conn.find(_session_id);
        if (_session_find == m_session_to_conn.end()) {
            //服务器没了就不转发了
            RETURN_VOID;
        }

        //需要优化
        const uint32_t _conn_id =  _session_find->second->m_conn_id;
        MessagePtr _msg(ProtobufCodec::getInstance()->decode(msg_->pack_name(), msg_->pack_str()));
        NetManager::getInstance()->SendMessageBuff(_conn_id, _msg);
    });

    ProtobufDispatch::getInstance()->registerMessageCallback<ServerLink>([this](const uint32_t conn_,
        const std::shared_ptr<ServerLink>& msg_,
        const int64_t& tm_) {
        

        
        auto _conn_find = m_id_to_server.find(conn_);
        if (_conn_find == m_id_to_server.end()) {
            LogError << "[ServerRegisterSystem] ServerLink ERR" << msg_->node_type() << FlushLog;
            return;
        }

        auto _session_find = m_conn_to_session.find(conn_);
        if (_session_find == m_conn_to_session.end()) {
            LogError << "[ServerRegisterSystem] ServerLink ERR" << msg_->node_type() << FlushLog;
            return;
        }
        _session_find->second->m_state = GateSessionState::Pass;

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
        //当有连接连入生成Seesion 并绑定
        //当前只是连接并没有表明身份
        GateSession_t _gate_session = std::make_shared<GateSession>();
        _gate_session->m_conn_id = conn_;
        _gate_session->m_state = GateSessionState::NeedAuthenticate;
        _gate_session->m_session_id = UniqueNumberFactory::getInstance()->build();
        m_session_to_conn[_gate_session->m_session_id] = _gate_session;
        m_conn_to_session[_gate_session->m_conn_id] = _gate_session;

    }, "AcceptConnect");

    MessageBus::getInstance()->Attach([this](uint32_t conn_) {
        if (m_id_to_server.find(conn_) != m_id_to_server.end()) {
            LogInfo << "[ServerRegisterSystem] CloseConnect" << (uint32_t)conn_ << FlushLog;
            m_id_to_server.erase(conn_);
        }
        auto _session_find = m_conn_to_session.find(conn_);
        if (_session_find != m_conn_to_session.end()) {
            for (auto&& _it : _session_find->second->m_type_conn) {
                auto _serverInfo_find = m_id_to_server.find(_it.second);

                if (_serverInfo_find != m_id_to_server.end()) {
                    _serverInfo_find->second->m_load_number--;


                    //通知目标服务器销毁session
                    SessionDestory_t _create_msg = std::make_shared<SessionDestory>();
                    _create_msg->set_seesion_id(_session_find->second->m_session_id);
                    NetManager::getInstance()->SendMessageBuff(_it.second, _create_msg);
                }
            }
            m_session_to_conn.erase(_session_find->second->m_session_id);
        }




        m_conn_to_session.erase(conn_);
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