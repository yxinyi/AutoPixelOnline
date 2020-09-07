#include "./UIManager.h"
#include "../RenderManager.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui_sdl.h"

UIManager::UIManager() {
    MessageBus::getInstance()->Attach([this]() {
        m_now_scene = UIScene::Game;
    }, "EnterGame");
    MessageBus::getInstance()->Attach([this]() {
        m_now_scene = UIScene::Login;
    }, "BackLogin");

    SDL_Renderer* _renderer = RenderManager::getInstance()->GetRenderer();

    ImGui::CreateContext();
    ImGuiSDL::Initialize(_renderer, 800, 600);
}

UIManager::~UIManager() {

    ImGuiSDL::Deinitialize();
}


bool UIManager::Register(const UIScene scene_type_, UIRenderFunc func_) {
    m_scene_pool[scene_type_].push_back(func_);
    return true;
}
bool UIManager::loop() {

    ImGuiIO& io = ImGui::GetIO();

    for (auto&& _func_it : m_scene_pool[m_now_scene]) {
        _func_it();
    }

    ImGui::NewFrame();

    bool show_demo_window = true;
    ImGui::ShowDemoWindow(&show_demo_window);


    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());

    return true;
}
