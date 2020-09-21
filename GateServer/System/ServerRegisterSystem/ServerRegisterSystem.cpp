#include "./ServerRegisterSystem.h"
#include "proto/PlayerLogin.pb.h"
RegSystem(ServerRegisterSystem)

123123
//��Ҫ��������� gate ϵͳ
//��ǰϵͳ��Ҫд���������ʵ�ֱ����߼����������߶����µĶϿ����� client ,Ŀ�����һ���ܴӵײ���ܽ����Ŀ�ĵĿ��

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


    ProtobufDispatch::getInstance()->SetDefaultCallback([](const uint64_t conn_,
        const std::shared_ptr<Message>& msg_,
        const int64_t& tm_) {
        MessageBus::getInstance()->SendReq<uint32_t, std::string, std::string>(ApiGetConnID(conn_), msg_->GetTypeName(), msg_->SerializeAsString(), "DespatchDecodeFailed");
    });

    MessageBus::getInstance()->Attach([this](uint32_t conn_, std::string msg_name_, std::string msg_str_) {
        const uint32_t _conn_id = ApiGetConnID(conn_);
        auto _session_find = m_conn_to_session.find(_conn_id);
        if (_session_find == m_conn_to_session.end()) {
            RETURN_VOID;
        }

        //����Ƿ�ͨ����֤
        //if (_session_find->second->m_state != GateSessionState::Pass) {
        //    //���ûͨ��,���ǿͻ���,���ж��Ƿ��ǵ�½,����ǵ�½��֤���������
        //    auto _serverinfo_find = m_id_to_server.find(_conn_id);
        //    if (_serverinfo_find->second->m_node_type != NodeType::Client) {// || msg_->GetTypeName() != "PlayerLogin") {
        //        RETURN_VOID;
        //    }
        //}
        //������Ϣ�ҵ�ע���˸���Ϣ�ķ�����,
        const string& _msg_name = msg_name_;
        auto _info_find = m_msg_str_to_server.find(_msg_name);
        if (_info_find == m_msg_str_to_server.end()) {
            NetManager::getInstance()->SendMessageBuff(_conn_id, ApiBuildErrorMsg(SERVER_IS_CLOSE));
            return;
        }

        if (!_info_find->second.size()) {
            NetManager::getInstance()->SendMessageBuff(_conn_id, ApiBuildErrorMsg(SERVER_IS_CLOSE));
            return;
        }
        for (auto _node_it = _info_find->second.begin(); _node_it != _info_find->second.end(); ) {
            if (ServerInfo_t _info = _node_it->lock()) {
                if (_session_find->second->m_state != GateSessionState::Pass) {
                    //�����ͨ��ֻ�������˺�ϵͳͨ��
                    if (_info->m_node_type != NodeType::AccountServer) {
                        _node_it++;
                        continue;
                    }
                }
                //�������������,�����ת��
                _session_find->second->m_type_conn.insert(_info->m_conn_id);
                m_id_to_server[_info->m_conn_id]->m_load_number++;

                LogInfo << "[ServerRegisterSystem] forward msg " << msg_name_ << " to target " << GetNodeTypeStr(_info->m_node_type) << FlushLog;

                //���ת��
                SessionPack_t _pack = std::make_shared<SessionPack>();
                _pack->set_seesion_id(_session_find->second->m_session_id);
                _pack->set_pack_name(msg_name_);
                _pack->set_pack_str(msg_str_);
                NetManager::getInstance()->SendMessageBuff(_info->m_conn_id, _pack);

                _node_it++;
            }
            else {
                _node_it = _info_find->second.erase(_node_it);
            }
        }
    }, "DespatchDecodeFailed");
    
    ProtobufDispatch::getInstance()->registerMessageCallback<PlayerLoginAck>([this](const uint64_t conn_,
        const std::shared_ptr<PlayerLoginAck>& msg_,
        const int64_t& tm_) {
        auto _session_find = m_session_to_conn.find(msg_->session_key());
        if (_session_find == m_session_to_conn.end()) {
            RETURN_VOID;
        }
    
        if (msg_->result() == PlayerLoginAck_CheckResult_Pass) {
            _session_find->second->m_state = GateSessionState::Pass;
        }
    
    });

    //SessionPack ���Gate�յ�����Ϣ,��Ϊת����Ϣ,ͨ����Ϣ�е�session �ҵ���Ӧ������
    ProtobufDispatch::getInstance()->registerMessageCallback<SessionPack>([this](const uint64_t conn_,
        const std::shared_ptr<SessionPack>& msg_,
        const int64_t& tm_) {
        const uint32_t _session_id = msg_->seesion_id();
        auto _session_find = m_session_to_conn.find(_session_id);
        if (_session_find == m_session_to_conn.end()) {
            //������û�˾Ͳ�ת����
            RETURN_VOID;
        }

        //��Ҫ�Ż�
        const uint32_t _conn_id = _session_find->second->m_conn_id;
        NetManager::getInstance()->SendMessageBuff(_conn_id, msg_->pack_name(), msg_->pack_str());
    });



    /*
        �����������ڵ�����
        ���ӳɹ����� ServerMessageRegister ������Ϣ�Զ�ע��,�������������
    */




    ProtobufDispatch::getInstance()->registerMessageCallback<ServerMessageRegister>([this](const uint64_t conn_,
        const std::shared_ptr<ServerMessageRegister>& msg_,
        const int64_t& tm_) {
        const uint32_t _conn_id = ApiGetConnID(conn_);
        auto _conn_find = m_id_to_server.find(_conn_id);
        if (_conn_find == m_id_to_server.end()) {
            LogError << "[ServerRegisterSystem] ServerMessageRegister ERR" << _conn_id << FlushLog;
            return;
        }
        auto _session_find = m_conn_to_session.find(_conn_id);
        if (_session_find == m_conn_to_session.end()) {
            LogError << "[ServerRegisterSystem] ServerLink ERR" << msg_->node_type() << FlushLog;
            return;
        }
        _session_find->second->m_state = GateSessionState::Pass;
        const NodeType _node_type = (NodeType)msg_->node_type();
        _conn_find->second->m_node_type = (NodeType)msg_->node_type();


        if (_node_type != NodeType::Client && m_nodetype_to_server.find(_node_type) != m_nodetype_to_server.end()) {
            LogError << "[ServerRegisterSystem] ServerLink Exist" << GetNodeTypeStr(_node_type) << FlushLog;
            CConnectionMgr::getInstance()->CloseConnection(_conn_id);
            RETURN_VOID;
        }



        LogInfo << "[ServerRegisterSystem] ServerLink runing" << (uint32_t)_conn_id << FlushLog;
        for (auto&& _it : msg_->message_str()) {
            LogInfo << "[ServerRegisterSystem] msg str " << _it << FlushLog;
        }
        _conn_find->second->m_state = ServerState::runing;

        int _msg_size = msg_->message_str_size();
        for (int _msg_idx = 0; _msg_idx < _msg_size; _msg_idx++) {
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
        m_id_to_server[_info->m_conn_id] = _info;
        //����������������Seesion ����
        //��ǰֻ�����Ӳ�û�б������
        GateSession_t _gate_session = std::make_shared<GateSession>();
        _gate_session->m_conn_id = conn_;
        _gate_session->m_state = GateSessionState::NeedAuthenticate;
        _gate_session->m_session_id = UniqueNumberFactory::getInstance()->build32();
        m_session_to_conn[_gate_session->m_session_id] = _gate_session;
        m_conn_to_session[_gate_session->m_conn_id] = _gate_session;

    }, "AcceptConnect");

    MessageBus::getInstance()->Attach([this](uint32_t conn_) {
        auto _serverInfo_find = m_id_to_server.find(conn_);
        if (_serverInfo_find == m_id_to_server.end()) {
            return;
        }
        //����ǵ�ǰ�������еĹ��ܷ������Ͽ�,��ɾ��Ψһ����
        if (_serverInfo_find->second->m_node_type != NodeType::Client && _serverInfo_find->second->m_node_type != NodeType::NodeError) {
            m_nodetype_to_server.erase(_serverInfo_find->second->m_node_type);
        }
        auto _session_find = m_conn_to_session.find(conn_);
        if (_session_find != m_conn_to_session.end()) {
            //��ѯ��ǰ���Ӷ���Щ�ڵ���й�ͨ��,��������
            for (auto&& _it : _session_find->second->m_type_conn) {
                auto _serverinfo_find = m_id_to_server.find(_it);
                if (_serverinfo_find != m_id_to_server.end()) {
                    _serverinfo_find->second->m_load_number--;

                    //֪ͨĿ�����������session
                    SessionDestory_t _create_msg = std::make_shared<SessionDestory>();
                    _create_msg->set_seesion_id(_session_find->second->m_session_id);
                    NetManager::getInstance()->SendMessageBuff(_it, _create_msg);
                }
            }
            m_session_to_conn.erase(_session_find->second->m_session_id);
            m_conn_to_session.erase(conn_);
        }
        

        m_id_to_server.erase(conn_);
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