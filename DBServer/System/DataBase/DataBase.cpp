#include "./DataBase.h"

RegSystem(CDBServerSystem)

bool CDBServerSystem::EnvDefine() {
    ProtobufDispatch::getInstance()->registerMessageCallback<DataBaseReq>([this](const uint64_t conn_,
        const std::shared_ptr<DataBaseReq>& message_,
        const int64_t& receive_time_) {
        LogInfo << "[DataBaseReq]" << FlushLog;
    
        const uint64_t _msg_id = message_->msg_id();
        DBOperatorType _op = (DBOperatorType)message_->cmd_op();
        const string& _key = message_->key();
        const string& _val = message_->val();
    
        DataBaseAck_t _ack = std::make_shared<DataBaseAck>();
        _ack->set_msg_id(_msg_id);
        DBOperatorErr _err = DBOperatorErr::ERR;
        switch (_op)
        {
        case DBOperatorType::Query: {
            std::string _rst;
            leveldb::Status _status = m_db->Get(leveldb::ReadOptions(), _key, &_rst);
            if (_status.ok()) {
                _err = DBOperatorErr::SUCCESS;
                _ack->set_result_str(_rst);
            }
            else {
                LogError << "[DBOperatorType::Query] " << _status.ToString() << FlushLog;
            }
            break;
        }
        case DBOperatorType::Delete: {
            leveldb::Status _status = m_db->Delete(leveldb::WriteOptions(), _key);
            if (_status.ok()) {
                _err = DBOperatorErr::SUCCESS;
            }
            else {
                LogError << "[DBOperatorType::Delete] " << _status.ToString() << FlushLog;
            }
            break;
        }
        case DBOperatorType::Insert: {
            std::string _rst;
            if (!m_db->Get(leveldb::ReadOptions(), _key, &_rst).ok()) {
                leveldb::Status _status = m_db->Put(leveldb::WriteOptions(), _key, _val);
                if (_status.ok()) {
                    _err = DBOperatorErr::SUCCESS;
                }
                else {
                    LogError << "[DBOperatorType:Insert] put err" << "op: " << (uint32_t)_op << " " << _key << FlushLog;

                }
            }
            else {
                LogError << "[DBOperatorType:Insert]" << "op: " << (uint32_t)_op << " " << _key << " exists " << FlushLog;
            }
            break;
        }
        case DBOperatorType::Update:
        case DBOperatorType::Upsert: {
            leveldb::Status _status = m_db->Put(leveldb::WriteOptions(), _key, _val);
            if (_status.ok()) {
                _err = DBOperatorErr::SUCCESS;
            }
            else {
                LogError << "[DBOperatorType]" << "op: " << (uint32_t)_op << " " << _status.ToString() << FlushLog;
            }
            break;
        }
    
        default:
            break;
        }
    
        _ack->set_query_state((uint32_t)_err);
        NetManager::getInstance()->SendMessageBuff(conn_, _ack);
    });




    return true;
}
bool CDBServerSystem::PreInit() {
    m_options.create_if_missing = true;
    leveldb::Status status = leveldb::DB::Open(m_options, "./GameData", &m_db);
    std::cout << "PreInit: " << status.ToString() << std::endl;
    assert(status.ok());
    return true;
}
bool CDBServerSystem::Init() {
    return true;
}
bool CDBServerSystem::Loop(const uint64_t interval_) {
    return true;
}
bool CDBServerSystem::Quit() {
    return true;
}
bool CDBServerSystem::Destroy() {
    delete m_db;
    return true;
}