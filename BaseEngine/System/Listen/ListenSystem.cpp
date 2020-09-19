#include "./ListenSystem.h"
#include "EngineInclude.h"

const std::string g_listen = "127.0.0.1";
const uint32_t g_listen_port = 10000;
bool ListenSystem::EnvDefine() {
    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
        if (!_conn) {
            return;
        }
        if (_conn->GetConnNodeType() != NodeType::ListServer) {
            return;
        }
        //如果连接成功,则发消息获取当前服务器需要鉴监听的ip和端口号
        RetrieveServerConfigReq_t _msg = std::make_shared<RetrieveServerConfigReq>();
        _msg->set_server_type((uint32_t)getNodeType());
        ApiSendMessageToSessionConnect((SessionConn)conn_id_,_msg);

    }, "OpenConnect");


    MessageBus::getInstance()->Attach([this](std::string ip_, uint32_t port_) {
        //进行监听
        NetManager::getInstance()->Accept(ip_,port_);

    }, "RetrieveListenConfig");

    ProtobufDispatch::getInstance()->registerMessageCallback<RetrieveServerConfigAck>([this](const SessionConn conn_,
        const std::shared_ptr<RetrieveServerConfigAck>& msg_,
        const int64_t& receive_time_) {
        if (msg_->result_state() == RetrieveServerConfigAck_checkResult_notExists) {
            LogError << "[ListenSystem] not find this server has config in list server " << FlushLog;
            return;
        }

        const std::string _listen_ip = msg_->listen_ip();
        const uint32_t    _listen_port = msg_->listen_port();
        if (!_listen_ip.empty()) {
            MessageBus::getInstance()->SendReq<std::string, uint32_t>(_listen_ip, _listen_port, "RetrieveListenConfig");
        }

        const std::string _db_ip = msg_->db_ip();
        const uint32_t    _db_port = msg_->db_port();
        if (!_db_ip.empty()) {
            MessageBus::getInstance()->SendReq<std::string, uint32_t>(_db_ip, _db_port, "RetrieveDBConfig");
        }

        const std::string _gate_ip = msg_->gate_ip();
        const uint32_t    _gate_port = msg_->gate_port();

        if (!_gate_ip.empty()) {
            MessageBus::getInstance()->SendReq<std::string, uint32_t>(_gate_ip, _gate_port, "RetrieveGateConfig");
        }
    });

    return true;
}
bool ListenSystem::PreInit() {
    return true;
}
bool ListenSystem::Init() {
    NetManager::getInstance()->Connect(g_listen,g_listen_port,NodeType::ListServer);

    return true;
}
bool ListenSystem::Loop(const uint64_t interval_) {
    return true;
}
bool ListenSystem::Quit() {
    return true;
}
bool ListenSystem::Destroy() {
    return true;
}