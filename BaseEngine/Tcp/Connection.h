#pragma once
#include "asio.hpp"
#include "../../Common/include/tool/Buffer.h"
#include "include/tool/UniqueNumberFactory.h"

const uint64_t g_recv_once_size = 1024;


/*
���շ���: Connection �������һ����ʱbuff�ṹ,���°������ʱ��,Լ��ͷ�����ϵ�ǰ���Ĺ̶���С,Ȼ����н���,���������ܵİ���С���м�¼,��
����һ��ר���������������Ľṹ,����ʹ���ڴ��?�򶨳�buff�ṹ,��ÿ�ν��յ�����ʱ,�������ж�,�Ƿ�������˵�ǰ��,���ѽ���,����а�����ȡ,ֱ��
ת�Ʊ���buff���߽��� memcpy ����, ����һ���¼�����λ,�����¼��ַ�.

���ͷ���: ����ڽ��ܷ���,�������Լ�,����Ҫ���͵���Ϣ��ֱ��ת�����¼���,ֱ�ӽ��з���,��ʹ�ö��̷߳���.

*/

struct Header{
    size_t m_buf_length;
    char   m_msg_id;
};



class CConnection {
public:
    bool Send() {
        if (m_snd_buff.readableBytes()) {
            //�������
            return true;
        }
        m_socket.async_write_some(asio::buffer(m_snd_buff.peek(), m_snd_buff.readableBytes()), [this](asio::error_code err_,
            std::size_t size_) {
            if (err_) {
                close();
                return;
            }

            Send();
        });
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

            Header* _head = (Header*)m_recv_buff.peek();
            const uint32_t _packet_length = _head->m_buf_length;

            //������??
            if (_packet_length >= m_recv_buff.readableBytes()) {
                string _buff_str = m_recv_buff.retrieveAsString(_packet_length);
                shared_ptr<CBuffer> _pack_buff = CMemoryPool<CBuffer>::getInstance()->alloc();
                _pack_buff->append(_buff_str.data(),_buff_str.size());
                shared_ptr<MsgPacket> _msg_packet(new MsgPacket);
                _msg_packet->m_buffer = _pack_buff;
                _msg_packet->m_type = MsgNet;
                _msg_packet->m_msg_id = UniqueNumberFactory::getInstance()->build();
                MessagePackPool::getInstance()->push_msg(_msg_packet);
            }
            Recv();
        });
        return true;
    }
    void close() {
        m_socket.shutdown(asio::ip::tcp::socket::shutdown_both);
    }
    asio::ip::tcp::socket GetSocket() { returbn m_socket; }
    CConnection(asio::io_service& service_):m_socket(service_)
    {
    
    }
    ~CConnection() {}
private:
    asio::ip::tcp::socket m_socket;
    char m_tmp_buff[g_recv_once_size];

    CBuffer  m_recv_buff;
    CBuffer  m_snd_buff;
};

class CConnectionMgr : public Singleton<CConnectionMgr> {
public:

    CConnection* CreateConnection(asio::io_service& service_) {
        CConnection* _tmp_conn = new CConnection(service_);
        m_conn_vec.push_back(_tmp_conn);
        return _tmp_conn;
    };

private:
    std::list<CConnection*> m_idle_conn_list;

    std::vector<CConnection*> m_conn_vec;
};