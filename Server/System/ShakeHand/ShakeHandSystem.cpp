#include "./ShakeHandSystem.h"
#include "../../../Common/include/tool/ProtobufDispatcher.h"
#include "../../../Common/include/proto/Shakehand.pb.h"


using ShakeHandEvent_t = shared_ptr<ShakeHandEvent>;
bool ShakeHandSystem::EnvDefine() {
    EventRegister(ShakeHandEvent, [](const uint32_t conn_,
        const ShakeHandEvent_t& message_,
        const int64_t& receive_time_) {
        std::cout << "ShakeHandEvent_t" << std::endl;
    });
    return true;
}
bool ShakeHandSystem::PreInit() {
    return true;
}
bool ShakeHandSystem::Init() {
    return true;
}
bool ShakeHandSystem::Loop(const uint64_t interval_) {
    return true;
}
bool ShakeHandSystem::Quit() {
    return true;
}
bool ShakeHandSystem::Destroy() {
    return true;
}