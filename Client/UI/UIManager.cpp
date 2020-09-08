#include "./UIManager.h"
#include "RenderManager.h"

UIManager::UIManager() {
}

bool UIManager::Init(){
    MessageBus::getInstance()->Attach([this]() {
        m_now_scene = UIScene::Game;
    }, "EnterGame");
    MessageBus::getInstance()->Attach([this]() {
        m_now_scene = UIScene::Login;
    }, "BackLogin");

    return true;
}

UIManager::~UIManager() {
}


bool UIManager::Register(const UIScene scene_type_, UIRenderFunc func_) {
    m_scene_pool[scene_type_].push_back(func_);
    return true;
}
bool UIManager::loop() {


    ImGui::ShowDemoWindow(nullptr);
    for (auto&& _func_it : m_scene_pool[m_now_scene]) {
        _func_it();
    }
    return true;
}
