#include "./RenderManager.h"


uint32_t RenderManager::GetWinID() {
    return SDL_GetWindowID(m_window);
}

SDL_Renderer* RenderManager::GetRenderer() {
    return m_render;
}


bool RenderManager::WindowInit() {
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

    UIManager::getInstance()->Init(m_render);
    LogInfo << "WindowInit" << FlushLog;
    return true;
}
bool RenderManager::WindowUpdate(const int64_t& dt_) {
    return true;
}
bool RenderManager::Loop(const uint64_t interval_) {
    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("verdana.ttf", 18.0f, NULL, NULL);
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
        case SDL_KEYUP:
            break;
        case SDL_MOUSEWHEEL:
            wheel = m_event.wheel.y;
            break;
        }
    }


    static vector<int> _input(SDL_NUM_SCANCODES);

    const Uint8* _key_state = SDL_GetKeyboardState(NULL);
    for (int _input_idx = 0; _input_idx < SDL_NUM_SCANCODES; _input_idx++) {
        if (_key_state[_input_idx]) {
            char _key = SDL_GetKeyFromScancode((SDL_Scancode)_input_idx);
            printf("<%c> is pressed.\n", _key);
            _input[_input_idx]++;
            if (_input[_input_idx] == 1) {
                io.AddInputCharacterUTF16(_key);
            }
        }
        else {
            _input[_input_idx] = 0;
        }
        io.KeysDown[_input_idx] = _key_state[_input_idx];
    }

    int mouseX, mouseY;
    const int buttons = SDL_GetMouseState(&mouseX, &mouseY);
    io.DeltaTime = 1.0f / 60.0f;
    io.MousePos = ImVec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
    io.MouseDown[0] = buttons & SDL_BUTTON(SDL_BUTTON_LEFT);
    io.MouseDown[1] = buttons & SDL_BUTTON(SDL_BUTTON_RIGHT);
    io.MouseWheel = static_cast<float>(wheel);


    SDL_SetRenderDrawColor(m_render, 0, 0, 0, 255);
    SDL_RenderClear(m_render);
    for (auto& _func_it : m_render_funcs) {
        _func_it(m_window, m_render);
    }
    UIManager::getInstance()->loop();

    SDL_RenderPresent(m_render);
    m_render_funcs.clear();


    return true;
}
void RenderManager::Register(std::function<void(SDL_Window*, SDL_Renderer*)> func_) {
    m_render_funcs.push_back(func_);

}
