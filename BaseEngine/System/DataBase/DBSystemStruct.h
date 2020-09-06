#pragma once
#include <string>
#include <memory>
#include <functional>
#include "proto/DataBase.pb.h"
using namespace std;

enum class DBOperatorErr {
    SUCCESS,
    TIME_OUT,
    ERR,
};
using DBQueryCB = std::function<void(DBOperatorErr, string)>;
struct DBOpUnity {
    uint64_t m_oid = 0;
    uint64_t m_start_time = 0;
    DBOperatorType m_op = DBOperatorType::None;
    DBQueryCB m_cb = nullptr;
};

using DBOpUnity_t = shared_ptr<DBOpUnity>;

enum class DBOperatorType {
    None,
    Query,
    Update,
    Insert,
    Upsert,
    Delete,
};

using DataBaseReq_t = shared_ptr<DataBaseReq>;
using DataBaseAck_t = shared_ptr<DataBaseAck>;

