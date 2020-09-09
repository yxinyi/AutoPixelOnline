#include "./CliErrorNotify.h"
#include "EngineInclude.h"
#include "Error/Error.h"
#include "proto/PlayerLogin.pb.h"
#include <math.h>

RegSystem(CliErrorNotify)


void ApiPushError(ErrorID err_, std::vector<std::string> param_) {
    std::shared_ptr<CliErrorNotify> _sys = SystemManager::getInstance()->GetSystem<CliErrorNotify>();
    _sys->PushErrPack(err_, param_);

}



void CliErrorNotify::PushErrPack(ErrorID err_, const std::vector<std::string>& param_) {
    CliErrorPack_t _err_msg = std::make_shared<CliErrorPack>();
    _err_msg->m_err = err_;
    for (auto&& _param_it : param_) {
        _err_msg->m_param.push_back(_param_it);
    }
    m_error_list.push_back(_err_msg);
}

bool CliErrorNotify::EnvDefine() {
    ProtobufDispatch::getInstance()->registerMessageCallback<ErrorMsg>([this](const uint32_t conn_,
        const std::shared_ptr<ErrorMsg>& message_,
        const int64_t& receive_time_) {
        std::vector<std::string>  _param(message_->param().begin(), message_->param().end());
        PushErrPack((ErrorID)message_->error_id(), _param);
    });
    return true;
}


bool CliErrorNotify::PreInit() {
    return true;
}
bool CliErrorNotify::Init() {

    UIManager::getInstance()->Register(UIScene::Login, [this]() {
        uint64_t _now_time = Time::getInstance()->Now();
        if (m_last_error_time + g_error_interval > _now_time) {
            if (m_laster_err) {
                ImGui::SetNextWindowPos(ImVec2(0, 0));
                ImGui::SetNextWindowSize(ImVec2(300, 50));
                if (!ImGui::Begin("ERrorDialog", nullptr, 0))
                {
                    ImGui::End();
                    return;
                }
                ImGui::Text(std::to_string((uint32_t)m_laster_err->m_err).c_str());
                ImGui::End();

            }
        }
        else {
            m_laster_err.reset();
            if (m_error_list.size()) {
                m_laster_err = m_error_list.front();
                m_error_list.pop_front();
                m_last_error_time = _now_time;
            }
        }
    });

    return true;
}
bool CliErrorNotify::Loop(const uint64_t interval_) {




    return true;
}
bool CliErrorNotify::Quit() {
    return true;
}
bool CliErrorNotify::Destroy() {
    return true;
}