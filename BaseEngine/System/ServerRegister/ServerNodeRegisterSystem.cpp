#include "./ServerNodeRegisterSystem.h"

bool ServerNodeRegisterSystem::EnvDefine() {

    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
        if (!_conn) {
            RETURN_VOID;
        }

        if (_conn->GetConnNodeType() == NodeType::GateServer) {
            LogInfo << "[ServerNodeRegisterSystem] OpenConnect" << (uint32_t)conn_id_ << FlushLog;
            ServerLink_t _link = make_shared<ServerLink>();
            _link->set_node_type((uint32_t)getNodeType());
            NetManager::getInstance()->SendMessageBuff(conn_id_, _link);
        }

    }, "OpenConnect");

    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
        if (!_conn) {
            RETURN_VOID;
        }

        if (_conn->GetConnNodeType() == NodeType::GateServer) {
            LogInfo << "[ServerNodeRegisterSystem] CloseConnect" << (uint32_t)conn_id_ << FlushLog;
            ConnGateServer();
        }

    }, "CloseConnect");

    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
        if (!_conn || _conn->GetConnNodeType() != NodeType::DataBaseServer) {
            RETURN_VOID;
        }
        ServerMessageRegister_t _msg_reg = make_shared<ServerMessageRegister>();

        auto _all_name = ProtobufDispatch::getInstance()->GetAllMessageTypeStr();
        for (auto&& _name_it : _all_name) {
            _msg_reg->add_message_str(_name_it);
        }
        set<uint32_t> _cnn_set = CConnectionMgr::getInstance()->GetConnection(NodeType::GateServer);
        if (_cnn_set.size() != 1) {
            RETURN_VOID;
        }
        for (auto&& _conn_it : _cnn_set) {
            NetManager::getInstance()->SendMessageBuff(_conn_it, _msg_reg);
        }

    }, "DBServerOpen");

    return true;
}
bool ServerNodeRegisterSystem::PreInit() {
    return true;
}
extern NodeType getNodeType();

bool ServerNodeRegisterSystem::ConnGateServer() {
    LogInfo << "[ServerNodeRegisterSystem] ConnGateServer " << GetGateIP() << " " << GetGatePort() << FlushLog;

    NetManager::getInstance()->Connect(GetGateIP(), GetGatePort(), NodeType::GateServer);
    return true;
}

bool ServerNodeRegisterSystem::Init() {

    ConnGateServer();
    return true;
}
bool ServerNodeRegisterSystem::Loop(const uint64_t interval_) {
    return true;
}
bool ServerNodeRegisterSystem::Quit() {
    return true;
}
bool ServerNodeRegisterSystem::Destroy() {
    return true;
}