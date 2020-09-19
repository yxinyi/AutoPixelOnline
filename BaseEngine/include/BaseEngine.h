#pragma once
#include "../Tcp/PakcageList.h"
#include "System/BaseSystem.h"
#include "System/ShakeHand/ShakeHandSystem.h"
#include "System/Session/SessionSystem.h"
#include "System/Listen/ListenSystem.h"
#include "System/Gate/GateSystem.h"
#include "System/DataBase/DBSystem.h"
#include "System/ServerRegister/ServerNodeRegisterSystem.h"
#include "EngineInclude.h"

void BaseSystemRegister();
class CBaseEngine :public Singleton<CBaseEngine> {
public:
    CBaseEngine();
    ~CBaseEngine();
    void run(const int64_t receive_time_);
};

