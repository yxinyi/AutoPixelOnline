#include "./AccountSystem.h"
#include "./AccountStruct.h"
#include "./AccountSystem.h"
#include "EngineInclude.h"
#include "System/DataBase/DBSystem.h"
#include "Error/Error.h"
#include <math.h>

RegSystem(AccountSystem)

const std::string g_login_db_query = "AccountSystemAccountQuery:";

bool AccountSystem::EnvDefine() {
    ProtobufDispatch::getInstance()->registerMessageCallback<PlayerLogin>([this](const uint32_t conn_,
        const std::shared_ptr<PlayerLogin>& message_,
        const int64_t& receive_time_) {
        
        CDataBaseSystem_t _sys = SystemManager::getInstance()->GetSystem<CDataBaseSystem>();
        const std::string _query_account = message_->account();
        std::string _key = g_login_db_query + _query_account;

        _sys->Query(_key, [message_](DBOperatorErr err_, std::string val_) {
            if (err_ == DBOperatorErr::SUCCESS) {
                if (message_->password() == val_) {
                    
                }
                else {
                
                }
            }
        });

    });
    return true;
}


bool AccountSystem::PreInit() {
    return true;
}
bool AccountSystem::Init() {
    return true;
}
bool AccountSystem::Loop(const uint64_t interval_) {

    return true;
}
bool AccountSystem::Quit() {
    return true;
}
bool AccountSystem::Destroy() {
    return true;
}