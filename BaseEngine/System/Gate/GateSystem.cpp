#include "./GateSystem.h"
#include "EngineInclude.h"

bool GateSystem::EnvDefine() {
    
    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
        if (!_conn) {
            RETURN_VOID;
        }

        if (_conn->GetConnNodeType() == NodeType::GateServer) {
            ConnGateServer();
        }

    }, "CloseConnect");
    MessageBus::getInstance()->Attach([this](std::string ip_, uint32_t port_) {
        m_gateserver_ip = ip_;
        m_gateserver_port = port_;
        ConnGateServer();
    }, "RetrieveGateConfig");

    return true;
}

bool GateSystem::ConnGateServer() {
    LogInfo << "[ServerNodeRegisterSystem] ConnGateServer " << m_gateserver_ip << " " << m_gateserver_port << FlushLog;
    NetManager::getInstance()->Connect(m_gateserver_ip, m_gateserver_port, NodeType::GateServer);
    return true;
}


bool GateSystem::PreInit() {
    return true;
}
bool GateSystem::Init() {
    return true;
}
bool GateSystem::Loop(const uint64_t interval_) {
    return true;
}
bool GateSystem::Quit() {
    return true;
}
bool GateSystem::Destroy() {
    return true;
}