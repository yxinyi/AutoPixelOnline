#pragma once
#include <string>
#include <memory>
#include <functional>
#include "proto/DataBase.pb.h"

enum class DBOperatorErr {
    SUCCESS,
    TIME_OUT,
    ERR,
};
using DBQueryCB = std::function<void(DBOperatorErr, std::string)>;

enum class DBOperatorType {
    None,
    Query,
    Update,
    Insert,
    Upsert,
    Delete,
};
struct DBOpUnity {
    uint64_t m_oid = 0;
    uint64_t m_start_time = 0;
    DBOperatorType m_op = DBOperatorType::None;
    DBQueryCB m_cb = nullptr;
};

using DBOpUnity_t = std::shared_ptr<DBOpUnity>;

using DataBaseReq_t = std::shared_ptr<DataBaseReq>;
using DataBaseAck_t = std::shared_ptr<DataBaseAck>;

