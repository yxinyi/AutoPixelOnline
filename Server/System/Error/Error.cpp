#pragma once
#include "./Error.h"

ErrorMsg_t ApiBuildErrorMsg(const ErrorID err_, vector<string> params_) {
    ErrorMsg_t _msg = std::make_shared<ErrorMsg>();
    _msg->set_error_id(err_);
    for (auto&& _str_it :params_) {
        _msg->add_param(_str_it);
    }
    return _msg;
}