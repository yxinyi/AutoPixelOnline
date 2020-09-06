#include "./DBSystem.h"
using namespace std;

bool CDataBaseSystem::EnvDefine() {
    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
        if (_conn->GetNickName() != "DBServer") {
            return;
        }
        m_dbserver_connected_ok = DBConnecState::open;
        m_dbserver_connected_id = _conn->getConnId();
    }, "OpenConnect");
    MessageBus::getInstance()->Attach([this](uint32_t conn_id_) {
        CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_id_);
        if (_conn->GetNickName() != "DBServer") {
            return;
        }
        m_dbserver_connected_ok = DBConnecState::close;
        m_dbserver_connected_id = 0;
    }, "CloseConnect");


    ProtobufDispatch::getInstance()->registerMessageCallback<DataBaseAck>( [this](const uint32_t conn_,
        const shared_ptr<DataBaseAck>& message_,
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
    
    return true;
}
bool CDataBaseSystem::PreInit() {
    NetManager::getInstance()->Connect(m_dbserver_ip, m_dbserver_port, "DBServer");
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
    if (DBConnecState::close == m_dbserver_connected_ok) {
        NetManager::getInstance()->Connect(m_dbserver_ip, m_dbserver_port, "DBServer");
        m_dbserver_connected_ok = DBConnecState::connecting;
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
    DataBaseReq_t _msg = make_shared<DataBaseReq>();
    _msg->set_cmd_op((uint32_t)opt_);
    _msg->set_key(key_);
    _msg->set_val(val_);
    _msg->set_msg_id(_oid);
    if (m_dbserver_connected_ok == DBConnecState::open) {
        NetManager::getInstance()->SendMessageBuff(m_dbserver_connected_id, _msg);
    }
    else {
        m_proto_send_cache.push_back(_msg);
    }
    DBOpUnity_t _unity = make_shared<DBOpUnity>();
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
