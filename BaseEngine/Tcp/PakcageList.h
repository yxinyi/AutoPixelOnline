#pragma once
#include "asio.hpp"
#include "../../Common/include/tool/Buffer.h"
#include <mutex>
#include "include/tool/UniqueNumberFactory.h"
#include "include/tool/ObjectPool.h"


/*
    Connection解决沾包问题,并交由本层,进行进一步解析,并进行消息分发

    如果是二进制消息,然后解析出事件主题为 string 类型, 先解析长度,再获取 主题后推入队列

    如果是protobuf 消息, 则进行消息解码,然后推入队列,
    需要线程安全
*/

enum class PackageType {
    OpenConnect,
    CloseConnect,
    AcceptConnect,
    Msg,
};

struct Package {
    PackageType m_msg_type;
    uint32_t m_conn_id;
    std::shared_ptr<CBuffer> m_buffer;
    void init(const PackageType type_,const uint32_t conn_id_, std::shared_ptr<CBuffer> buf_ = nullptr) {
        m_conn_id = conn_id_;
        m_buffer = buf_;
        m_msg_type = type_;
    };
    void reset() { m_conn_id = 0; m_buffer.reset(); };
};

// thread safe
class CPackageMgr : public Singleton<CPackageMgr> {
public:
    void push(std::shared_ptr<Package> pack_) {
        std::unique_lock<std::mutex> _lock(m_vec_mutex);
        m_package_vec.push_back(pack_);
    }
    void swap(std::vector<std::shared_ptr<Package>>& out_vec_) {
        std::unique_lock<std::mutex> _lock(m_vec_mutex);
        out_vec_.swap(m_package_vec);
    }
private:
    std::mutex m_vec_mutex;
    std::vector<std::shared_ptr<Package>> m_package_vec;

};