#include "./DataBase.h"

RegSystem(CDBServerSystem)

bool CDBServerSystem::EnvDefine() {
    ProtobufDispatch::getInstance()->registerMessageCallback<DataBaseReq>([this](const uint32_t conn_,
        const std::shared_ptr<DataBaseReq>& message_,
        const int64_t& receive_time_) {
    });

    MessageBus::getInstance()->Attach([this](Session_t session_, MessagePtr base_msg_) {
        std::shared_ptr<DataBaseReq> _message = std::static_pointer_cast<DataBaseReq>(base_msg_);
        if (!_message) {
            RETURN_VOID;
        }
        LogInfo << "[DataBaseReq]" << FlushLog;
        const uint64_t _msg_id = _message->msg_id();
        DBOperatorType _op = (DBOperatorType)_message->cmd_op();
        const string& _key = _message->key();
        const string& _val = _message->val();

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
                LogError << "[DBOperatorType::Delete]" << _status.ToString() << FlushLog;
            }
            break;
        }
        case DBOperatorType::Delete: {
            leveldb::Status _status = m_db->Delete(leveldb::WriteOptions(), _key);
            if (_status.ok()) {
                _err = DBOperatorErr::SUCCESS;
            }
            else {
                LogError << "[DBOperatorType::Delete]" << _status.ToString() << FlushLog;
            }
            break;
        }
        case DBOperatorType::Update:
        case DBOperatorType::Insert:
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
        session_->SendMessageBuff(_ack);
    }, "DataBaseReq");

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