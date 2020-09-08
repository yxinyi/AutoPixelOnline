#pragma once
#include "./ErrorStruct.h"

ErrorMsg_t ApiBuildErrorMsg(const ErrorID err_, std::vector<string> params_ = {});