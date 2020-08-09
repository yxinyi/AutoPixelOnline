#include "DBMgr.h"

using namespace std;

DBMgr::DBMgr() {

}
bool DBMgr::init(const std::string& ip_, const std::string& port_) {

    std::shared_ptr<CTcpClient> _DB_client(new CTcpClient);
    _DB_client->init(ip_, std::atol(port_.c_str()));
    RegTcp(_DB_client);
    m_db_client = _DB_client;
    return true;
}


bool DBMgr::Upsert(const string& tbl_name_, const string& key, std::shared_ptr<google::protobuf::Message> msg_, DBCmd cmd_) {
    std::shared_ptr<SChannel> _channel = m_db_client->getChannel();// send();
    std::shared_ptr< SMsgPacket> _msg_packet(new SMsgPacket);
    _msg_packet->m_channel = _channel;
    _msg_packet->m_msg = msg_;
    m_db_client->send(_msg_packet);
    return true;
}
bool DBMgr::Query(const string& tbl_name_, const string& key, DBCmd = _null_func);
bool DBMgr::Delete(const string& tbl_name_, const string& key, DBCmd = _null_func);
