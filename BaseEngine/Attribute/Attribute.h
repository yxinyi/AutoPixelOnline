#pragma once
#include <memory>
#include <string>
#include "tool/SingletonTemplate.h"
#include "google/protobuf/message.h"
#include "proto/CreatureNotify.pb.h"


using namespace google::protobuf;

using Message_t = shared_ptr<Message>;
class CAttr {
public:
    CAttr(const string& name_) :m_attr_name(name_) {}
    virtual bool RestoreForProto(Message_t msg_) {
        if (msg_->GetTypeName() != m_attr_name) {
            return false;
        }
        return decodeSaveData(msg_);
    }

    virtual bool RestoreForProto(const std::string& proto_name_, const std::string& msg_) {
        if (proto_name_ != m_attr_name) {
            return false;
        }
        return decodeSaveData(msg_);
    }

    virtual shared_ptr<CAttr> Clone() { return nullptr; };
    virtual Message_t ToDataBaseProto() { return nullptr; };
    virtual Message_t ToClientProto() { return nullptr; };

    virtual std::string ToClientStr() {
        Message_t _msg = ToClientProto();
        if (!_msg) {
            return "";
        }
        return  _msg->SerializeAsString();
    }
    string GetName() { return m_attr_name; }
protected:
    virtual bool decodeSaveData(Message_t msg_) { return false; };
    virtual bool decodeSaveData(const std::string& msg_) { return false; };
    string m_attr_name;
    virtual  ~CAttr() {};
};



using ModuleData_t = shared_ptr<ModuleData>;
using AllAttributeDataNotify_t = shared_ptr<AllAttributeDataNotify>;

class CAttrs {
public:
    bool Register(shared_ptr<CAttr> attr_) {
        if (m_attr_pool.find(attr_->GetName()) != m_attr_pool.end()) {
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
            return nullptr;
        }

        return _attr;
    }
    shared_ptr<CAttrs> Clone() {
        shared_ptr<CAttrs> _attrs = make_shared<CAttrs>();
        for (auto&& _attr_it : m_attr_pool) {
            _attrs->m_attr_pool[_attr_it.first] = _attr_it.second->Clone();
        }
        return _attrs;
    }

    void BuildAllProto(AllAttributeDataNotify_t ntf_) {
        std::vector<ModuleData_t> _rst_vec;
        for (auto&& _it : m_attr_pool) {
            auto _data = ntf_->add_data();
            _data->set_msg_type_str(_it.second->GetName());
            _data->set_binary(_it.second->ToClientStr());
        }
    }

    std::string BuildToProto(const string& module_str_) {
        auto _find = m_attr_pool.find(module_str_);
        if (_find == m_attr_pool.end()) {
            return "";
        }
        return _find->second->ToClientStr();
    }

    void RestoreForProto(const string& str_name_, const string& binary_) {
        auto _find = m_attr_pool.find(str_name_);
        if (_find == m_attr_pool.end()) {
            return;
        }
        _find->second->RestoreForProto(str_name_,binary_);
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
        if (!m_prototype_pool[obj_name_]) {
            CAttrPrototype_t _prototype = make_shared<CAttrPrototype>();
            m_prototype_pool[obj_name_] = _prototype;
        }
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
