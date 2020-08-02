#pragma once
#include <regex>
#include <vector>
#include <string>


std::vector<std::string> ApiStringSplit(const std::string& input_str_,const std::string& slipt_str_ = " ") {
    std::regex _ws_re(slipt_str_.c_str()); // whitespace
    return std::vector<std::string>(std::sregex_token_iterator(input_str_.begin(), input_str_.end(), _ws_re, -1),
        std::sregex_token_iterator());
}

std::string ApiStringReplace(const std::string& input_str_, const std::string& old_str_, const std::string& new_str_) {
    std::string _tmp_rst = input_str_;
    while (_tmp_rst.find(old_str_) != std::string::npos) {
        std::string _berfore_str(_tmp_rst.begin(), _tmp_rst.begin() + _tmp_rst.find(old_str_));
        _berfore_str += new_str_;
        _berfore_str += std::string(_tmp_rst.begin() + _tmp_rst.find(old_str_) + old_str_.size(), _tmp_rst.begin() + _tmp_rst.size());
        _tmp_rst = _berfore_str;
    }
    return _tmp_rst;
}