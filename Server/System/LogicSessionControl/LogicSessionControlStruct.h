#pragma once
#include <vector>
#include <list>
#include <set>
#include <memory>
#include "proto/PlayerLogin.pb.h"
#include "proto/Session.pb.h"

using LogicEnterFromAccountServer_t = std::shared_ptr<LogicEnterFromAccountServer>;
using SessionDestory_t= std::shared_ptr<SessionDestory>;

#define ClientEnterEvent "ClientEnter" 
#define ClientOutEvent "ClientQuit" 