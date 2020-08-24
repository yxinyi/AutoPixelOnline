#pragma once
#include "asio.hpp"
#include "../../Common/include/tool/Buffer.h"
#include <mutex>
#include "include/tool/UniqueNumberFactory.h"
#include "include/tool/ObjectPool.h"


/*
    Connection���մ������,�����ɱ���,���н�һ������,��������Ϣ�ַ�

    ����Ƕ�������Ϣ,Ȼ��������¼�����Ϊ string ����, �Ƚ�������,�ٻ�ȡ ������������

    �����protobuf ��Ϣ, �������Ϣ����,Ȼ���������,
    ��Ҫ�̰߳�ȫ
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