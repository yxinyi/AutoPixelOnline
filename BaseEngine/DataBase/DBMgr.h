#pragma once
#include <string>
#include <map>
#include <memory>
#include <vector>
#include <functional>
#include "tool/SingletonTemplate.h"
#include "tool/LogInfo.h"
#include "google/protobuf/message.h"
using namespace std;

using DBCmd = std::function<void(std::vector<std::map<string, string>>)>;
const DBCmd _null_func = [](std::vector<std::map<string, string>>) {
    return;
};
class DBMgr : public Singleton<DBMgr> {
public:
    bool Upsert(const string& tbl_name_, const string& key, std::shared_ptr<google::protobuf::Message> msg_, DBCmd = _null_func);
    bool Query(const string& tbl_name_, const string& key, DBCmd = _null_func);
    bool Delete(const string& tbl_name_, const string& key, DBCmd = _null_func);


private:
    std::map<uint64_t, DBCmd> m_call_back;
};
//bool UpSert