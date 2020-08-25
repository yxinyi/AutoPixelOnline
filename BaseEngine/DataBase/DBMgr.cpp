#include "DBMgr.h"

using namespace std;


bool DBMgr::init(const std::string& ip_, const std::string& port_) {

    return true;
}


bool DBMgr::Upsert(const string& tbl_name_, const string& key, std::shared_ptr<google::protobuf::Message> msg_, DBCmd cmd_) {
    return true;
}
bool DBMgr::Query(const string& tbl_name_, const string& key, DBCmd cmd_) {
    return true;
}
bool DBMgr::Delete(const string& tbl_name_, const string& key, DBCmd cmd_) {
    return true;
}
