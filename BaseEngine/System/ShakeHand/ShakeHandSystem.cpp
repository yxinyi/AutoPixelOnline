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
    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        m_conne_vec.insert(conn_id_);
    }, "OpenConnect");

    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        m_conne_vec.erase(conn_id_);
        m_remote.erase(conn_id_);
    }, "CloseConnect");
    
    TimerTaskMgr->RegisterTask("ShakeHandEvent", 0, g_interval, -1, [this]() {
        this->ShakeHandForEveryOne();
    });
    TimerTaskMgr->RegisterTask("ShakeHandCheck", 0, g_interval, -1, [this]() {
        this->ShakeHandCheck();
    });
    //TimerTaskMgr->RegisterTask("ShakeHandInfo", 0, g_interval, -1, [this]() {
    //    LogInfo << "[ShakeHandSystem] ShakeHandInfo remote size: " << m_remote.size() << FlushLog;
    //    LogInfo << "[ShakeHandSystem] ShakeHandInfo connec size: " << m_conne_vec.size() << FlushLog;
    //});
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

//主动连接,主动发起握手
bool ShakeHandSystem::ShakeHandForEveryOne() {
    shared_ptr<ShakeHandEvent> _event = make_shared<ShakeHandEvent>();
    std::vector<uint32_t > _error_delete_conn;
    for (auto&& _conn_it : m_conne_vec) {
        NetManager::getInstance()->SendMessageBuff(_conn_it, _event);
    }

    return true;
}

//被动连接,被动检测远端是否掉线
bool ShakeHandSystem::ShakeHandCheck() {
    uint64_t _now_time = NowTime->NowMillisecond();
    std::vector<uint32_t > _out_time_conn;
    for(auto&& _cnn_it : m_remote) {
        if (_now_time - _cnn_it.second > g_interval * 2 ) {
            if (CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(_cnn_it.first)) {
                _out_time_conn.push_back(_cnn_it.first);
                MessageBus::getInstance()->SendReq< uint32_t>(_cnn_it.first, "ShakeHandOutTimeBefore");
                std::cout << _conn->getIPStr() << " close " << std::endl;
                CConnectionMgr::getInstance()->CloseConnection(_cnn_it.first);
            }
            else {
                _out_time_conn.push_back(_cnn_it.first);
            }
        }
    }

    for (auto&& _out_time_it : _out_time_conn) {
        MessageBus::getInstance()->SendReq< uint32_t>(_out_time_it, "ShakeHandOutTimeAfter");
    }


    return true;
}

void  ShakeHandSystem::ShakeHandPrint(const uint32_t conn_){
    
    if (CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_)) {
        m_remote[conn_] = NowTime->NowMillisecond();
        std::cout << "ShakeHandPrint: " << _conn->getIPStr() << std::endl;
        std::cout << "ShakeHandSize: " << m_remote.size() << std::endl;
    }

}