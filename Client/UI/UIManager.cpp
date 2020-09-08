#include "./UIManager.h"

#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui_sdl.h"

UIManager::UIManager() {
}

bool UIManager::Init(SDL_Renderer* renderer_) {
    MessageBus::getInstance()->Attach([this]() {
        m_now_scene = UIScene::Game;
    }, "EnterGame");
    MessageBus::getInstance()->Attach([this]() {
        m_now_scene = UIScene::Login;
    }, "BackLogin");
    ImGui::CreateContext();
    ImGuiSDL::Initialize(renderer_, 1280, 720);
    return true;
}

UIManager::~UIManager() {

    ImGuiSDL::Deinitialize();
}


bool UIManager::Register(const UIScene scene_type_, UIRenderFunc func_) {
    m_scene_pool[scene_type_].push_back(func_);
    return true;
}
bool UIManager::loop() {

    ImGui::NewFrame();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);


    for (auto&& _func_it : m_scene_pool[m_now_scene]) {
        _func_it();
    }
    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());

    return true;
}
