#include "./ServerStartConfigRetrieveSystem.h"

RegSystem(ServerStartConfigRetrieveSystem)

bool ServerStartConfigRetrieveSystem::EnvDefine() {
    ProtobufDispatch::getInstance()->registerMessageCallback<RetrieveServerConfigReq>([this](const SessionConn session_conn_,
        const RetrieveServerConfigReq_t& message_,
        const int64_t& receive_time_) {

        const NodeType _src_type = (NodeType)message_->server_type();
        std::string _conn_ip = ApiGetConnectIPPortStr(ApiGetConnID(session_conn_));
        RetrieveServerConfigAck_t _ack = std::make_shared<RetrieveServerConfigAck>();
        if (_src_type == NodeType::Client) {
            
        }



        auto _rst_state = RetrieveServerConfigAck_checkResult_notExists;
        do {

            //看IP是否注册
            auto _config_find = m_servers_config.find(_conn_ip);
            if (_config_find == m_servers_config.end()) {
                _rst_state = RetrieveServerConfigAck_checkResult_notExists;
                break;
            }
            //看类型是否正确

            
            _rst_state = RetrieveServerConfigAck_checkResult_success;

        } while (false);

        _ack->set_result_state(_rst_state);
        ApiSendMessageToSessionConnect(session_conn_, _ack);
    });
    return true;
}
bool ServerStartConfigRetrieveSystem::PreInit() {
    // 应该从文件中读取或者从特殊的数据库中获取这些信息
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