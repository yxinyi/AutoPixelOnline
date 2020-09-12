#include "./AccountSystem.h"
#include "./AccountStruct.h"
#include "EngineInclude.h"
#include "System/DataBase/DBSystem.h"
#include "Error/Error.h"
#include <math.h>

RegSystem(AccountSystem)

const std::string g_login_db_query = "AccountSystemAccountQuery:";
const std::string g_account_key_db_query = "AccountSystemAccountKeyQuery:";

bool AccountSystem::EnvDefine() {


    ProtobufDispatch::getInstance()->registerMessageCallback<BenchTest>([this](const uint64_t session_,
        const std::shared_ptr<BenchTest>& message_,
        const int64_t& receive_time_) {
        LogInfo << message_->num() << FlushLog;

    });



    ProtobufDispatch::getInstance()->registerMessageCallback<PlayerRegsiter>([this](const uint64_t session_,
        const PlayerRegsiter_t& message_,
        const int64_t& receive_time_) {

        const std::string _register_account = message_->account();
        const std::string _register_password = message_->password();

        CDataBaseSystem_t _sys = SystemManager::getInstance()->GetSystem<CDataBaseSystem>();
        std::string _key = g_login_db_query + _register_account;

        _sys->Query(_key, [_register_account, _register_password, session_](DBOperatorErr err_, std::string val_) {
            if (err_ == DBOperatorErr::SUCCESS) {
                //成功标示账号已经被注册返回消息去
                NetManager::getInstance()->SendMessageBuff(session_, ApiBuildErrorMsg(ACCOUNT_PASSWORD_REGISTER_EXISTS));
                return;
            }
            //不存在,则进行注册,
            CDataBaseSystem_t _sys = SystemManager::getInstance()->GetSystem<CDataBaseSystem>();
            std::string _key = g_login_db_query + _register_account;
            _sys->Insert(_key, _register_password, [session_, _register_account](DBOperatorErr err_, std::string val_) {
                if (err_ == DBOperatorErr::ERR) {
                    //已经被注册
                    NetManager::getInstance()->SendMessageBuff(session_, ApiBuildErrorMsg(ACCOUNT_PASSWORD_REGISTER_EXISTS));
                    return;
                }
                //生成 account_key 唯一
                CDataBaseSystem_t _sys = SystemManager::getInstance()->GetSystem<CDataBaseSystem>();
                std::string _key = g_account_key_db_query + _register_account;
                uint64 _account_key = UniqueNumberFactory::getInstance()->build();
                _sys->Insert(_key, std::to_string(_account_key), [session_](DBOperatorErr err_, std::string val_) {
                    if (err_ == DBOperatorErr::ERR) {
                        //已经被注册
                        NetManager::getInstance()->SendMessageBuff(session_, ApiBuildErrorMsg(ACCOUNT_PASSWORD_REGISTER_EXISTS));
                        return;
                    }
                    NetManager::getInstance()->SendMessageBuff(session_, ApiBuildErrorMsg(ACCOUNT_PASSWORD_REGISTER_OK));
                });
            });
        });


    });

    ProtobufDispatch::getInstance()->registerMessageCallback<PlayerLogin>([this](const uint64_t session_,
        const std::shared_ptr<PlayerLogin>& message_,
        const int64_t& receive_time_) {

        CDataBaseSystem_t _sys = SystemManager::getInstance()->GetSystem<CDataBaseSystem>();
        const std::string _query_account = message_->account();
        std::string _key = g_login_db_query + _query_account;

        _sys->Query(_key, [_query_account, message_, session_](DBOperatorErr err_, std::string val_) {
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


            if (_rst == PlayerLoginAck_CheckResult_Refuse) {
                //如果没通过发个提示到客户端
                NetManager::getInstance()->SendMessageBuff(session_, ApiBuildErrorMsg(ACCOUNT_PASSWORD_ERR));
            }
            else {
                //通过检查,通知Logic开始登陆
                NetManager::getInstance()->SendMessageBuff(session_, ApiBuildErrorMsg(ACCOUNT_PASSWORD_PASS));
                CDataBaseSystem_t _sys = SystemManager::getInstance()->GetSystem<CDataBaseSystem>();

                std::string _account_key_query_key = g_account_key_db_query + _query_account;

                _sys->Query(_account_key_query_key, [_rst, message_, session_](DBOperatorErr err_, std::string val_) {
                    PlayerLoginAck_CheckResult _rst = PlayerLoginAck_CheckResult_Refuse;
                    if (err_ == DBOperatorErr::SUCCESS) {
                        _rst = PlayerLoginAck_CheckResult_Pass;
                    }

                    //发一个消息到 gate 表示结果,
                    std::shared_ptr<PlayerLoginAck> _ack = std::make_shared<PlayerLoginAck>();
                    _ack->set_session_key(ApiGetSession(session_));
                    _ack->set_result(_rst);
                    NetManager::getInstance()->SendMessageBuff(ApiGetConnID(session_), _ack);
                    //发消息到逻辑服务器,让那边准备好基本信息,
                    std::shared_ptr<LogicEnterFromAccountServer> _logic_ack = std::make_shared<LogicEnterFromAccountServer>();
                    _logic_ack->set_session_key(ApiGetSession(session_));
                    _logic_ack->set_account_key(atoll(val_.c_str()));
                    NetManager::getInstance()->SendMessageBuff(ApiGetConnID(session_), _logic_ack);

                });

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
