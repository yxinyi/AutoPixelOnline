#pragma once
#include "../Tcp/PakcageList.h"
#include "../BaseEngine/System/BaseSystem.h"
#include "../BaseEngine/System/ShakeHand/ShakeHandSystem.h"
#include "../BaseEngine/System/DataBase/DBSystem.h"
#include "../BaseEngine/System/ServerRegister/ServerNodeRegisterSystem.h"
#include "../BaseEngine/EngineInclude.h"



void BaseSystemRegister() {
    RegSystem(ShakeHandSystem);
    if (getNodeType() != NodeType::GateServer && getNodeType() != NodeType::DataBaseServer) {
        RegSystem(CDataBaseSystem);
        RegSystem(ServerNodeRegisterSystem);
    }
}

class CBaseEngine :public Singleton<CBaseEngine> {
public:
    CBaseEngine() {
        BaseSystemRegister();
        Singleton<SystemManager>::getInstance()->EnvDefine();
        Singleton<SystemManager>::getInstance()->PreInit();
        Singleton<SystemManager>::getInstance()->Init();
    }
    ~CBaseEngine() {
        Singleton<SystemManager>::getInstance()->Quit();
        Singleton<SystemManager>::getInstance()->Destroy();
    }
    void run(const int64_t receive_time_) {
        std::vector<shared_ptr<Package>> _vec;
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
                MessagePtr _msg = MessagePtr(ProtobufCodec::getInstance()->decode(_msg_name_str, _msg_str));
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
};

