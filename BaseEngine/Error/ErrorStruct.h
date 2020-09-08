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
    ErrorMAX,
}; 


using ErrorMsg_t = std::shared_ptr<ErrorMsg>;

