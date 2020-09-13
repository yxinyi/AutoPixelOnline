#pragma once
#include "proto/PlayerLogin.pb.h"
#include <memory>


using PlayerLogin_t = std::shared_ptr<PlayerLogin>;
using PlayerRegsiter_t = std::shared_ptr<PlayerRegsiter>;

#define EnterGameEvent "EnterGame"
#define BackLoginEvent "BackLogin"