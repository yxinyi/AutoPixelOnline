#include "./ServerNodeRegisterSystem.h"

bool ServerNodeRegisterSystem::EnvDefine() {


    //将当前服务器的所有网络消息进行注册
    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
        if (!_conn || _conn->GetConnNodeType() != NodeType::GateServer) {
            RETURN_VOID;
        }
        ServerMessageRegister_t _msg_reg = std::make_shared<ServerMessageRegister>();
        _msg_reg->set_node_type((uint32_t)getNodeType());

        auto _all_name = ProtobufDispatch::getInstance()->GetAllMessageTypeStr();
        for (auto&& _name_it : _all_name) {
            _msg_reg->add_message_str(_name_it);
        }
        ApiSendMessageToSessionConnect(conn_id_, _msg_reg);

    }, "OpenConnect");




    return true;
}
bool ServerNodeRegisterSystem::PreInit() {
    return true;
}
extern NodeType getNodeType();


bool ServerNodeRegisterSystem::Init() {

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