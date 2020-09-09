#include "./CliLoginSystem.h"
#include "./CliLoginStruct.h"
#include "ErrorNotify/CliErrorNotify.h"
#include "EngineInclude.h"
#include "Error/Error.h"
#include <math.h>

RegSystem(CliLoginSystem)

bool CliLoginSystem::EnvDefine() {

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

            PlayerLogin_t _login = std::make_shared<PlayerLogin>();
            if (CConnection_t _conn = CConnectionMgr::getInstance()->GetOnlyOneConnection(NodeType::GateServer)) {
                NetManager::getInstance()->SendMessageBuff(_conn->getConnId(), _login);
            }
            else {
              ApiPushError(GATE_SERVER_NOT_CONN);
            }
        }
        if (ImGui::Button("Register")){
            PlayerRegsiter_t _login = std::make_shared<PlayerRegsiter>();
            if (CConnection_t _conn = CConnectionMgr::getInstance()->GetOnlyOneConnection(NodeType::GateServer)) {
                NetManager::getInstance()->SendMessageBuff(_conn->getConnId(), _login);
            }
            else {
                ApiPushError(GATE_SERVER_NOT_CONN);
            }
        }
        ImGui::End();
    });
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