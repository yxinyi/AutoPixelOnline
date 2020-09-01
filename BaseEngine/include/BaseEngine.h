#pragma once
#include "../Tcp/PakcageList.h"
#include "tool/SingletonTemplate.h"
#include "../Common/include/tool/ProtobufDispatcher.h"
#include "../Common/include/tool/ProtobufCodec.h"
#include "../Common/include/tool/TimerTask.h"
#include "../BaseEngine/System/BaseSystem.h"
#include "../BaseEngine/System/ShakeHand/ShakeHandSystem.h"


void BaseSystemRegister() {
    RegSystem(ShakeHandSystem);

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
            const uint32_t _conn_id = _packet_it->m_conn_id;
            const uint32_t _name_length = _packet_it->m_buffer->readInt32();
            const string _msg_name_str = _packet_it->m_buffer->retrieveAsString(_name_length);
            const string _msg_str = _packet_it->m_buffer->retrieveAllAsString();
            MessagePtr _msg = MessagePtr(ProtobufCodec::getInstance()->decode(_msg_name_str, _msg_str));
            DispatcherEvent(_conn_id, _msg, receive_time_);
        }
        _vec.clear();
        TimerTaskMgr->Run();

        SystemManager::getInstance()->Loop(receive_time_);
    }
};

