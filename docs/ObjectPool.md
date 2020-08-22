## 基于C++11 可变参数构造对象池

#### 概要:

1. 最近写代码时发现需要一个对象池用于减少对象创建与销毁的开销。
2. 理想中对象池接口应尽量精简，逻辑尽量精简，并可以支持不同的初始化构造方式。
3. 阅读<<深入应用C++11 代码优化与工程级应用>>的对象池，其设计思路满足大部分需求，但示例代码略有瑕疵。
4. 在书中的代码基础上进行扩展。

#### 核心逻辑：

对象核心逻辑与大多数逻辑的优化思路是一致的，用空间换时间，通常来说，对象的创建有些部分是无法避免的，特别是在对系统进行内存申请的时候，所以，当幸苦创建的对象在我们不需要的时候返回给了系统，但是在紧接着的一小段时间内，我们又向系统申请一块内存用于创建一个新的对象，特别是当两个对象只不过是属性略微的区别，举例就比如游戏服务器中地图上的怪物被击杀在下一个刷新循环又被创建出来，这种场景下是会造成一定的浪费，所以对象池就是在对象进行销毁时，将即将销毁的对象进行暂存，再下次需要时，再从对象池中拿出，可以认为，两次对象的销毁预创建从系统层的内存申请反还优化成了应用层的赋值与指针移动，这一级别的优化还是很有必要的。

#### 思路：

1. 使用 shared_ptr 自定义析构，来进行对象销毁的自动维护，目的为在不需要使用对象后无需手动调用存入对象池的相关函数。
2. 使用 函数模版中的 变参模版 `template<class... Args>`来满足可能存在不同的构造参数个数。

#### 书中代码的问题：

1. 书中将不同构造方式的对象进行了一个区分，但是不同构造方式进行构造的结果其实是相同的对象，个人薄见，代码应尽量保持精简，特别是相同的对象就不应该由于构造方式的不同而区分存放，即使是不同的构造方式，也应该交由同一个对象池进行管理，只有当不同的对象有这种需求。
2. 书中代码有一个明显的问题，当对象通过智能指针的自定义进行析构的时候，并没有重新制定自定义析构函数，所以当再次被申请，又再次被释放时，对象将会被真正的销毁，不过这点可能是本就这样的设计，但个人来看，既然对象被创建了，那就应该被循环使用，所以个人对此进行修复，真正的一次申请永久使用。
3. 对象池不支持动态扩容，应该是由于该代码是示例代码，所以容量是固定的，当对象不足的时候不支持数量扩展。

#### 以下为代码：

```
#include <string>
#include <functional>
#include <memory>
#include <list>
#include <iostream>
#include <unordered_set>

using namespace std;

const size_t g_BaseCnt = 100;
template<class T>
class CObjectPool {
public:
    template<class... Args>
    shared_ptr<T> Get(Args&&... args_) {
        if (!m_object_list.size()) {
            const uint32_t _now_cnt = m_obj_total_count;
            for (uint32_t _grow_idx = 0; _grow_idx < _now_cnt; _grow_idx++) {
                buildObjToPool();
            }
        }
        shared_ptr<T> _tst_ptr = m_object_list.front();
        m_object_list.pop_front();
        (*_tst_ptr).init(std::forward<Args>(args_)...);
        return _tst_ptr;
    }

    void DestoryIdle() {
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
            m_object_list.emplace_back(shared_ptr<T>(obj_ptr_, std::bind(&CObjectPool<T>::ObjDestoryCallBack, this, std::placeholders::_1)));
        }
    }
    void buildObjToPool() {
        m_obj_total_count++;
        m_object_list.emplace_back(shared_ptr<T>(new T, std::bind(&CObjectPool<T>::ObjDestoryCallBack, this, std::placeholders::_1)));
    }
    
    CObjectPool() {
        for (size_t _init_idx = 0; _init_idx < g_BaseCnt; _init_idx++) {
            buildObjToPool();
        }
    }
    std::unordered_set<T*> m_delete_set;
    uint32_t m_obj_total_count;
    std::list<shared_ptr<T>> m_object_list;
};
```



#### 测试代码：

```
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


int main() {
    {
        std::vector<shared_ptr<CTestObj>> _obj_vec;
        _obj_vec.resize(50);
        for (size_t _idx = 0; _idx < _obj_vec.size(); _idx++) {
            _obj_vec[_idx] = (CObjectPool<CTestObj>::getInstance()->Get(1));
        }
        CObjectPool<CTestObj>::getInstance()->print();
        CObjectPool<CTestObj>::getInstance()->DestoryIdle();
        CObjectPool<CTestObj>::getInstance()->print();
        shared_ptr<CTestObj> _test_0 = CObjectPool<CTestObj>::getInstance()->Get();
        PrintTestObj("test_0", _test_0);
        shared_ptr<CTestObj> _test_1 = CObjectPool<CTestObj>::getInstance()->Get(1);
        PrintTestObj("test_1", _test_1);
        shared_ptr<CTestObj> _test_2 = CObjectPool<CTestObj>::getInstance()->Get(1, 2);
        PrintTestObj("test_2", _test_2);
        shared_ptr<CTestObj> _test_3 = CObjectPool<CTestObj>::getInstance()->Get(1, 2, 3);
        PrintTestObj("test_3", _test_3);
    }
    CObjectPool<CTestObj>::getInstance()->print();
    return 0;
}
```

#### 代码中存在的问题:

1. 可能会造成一定程度上的内存分配，由于没有具体应用到生产环境中，所以其扩容策略是当前总共存在的数量进行翻倍申请，但数量处于一些比较微妙的数值时，可能会进行过量的申请。
2. 对象池的对象必须 有 init() 和 reset()函数，用于对象数据的初始化和清空，可能来说会有一定程度上的侵入，但目前没有具体的需求，本人能力也十分的有限，无法预见到由此带来的问题，只有在以后开发时候遇到对应的不适时，再进行优化。
3. 目前没有针对不同大小的对象进行扩容数量的配置，当对象内存较大与较小的情况时，可能就需要不同的扩容与销毁策略。



