#include "./CreatureSystem.h"
#include "tool/ProtobufDispatcher.h"
#include "MessageBus/MessageBus.h"
#include "tool/ObjectPool.h"
#include "tool/LogInfo.h"
#include "Tcp/NetManager.h"
#include "Error/Error.h"
#include <memory>
#include "imgui.h"
#include "UI/UIManager.h"

RegSystem(CreatureSystem)

bool CreatureSystem::EnvDefine() {

    return true;
}

bool CreatureSystem::PreInit() {
    return true;
}
bool CreatureSystem::Init() {
    return true;
}
bool CreatureSystem::Loop(const uint64_t interval_) {



    return true;
}
bool CreatureSystem::Quit() {
    return true;
}
bool CreatureSystem::Destroy() {
    return true;
}
