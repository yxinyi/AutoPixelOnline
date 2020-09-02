#pragma once
#include <memory>
#include <string>
#include "tool/SingletonTemplate.h"
#include "google/protobuf/message.h"


class CAttr {
public:
    CAttr(const string& name_) :m_attr_name(name_) {}
    virtual bool LoadForSaveProto(shared_ptr<Message> msg_) {
        if (msg_->GetTypeName() != m_attr_name) {
            return false;
        }
        return decodeSaveData(msg_);
    }
    virtual shared_ptr<CAttr> Clone() = 0;

    virtual shared_ptr<Message> ToSaveProto() = 0;
    string GetName() { return m_attr_name; }
protected:
    virtual bool decodeSaveData(shared_ptr<Message> msg_) = 0;
    string m_attr_name;
};




class CAttrs {
public:
    bool Register(shared_ptr<CAttr> attr_) {
        if (m_attr_pool.find(attr_->GetName()) == m_attr_pool.end()) {
            return false;
        }
        m_attr_pool[attr_->GetName()] = attr_;
        return true;
    }

    template<class T>
    shared_ptr<T> ApiGetAttr(const string& module_name_) {
        auto _attr_find = m_attr_pool.find(module_name_);
        if (_attr_find == m_attr_pool.end()) {
            return nullptr;
        }
        shared_ptr<T> _attr = std::dynamic_pointer_cast<T>(_attr_find->second);
        if (!_attr) {
            return false;
        }

        return _attr;
    }
    shared_ptr<CAttrs> Clone() {
        shared_ptr<CAttrs> _attrs = make_shared<CAttrs>();
        for (auto&& _attr_it : m_attr_pool) {
            _attrs->m_attr_pool[_attr_it.first] = _attr_it.second->Clone();
        }
    }
private:
    std::map<string, shared_ptr<CAttr>> m_attr_pool;
};



using CAttrPrototype = CAttrs;
using CAttrs_t = shared_ptr<CAttrs>;
using CAttrPrototype_t = shared_ptr<CAttrPrototype>;
class CAttrManager :public Singleton<CAttrManager> {
public:
    void Register(const string& obj_name_, shared_ptr<CAttr> attr_) {
        m_prototype_pool[obj_name_]->Register(attr_);
    }
    CAttrs_t CreateAttr(const string& obj_name_) {
        auto _find = m_prototype_pool.find(obj_name_);
        if (_find  == m_prototype_pool.end()) {
            return nullptr;
        }
        return _find->second->Clone();
    }
private:
    std::unordered_map<string, CAttrPrototype_t> m_prototype_pool;
};
