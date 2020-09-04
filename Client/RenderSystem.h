#pragma once
#include "tool/SingletonTemplate.h"
#include "SDL2/SDL_render.h"
#include "SDL2/SDL.h"
#include "SDL2/SDL_events.h"
#include "System/BaseSystem.h"
#include <functional>
#include <vector>
#include <string>
#include "tool/LogInfo.h"

class RenderSystem :public Singleton<RenderSystem> {
public:
    bool WindowInit() {
        if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS) != 0)
        {
            std::string message = "Failed to init SDL2! Error: " + std::string(SDL_GetError());
            return false;
        }

        m_window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, SDL_WINDOW_SHOWN | SDL_WINDOW_INPUT_FOCUS | SDL_WINDOW_MOUSE_FOCUS | SDL_WINDOW_ALLOW_HIGHDPI);

        if (!m_window)
        {
            std::string _message = "Window failed to be created! SDL: ";
            _message += SDL_GetError();
            LogError << _message << FlushLog;
            return false;
        }

        m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_SOFTWARE);

        if (!m_render)
        {
            std::string _message = "Renderer failed to be created! SDL: ";
            _message += SDL_GetError();
            LogError << _message << FlushLog;
            return false;
        }

        LogInfo << "WindowInit" << FlushLog;

        return true;
    }
    bool WindowUpdate(const int64_t& dt_) {
        return true;
    }
    bool Loop(const uint64_t interval_) {
        SDL_SetRenderDrawColor(m_render, 0, 0, 0, 255);
        SDL_RenderClear(m_render);
        SDL_Renderer* _render = m_render;
        SDL_Window* _windiow = m_window;
        if (!_render || !_windiow) {
            LogError << "error " << FlushLog;
            return;
        }
        for (auto& _func_it : m_render_funcs) {
            _func_it(_windiow, _render);
        }
        SDL_RenderPresent(m_render);
        m_render_funcs.clear();
    }
    void Register(std::function<void(SDL_Window*, SDL_Renderer*)> func_) {
        m_render_funcs.push_back(func_);
    }
private:
    std::vector<std::function<void(SDL_Window*, SDL_Renderer*)>> m_render_funcs;
    SDL_Renderer* m_render;
    SDL_Window* m_window;
    SDL_Event m_event;
};
