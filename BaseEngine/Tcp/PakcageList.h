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

struct Package {
    string m_topic;
    
};

// thread safe
class CPackageMgr {
public:
    void push(shared_ptr<Package> pack_);
    void swap(std::vector<shared_ptr<Package>>& out_vec_);

private:
    std::vector<shared_ptr<Package>> m_package_vec;

};