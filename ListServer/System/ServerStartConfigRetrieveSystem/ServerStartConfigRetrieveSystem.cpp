#include "./ServerStartConfigRetrieveSystem.h"

RegSystem(ServerStartConfigRetrieveSystem)

RetrieveServerConfigAck_t ServerStartConfigRetrieveSystem::BuildAckMsg(const ServerConfig& config_) {
    RetrieveServerConfigAck_t _ack = std::make_shared<RetrieveServerConfigAck>();
    _ack->set_db_ip(config_.m_db_ip);
    _ack->set_db_port(config_.m_db_port);
    _ack->set_gate_ip(config_.m_gate_ip);
    _ack->set_gate_port(config_.m_gate_port);
    _ack->set_listen_ip(config_.m_listen_ip);
    _ack->set_listen_port(config_.m_listen_port);
    return _ack;
}
bool ServerStartConfigRetrieveSystem::EnvDefine() {
    ProtobufDispatch::getInstance()->registerMessageCallback<RetrieveServerConfigReq>([this](const SessionConn session_conn_,
        const RetrieveServerConfigReq_t& message_,
        const int64_t& receive_time_) {

        const NodeType _src_type = (NodeType)message_->server_type();
        std::string _conn_ip = ApiGetConnectIPPortStr(ApiGetConnID(session_conn_));
        RetrieveServerConfigAck_t _ack = nullptr;
        //if (_src_type == NodeType::Client) {
        //    //����ǿͻ���,����ҪЯ����ǰѡ��ķ�����,������ǰֻ��һ�������ֻ���ص�һ��
        //    const ServerConfig& _cfg = (m_servers_config.begin()->second)[NodeType::Client];
        //    _ack = BuildAckMsg(_cfg);
        //}

        auto _rst_state = RetrieveServerConfigAck_checkResult_notExists;
        do {

            //��IP�Ƿ�ע��
            //auto _config_find = m_servers_config.find(_conn_ip);
            //if (_config_find == m_servers_config.end()) {
            //    _rst_state = RetrieveServerConfigAck_checkResult_notExists;
            //    break;
            //}
            //�������Ƿ���ȷ

            const ServerConfig& _cfg = (m_servers_config.begin()->second)[_src_type];
            _ack = BuildAckMsg(_cfg);
            
            _rst_state = RetrieveServerConfigAck_checkResult_success;

        } while (false);

        _ack->set_result_state(_rst_state);
        ApiSendMessageToSessionConnect(session_conn_, _ack);
    });
    return true;
}
bool ServerStartConfigRetrieveSystem::PreInit() {
    // Ӧ�ô��ļ��ж�ȡ���ߴ���������ݿ��л�ȡ��Щ��Ϣ
    m_servers_config["127.0.0.1"] = {
        {NodeType::Client,{"",0,"",0,"127.0.0.1",9000}},
        {NodeType::GateServer,{"127.0.0.1",9000,"",0,"",0}},
        {NodeType::LogicServer,{"127.0.0.1",8000,"127.0.0.1",7000,"127.0.0.1",9000}},
        {NodeType::DataBaseServer,{"127.0.0.1",7000,"",0,"",0}},
        {NodeType::AccountServer,{"127.0.0.1",6000,"127.0.0.1",7000,"127.0.0.1",9000}},
        {NodeType::ListServer,{"127.0.0.1",5000,"",0,"",0}}
    };
    return true;
}
bool ServerStartConfigRetrieveSystem::Init() {
    return true;
}
bool ServerStartConfigRetrieveSystem::Loop(const uint64_t interval_) {
    return true;
}
bool ServerStartConfigRetrieveSystem::Quit() {
    return true;
}
bool ServerStartConfigRetrieveSystem::Destroy() {
    return true;
}