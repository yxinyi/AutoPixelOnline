#pragma once
#include "asio.hpp"
#include "../../Common/include/tool/Buffer.h"
#include <mutex>
#include "include/tool/UniqueNumberFactory.h"
#include "include/tool/ObjectPool.h"

const uint64_t g_recv_once_size = 1024;


/*
接收方案: Connection 本身带有一个临时buff结构,当新包传入的时候,约定头部带上当前包的固定大小,然后进行接收,将即将接受的包大小进行记录,并
创建一个专门用来接受整包的结构,可以使用内存池?或定长buff结构,当每次接收到数据时,都进行判断,是否接受完了当前包,如已接受,则进行包的提取,直接
转移本地buff或者进行 memcpy 都可, 生成一个事件包单位,进行事件分发.

发送方案: 相对于接受方案,步骤就相对简单,将需要发送的消息报直接转换城事件包,直接进行发送,可使用多线程方案.

*/

struct Header{
    size_t m_buf_length;
};



class CConnection {
public:
    bool DoSend() {
        std::vector<shared_ptr<CBuffer>> _local_vec;
        {
            std::unique_lock<std::mutex> _lock(m_snd_buff_mutex);
            if (!m_snd_buff_list.size()) {
                m_in_sended = false;
                return false;
            }
            else {
                m_in_sended = true;
            }
            _local_vec.swap(m_snd_buff_list);
        }

        shared_ptr<CBuffer> _snd_buff = CObjectPool<CBuffer>::getInstance()->Get();
        for (auto&& _buff_it : _local_vec) {
            const uint32_t length = _buff_it->readableBytes();
            _buff_it->prependInt64(length);
            _snd_buff->append(_buff_it->peek(), _buff_it->readableBytes());
        }

        _local_vec.clear();
        m_socket.async_write_some(asio::buffer(_snd_buff->peek(), _snd_buff->readableBytes()), [this](asio::error_code err_,
            std::size_t size_) {
            if (err_) {
                close();
                return;
            }

            DoSend();
        });
        
        return true;
    }
    bool Send(shared_ptr<CBuffer> buff_) {
        std::unique_lock<std::mutex> _lock(m_snd_buff_mutex);
        m_snd_buff_list.push_back(buff_);
        return true;
    }

    bool Recv() {
        m_socket.async_read_some(asio::buffer(m_tmp_buff, g_recv_once_size), [this](asio::error_code err_,
            std::size_t size_t_) {
            if (err_) {
                close();
                return;
            }
            //接受到了信息,要先确定总长度,然后将临时包中的数据转移至总buff中,然后判断是否已经传输完毕,如已传输完毕,则清空CBuffer包,
            //生成事件包进行分发,注意,m_cur_buff中可能有沾包的情况发生,如果转移了所有的数据还是有剩余的情况,就是发生了沾包,则整理CBuffer数据继续进行接受
            //接收完毕后继续等待异步读取
            
            //拷贝数据
            m_recv_buff.append(m_tmp_buff, size_t_);
            //清空临时buff，准备下次数据接收
            memset(m_tmp_buff, 0, g_recv_once_size);

            const uint32_t _packet_length = m_recv_buff.readInt64();
            //有问题??
            if (_packet_length <= m_recv_buff.readableBytes()) {
                string _buff_str = m_recv_buff.retrieveAsString(_packet_length);
                std::cout << "recv: " << _buff_str << std::endl;
                //shared_ptr<CBuffer> _pack_buff = CMemoryPool<CBuffer>::getInstance()->alloc();
                //_pack_buff->append(_buff_str.data(),_buff_str.size());
                //shared_ptr<MsgPacket> _msg_packet(new MsgPacket);
                //_msg_packet->m_buffer = _pack_buff;
                //_msg_packet->m_type = MsgNet;
                //_msg_packet->m_msg_id = UniqueNumberFactory::getInstance()->build();
                //MessagePackPool::getInstance()->push_msg(_msg_packet);
            }
            Recv();
        });
        return true;
    }
    void close() {
        m_socket.shutdown(asio::ip::tcp::socket::shutdown_both);
        m_is_conn = false;
    }

    void setConnId(const uint32_t conn_id_) {
        m_conn_id = conn_id_;
    }
    uint32_t getConnId() {
        return m_conn_id;
    }
    bool inSended() {
        return m_in_sended;
    }
    asio::ip::tcp::socket& GetSocket() { return m_socket; }
    CConnection(asio::io_service& service_):m_socket(service_)
    {
        m_is_conn = true;
    }
    bool isConnection() {
        return m_is_conn && m_socket.is_open();
    }
    ~CConnection() {}
private:
    asio::ip::tcp::socket m_socket;
    char m_tmp_buff[g_recv_once_size];
    uint32_t m_conn_id = -1;
    bool m_is_conn = false;
    bool m_in_sended = false;
    CBuffer  m_recv_buff;

    std::mutex m_snd_buff_mutex;
    std::vector<shared_ptr<CBuffer>> m_snd_buff_list;
};

class CConnectionMgr : public Singleton<CConnectionMgr> {
public:

    CConnection* CreateConnection(asio::io_service& service_) {
        CConnection* _tmp_conn = new CConnection(service_);
        _tmp_conn->setConnId(m_conn_vec.size());
        m_conn_vec.push_back(_tmp_conn);
        
        return _tmp_conn;
    };

    CConnection* GetConnection(const uint32_t conn_id_) {
        if (conn_id_ >= m_conn_vec.size()) {
            return nullptr;
        }
        return m_conn_vec[conn_id_];
    }

private:
    std::list<CConnection*> m_idle_conn_list;

    std::vector<CConnection*> m_conn_vec;
};