#pragma once
#include "include/proto/ErrorNotify.pb.h"
#include <string>
#include <vector>
#include <memory>

using namespace std;
using namespace google::protobuf;

enum ErrorID
{
    LOG_ERR = 1,
    ErrorMAX,
}; 


using ErrorMsg_t = shared_ptr<ErrorMsg>;

