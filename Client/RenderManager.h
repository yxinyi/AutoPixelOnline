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

class RenderManager :public Singleton<RenderManager> {
public:

    uint32_t GetWinID() {
        return SDL_GetWindowID(m_window);
    }

    SDL_Renderer* GetRenderer() {
        return m_render;
    }


    bool WindowInit() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
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
        ImGui::CreateContext();
        ImGuiSDL::Initialize(m_render, 1280, 720);

        return true;
    }
    bool WindowUpdate(const int64_t& dt_) {
        return true;
    }
    bool Loop(const uint64_t interval_) {
        
        ImGuiIO& io = ImGui::GetIO();

        int wheel = 0;
        while (SDL_PollEvent(&m_event) != 0)
        {
            switch (m_event.type)
            {
            case SDL_QUIT:
                break;

            case SDL_KEYDOWN:
                if (m_event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED)
                {
                    io.DisplaySize.x = static_cast<float>(m_event.window.data1);
                    io.DisplaySize.y = static_cast<float>(m_event.window.data2);
                }
                break;
            case SDL_MOUSEWHEEL:
                wheel = m_event.wheel.y;
                break;
            }
        }



        int mouseX, mouseY;
        const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
        io.DeltaTime = 1.0f / 60.0f;
        io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
        io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
        io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
        io.MouseWheel = static_cast<float>(wheel);


        ImGui::NewFrame();

        ImGui::ShowDemoWindow();

        SDL_SetRenderDrawColor(m_render, 0, 0, 0, 255);
        SDL_RenderClear(m_render);

        for (auto& _func_it : m_render_funcs) {
            _func_it(m_window, m_render);
        }
        ImGui::Render();
        ImGuiSDL::Render(ImGui::GetDrawData());

        SDL_RenderPresent(m_render);
        m_render_funcs.clear();


        return true;
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
