#include "./ShakeHandSystem.h"
#include "../../../Common/include/tool/ProtobufDispatcher.h"
#include "../../../BaseEngine/MessageBus/MessageBus.h"
#include "../../../BaseEngine/Tcp/Connection.h"
#include "../../../BaseEngine/Tcp/NetManager.h"
#include "../../../Common/include/proto/Shakehand.pb.h"
#include "../../../Common/include/tool/TimerTask.h"
#include "../../../Common/include/tool/Time.h"





const uint32_t g_interval = 6000;

using ShakeHandEvent_t = shared_ptr<ShakeHandEvent>;
bool ShakeHandSystem::EnvDefine() {
    EventRegister(ShakeHandEvent, [this](const uint32_t conn_,
        const ShakeHandEvent_t& message_,
        const int64_t& receive_time_) {
        this->ShakeHandPrint(conn_);
    });

    MessageBus::getInstance()->Attach([]() {
        std::cout << "MessageBus ShakeHand" << std::endl;
    }, "ShakeHand");
    TimerTaskMgr->RegisterTask("ShakeHandEvent", 0, g_interval, -1, [this]() {
        this->ShakeHandForEveryOne();
    });
    TimerTaskMgr->RegisterTask("ShakeHandCheck", 0, g_interval, -1, [this]() {
        this->ShakeHandCheck();
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
        CConnection_t _conn = NetManager::getInstance()->Connect(_cfg_it.m_ip, _cfg_it.m_port, _cfg_it.m_nick_name);
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
        if (!NetManager::getInstance()->SendMessageBuff(_conn_it, _event)) {
            _error_delete_conn.push_back(_conn_it);
        }
    }
    

    return true;
}

bool ShakeHandSystem::ShakeHandCheck() {
    uint64_t _now_time = NowTime->NowMillisecond();
    std::vector<uint32_t > _out_time_conn;
    for(auto&& _cnn_it : m_remote) {
        if (_now_time - _cnn_it.second > g_interval * 2 ) {
            if (CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(_cnn_it.first)) {
                _out_time_conn.push_back(_cnn_it.first);
                MessageBus::getInstance()->SendReq< uint32_t>(_cnn_it.first, "ShakeHandOutTimeBefore");
                std::cout << _conn->getIPStr() << " close " << std::endl;
                CConnectionMgr::getInstance()->DelelteConnection(_cnn_it.first);
            }
            else {
                _out_time_conn.push_back(_cnn_it.first);
            }
        }
    }

    for (auto&& _out_time_it : _out_time_conn) {
        m_remote.erase(_out_time_it);
        MessageBus::getInstance()->SendReq< uint32_t>(_out_time_it, "ShakeHandOutTimeAfter");
    }


    return true;
}

void  ShakeHandSystem::ShakeHandPrint(const uint32_t conn_){

    if (CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_)) {
        m_remote[conn_] = NowTime->NowMillisecond();
        std::cout << "ShakeHandPrint: " << _conn->getIPStr() << std::endl;
        std::cout << "ShakeHandSize: " << m_remote.size() << std::endl;
        //MessageBus::getInstance()->SendReq<void>("ShakeHand");
    
    }

}