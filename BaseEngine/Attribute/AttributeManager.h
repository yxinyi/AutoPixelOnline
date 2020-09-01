#pragma once
#include <unordered_map>
#include <string>
#include <memory>
#include "AttributeDefine.h"
#include "Attribute.h"

class AttributeMager {
public:
    std::weak_ptr<CAttribute> create(const uint64_t oid_, const std::string& obj_str_);

    template<class T>
    bool getAttr(const uint64_t oid_, const std::string& module_name_, const std::string& attr_info_, T& out_) {
        return true;
    }
    template<>
    bool getAttr(const uint64_t oid_, const std::string& module_name_, const std::string& attr_info_, float& out_) {
        auto _attr_find = m_attr_pool.find(oid_);
        if (_attr_find == m_attr_pool.end()) {
            return false;
        }

        

        return true;
    }
private:
    std::unordered_map<uint64_t, std::shared_ptr<CAttribute>> m_attr_pool;
};
