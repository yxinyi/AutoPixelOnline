#include "./CliLoginSystem.h"
#include "EngineInclude.h"
#include "Error/Error.h"
#include "proto/PlayerLogin.pb.h"
#include <math.h>

RegSystem(CliLoginSystem)

bool CliLoginSystem::EnvDefine() {

    return true;
}


bool CliLoginSystem::PreInit() {
    return true;
}
bool CliLoginSystem::Init() {
    UIManager::getInstance()->Register(UIScene::Login, []() {
        ImGui::SetNextWindowPos(ImVec2(440, 210));
        ImGui::SetNextWindowSize(ImVec2(400, 300));

        if (!ImGui::Begin("LogIn", nullptr, 0))
        {
            ImGui::End();
            return;
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