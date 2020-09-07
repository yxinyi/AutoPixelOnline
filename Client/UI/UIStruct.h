#pragma once
#include "tool/SingletonTemplate.h"
#include <functional>


enum class UIScene {
    Login,
    Game,

};

using UIRenderFunc = std::function<void()>;
