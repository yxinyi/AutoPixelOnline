#include "./CliLoginSystem.h"
#include "./CliLoginStruct.h"
#include "ErrorNotify/CliErrorNotify.h"
#include "EngineInclude.h"
#include "Error/Error.h"
#include <math.h>
#include "RenderManager.h"

RegSystem(CliLoginSystem)

bool CliLoginSystem::EnvDefine() {

    ProtobufDispatch::getInstance()->registerMessageCallback<PlayerEnterAck>([this](const SessionConn conn_,
        const std::shared_ptr<PlayerEnterAck>& message_,
        const int64_t& receive_time_) {
        MessageBus::getInstance()->SendReq(EnterGameEvent);
    });


    ProtobufDispatch::getInstance()->registerMessageCallback<ErrorMsg>([this](const uint64_t conn_,
        const std::shared_ptr<ErrorMsg>& message_,
        const int64_t& receive_time_) {
        if (message_->error_id() != (uint32_t)ErrorID::ACCOUNT_PASSWORD_PASS) {
            return;
        }
        m_login = true;
    });

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
        if (!m_login) {
            ImGui::InputText("Account", &m_account);
            ImGui::InputText("PassWord", &m_password);
            if (ImGui::Button("LogIn")) {
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
            if (ImGui::Button("Register")) {
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
        }
        else {
            std::string _text = m_account + "wellcome ! ";
            ImGui::Text(_text.c_str());
            if (ImGui::Button("Enter")) {
                if (CConnection_t _conn = CConnectionMgr::getInstance()->GetOnlyOneConnection(NodeType::GateServer)) {
                    std::shared_ptr<PlayerEnter> _player_enter = std::make_shared<PlayerEnter>();
                    NetManager::getInstance()->SendMessageBuff(_conn->getConnId(), _player_enter);
                }
            }
        }

        ImGui::End();
    });

    //TimerTaskManager::getInstance()->RegisterTask("BenchTest", 0, 1000, -1, [this]() {
    //    if (m_password.size()) {
    //        const uint32_t _loop_times = atoi(m_password.c_str());
    //        std::shared_ptr<BenchTest> _tst = std::make_shared<BenchTest>();
    //        CConnection_t _conn = CConnectionMgr::getInstance()->GetOnlyOneConnection(NodeType::GateServer);
    //        for (int _idx = 0; _idx < _loop_times; _idx++) {
    //            static uint32_t _num = 0;;
    //            _tst->set_num(_num++);
    //            NetManager::getInstance()->SendMessageBuff(_conn->getConnId(), _tst);
    //        }
    //    }
    //});

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