#include "./BaseEngine.h"

const char* GetNodeTypeStr(NodeType node_) {
    static std::vector<std::string> _vec = {
    "Client",
    "GateServer",
    "LogicServer",
    "DataBaseServer",
    "AccountServer",
    "ListServer"};

    return _vec[(uint32_t)node_].c_str();
}



void BaseSystemRegister() {
    RegSystem(ShakeHandSystem);
    RegSystem(ListenSystem);
    
    if (getNodeType() != NodeType::GateServer &&
        getNodeType() != NodeType::DataBaseServer &&
        getNodeType() != NodeType::Client&&
        getNodeType() != NodeType::ListServer
        ) {
        RegSystem(CDataBaseSystem);
        RegSystem(ServerNodeRegisterSystem);
        RegSystem(SessionSystem);
    }
}

CBaseEngine::CBaseEngine() {
    BaseSystemRegister();
    Singleton<SystemManager>::getInstance()->EnvDefine();
    Singleton<SystemManager>::getInstance()->PreInit();
    Singleton<SystemManager>::getInstance()->Init();
}
CBaseEngine::~CBaseEngine() {
    Singleton<SystemManager>::getInstance()->Quit();
    Singleton<SystemManager>::getInstance()->Destroy();
}
void CBaseEngine::run(const int64_t receive_time_) {
    std::vector<std::shared_ptr<Package>> _vec;
    CPackageMgr::getInstance()->swap(_vec);
    for (auto&& _packet_it : _vec) {
        switch (_packet_it->m_msg_type)
        {
        case PackageType::OpenConnect: {
            MessageBus::getInstance()->SendReq<uint32_t>(_packet_it->m_conn_id, "OpenConnect");
            break;
        }
        case PackageType::CloseConnect: {
            MessageBus::getInstance()->SendReq<uint32_t>(_packet_it->m_conn_id, "CloseConnect");
            CConnectionMgr::getInstance()->DelelteConnection(_packet_it->m_conn_id);
            break;
        }

        case PackageType::AcceptConnect: {
            MessageBus::getInstance()->SendReq<uint32_t>(_packet_it->m_conn_id, "AcceptConnect");
            break;
        }
        case PackageType::Msg: {
            const uint32_t _conn_id = _packet_it->m_conn_id;
            const uint32_t _name_length = _packet_it->m_buffer->readInt32();
            const string _msg_name_str = _packet_it->m_buffer->retrieveAsString(_name_length);
            const string _msg_str = _packet_it->m_buffer->retrieveAllAsString();
            MessagePtr _msg(ProtobufCodec::getInstance()->decode(_msg_name_str, _msg_str));
            if (!_msg) {
                LogInfo << "[CBaseEngine] despatch err msg_str : " << _msg_name_str << FlushLog;
                MessageBus::getInstance()->SendReq<uint32_t, std::string, std::string>(_conn_id, _msg_name_str, _msg_str, "DespatchDecodeFailed");
                continue;
            }
            else {
                LogInfo << "[CBaseEngine] despatch msg_str : " << _msg_name_str << FlushLog;
            }
            DispatcherEvent(_conn_id, _msg, receive_time_);
            break;
        }
        default:
            break;
        }
    }
    _vec.clear();
    TimerTaskMgr->Run();

    SystemManager::getInstance()->Loop(receive_time_);
}
