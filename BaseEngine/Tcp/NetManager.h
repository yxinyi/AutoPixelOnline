#include "../../Common/include/tool/SingletonTemplate.h"
#include "Connection.h"
#include "asio.h"


class NetManager : public Singleton<NetManager> {
public:
    bool Start();
    bool stop();
    bool SendMessageData(const uint32_t conn_id_, const char* data_, const uint32_t length_);
    bool SendMessageBuff(const uint32_t conn_id_, const CBuffer* buff_);
    bool waitConnect();
    
    CConnection* Connect(const string& ip_, const uint16_t port_);

    asio::ip::tcp::acceptor* m_acceptor;
    asio::io_service m_service;




};