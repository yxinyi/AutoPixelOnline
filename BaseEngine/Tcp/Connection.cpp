#include "./Connection.h"


std::string ApiGetConnectIPPortStr(const uint32_t conn_) {
    CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_);
    if (!_conn) {
        return "";
    }
    return _conn->getIPPortStr();
}
std::string ApiGetConnectIPStr(const uint32_t conn_) {
    CConnection_t _conn = CConnectionMgr::getInstance()->GetConnection(conn_);
    if (!_conn) {
        return "";
    }
    return _conn->getIPStr();
}
