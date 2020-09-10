#include "./CliLoginSystem.h"
#include "./CliLoginStruct.h"
#include "ErrorNotify/CliErrorNotify.h"
#include "EngineInclude.h"
#include "Error/Error.h"
#include <math.h>

RegSystem(CliLoginSystem)

bool CliLoginSystem::EnvDefine() {
    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
        if (!_conn) {
            RETURN_VOID;
        }

        if (_conn->GetConnNodeType() == NodeType::GateServer) {
            LogInfo << "[ServerNodeRegisterSystem] CloseConnect" << (uint32_t)conn_id_ << FlushLog;
        }

        LogInfo << "[CliLoginSystem] ReConnGateServer " << GetGateIP() << " " << GetGatePort() << FlushLog;
        NetManager::getInstance()->Connect(GetGateIP(), GetGatePort(), NodeType::GateServer);
    }, "CloseConnect");
    return true;
}


bool CliLoginSystem::PreInit() {
    return true;
}
bool CliLoginSystem::Init() {
    UIManager::getInstance()->Register(UIScene::Login, [this]() {
        ImGui::SetNextWindowPos(ImVec2(440, 210));
        ImGui::SetNextWindowSize(ImVec2(400, 300));

        if (!ImGui::Begin("LogIn", nullptr, 0))
        {
            ImGui::End();
            return;
        }
        ImGui::InputText("Account", &m_account);
        ImGui::InputText("PassWord", &m_password);
        if (ImGui::Button("LogIn")){

            if (CConnection_t _conn = CConnectionMgr::getInstance()->GetOnlyOneConnection(NodeType::GateServer)) {
                PlayerLogin_t _login = std::make_shared<PlayerLogin>();
                _login->set_account(m_account);
                _login->set_account(m_password);
                NetManager::getInstance()->SendMessageBuff(_conn->getConnId(), _login);
            }
            else {
              ApiPushError(GATE_SERVER_NOT_CONN);
            }
        }
        if (ImGui::Button("Register")){
            if (CConnection_t _conn = CConnectionMgr::getInstance()->GetOnlyOneConnection(NodeType::GateServer)) {
                PlayerRegsiter_t _reg = std::make_shared<PlayerRegsiter>();
                _reg->set_account(m_account);
                _reg->set_account(m_password);
                NetManager::getInstance()->SendMessageBuff(_conn->getConnId(), _reg);
            }
            else {
                ApiPushError(GATE_SERVER_NOT_CONN);
            }
        }
        ImGui::End();
    });
    LogInfo << "[CliLoginSystem] ConnGateServer " << GetGateIP() << " " << GetGatePort() << FlushLog;
    NetManager::getInstance()->Connect(GetGateIP(), GetGatePort(), NodeType::GateServer);
    return true;
}
bool CliLoginSystem::Loop(const uint64_t interval_) {

    RenderManager::getInstance()->Register([this](SDL_Window* windows_, SDL_Renderer* render_) {
    });
    return true;
}
bool CliLoginSystem::Quit() {
    return true;
}
bool CliLoginSystem::Destroy() {
    return true;
}