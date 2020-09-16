#include "./ShakeHandSystem.h"
#include "EngineInclude.h"
#include "proto/Shakehand.pb.h"
#include "Session/SessionStruct.h"



const uint32_t g_interval = 6000;

using ShakeHandEvent_t = std::shared_ptr<ShakeHandEvent>;
bool ShakeHandSystem::EnvDefine() {
    EventRegister(ShakeHandEvent, [this](const SessionConn conn_,
        const ShakeHandEvent_t& message_,
        const int64_t& receive_time_) {
        /*
            不涉及Session
        */
        const uint32_t _conn_id = ApiGetConnID(conn_);
        this->ShakeHandPrint(_conn_id);
    });


    EventRegister(AuthenticationEvent, [this](const SessionConn conn_,
        const std::shared_ptr<AuthenticationEvent>& message_,
        const int64_t& receive_time_) {
        /*
            不涉及Session
        */
        const NodeType _type = (NodeType)message_->node_type();
        const uint32_t _conn_id = ApiGetConnID(conn_);
        if (CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(_conn_id)) {
            _conn->SetConnNodeType(_type);
            LogInfo << "[ShakeHandSystem]: AuthenticationEvent [" << _conn->getIPPortStr() << "] conn_id : [" << _conn->getConnId() << "] NodeType : [" << GetNodeTypeStr(_conn->GetConnNodeType()) << "] " << FlushLog;
        }
    });

    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        if (CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_)) {
            _conn->setIPStr(_conn->GetSocket().remote_endpoint().address().to_string(), _conn->GetSocket().remote_endpoint().port());
            LogInfo << "[ShakeHandSystem]: AcceptConnect [" << _conn->getIPPortStr() << "] conn_id : [" << _conn->getConnId() << "]" << FlushLog;
        }
    }, "AcceptConnect");

    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        m_conne_vec.insert(conn_id_);
        if (CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_)) {
            LogInfo << "[ShakeHandSystem]: OpenConnect [" << _conn->getIPPortStr() << "] conn_id : [" << _conn->getConnId() << "] NodeType : [" << GetNodeTypeStr(_conn->GetConnNodeType()) << "] " << FlushLog;
        }
        std::shared_ptr<AuthenticationEvent> _authen = std::make_shared<AuthenticationEvent>();
        _authen->set_node_type((uint32_t)getNodeType());
        NetManager::getInstance()->SendMessageBuff(conn_id_, _authen);
        //第一次连接确认下身份
    }, "OpenConnect");

    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        m_conne_vec.erase(conn_id_);
        m_remote.erase(conn_id_);
        if (CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_)) {
            LogInfo << "[ShakeHandSystem]: CloseConnect [" << _conn->getIPPortStr() << "] conn_id : [" << _conn->getConnId() << "] NodeType : [" << GetNodeTypeStr(_conn->GetConnNodeType()) << "] " << FlushLog;
        }
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
    std::shared_ptr<ShakeHandEvent> _event = std::make_shared<ShakeHandEvent>();
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
                std::cout << _conn->getIPPortStr() << " close " << std::endl;
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
        const uint64_t _now_time = NowTime->NowMillisecond();
        m_remote[conn_] = _now_time;
        LogInfo << "[ShakeHandSystem]: ShakeHand [" << _conn->getIPPortStr() << "] conn_id : [" << _conn->getConnId() << "] NodeType : [" << GetNodeTypeStr(_conn->GetConnNodeType()) << "] lastTime: [" << _now_time <<"]" << FlushLog;
    }

}