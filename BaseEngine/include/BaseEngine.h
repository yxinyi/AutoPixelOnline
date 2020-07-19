#pragma once
#include "TcpConnonetManager.h"
#include "tool/SingletonTemplate.h"

class CBaseEngine:public Singleton<CBaseEngine> {
public:
    CBaseEngine();
    void run(const int64_t& receive_time_);
};
