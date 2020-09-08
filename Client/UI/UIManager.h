#pragma once
#include "./UIStruct.h"
#include "EngineInclude.h"
#include <map>


struct SDL_Renderer;
class UIManager :public Singleton<UIManager> {
public:
    UIManager();
    ~UIManager();
    bool Init();
    bool Register(const UIScene scene_type_, UIRenderFunc func_);
    bool loop();

private:
    UIScene m_now_scene = UIScene::Login;
    UIScene m_default_scene = UIScene::Login;
private:
    std::map<UIScene,std::vector<UIRenderFunc>> m_scene_pool;
};