#include "./DataBase.h"

RegSystem(CDataBaseSystem)

bool CDataBaseSystem::EnvDefine() {
    EventRegister(DataBaseReq, [this](const uint32_t conn_,
        const shared_ptr<DataBaseReq>& message_,
        const int64_t& receive_time_) {
        const uint64_t _msg_id = message_->msg_id();
        DBOperatorType _op = (DBOperatorType)message_->cmd_op();
        const string& _key = message_->key();
        const string& _val = message_->val();
        
        DataBaseAck_t _ack = make_shared<DataBaseAck>();
        _ack->set_msg_id(_msg_id);

        switch (_op)
        {
        case DBOperatorType::Query: {
            std::string _rst;
            leveldb::Status _status = m_db->Get(leveldb::ReadOptions(), _key, &_rst);
            if (_status.ok()) {
                _ack->set_query_state((uint32_t)DBOperatorErr::SUCCESS);
                _ack->set_result_str(_rst);
            }
            else {
                _ack->set_query_state((uint32_t)DBOperatorErr::ERR);
                LogError << "[DBOperatorType::Delete]" << _status.ToString() << FlushLog;
            }
            break;
        }
        case DBOperatorType::Delete: {
            leveldb::Status _status = m_db->Delete(leveldb::WriteOptions(), _key);
            if (_status.ok()) {
                _ack->set_query_state((uint32_t)DBOperatorErr::SUCCESS);
            }
            else {
                _ack->set_query_state((uint32_t)DBOperatorErr::ERR);
                LogError << "[DBOperatorType::Delete]" << _status.ToString() << FlushLog;
            }
            break;
        }
        case DBOperatorType::Update:
        case DBOperatorType::Insert:
        case DBOperatorType::Upsert: {
            leveldb::Status _status = m_db->Put(leveldb::WriteOptions(), _key, _val);
            if (_status.ok()) {
                _ack->set_query_state((uint32_t)DBOperatorErr::SUCCESS);
            }
            else {
                _ack->set_query_state((uint32_t)DBOperatorErr::ERR);
                LogError << "[DBOperatorType]"  << "op: " << (uint32_t)_op  <<" "<< _status.ToString() << FlushLog;
            }
            break;
        }

        default:
            break;
        }

        NetManager::getInstance()->SendMessageBuff(conn_,_ack);
    });
    return true;
}
bool CDataBaseSystem::PreInit() {
    m_options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(m_options, "./GameData", &m_db);
    std::cout << "PreInit: " << status.ToString() << std::endl;
    assert(status.ok());
    return true;
}
bool CDataBaseSystem::Init() {
    return true;
}
bool CDataBaseSystem::Loop(const uint64_t interval_) {
    std::string _val;
    m_db->Get(leveldb::ReadOptions(), "123", &_val);
    std::cout << "val: " << _val << std::endl;
    return true;
}
bool CDataBaseSystem::Quit() {
    return true;
}
bool CDataBaseSystem::Destroy() {
    delete m_db;
    return true;
}