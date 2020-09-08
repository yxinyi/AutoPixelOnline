#include "./DBSystem.h"
#include "proto/ServerLink.pb.h"

bool CDataBaseSystem::EnvDefine() {
    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
        if (!_conn || _conn->GetConnNodeType() != NodeType::DataBaseServer) {
            return;
        }
        m_dbserver_connected_ok = DBConnecState::Open;
        m_dbserver_connected_id = _conn->getConnId();

        LogError << "[CDataBaseSystem] DBServer open" << FlushLog;
        MessageBus::getInstance()->SendReq<uint32_t>(conn_id_, "DBServerOpen");
    }, "OpenConnect");
    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
        if (!_conn ||_conn->GetConnNodeType() != NodeType::DataBaseServer) {
            return;
        }
        m_dbserver_connected_ok = DBConnecState::Close;
        m_dbserver_connected_id = 0;
        LogError << "[CDataBaseSystem] DBServer close" << FlushLog;
        MessageBus::getInstance()->SendReq<uint32_t>(conn_id_, "DBServerClose");
    }, "CloseConnect");


    ProtobufDispatch::getInstance()->registerMessageCallback<DataBaseAck>( [this](const uint32_t conn_,
        const std::shared_ptr<DataBaseAck>& message_,
        const int64_t& receive_time_) {
        const uint64_t _msg_id = message_->msg_id();
        LogInfo << "[DataBaseAck]" << FlushLog;
        auto _op_find = m_op_pool.find(_msg_id);
        if (_op_find == m_op_pool.end()) {
            return;
        }
        _op_find->second->m_cb((DBOperatorErr)message_->query_state(), message_->result_str());
        m_op_pool.erase(_op_find->first);
    });
    


    ProtobufDispatch::getInstance()->registerMessageCallback<DataBaseNotify>([this](const uint32_t conn_,
        const std::shared_ptr<DataBaseNotify>& message_,
        const int64_t& receive_time_) {

        std::set<uint32_t> _cnn_set = CConnectionMgr::getInstance()->GetConnection(NodeType::DataBaseServer);
        if (_cnn_set.size()) {
            for (auto&& _it : _cnn_set) {
                CConnectionMgr::getInstance()->CloseConnection(_it);
            }
        }
        m_dbserver_ip = message_->db_ip();
        m_dbserver_port = message_->db_port();
        m_dbserver_connected_ok = DBConnecState::Close;
        
    });

    return true;
}

bool CDataBaseSystem::ConnecDBServer() {
    if (m_dbserver_connected_ok != DBConnecState::Close) {
        return false;
    }
    NetManager::getInstance()->Connect(m_dbserver_ip, m_dbserver_port, NodeType::DataBaseServer);
    m_dbserver_connected_ok = DBConnecState::Connecting;
    return true;
}

bool CDataBaseSystem::PreInit() {
    return true;
}
bool CDataBaseSystem::Init() {
    TimerTaskManager::getInstance()->RegisterTask("DBSystemCacheClear", m_query_time_out, m_query_time_out, -1, [this]() {
        for (auto _cache_it = m_proto_send_cache.cbegin(); _cache_it != m_proto_send_cache.cend(); _cache_it++) {
            const uint64_t _msg_id = (*_cache_it)->msg_id();
            if (m_op_pool.find(_msg_id) != m_op_pool.end()) {
                NetManager::getInstance()->SendMessageBuff(m_dbserver_connected_id, *_cache_it);
            }
        }
        m_proto_send_cache.clear();
    });

    //超时处理
    TimerTaskManager::getInstance()->RegisterTask("DBSystemOpTimeOut", m_query_time_out, m_query_time_out, -1, [this]() {
        const uint64_t _now_time = Time::getInstance()->NowMillisecond();
        for (auto _it = m_op_pool.cbegin(); _it != m_op_pool.cend();) {
            if (_it->second->m_start_time + m_query_time_out < _now_time) {
                _it->second->m_cb(DBOperatorErr::TIME_OUT, "");
                _it = m_op_pool.erase(_it);
            }
            else {
                _it++;
            }
        }
    });

    return true;
}
bool CDataBaseSystem::Loop(const uint64_t interval_) {
    //重连 DBServer 
    if (ConnecDBServer()) {
        LogError << "[CDataBaseSystem] DBServer connected" << FlushLog;

    }


    return true;
}
bool CDataBaseSystem::Quit() {
    return true;
}
bool CDataBaseSystem::Destroy() {
    return true;
}

bool CDataBaseSystem::op(DBOperatorType opt_, const string& key_, DBQueryCB cb_, const string& val_) {

    const uint64_t _st_time = Time::getInstance()->NowMillisecond();
    const uint64_t _oid = UniqueNumberFactory::getInstance()->build();
    DataBaseReq_t _msg = std::make_shared<DataBaseReq>();
    _msg->set_cmd_op((uint32_t)opt_);
    _msg->set_key(key_);
    _msg->set_val(val_);
    _msg->set_msg_id(_oid);
    if (m_dbserver_connected_ok == DBConnecState::Open) {
        NetManager::getInstance()->SendMessageBuff(m_dbserver_connected_id, _msg);
    }
    else {
        m_proto_send_cache.push_back(_msg);
    }
    DBOpUnity_t _unity = std::make_shared<DBOpUnity>();
    _unity->m_cb = cb_;
    _unity->m_op = opt_;
    _unity->m_oid = _oid;
    _unity->m_start_time = _st_time;

    m_op_pool[_unity->m_oid] = _unity;
    return true;
}

bool CDataBaseSystem::Query(const string& key_, DBQueryCB cb_) {
    return op(DBOperatorType::Query, key_, cb_);
}
bool CDataBaseSystem::Delete(const string& key_, DBQueryCB cb_) {
    return op(DBOperatorType::Delete, key_, cb_);
}
bool CDataBaseSystem::Update(const string& key_, const string& val_, DBQueryCB cb_) {
    return op(DBOperatorType::Update, key_, cb_, val_);
}
bool CDataBaseSystem::Insert(const string& key_, const string& val_, DBQueryCB cb_) {
    return op(DBOperatorType::Insert, key_, cb_, val_);
}
bool CDataBaseSystem::Upsert(const string& key_, const string& val_, DBQueryCB cb_) {
    return op(DBOperatorType::Upsert, key_, cb_, val_);
}
