#include "tool/ObjectPool.h"
#include <iostream>
#include <vector>
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

void testMain() {
    CObjectPoolTest();
    system("pause");
}
