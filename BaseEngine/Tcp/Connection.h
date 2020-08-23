#pragma once
#include "asio.hpp"
#include "../../Common/include/tool/Buffer.h"
#include <mutex>
#include "include/tool/UniqueNumberFactory.h"
#include "include/tool/ObjectPool.h"

const uint64_t g_recv_once_size = 1024;


/*
���շ���: Connection �������һ����ʱbuff�ṹ,���°������ʱ��,Լ��ͷ�����ϵ�ǰ���Ĺ̶���С,Ȼ����н���,���������ܵİ���С���м�¼,��
����һ��ר���������������Ľṹ,����ʹ���ڴ��?�򶨳�buff�ṹ,��ÿ�ν��յ�����ʱ,�������ж�,�Ƿ�������˵�ǰ��,���ѽ���,����а�����ȡ,ֱ��
ת�Ʊ���buff���߽��� memcpy ����, ����һ���¼�����λ,�����¼��ַ�.

���ͷ���: ����ڽ��ܷ���,�������Լ�,����Ҫ���͵���Ϣ��ֱ��ת�����¼���,ֱ�ӽ��з���,��ʹ�ö��̷߳���.

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
            //���ܵ�����Ϣ,Ҫ��ȷ���ܳ���,Ȼ����ʱ���е�����ת������buff��,Ȼ���ж��Ƿ��Ѿ��������,���Ѵ������,�����CBuffer��,
            //�����¼������зַ�,ע��,m_cur_buff�п�����մ�����������,���ת�������е����ݻ�����ʣ������,���Ƿ�����մ��,������CBuffer���ݼ������н���
            //������Ϻ�����ȴ��첽��ȡ
            
            //��������
            m_recv_buff.append(m_tmp_buff, size_t_);
            //�����ʱbuff��׼���´����ݽ���
            memset(m_tmp_buff, 0, g_recv_once_size);

            const uint32_t _packet_length = m_recv_buff.readInt64();
            //������??
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