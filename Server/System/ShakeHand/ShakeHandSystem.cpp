#include "./ShakeHandSystem.h"
#include "../../../Common/include/tool/ProtobufDispatcher.h"
#include "../../../BaseEngine/MessageBus/MessageBus.h"
#include "../../../Common/include/proto/Shakehand.pb.h"


RegSystem(ShakeHandSystem);

using ShakeHandEvent_t = shared_ptr<ShakeHandEvent>;
bool ShakeHandSystem::EnvDefine() {
    EventRegister(ShakeHandEvent, [this](const uint32_t conn_,
        const ShakeHandEvent_t& message_,
        const int64_t& receive_time_) {
        this->ShakeHandPrint();
    });

    MessageBus::getInstance()->Attach([]() {
        std::cout << "MessageBus ShakeHand" << std::endl;
    }, "ShakeHand");
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

void  ShakeHandSystem::ShakeHandPrint(){
    std::cout << "ShakeHandPrint" << std::endl;

    MessageBus::getInstance()->SendReq<void>("ShakeHand");

}