#pragma once
#include "asio.hpp"
#include "../../Common/include/tool/Buffer.h"
#include <set>
#include <map>
#include <mutex>
#include "include/tool/UniqueNumberFactory.h"
#include "include/tool/ObjectPool.h"
#include "PakcageList.h"
#include "ServerTypeStruct.h"

const uint64_t g_recv_once_size = 1024;
static uint32_t s_length_statc = sizeof int64_t;


/*
���շ���: Connection �������һ����ʱbuff�ṹ,���°������ʱ��,Լ��ͷ�����ϵ�ǰ���Ĺ̶���С,Ȼ����н���,���������ܵİ���С���м�¼,��
����һ��ר���������������Ľṹ,����ʹ���ڴ��?�򶨳�buff�ṹ,��ÿ�ν��յ�����ʱ,�������ж�,�Ƿ�������˵�ǰ��,���ѽ���,����а�����ȡ,ֱ��
ת�Ʊ���buff���߽��� memcpy ����, ����һ���¼�����λ,�����¼��ַ�.

���ͷ���: ����ڽ��ܷ���,�������Լ�,����Ҫ���͵���Ϣ��ֱ��ת�����¼���,ֱ�ӽ��з���,��ʹ�ö��̷߳���.

*/


class CConnection {
public:
    bool DoSend() {
        std::vector<std::shared_ptr<CBuffer>> _local_vec;
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

        std::shared_ptr<CBuffer> _snd_buff = CObjectPool<CBuffer>::getInstance()->Get();
        for (auto&& _buff_it : _local_vec) {
            const uint32_t length = (uint32_t)_buff_it->readableBytes();
            _buff_it->prependInt64(length);
            _snd_buff->append(_buff_it->peek(), _buff_it->readableBytes());
        }

        _local_vec.clear();
        m_socket.async_write_some(asio::buffer(_snd_buff->peek(), _snd_buff->readableBytes()), [this](asio::error_code err_,
            std::size_t size_) {
            if (err_) {
                printf("async_write_some %d \n", err_.value());
                close();
                return;
            }

            DoSend();
        });

        return true;
    }
    bool Send(std::shared_ptr<CBuffer> buff_) {
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

            uint64_t _packet_length = m_recv_buff.peekInt64();
            uint64_t _now_cur_length = m_recv_buff.readableBytes();


            //����8���ֽڵĳ��ȱ��,����ĳ���
            while (_packet_length + s_length_statc <= _now_cur_length) {
                m_recv_buff.retrieveInt64();
                std::string _buff_str = m_recv_buff.retrieveAsString(_packet_length);
                std::shared_ptr<CBuffer> _pack_buff = CObjectPool<CBuffer>::getInstance()->Get();
                _pack_buff->append(_buff_str.data(), _buff_str.size());
                std::shared_ptr<Package> _pack = CObjectPool<Package>::getInstance()->Get(PackageType::Msg, m_conn_id, _pack_buff);
                _pack->init(PackageType::Msg, m_conn_id, _pack_buff);
                //������Ϣ��
                CPackageMgr::getInstance()->push(_pack);

                if (m_recv_buff.readableBytes() >= s_length_statc) {
                    _packet_length = m_recv_buff.peekInt64();
                }
                else {
                    break;
                }
                _now_cur_length = m_recv_buff.readableBytes();
            }
            Recv();
        });
        return true;
    }
    void close() {
        if (m_is_conn) {
            std::error_code ignored_ec;
            m_socket.cancel();
            m_socket.shutdown(asio::ip::tcp::socket::shutdown_both, ignored_ec);
            m_socket.close(ignored_ec);
        }
        m_is_conn = false;
        
        std::shared_ptr<Package> _pack = CObjectPool<Package>::getInstance()->Get(PackageType::CloseConnect, m_conn_id);
        //������Ϣ��
        CPackageMgr::getInstance()->push(_pack);
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
    CConnection(asio::io_service& service_) :m_socket(service_)
    {
    }

    void SetConnNodeType(const NodeType& node_type_) {
        m_node_type = node_type_;
    }
    NodeType GetConnNodeType() {
        return m_node_type;
    }
    bool isConnection() {
        return m_is_conn;//&& m_socket.is_open();
    }

    void ConnectedOK() {
        m_is_conn = true;
        std::shared_ptr<Package> _pack = CObjectPool<Package>::getInstance()->Get(PackageType::OpenConnect, m_conn_id);
        //������Ϣ��
        CPackageMgr::getInstance()->push(_pack);
    }

    void AcceptOK() {
        m_is_conn = true;
        std::shared_ptr<Package> _pack = CObjectPool<Package>::getInstance()->Get(PackageType::AcceptConnect, m_conn_id);
        //������Ϣ��
        CPackageMgr::getInstance()->push(_pack);
    }
    ~CConnection() {}
    std::string getIPStr() {
        return remote_ip ;
    }
    std::string getPortStr() {
        return std::to_string(remote_port);
    }
    std::string getIPPortStr() {
        return remote_ip + " : " + std::to_string(remote_port);
    }

    void setIPStr(const std::string& remote_ip_,const uint16_t remote_port_) {
        remote_ip = remote_ip_;
        remote_port = remote_port_;
    }
private:
    NodeType m_node_type;
    asio::ip::tcp::socket m_socket;
    char m_tmp_buff[g_recv_once_size] = { 0 };
    uint32_t m_conn_id = -1;
    bool m_is_conn = false;
    bool m_in_sended = false;
    CBuffer  m_recv_buff;
    std::string remote_ip = "";
    uint16_t remote_port = 0;
    std::mutex m_snd_buff_mutex;
    std::vector<std::shared_ptr<CBuffer>> m_snd_buff_list;
};
using CConnection_t = std::shared_ptr<CConnection>;
using CConnection_wt = std::weak_ptr<CConnection>;

