#pragma once
#include <string>
#include <functional>
#include <memory>
#include <mutex>
#include <list>
#include <iostream>
#include <unordered_set>
#include "../tool/SingletonTemplate.h"

using namespace std;
/*
知识点:
1.自定义指针指针销毁
2.可变参数


使用方法,需要使用对象池的对象,必须定义 init()和reset() 函数,其中 init()可以是可变参数.

通过get 函数进行对象池获取时,可以将init的参数进行传入,会进行转发初始化,当不需要时,会自行添加回对象池


example:
class CTestObj {
public:
    CTestObj() {}
    ~CTestObj() {}
    void init(const int member_0_, const int member_1_, const int member_2_) {
        m_member_0 = member_0_;
        m_member_1 = member_1_;
        m_member_2 = member_2_;
    }
    void init(const int member_0_, const int member_1_) {
        m_member_0 = member_0_;
        m_member_1 = member_1_;
    }
    void init(const int member_0_) {
        m_member_0 = member_0_;
    }
    void init() {
    }
    void reset() {
        m_member_0 = 0;
        m_member_1 = 0;
        m_member_2 = 0;
    }

    int m_member_0 = 0;
    int m_member_1 = 0;
    int m_member_2 = 0;
};
void PrintTestObj(const string& name_ ,shared_ptr<CTestObj> test_obj_) {
    std::cout << "################" << std::endl;
    std::cout << name_ << " : " << test_obj_->m_member_0 << std::endl;
    std::cout << name_  << " : " << test_obj_->m_member_1 << std::endl;
    std::cout << name_  << " : " << test_obj_->m_member_2 << std::endl;
}


void CObjectPoolTest() {
    //objcetPool test
    {
        std::vector<shared_ptr<CTestObj>> _obj_vec;
        _obj_vec.resize(50);
        for (size_t _idx = 0; _idx < _obj_vec.size(); _idx++) {
            _obj_vec[_idx] = (CObjectPool<CTestObj>::getInstance()->Get(1));
        }
        CObjectPool<CTestObj>::getInstance()->print();
        CObjectPool<CTestObj>::getInstance()->DestoryIdle();
        CObjectPool<CTestObj>::getInstance()->print();
        //shared_ptr<CTestObj> _test_0 = CObjectPool<CTestObj>::getInstance()->Get();
        //PrintTestObj("test_0", _test_0);
        //shared_ptr<CTestObj> _test_1 = CObjectPool<CTestObj>::getInstance()->Get(1);
        //PrintTestObj("test_1", _test_1);
        //shared_ptr<CTestObj> _test_2 = CObjectPool<CTestObj>::getInstance()->Get(1, 2);
        //PrintTestObj("test_2", _test_2);
        //shared_ptr<CTestObj> _test_3 = CObjectPool<CTestObj>::getInstance()->Get(1, 2, 3);
        //PrintTestObj("test_3", _test_3);
    }
    CObjectPool<CTestObj>::getInstance()->print();
}


*/

static const size_t g_BaseCnt = 100;
template<class T>
class CObjectPool : public Singleton<CObjectPool<T>> {
    friend class Singleton<CObjectPool<T>>;
public:
    template<class... Args>
    shared_ptr<T> Get(Args&&... args_) {
        shared_ptr<T> _tst_ptr;
        bool _need_grow = false;
        {
            std::unique_lock<std::mutex> _lock(m_mutex);
            _tst_ptr = m_object_list.front();
            m_object_list.pop_front();
            if (!m_object_list.size()) {
                _need_grow = true;
            }
        }
        if (_need_grow) {
            const uint32_t _now_cnt = m_obj_total_count;
            for (uint32_t _grow_idx = 0; _grow_idx < _now_cnt; _grow_idx++) {
                buildObjToPool();
            }
        }
        (*_tst_ptr).init(std::forward<Args>(args_)...);
        return _tst_ptr;
    }

    void DestoryIdle() {
        std::unique_lock<std::mutex> _lock(m_mutex);
        for (auto&& _ptr_it : m_object_list) {
            m_delete_set.insert(_ptr_it.get());
        }
        m_object_list.clear();
    }
    void print() {
        std::cout << "m_current_count: " << m_obj_total_count << std::endl;
        std::cout << "m_object_list size: " << m_object_list.size() << std::endl;
    }
private:
    void ObjDestoryCallBack(T* obj_ptr_) {
        if (m_delete_set.find(obj_ptr_) != m_delete_set.end()) {
            m_obj_total_count--;
            delete obj_ptr_;
        }
        else {
            obj_ptr_->reset();
            {
                std::unique_lock<std::mutex> _lock(m_mutex);
                m_object_list.emplace_back(shared_ptr<T>(obj_ptr_, std::bind(&CObjectPool<T>::ObjDestoryCallBack, this, std::placeholders::_1)));
            }
        }
    }
    void buildObjToPool() {
        std::unique_lock<std::mutex> _lock(m_mutex);
        m_obj_total_count++;
        m_object_list.emplace_back(shared_ptr<T>(new T, std::bind(&CObjectPool<T>::ObjDestoryCallBack, this, std::placeholders::_1)));
    }
    
    CObjectPool() {
        for (size_t _init_idx = 0; _init_idx < g_BaseCnt; _init_idx++) {
            buildObjToPool();
        }
    }
    uint32_t m_obj_total_count;

    std::mutex m_mutex;
    std::list<shared_ptr<T>> m_object_list;
    std::unordered_set<T*> m_delete_set;
};