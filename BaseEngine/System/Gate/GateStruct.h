#pragma once
#include <memory>
#include "proto/ListServer.pb.h"

using RetrieveServerConfigReq_t = std::shared_ptr<RetrieveServerConfigReq>;
using RetrieveServerConfigAck_t = std::shared_ptr<RetrieveServerConfigAck>;