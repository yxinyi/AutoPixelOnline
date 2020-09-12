#pragma once
#include "include/proto/ErrorNotify.pb.h"
#include <string>
#include <vector>
#include <memory>

using namespace google::protobuf;

enum ErrorID
{
    LOG_ERR = 1,
    LOG_POS_NOT_EXISTS = 2,
    SERVER_IS_CLOSE = 3,
    GATE_SERVER_NOT_CONN = 4,
    ACCOUNT_PASSWORD_ERR = 5,
    ACCOUNT_PASSWORD_PASS = 6,
    ACCOUNT_PASSWORD_REGISTER_EXISTS = 7, //账号已经存在
    ACCOUNT_PASSWORD_REGISTER_OK = 8,   //账号注册成功
    ErrorMAX,
}; 

struct CliErrorPack {
    ErrorID m_err;
    std::vector<std::string> m_param;
};
using CliErrorPack_t = std::shared_ptr<CliErrorPack>;
using ErrorMsg_t = std::shared_ptr<ErrorMsg>;