class CConnectionMgr : public Singleton<CConnectionMgr> {
public:

    CConnection_t CreateConnection(asio::io_service& service_, const NodeType& node_type_ = NodeType::Client) {
        CConnection_t _tmp_conn = std::make_shared<CConnection>(service_);
        const uint32_t _conn_id = m_conn_inc_id++;
        _tmp_conn->setConnId(_conn_id);

        m_conn_pool[_conn_id] = _tmp_conn;
        _tmp_conn->SetConnNodeType(node_type_);
        m_nodetype_to_conn[node_type_].insert(_conn_id);

        return _tmp_conn;
    };

    CConnection_t GetConnection(const uint32_t conn_id_) {
        if (m_conn_pool.find(conn_id_) == m_conn_pool.end()) {
            return nullptr;
        }
        return m_conn_pool[conn_id_];
    }
    std::set<uint32_t> GetConnection(const NodeType& node_type_) {
        auto _conn_find = m_nodetype_to_conn.find(node_type_);
        if (_conn_find == m_nodetype_to_conn.end()) {
            return {};
        }
        return _conn_find->second;
    }


    CConnection_t GetOnlyOneConnection(const NodeType& node_type_) {
        auto _conn_find = m_nodetype_to_conn.find(node_type_);
        if (_conn_find == m_nodetype_to_conn.end()) {
            return nullptr;
        }

        if (_conn_find->second.size() != 1) {
            return nullptr;
        }

        return m_conn_pool[*_conn_find->second.begin()];
    }

    bool CloseConnection(const uint32_t conn_id_) {
        auto _conn_find = m_conn_pool.find(conn_id_);
        if (_conn_find == m_conn_pool.end()) {
            return false;
        }
        _conn_find->second->close();
        return true;
    }
    bool DelelteConnection(const uint32_t conn_id_) {
        auto _conn_find = m_conn_pool.find(conn_id_);
        if (_conn_find == m_conn_pool.end()) {
            return false;
        }
        m_nodetype_to_conn[_conn_find->second->GetConnNodeType()].erase(conn_id_);
        m_conn_pool.erase(conn_id_);
        return true;
    }
private:
    std::map<uint32_t, CConnection_t> m_conn_pool;
    std::map<NodeType, std::set<uint32_t>> m_nodetype_to_conn;
    uint32_t m_conn_inc_id = 0;
};


//Api

std::string ApiGetConnectIPPortStr(const uint32_t conn_);
std::string ApiGetConnectIPStr(const uint32_t conn_);

