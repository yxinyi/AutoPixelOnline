#include "./MapRender.h"
#include "MessageBus/MessageBus.h"
#include "Creature/Creature.h"
#include "tool/ObjectPool.h"
#include "tool/UniqueNumberFactory.h"
#include "Error/Error.h"
#include "Tcp/NetManager.h"
#include <math.h>

RegSystem(MapRenderSystem)

bool MapRenderSystem::EnvDefine() {
    return true;
}
bool MapRenderSystem::PreInit() {
    return true;
}
bool MapRenderSystem::Init() {
    return true;
}
bool MapRenderSystem::Loop(const uint64_t interval_) {
    return true;
}
bool MapRenderSystem::Quit() {
    return true;
}
bool MapRenderSystem::Destroy() {
    return true;
}