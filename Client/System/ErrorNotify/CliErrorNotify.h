#pragma once
#include "System/BaseSystem.h"
#include "Attribute/Attribute.h"
#include "tool/AStar.h"
#include <vector>
#include <list>
#include "proto/Map.pb.h"
#include "../Client/RenderManager.h"
#include "UI/UIManager.h"
#include <set>


class CliErrorNotify :public BaseSystem {
public:
    CliErrorNotify() :BaseSystem(typeid(CliErrorNotify).name()) {}
    ~CliErrorNotify() {}
    bool EnvDefine();
    bool PreInit();
    bool Init();
    bool Loop(const uint64_t interval_);
    bool Quit();
    bool Destroy();
public:
    void PushErrPack(ErrorID, const std::vector<std::string>&);
private:
    std::list<CliErrorPack_t> m_error_list;
    const uint32_t g_error_interval = 1;
    uint64_t m_last_error_time = 0; 
    CliErrorPack_t m_laster_err = nullptr;
};

void ApiPushError(ErrorID, std::vector<std::string> param_ = {});