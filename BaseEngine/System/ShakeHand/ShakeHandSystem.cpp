#include "./ShakeHandSystem.h"
#include "../../../Common/include/tool/ProtobufDispatcher.h"
#include "../../../BaseEngine/MessageBus/MessageBus.h"
#include "../../../BaseEngine/Tcp/Connection.h"
#include "../../../BaseEngine/Tcp/NetManager.h"
#include "../../../Common/include/proto/Shakehand.pb.h"
#include "../../../Common/include/tool/TimerTask.h"
#include "../../../Common/include/tool/Time.h"



RegSystem(ShakeHandSystem)

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
    TimerTaskMgr->RegisterTask("ShakeHandEvent", 0, 6000, -1, [this]() {
        this->ShakeHandForEveryOne();
    });
    return true;
}
bool ShakeHandSystem::PreInit() {
    return true;
}
extern std::vector<ConnectTargetConfig> getConnectConfig();
bool ShakeHandSystem::Init() {
    std::vector<ConnectTargetConfig> _conn_cfg = getConnectConfig();
    for (auto&& _cfg_it : _conn_cfg) {
        CConnection_t _conn = NetManager::getInstance()->Connect(_cfg_it.m_ip, _cfg_it.m_port);
        m_conne_vec.insert(_conn->getConnId());
    }
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


bool ShakeHandSystem::ShakeHandForEveryOne() {
    shared_ptr<ShakeHandEvent> _event = make_shared<ShakeHandEvent>();
    std::vector<uint32_t > _error_delete_conn;
    for (auto&& _conn_it : m_conne_vec) {
        //if (!NetManager::getInstance()->SendMessageBuff(_conn_it, _event)) {
        //    _error_delete_conn.push_back(_conn_it);
        //}
    }
    for (auto&& _delete_it : _error_delete_conn) {
        m_conne_vec.erase(_delete_it);
    }
    return true;
}

void  ShakeHandSystem::ShakeHandPrint(){
    std::cout << "ShakeHandPrint" << std::endl;

    MessageBus::getInstance()->SendReq<void>("ShakeHand");

}