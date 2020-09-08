#pragma once
#include "tool/SingletonTemplate.h"
#include "System/BaseSystem.h"
#include <functional>
#include <vector>
#include <string>
#include "tool/LogInfo.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "imgui.h"
#include "imgui_impl_dx9.h"
#include "imgui_impl_win32.h"
#include "imgui_sdl.h"
#include "UI/UIManager.h"

class RenderManager :public Singleton<RenderManager> {
public:

    uint32_t GetWinID();
    SDL_Renderer* GetRenderer();
    ~RenderManager();
    bool WindowInit();
    bool WindowUpdate(const int64_t& dt_);
    bool Loop(const uint64_t interval_);
    void Register(std::function<void(SDL_Window*, SDL_Renderer*)> func_);
private:
    std::vector<std::function<void(SDL_Window*, SDL_Renderer*)>> m_render_funcs;
    SDL_Renderer* m_render;
    SDL_Window* m_window;
    SDL_Event m_event;
    WNDCLASSEX m_wc;
};
