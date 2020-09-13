#include "./RenderManager.h"
#include <d3d11.h>

uint32_t RenderManager::GetWinID() {
    return SDL_GetWindowID(m_window);
}

SDL_Renderer* RenderManager::GetRenderer() {
    return m_render;
}

bool RenderManager::WindowInit() {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0)
    {
        std::string message = "Failed to init SDL2! Error: " + std::string(SDL_GetError());
        return false;
    }

    SDL_WindowFlags _window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    m_window = SDL_CreateWindow("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, _window_flags);
    if (!m_window)
    {
        std::string _message = "Window failed to be created! SDL: ";
        _message += SDL_GetError();
        LogError << _message << FlushLog;
        return false;
    }

    m_render = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED);

    if (!m_render)
    {
        std::string _message = "Renderer failed to be created! SDL: ";
        _message += SDL_GetError();
        LogError << _message << FlushLog;
        return false;
    }

    UIManager::getInstance()->Init();

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGuiSDL::Initialize(m_render, 1280, 720);
    SDL_Texture* texture = SDL_CreateTexture(m_render, SDL_PIXELFORMAT_RGBA32, SDL_TEXTUREACCESS_TARGET, 100, 100);
    {
        SDL_SetRenderTarget(m_render, texture);
        SDL_SetRenderDrawColor(m_render, 255, 0, 255, 255);
        SDL_RenderClear(m_render);
        SDL_SetRenderTarget(m_render, nullptr);
    }
    ImGui_ImplSDL2_InitForD3D(m_window);

    LogInfo << "WindowInit" << FlushLog;
    return true;
}

RenderManager::~RenderManager() {

    ImGuiSDL::Deinitialize();

    SDL_DestroyRenderer(m_render);
    SDL_DestroyWindow(m_window);

    ImGui::DestroyContext();
}

bool RenderManager::WindowUpdate(const int64_t& dt_) {
    return true;
}


static ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);
bool RenderManager::Loop(const uint64_t interval_) {
    int wheel = 0;
    while (SDL_PollEvent(&m_event))
    {
        ImGui_ImplSDL2_ProcessEvent(&m_event);

    }
    SDL_SetRenderDrawColor(m_render, 114, 144, 154, 255);
    SDL_RenderClear(m_render);
    ImGui_ImplSDL2_NewFrame(m_window);
    ImGui::NewFrame();

    for (auto& _func_it : m_render_funcs) {
        _func_it(m_window, m_render);
    }

    UIManager::getInstance()->loop();

    ImGui::Render();
    ImGuiSDL::Render(ImGui::GetDrawData());

    SDL_RenderPresent(m_render);
    m_render_funcs.clear();


    return true;
}
void RenderManager::Register(std::function<void(SDL_Window*, SDL_Renderer*)> func_) {
    m_render_funcs.push_back(func_);

}
