#include "./AccountSystem.h"
#include "./AccountStruct.h"
#include "EngineInclude.h"
#include "System/DataBase/DBSystem.h"
#include "Error/Error.h"
#include <math.h>

RegSystem(AccountSystem)

const std::string g_login_db_query = "AccountSystemAccountQuery:";

bool AccountSystem::EnvDefine() {


    ProtobufDispatch::getInstance()->registerMessageCallback<BenchTest>([this](const uint64_t session_,
        const std::shared_ptr<BenchTest>& message_,
        const int64_t& receive_time_) {
        LogInfo << message_->num() << FlushLog;

    });
    

    ProtobufDispatch::getInstance()->registerMessageCallback<PlayerLogin>([this](const uint64_t session_,
        const std::shared_ptr<PlayerLogin>& message_,
        const int64_t& receive_time_) {

        CDataBaseSystem_t _sys = SystemManager::getInstance()->GetSystem<CDataBaseSystem>();
        const std::string _query_account = message_->account();
        std::string _key = g_login_db_query + _query_account;

        _sys->Query(_key, [message_, session_](DBOperatorErr err_, std::string val_) {
            PlayerLoginAck_CheckResult _rst = PlayerLoginAck_CheckResult_Refuse;
            do {
                if (err_ != DBOperatorErr::SUCCESS) {
                    break;
                }
                if (message_->password() != val_) {
                    break;
                }
                _rst = PlayerLoginAck_CheckResult_Pass;
            } while (false);

            std::shared_ptr<PlayerLoginAck> _ack = std::make_shared<PlayerLoginAck>();
            //发一个消息到 gate 表示结果,
            _ack->set_session_key(ApiGetSession(session_));
            _ack->set_result(PlayerLoginAck_CheckResult_Pass);
            NetManager::getInstance()->SendMessageBuff(ApiGetConnID(session_), _ack);
            if (_rst == PlayerLoginAck_CheckResult_Refuse) {
                //如果没通过发个提示到客户端
                //session_->SendMessageBuff(ApiBuildErrorMsg(ACCOUNT_PASSWORD_ERR));
                NetManager::getInstance()->SendMessageBuff(session_, ApiBuildErrorMsg(ACCOUNT_PASSWORD_ERR));
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
