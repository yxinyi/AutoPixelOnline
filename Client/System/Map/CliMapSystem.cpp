#include "./CliMapSystem.h"
#include "MessageBus/MessageBus.h"
#include "Creature/Creature.h"
#include "tool/ObjectPool.h"
#include "tool/UniqueNumberFactory.h"
#include "Error/Error.h"
#include "Tcp/NetManager.h"
#include <math.h>

RegSystem(CliMapSystem)

bool CliMapSystem::EnvDefine() {
    return true;
}
bool CliMapSystem::PreInit() {
    return true;
}
bool CliMapSystem::Init() {
    return true;
}
bool CliMapSystem::Loop(const uint64_t interval_) {
    return true;
}
bool CliMapSystem::Quit() {
    return true;
}
bool CliMapSystem::Destroy() {
    return true;
}